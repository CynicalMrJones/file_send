
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include "../lib/lib.h"


int main(int argc, char **argv){
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    //creating an address space
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8888);

    //Bind to address
    if (bind(socketfd,(struct sockaddr*)&address, sizeof(address)) != 0){
        printf("Failed to bind to %d\n", htons(address.sin_port)); 
        exit(-1);
    }

    //Listen on port
    printf("Listening on port: %d\n", htons(address.sin_port)); 
    int lis = listen(socketfd, 5);
    if (lis == 0){
        printf("Connection established\n"); 
    }

    file test = read_file(argv[1]);
    unsigned char *meme = dumb_ser(test);
    size_t size = strlen(test.name) + sizeof(test.len) + strlen(test.data);

    while(1){
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        int acc = accept(socketfd, (struct sockaddr*)&address, &client_len);

        int bytes_sent = 0;
        int sent = 0;
        while(bytes_sent < size){
            sent = send(acc, meme, size, MSG_CONFIRM);
            printf("Sending\n");
            bytes_sent += sent;
        }
        printf("Done sending\n");
    }
}
