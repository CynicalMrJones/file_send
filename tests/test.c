#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/lib.h"

void test_dumb_ser(){
    printf("Testing in dumb_ser()\n");
    file f = read_file("tests/test.txt");
    FILE *check = fopen("tests/hex.txt", "rb");
    if(check == NULL){
        printf("\033[1;31mFailed:\033[0m Could not open file\n");
        exit(0);
    }
    unsigned char *test = dumb_ser(f);
    int size = 116 + f.len;
    for(int i = 0; i < size; i++){
        unsigned char c = fgetc(check);
        if(test[i] != c){
            printf("\033[1;31mFailed:\033[0m All bytes are not the same\n");
            printf("\n");
            return;
        }
    }
    printf("\033[1;32mPassed:\033[0m All bytes are the same\n");
    printf("\n");
}

void test_de_dumb_ser(){
    printf("Testing in de_dumb_ser()\n");

    file f = read_file("tests/test.txt");
    unsigned char *ser = dumb_ser(f);
    memset(ser, 0, 8);
    file test = de_dumb_ser(ser);

    if(strcmp(test.name, "tests/test.txt") == 0){
        printf("\033[1;32mPass:\033[0m test.name\n");
    }
    else{
        printf("\033[1;31mFailed:\033[0m test.name\n");
    }

    //Testing len
    if(test.len == 13){
        printf("\033[1;32mPass:\033[0m test.len\n");
    }
    else{
        printf("\033[1;31mFailed:\033[0m test.len\n");
    }

    //Testing data
    if(strcmp(test.data, "Hello, World\n") == 0){
        printf("\033[1;32mPass:\033[0m test.data\n");
    }
    else{
        printf("\033[1;31mFailed:\033[0m test.data\n");
    }
    printf("\n");
}

void test_read_file(){
    printf("Testing in read_file()\n");
    file f = read_file("tests/test.txt");
    //Testing name
    if(strcmp(f.name, "tests/test.txt") == 0){
        printf("\033[1;32mPass:\033[0m f.name\n");
    }
    else{
        printf("\033[1;31mFailed:\033[0m f.name\n");
    }

    //Testing len
    if(f.len == 13){
        printf("\033[1;32mPass:\033[0m f.len\n");
    }
    else{
        printf("\033[1;31mFailed:\033[0m f.len\n");
    }

    //Testing data
    if(strcmp(f.data, "Hello, World\n") == 0){
        printf("\033[1;32mPass:\033[0m f.data\n");
    }
    else{
        printf("\033[1;31mFailed:\033[0m f.data\n");
    }
    printf("\n");
}


int main(){
    test_read_file();
    test_dumb_ser();
    test_de_dumb_ser();

    // FILE *hex = fopen("tests/hex.txt", "wb");
    // file f = read_file("tests/test.txt");
    // printf("len of file: %ld\n", f.len);
    // unsigned char *ser = dumb_ser(f);
    // size_t size = 116 + f.len;
    // fwrite(ser, sizeof(char), size, hex);
    return 0;
}
