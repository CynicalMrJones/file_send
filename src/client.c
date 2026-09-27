
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

    size_t size;
    recv(sock, &size, 8, 0);
    unsigned char *buff = malloc(size * sizeof(unsigned char));
    int bytes_recv = 0;
    int total = 0;
    while (total < size){
        bytes_recv = recv(sock, buff + total, size - total, 0);
        total += bytes_recv;
        if (bytes_recv == 0){
            break;
        }
    }

    file test = de_dumb_ser(buff);

    FILE *fptr = fopen(test.name, "wb");
    if (fptr == NULL){
        printf("Could not open file\n");
        exit(-1);
    }

    fwrite(test.data, sizeof(char), test.len, fptr);
    fclose(fptr);
}
