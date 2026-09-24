
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "../lib/lib.h"


int main(int argc, char **argv){
    int sock = 0;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8888);

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <=0){
        return -1;
    }


    int conn = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(conn == 0){
        printf("Connected\n");
    }
    else{
        printf("Failed to connect\n");
        exit(0);
    }

    //Not allocated properly
    size_t size;

    //TODO: I think the issue is here and need to check
    recv(sock, &size, 8, 0);
    unsigned char *buff = malloc(size * sizeof(unsigned char));
    recv(sock, buff, size, 0);

    //For printing the data
    printf("Size: %ld\n", size);
    for (int i = 0; i < size - 8; i++){
        printf("%02x ", buff[i]);
    }
    printf("\n");

    file test = de_dumb_ser(buff);
    printf("name: %s\n", test.name);
    printf("len: %ld\n", test.len);
    printf("data: %s\n", test.data);

    FILE *fptr = fopen("test.file", "wb");

    fwrite(test.data, sizeof(char), test.len, fptr);
    fclose(fptr);
}
