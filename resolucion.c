/*
$ resolucion 195.53.213.16
195.53.213.16 www.iberia.es
*/
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h> 


int main(int argc, char *argv[]){
    struct in_addr addr;
    //struct in_addr **addr_list;
    struct hostent *res;
 
    if(argc != 2){
        printf("Entrada no valida.\nUsar:\n\t./resolucion {direccion_ip}\n");
        return 1;
    }

    inet_aton(argv[1], &addr);
    res = gethostbyaddr(&addr, sizeof(addr), AF_INET);

    if(res == NULL){
        printf("ERROR\n");
        return 1;
    }
    
    printf("%s %s\n", argv[1], res->h_name);


        printf("\t- %s\n", inet_aton(res->h_addr));
    /*while(res->h_addr != NULL){
        printf("\t- %s\n", inet_ntoa(res->h_addr));
    }*/
    
    /*printf("Host: %s\n", argv[1]);
    printf("Nombre: %s\n", res->h_name);

    printf("Direcciones:\n");
    addr_list = (struct in_addr **)res->h_addr_list;
    for(int i = 0; addr_list[i] != NULL; i++){
        printf("\t- %s\n", inet_ntoa(*addr_list[i]);
    }*/

    return 0;
}