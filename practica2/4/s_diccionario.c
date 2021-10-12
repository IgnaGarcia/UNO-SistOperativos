#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define PORT 30003
#define N 4

int buscar(char*, char**);

int buscar(char* palabra, char** diccionario){
    
    return 0;
}

int main(int argc, char *argv[]){
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_addr, client_addr;

    char *palabras[N] = {"PERRO", "GATO", "PERSONA", "AGUA"};
    char *defs[N] = {"mamifero canido domestico de 4 patas", "mamifero felino domestico de 4 patas", "individuo de la especie humana", "sustancia liquida sin olor, color ni sabor"};

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);					

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);
    server_len = sizeof(server_addr);

    bind(server_sockfd, (struct sockaddr *)&server_addr, server_len);

    listen(server_sockfd, 5);
    while(1) {
        printf("escuchando...\n");

        client_len = sizeof(client_addr);
        client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_addr, (unsigned int *)&client_len);
        printf("conectado...\n");
        while(1){
            char req[256];
            read(client_sockfd, &req, 256);
            printf(">%s\n", req);
            if(req[0] == '0'){
                write(client_sockfd, "ADIOS", 256);
                break;
            } else if(req[0] == '1'){
                write(client_sockfd, "listar", 256);                
            } else if(req[0] == '2'){
                write(client_sockfd, "BUSCAR <palabra>\nAYUDA\nLISTAR\nSALIR\n", 256);
            } else if(req[0] == '3'){
                char res[20];
                strncpy(res, &req[1], sizeof(req));
                for(int i=0; i<N; i++){
                    if(strcmp(palabras[i], res)){
                        write(client_sockfd, defs[i], 256);
                        break;
                    }
                }
            } else {
                printf("ERROR\n");
            }
        }
        close(client_sockfd);
    }
    return 0;
}

