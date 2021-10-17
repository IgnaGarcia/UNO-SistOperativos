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
    char buffer[256], req[256];

    if(argc != 3){
        printf("Entrada no valida.\nUsar:\n\tPara Cifrar:\t./c_cifrado -c {cadena}\n\tPara Descifrar:\t./c_cifrado -d {cadena}\n");
        return 1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);
    len = sizeof(address);

    result = connect(sockfd, (struct sockaddr *)&address, len);
    if(result < 0) {
        perror("ERROR en la conexion\n"); 
        return 1;
    }

    if(strcmp(argv[1], "-c") == 0){
        *req = '0';
        strcat(req, argv[2]);
    } else if(strcmp(argv[1], "-d") == 0){
        *req = '1';
        strcat(req, argv[2]);
    } else {
        printf("Entrada no valida.\nUsar:\n\tPara Cifrar:\t./c_cifrado -c {cadena}\n\tPara Descifrar:\t./c_cifrado -d {cadena}\n");
        return 1;
    }

    printf("Enviando peticion...\n");
    write(sockfd, &req, strlen(req));
    read(sockfd, &buffer, sizeof(buffer));

    printf("Cadena:\n%s\n", buffer);
    close(sockfd);

    return 0;
}
