include Make.defines

PROGS =  passwordBreaker passwordServer

OPTIONS = -DUNIX  -DUSE_SIGACTION -DANSI


COBJECTS =      methods.o
CSOURCES =      methods.c
SERVEROBJECTS = server.o getRequest.o processRequest.o response.o
SERVERSOURCES = server.c getRequest.c processRequest.c response.c
CLIENTOBJECTS = client.o clientGetRequest.o clientProcessRequest.o
CLIENTSOURCES = client.c clientGetRequest.c clientProcessRequest.c

CPLUSOBJECTS =

COMMONSOURCES =

CPLUSSOURCES =

all:    ${PROGS}


	client:        $(CLIENTOBJECTS) $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(COMMONSOURCES) $(SOURCES)
	${CC} ${LINKOPTIONS}  $@ $(CLIENTOBJECTS) $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(LINKFLAGS)


	server:         $(SERVEROBJECTS) $(CPLUSOBJECTS) $(COBJECTS)
	${CC} ${LINKOPTIONS} $@ $(SERVEROBJECTS) $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(LINKFLAGS)


	.cc.o:  $(HEADERS)
	$(CPLUS) $(CPLUSFLAGS) $(OPTIONS) $<

	.c.o:   $(HEADERS)
	$(CC) $(CFLAGS) $(OPTIONS) $<



	backup:
	rm -f Assignment1.tar.gz
	tar -cf Assignment1.tar *
	gzip -f Assignment1.tar

	clean:
	rm -f ${PROGS} ${CLEANFILES}

	depend:
	makedepend client.c server.c -I/usr/lib/gcc/x86_64-linux-gnu/4.6/include $(CFLAGS) $(HEADERS) $(SOURCES) $(COMMONSOURCES) $(CLIENTSOURCES) $(SERVERSOURCES) $(CSOURCES)
	#               mkdep $(CFLAGS) $(HEADERS) $(SOURCES) $(COMMONSOURCES) $(CSOURCES)
