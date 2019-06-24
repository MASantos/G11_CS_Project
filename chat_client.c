/* From header /usr/include/netinet/in.h

struct sockaddr_in {
        __uint8_t       sin_len;
        sa_family_t     sin_family;
        in_port_t       sin_port;
        struct  in_addr sin_addr;
        char            sin_zero[8];
};

 */

#include "chat_client.h"

#ifndef DEBUG
#define DEBUG 0
#endif

//int newServer(char* srvIP,struct sockaddr_in& serv_addr_ptr){
struct sockaddr_in* newServerAddress(char* srvIP, int port){
	if (DEBUG) printf("DEBUG: Client: initializing *serv_add_ptr\n");
    
	struct sockaddr_in* serv_addr_ptr = (struct sockaddr_in*) calloc(1,sizeof(struct sockaddr_in));
    //memset(serv_addr_ptr, '0', sizeof(*serv_addr_ptr)); 
   
    serv_addr_ptr->sin_family = AF_INET; 
    serv_addr_ptr->sin_port = htons(port); 
       
	if (DEBUG) printf("DEBUG: Client: initialized *serv_add_ptr\n");
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, srvIP, &serv_addr_ptr->sin_addr)<=0)  
    { 
        printf("\nClient: Invalid address/ Address not supported \n"); 
        return NULL; 
    } 
	if (DEBUG) printf("DEBUG: Client: new Server set up\n");
	return serv_addr_ptr;
}

int connect2Server(struct sockaddr_in* serv_addr_ptr){
	int sock = newSocket();
    if (connect(sock, (struct sockaddr *)serv_addr_ptr, sizeof(*serv_addr_ptr)) < 0) 
    { 
        printf("\nClient: Connection Failed \n"); 
        return -1; 
    }
	if (DEBUG) printf("DEBUG: Client: new Connection set up\n");
	return sock;
}

int startChat(int write_sock){
	if ( write_sock < 0 ){
		printf("EROR: Client:: startChat: No line to server. Bailing out\n");
		return -1;
	}

    //char msg[30]; 
    char buffer[1024] = {0}; 
	printf("Chat ready:\n"); 
    while( 1){
		printf(">");
		fgets(buffer, 30, stdin);
		if ( strncmp(buffer,"exit",4)==0) break;
		send( write_sock , buffer, strlen(buffer) , 0);
    } 
    return 0; 
}

