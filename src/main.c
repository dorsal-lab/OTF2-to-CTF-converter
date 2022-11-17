/******************************************************
 * Copyright (c) 2021 Ecole Polytechnique de Montreal
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. 
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <otf2/otf2.h>
#include "utilities_functions.h"

#define DEFAULT_CLOCK_FREQUENCY 1000000000
#define DEFAULT_OFFSET 0

int main (int argc, char **argv)
{
    int arg_name = 0;  
    int64_t njobs = -1;
    char output_directory[2000] = "";

    while(arg_name != -1){
        static struct option long_options[] ={
            {"njobs", required_argument, 0, 'n'},
            {"output", required_argument, 0, 'o'},
        };
        int option_index = 0;
        arg_name = getopt_long (argc, argv, "n:o:", long_options, &option_index);

        switch (arg_name){
            case 'n':
                njobs = atoi(optarg);
                break;
            case 'o':
                strcat(output_directory, optarg);
                break;
            case -1:
                break;
            default:
                abort ();
        }
    }

    const char *input_trace = argv[argc - 1];
    OTF2_Reader *reader = OTF2_Reader_Open(input_trace);
    if(reader == NULL){
        printf("ERROR : Can't open OTF2 trace\n");
        abort();
    } 	

    open_output_directory(output_directory);
    uint64_t nb_threads = get_thread_number(reader, njobs);


    printf("Trace to convert : %s \n", input_trace);
    printf("Output directory : %s \n", output_directory);
    printf("Number of threads that will be used : %lu\n", nb_threads);


    thread_locations_t *thread_locations = get_threads_locations_ids(reader, nb_threads);
    clock_properties_t *clock_properties = get_clock_properties(reader);

    if(!clock_properties->filled){
        clock_properties->frequency = DEFAULT_CLOCK_FREQUENCY;
        clock_properties->offset = DEFAULT_OFFSET;
    }
    get_real_offset(reader, clock_properties, thread_locations, nb_threads);
    copy_metadata_file(output_directory, clock_properties->frequency);
    convert_global_definitions(reader, output_directory, clock_properties);
    start_threads(reader, output_directory, nb_threads, thread_locations, clock_properties);
    delete_clock_properties(clock_properties);
    delete_threads_locations(thread_locations, nb_threads);
    exit(0);
}
