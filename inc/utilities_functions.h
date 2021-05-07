/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Yoann Heitz
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <otf2/otf2.h>

typedef struct{
    struct barectf_default_ctx *ctx;
    uint64_t clock_frequency;
    uint64_t *clock_address;
} user_data_t;

typedef struct {
    uint64_t nb_thread_locations;
    uint64_t *thread_locations_ids;
} thread_locations_t;

typedef struct {
    uint64_t registered_locations;
    uint64_t nb_locations;
    uint64_t quotient;
    uint64_t rest;
    thread_locations_t *thread_locations;
} thread_locations_register_t;

typedef struct {
    uint32_t filled;
    uint32_t first_offset_defined;
    uint64_t frequency;
    uint64_t offset;
    uint64_t trace_length;
} clock_properties_t;

typedef struct {
    OTF2_Reader *reader;
    char *output_directory;
    uint64_t clock_frequency;
    thread_locations_t *thread_locations;
} pthread_data_t;

void OTF2_Call(OTF2_ErrorCode code);
void * open_output_directory(char *output_path);
uint64_t get_thread_number(OTF2_Reader *reader, int64_t njobs);
void copy_metadata_file(char *output_directory, uint64_t clock_frequency);
void get_real_offset(OTF2_Reader *reader, clock_properties_t *clock_properties, thread_locations_t *thread_locations, uint64_t nb_threads);
thread_locations_t * get_threads_locations_ids(OTF2_Reader *reader, int nb_threads);
clock_properties_t * get_clock_properties(OTF2_Reader* reader);
void convert_global_definitions(OTF2_Reader *reader, char* output_directory, clock_properties_t *clock_properties);
void start_threads(OTF2_Reader *reader, char *output_directory, uint64_t nb_threads, thread_locations_t *thread_locations, clock_properties_t *clock_properties);
void delete_threads_locations(thread_locations_t *thread_locations, int nb_threads);
void delete_clock_properties(clock_properties_t *clock_properties);
