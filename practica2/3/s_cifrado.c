#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define PORT 30000

int indiceDe(char);
int esMayuscula(char);

int indiceDe(char letra){
    char *ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    char *abc = "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < 26; i++){
        if(ABC[i] == letra || abc[i] == letra) return i;
    }
    return -1;
}

int esMayuscula(char letra){
    return letra <= 90 && letra >= 65;
}

int main(int argc, char *argv[]){
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    int corrido, indice;
    char *ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    char *abc = "abcdefghijklmnopqrstuvwxyz";

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);					

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);
    server_len = sizeof(server_address);

    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

    listen(server_sockfd, 5);
    while(1) {
        char buffer[256], res[256] = "";
        printf("ESCUCHANDO...\n");

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, (unsigned int *)&client_len);

        read(client_sockfd, &buffer, sizeof(buffer));

        if(buffer[0] == '0'){

            printf("CIFRANDO> %s...\n", buffer);

            for(int i = 1; i < strlen(buffer); i++){
                indice = indiceDe(buffer[i]);
                corrido = (indice - 3 + 26) % 26;

                if(indice != -1 && esMayuscula(buffer[i])) res[i-1] = ABC[corrido];
                else if(indice != -1) res[i-1] = abc[corrido];
                else res[i-1] = buffer[i];
            }

            printf("CIFRADO> %s\n", res);

        } else if(buffer[0] == '1') {

            printf("DESCIFRANDO> %s...\n", buffer);

            for(int i = 1; i < strlen(buffer); i++){
                indice = indiceDe(buffer[i]);
                corrido = (indice + 3 + 26) % 26;;

                if(indice != -1 && esMayuscula(buffer[i])) res[i-1] = ABC[corrido];
                else if(indice != -1) res[i-1] = abc[corrido];
                else res[i-1] = buffer[i];
            }

            printf("DESCIFRADO> %s...\n", res);

        } else {
            strcpy(res, "INVALIDO\n");
        }
        write(client_sockfd, &res, strlen(res));
        close(client_sockfd);
    }
    return 0;
}

