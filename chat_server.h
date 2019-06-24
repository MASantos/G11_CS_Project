/* Chat
 */

#ifndef __CHAT_SERVER_H__
#define __CHAT_SERVER_H__

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "chat_common.h"
#include <netinet/in.h> //For Server: works as well in In OSX (*NIX?)
//#include <arpa/inet.h>  //For Client: in OSX (*UNIX?) it's arpa/inet.h

struct chatServer {
	int requests;
	struct sockaddr_in address;
};
typedef struct chatServer chatServer;	

//struct sockaddr_in newServer(char* srvIP, int port);
chatServer newServer(char* srvIP, int port);
 
int bindServer2Port(int server_sock, struct sockaddr_in* address);

int startListening(int server_sock);

int acceptRequests(int server_sock, struct sockaddr_in* address);

int startChat(int sock);

#endif // END __CHAT_SERVER_H__ 

