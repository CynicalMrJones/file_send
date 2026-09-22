
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* name;
    size_t len;
    char* data;
} file;

file read_file(char *path){
    FILE *f = fopen(path, "rb");
    if (f == NULL){ printf("Failed to open f\n");
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
