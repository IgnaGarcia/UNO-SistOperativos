#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PORT 30003

int main(int argc, char *argv[]){
    int sockfd, len, result;
    struct sockaddr_in address;
    char res[256];
    char *search = "BUSCAR", *list = "LISTAR", *exit = "SALIR", *help = "AYUDA"; 

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

    while(1) {
        char req[256] = "", inp[50] = "";
        printf("DICCIONARIO>");
        scanf("%s", inp);

        if(strcmp(inp, exit) == 0){
            *req = '0';
        } else if(strcmp(inp, list) == 0){
            *req = '1';
        } else if(strcmp(inp, help) == 0){
            *req = '2';
        } else{
            if(strcmp(inp,search) == 0){
                *req = '3';
                scanf("%s", inp);
                strcat(req,inp);
            } else {
                *req = '9';
                printf("Entrada no valida, vuelve a intentar con BUSCAR-AYUDA-LISTAR-SALIR\n");
            }
        } 
        if(req[0] != '9'){
            write(sockfd, &req, sizeof(req));
            read(sockfd, &res, 256);
            if(req[0] == '0') {
                close(sockfd);
                break;
            }
            printf("\n---\n%s\n---\n", res);
        }
    }

    close(sockfd);
    return 0;
}
