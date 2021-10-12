#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PORT 30000

int main(int argc, char *argv[]){
    int sockfd, len, result;
    struct sockaddr_in address;
    char *buffer;

    if(argc != 3){
        printf("Entrada no valida.\nUsar:\n\tPara Cifrar:\t./c_cifrado -c {cadena}\n\tPara Descifrar:\t./c_cifrado -d {cadena}\n");
        return 1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORT);
    len = sizeof(address);

    result = connect(sockfd, (struct sockaddr *)&address, len);
    if(result < 0) {
        perror("ERROR en la conexion\n"); 
        return 1;
    }

    if(strcmp(argv[1], "-c")){
        buffer = strcat("0", argv[2]);
    } else if(strcmp(argv[1], "-d")){
        buffer = strcat("1", argv[2]);
    } else {
        printf("Entrada no valida.\nUsar:\n\tPara Cifrar:\t./c_cifrado -c {cadena}\n\tPara Descifrar:\t./c_cifrado -d {cadena}\n");
        return 1;
    }

    write(sockfd, &buffer, 256);
    read(sockfd, &buffer, 256);

    printf("Cadena:\n%s\n", buffer);
    close(sockfd);

    return 0;
}
