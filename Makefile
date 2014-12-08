all: client server

CLIENTOBJECTS = client.o clientGetResponse.o clientProcessResponse.o methods.o
SERVEROBJECTS = server.o getRequest.o processRequest.o response.o methods.o

client:
	gcc -o client client.c clientGetResponse.c clientProcessResponse.c methods.c

server:
	gcc -o server server.c getRequest.c processRequest.c response.c methods.c sendRequest.c getResponse.c

clean:
	rm -f $(CLIENTOBJECTS) $(SERVEROBJECTS) *.h~ *.c~ Makefile~ client server
