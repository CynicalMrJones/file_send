
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Dumb Serializer
// I have no idea what i am doing
// Im gonna try this and if it works im cool:
// The idea  is to return a pointer that contains all the data of a file
// Thought process:
// First 8 bytes is the size of the whole package
// Bytes 9-18 (10) bytes are for file name (picked randomly)
// Bytes 19-26 (8) will be the length of the file
// Bytes 27-EOF will be the data in the file
// Wish me luck
unsigned char *dumb_ser(file fil){
    //Deconstruct the file into its parts
    char *name = fil.name;
    size_t len = fil.len;
    char *data= fil.data;

    //create a buffer that is the size of the full stucture with padding
    size_t size = 8 + 10 + 8 + len;
    unsigned char *buff = calloc(size, sizeof(unsigned char));

    //inject data properly into buffer
    memcpy(buff, &size, sizeof(size));
    memcpy(buff + 8, name, strlen(name));
    memcpy(buff + 18, &len, sizeof(len));
    memcpy(buff + 26, data, len);

    return buff;
}

/*
 * Dumb Deserializer
 * Since it worked so well the last time lest do it again
 * First 10 bytes are for the filename (picked randomly)
 * Bytes 11-18 (8) will be the length of the file
 * Bytes 19-EOF will be the data in the file
 */
file de_dumb_ser(unsigned char *ser){
    //Break the data into name
    char *name = malloc(10 * sizeof(char));
    memcpy(name, ser, 10);
    //Break the data into len
    size_t len;
    memcpy(&len, ser + 10, 8);
    //Break the data into...data 
    char *data = malloc(len * sizeof(char));
    memcpy(data, ser + 18, len);

    file de_ser = {
        .name = name,
        .len = len,
        .data = data
    };
    return de_ser;
}

void print_ordered_bytes(unsigned char* print, size_t len){
    for (int i = 0; i < len; i++) {
        printf("%02x ", print[i]);
    }
        printf("\n");
}

file read_file(char *path){
    FILE *f = fopen(path, "rb");
    if (f == NULL){     
        printf("Failed to open file in read_file()\n");
        exit(0);
    }

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);

    file file= {
        .name = path,
        .len = size,
        .data = malloc(size * sizeof(char))
    };

    fread(file.data, 1, file.len, f);

    return file;
}

