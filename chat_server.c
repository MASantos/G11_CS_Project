/* Chat
   Server side C/C++ program to demonstrate Socket programming 
*/
#include "chat_server.h"

//struct sockaddr_in newServer(char* srvIP, int port){   
chatServer newServer(char* srvIP, int port){   
    struct sockaddr_in address; 
    int opt = 1; 
    // Creating socket file descriptor 
    int server_sock = newSocket();
    
    // Forcefully attaching socket to the port 8080 
    //if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR ,
                                                  &opt, sizeof(opt))<0 ) 
    { 
        perror("ERROR Server:: setsockopt"); 
        printf("Warning: server socket error\n");
		//exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_port = htons( port );
    address.sin_addr.s_addr = INADDR_ANY; 

	bindServer2Port(server_sock, &address);

	startListening(server_sock);

	chatServer cs;
	cs.socket = server_sock;
	cs.address = address;
	//cs.requests = acceptRequests(server_sock, &address);
	cs.requests = -1;

	return cs; 
}
 
int bindServer2Port(int server_sock, struct sockaddr_in* address_ptr){ 
    // Forcefully attaching socket to the port 8080 
    if (bind(server_sock, (struct sockaddr *)address_ptr,sizeof(*address_ptr))<0) 
    { 
        perror("ERROR Server:: bind failed"); 
        exit(EXIT_FAILURE); 
    }
	return 0;
}

int startListening(int server_sock){ 
    if (listen(server_sock, 3) < 0) 
    { 
        perror("ERROR Server:: listen"); 
        exit(EXIT_FAILURE); 
    }
	return 0;
} 

int acceptConnections(int server_sock, struct sockaddr_in* address_ptr){
    int connect_socket; 
	size_t addrlen = sizeof(*address_ptr);
    if ( (connect_socket = accept(server_sock, (struct sockaddr *)address_ptr,  
                       (socklen_t*)&addrlen)) <0 ) 
    { 
        perror("ERROR Server:: accept");
		printf("DEBUG: Server:: accept: requests socket = %d\n",connect_socket);	
        exit(EXIT_FAILURE); 
    }
	return connect_socket;
}

int acceptRequests(chatServer* cs){
    int connect_socket = -1; 
	size_t addrlen = sizeof(cs->address);
    if ( (connect_socket = accept(cs->socket, (struct sockaddr *)&cs->address,  
                       (socklen_t*)&addrlen)) <0 ) 
    { 
        perror("ERROR Server:: accept");
		printf("DEBUG: Server:: accept: requests socket = %d\n",connect_socket);	
        exit(EXIT_FAILURE); 
    }
	return connect_socket;
	
}

//int startChat(int requests_sock){
int startChat( chatServer* cs){
	for(;;){
		//int requests_sock = acceptConnections(cs->socket, &cs->address);
		int requests_sock = acceptRequests(cs);
		if ( requests_sock < 0 ){
			printf("ERROR: Server:: startChat: No line to server. Bailing out\n");
			return -1;
		}
		int child = -1;
		if ( (child = fork() ) == 0 ){
			close(cs->socket);
			char buffer[1024] = {0};
			while( 1) {
				read( requests_sock , buffer, 1024); 
    			printf("(%d)< %s", requests_sock, buffer);
				if ( strncmp(buffer,"exit",4) == 0 ) break;
				memset(buffer,0,strlen(buffer));
    		}
			close(requests_sock);
			exit(0);
    	}
		close(requests_sock);
    }
    return 0; 
} 

