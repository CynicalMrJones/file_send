
#ifndef LIB_H_
#define LIB_H_

#include <stdlib.h>

typedef struct {
    char* name;
    size_t len;
    char* data;
} file;


file read_file(char *path);

#endif

