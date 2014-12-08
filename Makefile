all: client server

client:
	gcc -o client client.c clientGetResponse.c clientProcessResponse.c methods.c

server:
	gcc -o server server.c getRequest.c processRequest.c response.c methods.c
