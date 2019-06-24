/* From header /usr/include/netinet/in.h

struct sockaddr_in {
        __uint8_t       sin_len;
        sa_family_t     sin_family;
        in_port_t       sin_port;
        struct  in_addr sin_addr;
        char            sin_zero[8];
};

 */

#include "chat_common.h"

void usage(){
	printf("\n \
Usage: chat-client (-h | serverIP [serverPort=8080] ) \n \
\n");
}

int newPort(){
	return DEFAULT_SERVER_PORT;
}

char* newServerIP(){
	return DEFAULT_SERVER_IP;
}

int newSocket(){
    int sock = -1;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        //return -1; 
    } 
	if (DEBUG) printf("DEBUG: new Socket set up\n");
	return sock;
}


