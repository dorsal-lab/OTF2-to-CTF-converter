#include <otf2/otf2.h>
#include <stdio.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define OTF2_CALL(call) if(call != OTF2_SUCCESS) {printf("OTF2 error : %s\n", OTF2_Error_GetDescription(call)); abort();}

struct stat st = {0};
//Creates the output directory with the given name or a name created with pid and time 
void* open_output_directory(char* output_path){
    if(output_path[0] == '\0'){
        strcat(output_path, "./converted_otf2_");
        
        char pid_buffer[10] ="";
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
    mkdir(output_path, 0700);    
}

//Determines the optimal number of threads or use the one that was given if valid
uint64_t get_thread_number(OTF2_Reader* reader, int64_t njobs){
    uint64_t number_of_locations;
    int nprocs = get_nprocs();
    OTF2_CALL(OTF2_Reader_GetNumberOfLocations(reader, &number_of_locations));
    if(njobs != -1){
        if(nprocs > njobs && njobs > 0){
            nprocs = njobs;
        }
    }
    if(nprocs > number_of_locations){
        return number_of_locations;
    }
    return nprocs;
}