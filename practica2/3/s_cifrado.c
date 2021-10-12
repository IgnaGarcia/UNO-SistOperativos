#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define PORT 30000

int descifrar(char*, char*);
int cifrar(char*, char*);

int descifrar(char* m_cifrado, char* m_descifrado) {
    //char* ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    //char* abc = "abcdefghijklmnopqrstuvwxyz";
    int i = 0;
    while(m_cifrado[i] != '\0'){
        m_descifrado[i] = (m_cifrado[i] + i) % 26;
    }
    return 0;
}

int cifrar(char* m_descifrado, char* m_cifrado) {
    //char* ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    //char* abc = "abcdefghijklmnopqrstuvwxyz";
    int i = 0;
    while(m_descifrado[i] != '\0'){
        m_cifrado[i] = (m_descifrado[i] - i) % 26;
    }
    return 0;
}

int main(int argc, char *argv[]){
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    char *buffer, *res;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);					

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl("127.0.0.1");
    server_address.sin_port = htons(PORT);
    server_len = sizeof(server_address);

    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

    memset(buffer, 0, 256);
    listen(server_sockfd, 5);
    while(1) {
        printf("escuchandp...\n");

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, (unsigned int *)&client_len);

        read(client_sockfd, &buffer, 256);

        if(buffer[0] == '0'){
            cifrar(buffer, res);
        } else if(buffer[0] == '1') {
            descifrar(buffer, res);
        } else {
            res = "invalid";
        }

        write(client_sockfd, &res, 256);
        close(client_sockfd);
    }
    return 0;
}

