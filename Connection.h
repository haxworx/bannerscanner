#ifndef __Connection_H__
#define __Connection_H__
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>
#include <netdb.h>
#include <fcntl.h>

#define TCP_TIMEOUT 5

using namespace std;


class Connection {
	public:
		int Connect(char *, int);
		void Disconnect(void);
		char *Receive(int);
		int Send(char *, int);
		char buf[65535];

	
	private:
		char *hostname;
		int port;
		int sock;	
};

#endif
