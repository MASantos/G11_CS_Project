
default: client server

all: default

client: 
	gcc chat.c chat_client.c chat_common.c  -o chat

server:
	gcc chatd.c chat_server.c chat_common.c  -o chatd
