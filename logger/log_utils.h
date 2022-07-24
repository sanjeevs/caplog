#pragma once

#include <stdint.h>
#include <fcntl.h>
#include <cstdio>

// C style utility to manipulate the log file.
//


extern int write_file(const char* path, const void* data, size_t size, 
                      int flags = O_WRONLY, mode_t mode = 0664);

extern FILE* safe_fopen(const char* filename, const char* mode);

extern size_t safe_fwrite(const void * ptr, size_t size, size_t count, 
                          FILE * stream);

extern int safe_fflush(FILE *stream);





