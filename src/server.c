
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/statvfs.h>
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

int main(){
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    //creating an address space
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8888);

    //Bind to address
    if (bind(socketfd,(struct sockaddr*)&address, sizeof(address)) != 0){
        printf("Failed to bind to %d\n", address.sin_port); 
    }

    //Listen on port
    printf("Listening on port: %d\n", htons(address.sin_port)); 
    int lis = listen(socketfd, 5);
    if (lis == 0){
        printf("Connection established\n"); 
    }

    file test = read_file("joey.jpeg");

    printf("name: %s\nlen: %ld\ndata: %s\n", test.name, test.len, test.data); 


    while(1){
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        int acc = accept(socketfd, (struct sockaddr*)&address, &client_len);
        printf("FD: %d\n", acc); 

        send(acc, &test.len, sizeof(size_t), MSG_CONFIRM);
        send(acc, test.name, strlen(test.name), MSG_CONFIRM);
        send(acc, test.data, test.len, MSG_CONFIRM);
    }
}
