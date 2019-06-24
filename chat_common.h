/* Chat
 */

#ifndef __CHAT_COMMON_H__
#define __CHAT_COMMON_H__

#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <string.h> 

#ifndef DEBUG
#define DEBUG 0
#endif

#define DEFAULT_SERVER_PORT 8080 
#define DEFAULT_SERVER_IP "127.0.0.1"

void usage();

int newPort();

char* newServerIP();

int newSocket();

#endif // END __CHAT_COMMON_H__ 

