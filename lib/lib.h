
#ifndef LIB_H_
#define LIB_H_

#include <stdlib.h>

typedef struct {
    char* name;
    size_t len;
    char* data;
} file;


unsigned char *dumb_ser(file fil);
file de_dumb_ser(unsigned char *ser);
file read_file(char *path);
void print_ordered_bytes(unsigned char* print, size_t len);

#endif

