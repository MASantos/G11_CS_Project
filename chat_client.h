/* Chat
 */

#ifndef __CHAT_CLIENT_H__
#define __CHAT_CLIENT_H__

//#include <netinet/in.h> //In OSX (*NIX?) it's arpa/inet.h
#include <arpa/inet.h> 
#include "chat_common.h"

struct sockaddr_in* newServerAddress(char* srvIP, int port);

int connect2Server(struct sockaddr_in* server_addr_ptr);

int startChat(int sock);

#endif // END __CHAT_CLIENT_H__ 

