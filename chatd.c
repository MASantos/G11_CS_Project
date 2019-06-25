
// Server side C/C++ program to demonstrate Socket programming 
  
#include "chat_server.h"

int main(int argc, char const *argv[]) 
{
	if ( argc > 1  && (strcmp("-h",argv[1])==0 || strcmp("--help",argv[1])==0) ) {
		usage();
		exit(0);
	}

	char* serverIP = newServerIP();
	int serverPort = newPort();
	
    if (argc >= 3 ) {
		serverIP = (char*) argv[1];
		serverPort = atoi(argv[2]);
		argc -=2;	
	}else if (argc == 2){
		serverIP = (char*) argv[1];
		argc -=1;	
	}
	printf("Setting up server at IP:port %s:%d\n",serverIP, serverPort);

    chatServer cserver = newServer(serverIP,serverPort); //create srv socket, bind addr, enable listen (SBL)
    
    startChat( &cserver );
	
	close( cserver.socket);	
	return 0; 
} 

