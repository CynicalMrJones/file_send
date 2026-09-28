
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
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
    printf("Length of file in the server %ld\n", test.len);

    unsigned char *meme = dumb_ser(test);
    //TODO: This should not be a magic number
    size_t size = 8 + 100 + 8 + test.len;

    while(1){
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        int acc = accept(socketfd, (struct sockaddr*)&client_address, &client_len);

        int bytes_sent = 0;
        int sent = 0;
        while(bytes_sent < size){
            sent = send(acc, meme + bytes_sent, size - bytes_sent, 0);
            printf("Sending\n");
            if (sent == 0){
                break;
            }
            bytes_sent += sent;
            printf("Sent: %d\n", sent);
        }
        printf("Done sending\n");
        close(acc);
    }
}
