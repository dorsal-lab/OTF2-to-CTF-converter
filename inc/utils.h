#include <stdint.h>
#include <otf2/otf2.h>

uint64_t get_thread_number(OTF2_Reader* reader, int64_t njobs);
void* open_output_directory(char* output_path);