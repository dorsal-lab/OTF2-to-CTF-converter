#include <stdint.h>
#include <otf2/otf2.h>
#include "barectf-platform-linux-fs.h"
#include "barectf.h" 

typedef struct{
    struct barectf_default_ctx* ctx;
    uint64_t clock_frequency;
    uint64_t* clock_address;
} user_data_t;