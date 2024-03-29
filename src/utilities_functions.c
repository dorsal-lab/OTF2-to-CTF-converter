/******************************************************
 * Copyright (c) 2021 Ecole Polytechnique de Montreal
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 ******************************************************/

#define _POSIX_C_SOURCE 199309L

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "barectf-platform-linux-fs.h"
#include "barectf.h"
#include "event_callbacks.h"
#include "global_def_callbacks.h"
#include "utilities_functions.h"
#include <otf2/otf2.h>

#define ITERATIONS_NUMBER 50
#define BUFFER_SIZE 1000
#define CLOCK_FREQUENCY_LINE_NUMBER 69
#define OFFSET_S_LINE_NUMBER 71
#define OFFSET_LINE_NUMBER 72

// Error code checking for OTF2 API calls
void OTF2_Call(OTF2_ErrorCode code)
{
    if (code != OTF2_SUCCESS) {
        printf("OTF2 error : %s\n", OTF2_Error_GetDescription(code));
        abort();
    }
}

struct stat st = { 0 };
// Creates the output directory with the given name or a name created with pid and time
void* open_output_directory(char* output_path)
{
    if (output_path[0] == '\0') {
        strcat(output_path, "./converted_otf2_");

        char pid_buffer[10] = "";
        sprintf(pid_buffer, "%d_", getpid());
        strcat(output_path, pid_buffer);

        char time_buffer[20];
        sprintf(time_buffer, "%ld", time(NULL));
        strcat(output_path, time_buffer);
    }

    if (stat(output_path, &st) != -1) {
        printf("ERROR : Directory %s already exists.\n", output_path);
        abort();
    }
    mkdir(output_path, 0777);
}

// Determines the optimal number of threads or use the one that was given if valid
uint64_t get_thread_number(OTF2_Reader* reader, int64_t njobs)
{
    uint64_t number_of_locations;
    int nprocs = get_nprocs();
    OTF2_Call(OTF2_Reader_GetNumberOfLocations(reader, &number_of_locations));
    if (njobs != -1) {
        if (nprocs > njobs && njobs > 0) {
            nprocs = njobs;
        }
    }
    if (nprocs > number_of_locations) {
        return number_of_locations;
    }
    return nprocs;
}

// Function that computes the time as a long from a timespec structure
long compute_time(struct timespec timespec_struct)
{
    return 1000000000 * (long)timespec_struct.tv_sec + timespec_struct.tv_nsec;
}

// Function that calculates the offsets (seconds and nanoseconds) to the Epoch
void calculate_offsets(long* offset_s, long* offset_ns)
{
    long min_delta = LONG_MAX;
    long current_delta, time_realtime, time_monotonic0, time_monotonic1, offset, time_monotonic_average;
    struct timespec time_monotonic0_ts, time_monotonic1_ts, time_realtime_ts;

    for (int step = 0; step < ITERATIONS_NUMBER; step++) {

        clock_gettime(CLOCK_MONOTONIC, &time_monotonic0_ts);
        clock_gettime(CLOCK_REALTIME, &time_realtime_ts);
        clock_gettime(CLOCK_MONOTONIC, &time_monotonic1_ts);

        time_realtime = compute_time(time_realtime_ts);
        time_monotonic0 = compute_time(time_monotonic0_ts);
        time_monotonic1 = compute_time(time_monotonic1_ts);
        current_delta = time_monotonic1 - time_monotonic0;
        if (current_delta < min_delta) {
            min_delta = current_delta;
            time_monotonic_average = (time_monotonic1 + time_monotonic0) / 2;
            offset = time_realtime - time_monotonic_average;
            *offset_s = offset / 1000000000;
            *offset_ns = offset % 1000000000;
        }
    }
}

// Function that copy the metadata file from the converter directory to the given output directory
void copy_metadata_file(char* output_directory, uint64_t clock_frequency)
{
    const char* converter_directory = getenv("OTF2_CONVERTER");
    if (converter_directory == NULL) {
        printf("ERROR : OTF2_CONVERTER environment variable is not set.\n");
        abort();
    }
    char metadata_name[] = "/metadata";

    // Constructs the path of the metadata file in the converter directory
    size_t metadata_path_size = strlen(converter_directory) + strlen(metadata_name) + 1;
    char* metadata_path = (char*)malloc(metadata_path_size * sizeof(char));
    strncpy(metadata_path, converter_directory, metadata_path_size);
    strncat(metadata_path, metadata_name, metadata_path_size);

    // Constructs the output path for the metadata file
    size_t output_path_size = strlen(output_directory) + strlen(metadata_name) + 1;
    char* output_path = (char*)malloc(output_path_size * sizeof(char));
    strncpy(output_path, output_directory, output_path_size);
    strncat(output_path, metadata_name, output_path_size);

    // Open the metadata file in reading mode
    FILE *source, *target;
    char ch;
    source = fopen(metadata_path, "r");
    if (source == NULL) {
        printf("ERROR : Couldn't find metadata file in converter directory.\n");
        abort();
    }

    // Open the output file in writing mode
    target = fopen(output_path, "w");
    if (target == NULL) {
        fclose(source);
        printf("ERROR : Couldn't copy metadata file in output directory.\n");
        abort();
    }

    // Copy the file line by line. Change trace name line and clock frequency line
    char buffer[BUFFER_SIZE];

    char clock_frequency_line[BUFFER_SIZE] = "";

    long offset_s, offset_ns;
    calculate_offsets(&offset_s, &offset_ns);

    char offset_s_line[BUFFER_SIZE] = "";
    char offset_line[BUFFER_SIZE] = "";

    sprintf(clock_frequency_line, "\tfreq = %lu;\n", clock_frequency);
    sprintf(offset_s_line, "\toffset_s = %ld;\n", offset_s);
    sprintf(offset_line, "\toffset = %ld;\n", offset_ns);

    int count = 0;
    while ((fgets(buffer, BUFFER_SIZE, source)) != NULL) {
        switch (count) {
        case CLOCK_FREQUENCY_LINE_NUMBER:
            fputs(clock_frequency_line, target);
            break;
        case OFFSET_S_LINE_NUMBER:
            fputs(offset_s_line, target);
            break;
        case OFFSET_LINE_NUMBER:
            fputs(offset_line, target);
            break;
        default:
            fputs(buffer, target);
            break;
        }
        count++;
    }

    printf("Metadata file copied successfully.\n");
    fclose(source);
    fclose(target);
    free(metadata_path);
    free(output_path);
}

// Callback function that will put locations id into the locations_id structure of the corresponding thread
static OTF2_CallbackCode GlobDefLocation_Register(void* userData,
    OTF2_LocationRef location,
    OTF2_StringRef name,
    OTF2_LocationType locationType,
    uint64_t numberOfEvents,
    OTF2_LocationGroupRef locationGroup)
{
    thread_locations_register_t* thread_locations_register = (thread_locations_register_t*)userData;
    if (thread_locations_register->registered_locations == thread_locations_register->nb_locations) {
        return OTF2_CALLBACK_INTERRUPT;
    }

    uint64_t location_idx = thread_locations_register->registered_locations++;
    uint64_t quotient = thread_locations_register->quotient;
    uint64_t rest = thread_locations_register->rest;

    uint64_t thread_idx;
    uint64_t location_relative_idx;

    // Determines for which thread the location will be assigned (to be read) and saves the result into the thread_locations_register structure
    if (location_idx < rest * (quotient + 1)) {
        thread_idx = location_idx / (quotient + 1);
        location_relative_idx = location_idx % (quotient + 1);
    } else {
        thread_idx = (location_idx - rest) / quotient;
        location_relative_idx = (location_idx - rest) % quotient;
    }
    thread_locations_register->thread_locations[thread_idx].thread_locations_ids[location_relative_idx] = location;

    return OTF2_CALLBACK_SUCCESS;
}

// Callback function that will put clock properties into the corresponding structure
static OTF2_CallbackCode GlobDefClockProperties_Register(void* userData,
    uint64_t frequency,
    uint64_t offset,
    uint64_t trace_length)
{
    clock_properties_t* clock_properties = (clock_properties_t*)userData;
    clock_properties->frequency = frequency;
    clock_properties->offset = offset;
    clock_properties->trace_length = trace_length;
    clock_properties->filled = 1;
    clock_properties->first_offset_defined = 1;
    return OTF2_CALLBACK_SUCCESS;
}

// Function that gets the locations ids and assign them to the threads in order to balance the work charge
thread_locations_t* get_threads_locations_ids(OTF2_Reader* reader, int nb_threads)
{
    thread_locations_t* thread_locations = (thread_locations_t*)malloc(nb_threads * sizeof(thread_locations_t));

    // Gets the number of location and determines how many locations each thread will have to read
    uint64_t nb_locations;
    OTF2_Call(OTF2_Reader_GetNumberOfLocations(reader, &nb_locations));

    uint64_t quotient = nb_locations / nb_threads;
    uint64_t rest = nb_locations % nb_threads;
    for (int i = 0; i < nb_threads; i++) {
        thread_locations[i].nb_thread_locations = i < rest ? quotient + 1 : quotient;
        thread_locations[i].thread_locations_ids = (uint64_t*)malloc(thread_locations[i].nb_thread_locations * sizeof(uint64_t));
    }

    thread_locations_register_t* thread_locations_register = (thread_locations_register_t*)malloc(sizeof(thread_locations_register_t));
    thread_locations_register->registered_locations = 0;
    thread_locations_register->nb_locations = nb_locations;
    thread_locations_register->quotient = quotient;
    thread_locations_register->rest = rest;
    thread_locations_register->thread_locations = thread_locations;

    OTF2_GlobalDefReader* global_def_reader = OTF2_Reader_GetGlobalDefReader(reader);
    if (global_def_reader == NULL) {
        printf("Error : couldn't get GlobalDefReader\n");
        abort();
    }

    // Set a callback for each location for the global def reader : each location will be assigned to a thread
    OTF2_GlobalDefReaderCallbacks* global_def_callbacks = OTF2_GlobalDefReaderCallbacks_New();
    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetLocationCallback(global_def_callbacks,
        &GlobDefLocation_Register));
    OTF2_Call(OTF2_Reader_RegisterGlobalDefCallbacks(reader,
        global_def_reader,
        global_def_callbacks,
        thread_locations_register));
    OTF2_GlobalDefReaderCallbacks_Delete(global_def_callbacks);

    uint64_t definitions_read = 0;
    OTF2_Call(OTF2_Reader_ReadAllGlobalDefinitions(reader,
        global_def_reader,
        &definitions_read));

    OTF2_Call(OTF2_Reader_CloseGlobalDefReader(reader, global_def_reader));
    free(thread_locations_register);
    return thread_locations;
}

// Delete the thread_locations structures
void delete_threads_locations(thread_locations_t* thread_locations, int nb_threads)
{
    for (int i = 0; i < nb_threads; i++) {
        free(thread_locations[i].thread_locations_ids);
    }
    free(thread_locations);
}

// Function that set a callback for the clock properties definition and get the properties into a structure
clock_properties_t* get_clock_properties(OTF2_Reader* reader)
{
    clock_properties_t* clock_properties = (clock_properties_t*)malloc(sizeof(clock_properties_t));
    clock_properties->filled = 0;
    clock_properties->first_offset_defined = 0;
    OTF2_GlobalDefReader* global_def_reader = OTF2_Reader_GetGlobalDefReader(reader);
    if (global_def_reader == NULL) {
        printf("Error : couldn't get GlobalDefReader\n");
        abort();
    }
    OTF2_GlobalDefReaderCallbacks* global_def_callbacks = OTF2_GlobalDefReaderCallbacks_New();
    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetClockPropertiesCallback(global_def_callbacks,
        &GlobDefClockProperties_Register));
    OTF2_Call(OTF2_Reader_RegisterGlobalDefCallbacks(reader,
        global_def_reader,
        global_def_callbacks,
        clock_properties));
    OTF2_GlobalDefReaderCallbacks_Delete(global_def_callbacks);

    uint64_t definitions_read = 0;
    OTF2_Call(OTF2_Reader_ReadAllGlobalDefinitions(reader,
        global_def_reader,
        &definitions_read));
    OTF2_Call(OTF2_Reader_CloseGlobalDefReader(reader, global_def_reader));
    return clock_properties;
}

// Delete the clock properties structure
void delete_clock_properties(clock_properties_t* clock_properties)
{
    free(clock_properties);
}

// Callback that register the timestamp of a program begin event as the first timestamp of the trace if it is
// lower than the current offset
static OTF2_CallbackCode ProgramBeginEvent_Register(OTF2_LocationRef location,
    OTF2_TimeStamp time,
    uint64_t eventPosition,
    void* userData,
    OTF2_AttributeList* attributeList,
    OTF2_StringRef programName,
    uint32_t numberOfArguments,
    const OTF2_StringRef* programArguments)
{
    clock_properties_t* clock_properties = (clock_properties_t*)userData;
    if (clock_properties->first_offset_defined == 0) {
        clock_properties->offset == time;
        clock_properties->first_offset_defined = 1;
        return OTF2_CALLBACK_SUCCESS;
    }
    clock_properties->offset = (time < clock_properties->offset) ? time : clock_properties->offset;
    return OTF2_CALLBACK_SUCCESS;
}

// Function that reads every location and search for PROGRAM BEGIN event in order to find the first timestamp for all events
void get_real_offset(OTF2_Reader* reader, clock_properties_t* clock_properties, thread_locations_t* thread_locations, uint64_t nb_threads)
{
    OTF2_EvtReaderCallbacks* event_callbacks = OTF2_EvtReaderCallbacks_New();
    OTF2_Call(OTF2_EvtReaderCallbacks_SetProgramBeginCallback(event_callbacks,
        &ProgramBeginEvent_Register));
    for (uint64_t i = 0; i < nb_threads; i++) {
        for (uint64_t j = 0; j < thread_locations[i].nb_thread_locations; j++) {
            OTF2_EvtReader* evt_reader = OTF2_Reader_GetEvtReader(reader, thread_locations[i].thread_locations_ids[j]);
            OTF2_Call(OTF2_EvtReader_ApplyClockOffsets(evt_reader, true));
            OTF2_Call(OTF2_EvtReader_ApplyMappingTables(evt_reader, 1));
            OTF2_Call(OTF2_Reader_RegisterEvtCallbacks(reader,
                evt_reader,
                event_callbacks,
                clock_properties));
            uint64_t events_read = 1;
            OTF2_Call(OTF2_EvtReader_ReadEvents(evt_reader, 1, &events_read));
            OTF2_Call(OTF2_Reader_CloseEvtReader(reader, evt_reader));
        }
    }
    OTF2_EvtReaderCallbacks_Delete(event_callbacks);
}

// Function that opens a CTF stream for each location file, sets and registers the event callbacks in the corresponding event reader then reads all the events
void* convert_events(void* data_wrapper)
{
    pthread_data_t* pthread_data = (pthread_data_t*)data_wrapper;

    OTF2_Reader* reader = pthread_data->reader;
    char* output_directory = pthread_data->output_directory;
    uint64_t clock_frequency = pthread_data->clock_frequency;
    uint64_t nb_locations = pthread_data->thread_locations->nb_thread_locations;
    uint64_t* locations_ids = pthread_data->thread_locations->thread_locations_ids;

    OTF2_EvtReaderCallbacks* event_callbacks = OTF2_EvtReaderCallbacks_New();

    set_events_callbacks(event_callbacks);

    for (uint64_t i = 0; i < nb_locations; i++) {
        size_t stream_path_size;
        char location_id_str[20] = "";
        sprintf(location_id_str, "/%lu", locations_ids[i]);
        stream_path_size = strlen(location_id_str) + strlen(output_directory) + 1;

        char* stream_path = (char*)malloc(stream_path_size);
        strncpy(stream_path, output_directory, stream_path_size);
        strncat(stream_path, location_id_str, stream_path_size);

        uint64_t clock = 0;
        struct barectf_platform_linux_fs_ctx* platform_ctx = barectf_platform_linux_fs_init(4000, stream_path, 0, 0, 0, &clock);
        struct barectf_default_ctx* ctx = barectf_platform_linux_fs_get_barectf_ctx(platform_ctx);

        OTF2_DefReader* def_reader = OTF2_Reader_GetDefReader(reader, locations_ids[i]);
        if (def_reader) {
            uint64_t def_reads = 0;
            OTF2_Reader_ReadAllLocalDefinitions(reader,
                def_reader,
                &def_reads);
            OTF2_Reader_CloseDefReader(reader, def_reader);
        }

        OTF2_EvtReader* evt_reader = OTF2_Reader_GetEvtReader(reader, locations_ids[i]);
        user_data_t* user_data = (user_data_t*)malloc(sizeof(user_data_t));
        user_data->ctx = ctx;
        user_data->clock_address = &clock;
        user_data->clock_frequency = clock_frequency;
        OTF2_Call(OTF2_Reader_RegisterEvtCallbacks(reader,
            evt_reader,
            event_callbacks,
            user_data));
        OTF2_Call(OTF2_EvtReader_ApplyClockOffsets(evt_reader, 1));
        OTF2_Call(OTF2_EvtReader_ApplyMappingTables(evt_reader, 1));
        uint64_t events_read = 1;
        while (events_read != 0) {
            OTF2_Call(OTF2_EvtReader_ReadEvents(evt_reader, 1, &events_read));
        }
        OTF2_Call(OTF2_Reader_CloseEvtReader(reader, evt_reader));
        barectf_platform_linux_fs_fini(platform_ctx);
        free(user_data);
        free(stream_path);
    }
    OTF2_EvtReaderCallbacks_Delete(event_callbacks);
    return NULL;
}

// Function that creates the thread who will create CTF stream, read and write the events read in the corresponding locations
void start_threads(OTF2_Reader* reader,
    char* output_directory,
    uint64_t nb_threads,
    thread_locations_t* thread_locations,
    clock_properties_t* clock_properties)
{
    pthread_data_t* pthread_data = (pthread_data_t*)malloc(nb_threads * sizeof(pthread_data_t));
    pthread_t* pids = (pthread_t*)malloc(nb_threads * sizeof(pthread_t));
    for (uint64_t i = 0; i < nb_threads; i++) {
        pthread_data[i].reader = reader;
        pthread_data[i].output_directory = output_directory;
        pthread_data[i].clock_frequency = clock_properties->frequency;
        pthread_data[i].thread_locations = &(thread_locations[i]);
        pthread_create(&pids[i], NULL, convert_events, &(pthread_data[i]));
    }
    for (uint64_t i = 0; i < nb_threads; i++) {
        pthread_join(pids[i], NULL);
    }
    free(pthread_data);
    free(pids);
}

// Function that creates a stream for the global definitions, set the associated callbacks and read all the definitions. The callbacks will write a CTF event
// for each definition at the global offset timestamp
void convert_global_definitions(OTF2_Reader* reader, char* output_directory, clock_properties_t* clock_properties)
{
    size_t stream_path_size;
    char stream_name[] = "/global_def";
    stream_path_size = strlen(stream_name) + strlen(output_directory) + 1;
    char* stream_path = (char*)malloc(stream_path_size * sizeof(char));
    strcpy(stream_path, output_directory);
    strcat(stream_path, stream_name);

    uint64_t clock = clock_properties->offset - 1 >= 0 ? clock_properties->offset - 1 : 0;
    struct barectf_platform_linux_fs_ctx* platform_ctx = barectf_platform_linux_fs_init(10000, stream_path, 0, 0, 0, &clock);
    struct barectf_default_ctx* ctx = barectf_platform_linux_fs_get_barectf_ctx(platform_ctx);

    user_data_t* user_data = (user_data_t*)malloc(sizeof(user_data_t));
    user_data->ctx = ctx;
    user_data->clock_address = &clock;

    OTF2_GlobalDefReader* global_def_reader = OTF2_Reader_GetGlobalDefReader(reader);
    OTF2_GlobalDefReaderCallbacks* global_def_callbacks = OTF2_GlobalDefReaderCallbacks_New();

    set_global_def_callbacks(global_def_callbacks);

    OTF2_Call(OTF2_Reader_RegisterGlobalDefCallbacks(reader,
        global_def_reader,
        global_def_callbacks,
        user_data));

    OTF2_GlobalDefReaderCallbacks_Delete(global_def_callbacks);

    uint64_t definitions_read = 0;
    OTF2_Call(OTF2_Reader_ReadAllGlobalDefinitions(reader,
        global_def_reader,
        &definitions_read));
    OTF2_Call(OTF2_Reader_CloseGlobalDefReader(reader, global_def_reader));

    barectf_platform_linux_fs_fini(platform_ctx);
    free(user_data);
    free(stream_path);
}
