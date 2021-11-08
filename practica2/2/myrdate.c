/*
$ myrdate 129.6.15.28
myrdate: [129.6.15.28] Fri Sep 5 19:53:05 2014
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
 
#define OFFSET 2208988800
#define PORT 37

int main(int argc, char *argv[]){
    int sockfd, len, result, x;
    struct sockaddr_in address;
    char *buffer;

    if(argc != 2){
        printf("Entrada no valida.\nUsar:\n\t./myrdate {host}\n");
        return 1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(argv[1]);
    address.sin_port = htons(PORT);
    len = sizeof(address);

    result = connect(sockfd, (struct sockaddr *)&address, len);
    if(result < 0) {
        perror("error al conectar"); 
        return 1;
    }

    result = read(sockfd, &buffer, 4);
    if(result < 0){
        perror("error al leer");
        return 1;
    }

    x = buffer[0]*0x1000000LU + buffer[1]*0x10000LU + buffer[2]*0x100LU + buffer[3];
    x -= OFFSET;

    printf("[%s] %s\n", argv[1], ctime(&x));
    
    close(sockfd);
    return 0;
}