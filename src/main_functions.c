#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#include <otf2/otf2.h>
#include "barectf-platform-linux-fs.h"
#include "barectf.h" 
#include "main_functions.h"
#include "datatypes.h"
#include "event_callbacks.h"
#include "global_def_callbacks.h"

#define OTF2_CALL(call) if(call != OTF2_SUCCESS) {printf("OTF2 error : %s\n", OTF2_Error_GetDescription(call)); abort();}

//Function that converts a timestamp into nanoseconds given the clock frequency
uint64_t timestamp_to_ns(uint64_t timestamp, uint64_t clock_frequency){
    return (uint64_t)(timestamp * (1000000000./(float)clock_frequency));
}

//Function that copy the metadata file from the converter directory to the given output directory
void copy_metadata_file(char* output_directory){
    const char* converter_directory = getenv("OTF2_CONVERTER");
    if(converter_directory == NULL)
    {
      printf("ERROR : OTF2_CONVERTER environment variable is not set.\n");
      abort();
    }
    char* metadata_name = "/metadata";

    //Constructs the path of the metadata file in the converter directory
    size_t metadata_path_size = strlen(converter_directory) + strlen(metadata_name) + 1;
    char* metadata_path = (char *) malloc(metadata_path_size);
    strcpy(metadata_path, converter_directory);
    strcat(metadata_path, metadata_name);

    //Constructs the output path for the metadata file
    size_t output_path_size = strlen(output_directory) + strlen(metadata_name) + 1;
    char* output_path = (char *) malloc(output_path_size);
    strcpy(output_path, output_directory);
    strcat(output_path, metadata_name);

   //Open the metadata file in reading mode
   FILE *source, *target;
   char ch;
   source = fopen(metadata_path, "r");
   if (source == NULL)
   {
      printf("ERROR : Couldn't find metadata file in converter directory.\n");
      abort();
   }

   //Open the output file in writing mode
   target = fopen(output_path, "w");
   if (target == NULL)
   {
      fclose(source);
      printf("ERROR : Couldn't copy metadata file in output directory.\n");
      abort();
   }

   //Copy the file
   while ((ch = fgetc(source)) != EOF) fputc(ch, target);

   printf("Metadata file copied successfully.\n");
   fclose(source);
   fclose(target);
   free(metadata_path);
   free(output_path);
}

//Callback function that will put locations id into the locations_id structure of the corresponding thread
static OTF2_CallbackCode GlobDefLocation_Register( void* userData,
                          OTF2_LocationRef      location,
                          OTF2_StringRef        name,
                          OTF2_LocationType     locationType,
                          uint64_t              numberOfEvents,
                          OTF2_LocationGroupRef locationGroup )
{
    thread_locations_register_t* thread_locations_register = (thread_locations_register_t*)userData;
    if(thread_locations_register->registered_locations == thread_locations_register->nb_locations)
    {
        return OTF2_CALLBACK_INTERRUPT;
    }

    uint64_t location_idx = thread_locations_register->registered_locations++;
    uint64_t quotient = thread_locations_register->quotient;
    uint64_t rest = thread_locations_register->rest;
    
    uint64_t thread_idx;
    uint64_t location_relative_idx; 

    //Determines for which thread the location will be assigned (to be read) and saves the result into the thread_locations_register structure
    if(location_idx < rest * (quotient +1 )){
      thread_idx = location_idx/(quotient + 1);
      location_relative_idx = location_idx % (quotient +1 );
    }else{
      thread_idx = (location_idx - rest)/quotient;
      location_relative_idx = (location_idx - rest) % quotient;
    }
    thread_locations_register->thread_locations[thread_idx].thread_locations_ids[location_relative_idx] = location;

    return OTF2_CALLBACK_SUCCESS;
}

//Callback function that will put clock properties into the corresponding structure
static OTF2_CallbackCode GlobDefClockProperties_Register( void* userData,
                          uint64_t frequency,
                          uint64_t offset,
                          uint64_t trace_length)
{
    clock_properties_t* clock_properties = (clock_properties_t*)userData;
    clock_properties->frequency = frequency;
    clock_properties->offset = offset;
    clock_properties->trace_length = trace_length;
    clock_properties->filled = 1;
    return OTF2_CALLBACK_SUCCESS;
}

//Function that gets the locations ids and assign them to the threads in order to balance the work charge
thread_locations_t* get_threads_locations_ids(OTF2_Reader* reader, int nb_threads){
    thread_locations_t* thread_locations = (thread_locations_t*)malloc(nb_threads * sizeof(thread_locations_t));
    
    //Gets the number of location and determines how many locations each thread will have to read
    uint64_t nb_locations;
    OTF2_CALL(OTF2_Reader_GetNumberOfLocations(reader, &nb_locations));
    
    uint64_t quotient = nb_locations/nb_threads;
    uint64_t rest = nb_locations%nb_threads;
    for(int i = 0; i < nb_threads; i++){
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
    if(global_def_reader == NULL){
        printf("Error : couldn't get GlobalDefReader\n");
        abort();
    }

    //Set a callback for each location for the global def reader : each location will be assigned to a thread 
    OTF2_GlobalDefReaderCallbacks* global_def_callbacks = OTF2_GlobalDefReaderCallbacks_New();
    OTF2_CALL(OTF2_GlobalDefReaderCallbacks_SetLocationCallback( global_def_callbacks,
                                                       &GlobDefLocation_Register));
    OTF2_CALL(OTF2_Reader_RegisterGlobalDefCallbacks( reader,
                                            global_def_reader,
                                            global_def_callbacks,
                                            thread_locations_register ));
    OTF2_GlobalDefReaderCallbacks_Delete(global_def_callbacks);

    uint64_t definitions_read = 0;
    OTF2_CALL(OTF2_Reader_ReadAllGlobalDefinitions( reader,
                                          global_def_reader,
                                          &definitions_read));

    OTF2_CALL(OTF2_Reader_CloseGlobalDefReader(reader, global_def_reader));
    free(thread_locations_register);
    return thread_locations;
}

//Delete the thread_locations structures
void delete_threads_locations(thread_locations_t* thread_locations, int nb_threads){
    for(int i = 0; i < nb_threads; i++){
        free(thread_locations[i].thread_locations_ids);
    }
    free(thread_locations);
}

//Function that set a callback for the clock properties definition and get the properties into a structure
clock_properties_t* get_clock_properties(OTF2_Reader* reader){
    clock_properties_t* clock_properties = (clock_properties_t*)malloc(sizeof(clock_properties_t));
    clock_properties->filled = 0;
        OTF2_GlobalDefReader* global_def_reader = OTF2_Reader_GetGlobalDefReader(reader);
    if(global_def_reader == NULL){
        printf("Error : couldn't get GlobalDefReader\n");
        abort();
    }
    OTF2_GlobalDefReaderCallbacks* global_def_callbacks = OTF2_GlobalDefReaderCallbacks_New();
    OTF2_CALL(OTF2_GlobalDefReaderCallbacks_SetClockPropertiesCallback( global_def_callbacks,
                                                       &GlobDefClockProperties_Register));
    OTF2_CALL(OTF2_Reader_RegisterGlobalDefCallbacks( reader,
                                            global_def_reader,
                                            global_def_callbacks,
                                            clock_properties ));
    OTF2_GlobalDefReaderCallbacks_Delete( global_def_callbacks);

    uint64_t definitions_read = 0;
    OTF2_CALL(OTF2_Reader_ReadAllGlobalDefinitions( reader,
                                          global_def_reader,
                                          &definitions_read));
    OTF2_CALL(OTF2_Reader_CloseGlobalDefReader(reader, global_def_reader));
    return clock_properties;
}

//Delete the clock properties structure
void delete_clock_properties(clock_properties_t* clock_properties){
    free(clock_properties);
}

//Function that opens a CTF stream for each location file, sets and registers the event callbacks in the corresponding event reader then reads all the events 
void* convert_events(void* data_wrapper){
    pthread_data_t* pthread_data = (pthread_data_t*)data_wrapper;

    OTF2_Reader* reader = pthread_data->reader;
    char* output_directory = pthread_data->output_directory;
    uint64_t clock_frequency = pthread_data->clock_frequency;
    uint64_t nb_locations = pthread_data->thread_locations->nb_thread_locations;
    uint64_t* locations_ids = pthread_data->thread_locations-> thread_locations_ids;
    
    OTF2_EvtReaderCallbacks* event_callbacks = OTF2_EvtReaderCallbacks_New();

    set_events_callbacks(event_callbacks);

    for(uint64_t i = 0; i<nb_locations; i++){
        size_t fullSize;
        char location_id_str[20]= "";
        sprintf(location_id_str, "/%lu", locations_ids[i]);
        fullSize = strlen( location_id_str ) + strlen( output_directory ) + 1;
    
        char* stream_path = (char *) malloc( fullSize );
        strcpy( stream_path, output_directory );
        strcat( stream_path, location_id_str );       
        
        uint64_t clock = 0;
        struct barectf_platform_linux_fs_ctx* platform_ctx = barectf_platform_linux_fs_init(2000, stream_path, 0, 0, 0, &clock);
        struct barectf_default_ctx* ctx = barectf_platform_linux_fs_get_barectf_ctx(platform_ctx);        

        OTF2_EvtReader* evt_reader = OTF2_Reader_GetEvtReader(reader, locations_ids[i]);
        OTF2_CALL(OTF2_EvtReader_ApplyClockOffsets(evt_reader, true));
        OTF2_CALL(OTF2_EvtReader_ApplyMappingTables(evt_reader, true));	
        user_data_t* user_data = (user_data_t*)malloc(sizeof(user_data_t));
        user_data->ctx = ctx;
        user_data->clock_address = &clock;
        user_data->clock_frequency = clock_frequency;
        OTF2_CALL(OTF2_Reader_RegisterEvtCallbacks(reader,
                                            evt_reader,
                                            event_callbacks,
                                            user_data));
        uint64_t events_read = 1;
        while(events_read){
            OTF2_CALL(OTF2_EvtReader_ReadEvents(evt_reader, 1, &events_read));
        }
        OTF2_CALL(OTF2_Reader_CloseEvtReader(reader, evt_reader)); 
        barectf_platform_linux_fs_fini(platform_ctx);
        free(user_data);
        free(stream_path);
    }
  
    OTF2_EvtReaderCallbacks_Delete(event_callbacks);   
    return NULL;                                                                                                     
}

//Function that creates the thread who will create CTF stream, read and write the events read in the corresponding locations 
void start_threads(OTF2_Reader* reader, 
                    char* output_directory, 
                    uint64_t nb_threads,
                    thread_locations_t* thread_locations,
                    clock_properties_t* clock_properties)
{ 
    pthread_data_t* pthread_data =(pthread_data_t*)malloc(nb_threads * sizeof(pthread_data_t));
    pthread_t* pids = (pthread_t*)malloc(nb_threads * sizeof(pthread_t));
    for(uint64_t i = 0; i < nb_threads; i++){
        pthread_data[i].reader = reader;
        pthread_data[i].output_directory = output_directory;
        pthread_data[i].clock_frequency = clock_properties->frequency;
        pthread_data[i].thread_locations = &(thread_locations[i]);
        pthread_create(&pids[i], NULL, convert_events, &(pthread_data[i]));
    }
    for(uint64_t i = 0; i < nb_threads; i++){
        pthread_join(pids[i], NULL);
    }
    free(pthread_data);
    free(pids);
}

//Function that creates a stream for the global definitions, set the associated callbacks and read all the definitions. The callbacks will write a CTF event 
//for each definition at the global offset timestamp
void convert_global_definitions(OTF2_Reader* reader, char* output_directory, clock_properties_t* clock_properties){
    size_t fullSize;
    char* stream_name = "/global_def";
    fullSize = strlen(stream_name) + strlen(output_directory) + 1;
    char* stream_path = (char *) malloc( fullSize );
    strcpy( stream_path, output_directory);
    strcat( stream_path, stream_name);      
    
    uint64_t clock = timestamp_to_ns(clock_properties->offset, clock_properties->frequency);
    struct barectf_platform_linux_fs_ctx* platform_ctx = barectf_platform_linux_fs_init(2000, stream_path, 0, 0, 0, &clock);
    struct barectf_default_ctx* ctx = barectf_platform_linux_fs_get_barectf_ctx(platform_ctx);    
    
    user_data_t* user_data = (user_data_t*)malloc(sizeof(user_data_t));
    user_data->ctx = ctx;
    user_data->clock_address = &clock;    

    OTF2_GlobalDefReader* global_def_reader = OTF2_Reader_GetGlobalDefReader(reader);
    OTF2_GlobalDefReaderCallbacks* global_def_callbacks = OTF2_GlobalDefReaderCallbacks_New();

    set_global_def_callbacks(global_def_callbacks);

    OTF2_CALL(OTF2_Reader_RegisterGlobalDefCallbacks(reader,
                                                    global_def_reader,
                                                    global_def_callbacks,
                                                    user_data));

    OTF2_GlobalDefReaderCallbacks_Delete(global_def_callbacks);

    uint64_t definitions_read = 0;
    OTF2_CALL(OTF2_Reader_ReadAllGlobalDefinitions(reader,
                                                global_def_reader,
                                                &definitions_read));
    OTF2_CALL(OTF2_Reader_CloseGlobalDefReader(reader, global_def_reader));
        
    barectf_platform_linux_fs_fini(platform_ctx);
    free(user_data);
    free(stream_path);
}

