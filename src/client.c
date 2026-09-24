
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
        // printf("Connected\n");
    }
    else{
        // printf("Failed to connect\n");
        exit(0);
    }

    //Not allocated properly
    size_t length = 388;
    // recv(sock, &length, sizeof(size_t), MSG_CMSG_CLOEXEC); 
    file f = { 
        .name = malloc(length * sizeof(char)),
        .len = length,
        .data = malloc(length * sizeof(char))
    };
    char buff[1000];
    // recv(sock, f.name, 200, MSG_CMSG_CLOEXEC); 
    int bytes;
    while(1){
        bytes = recv(sock, buff, 398, MSG_CMSG_CLOEXEC);
        // printf("%d\n", bytes);
        printf("%s", buff);
        exit(0);
    }
    // recv(sock, buff, 388, MSG_CMSG_CLOEXEC); 
    printf("data: %s\n", buff); 

    // FILE *fptr = fopen(f.name, "wb");
    // FILE *fptr = fopen("test", "wb");
    //
    // // fwrite(f.data, sizeof(char), f.len, fptr);
    // fwrite(buff, sizeof(char), 1000, fptr);
    // fclose(fptr);

}
