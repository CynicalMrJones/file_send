
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    char* name;
    size_t len;
    char* data;
} file;

int main(){
    int sock = 0;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8888);


    int conn = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(conn == 0){
        printf("Connected\n");
    }
    else{
        printf("Failed to connect\n");
    }

    //Not allocated properly
    size_t length;
    recv(sock, &length, sizeof(size_t), MSG_CMSG_CLOEXEC); 
    file f = { 
        .name = malloc(length * sizeof(char)),
        .len = length,
        .data = malloc(length* sizeof(char))
    };
    recv(sock, f.name, 200, MSG_CMSG_CLOEXEC); 
    recv(sock, f.data, f.len, MSG_CMSG_CLOEXEC); 
    printf("name: %s\nlen: %ld\ndata: %s\n", f.name, f.len, f.data); 

    FILE *fptr = fopen(f.name, "wb");

    fwrite(f.data, sizeof(char), f.len, fptr);
    fclose(fptr);

}
