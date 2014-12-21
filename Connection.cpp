#include "Connection.h"

using namespace std;

void error_message(char *fmt, ...)
{
	va_list ap;
	char buf[1024] = { 0 };

	va_start(ap, fmt);
	vsprintf(buf, fmt, ap);
	va_end(ap);
	fprintf(stderr, "Error: %s\n", buf);

	exit(EXIT_FAILURE);
}

int Connection::Send(char *buf, int len)
{
	return write(Connection::sock, buf, len);
}

char * Connection::Receive(int len)
{
	if (len > sizeof(buf)) {
		cerr << "Error: max read size is 8192 bytes." << endl;
		exit(1);
	}

	ssize_t l = read(Connection::sock, Connection::buf, len);	
	buf[l] = '\0';

	return buf;
}

void Connection::Disconnect(void)
{
	close(sock);
}

int Connection::Connect(char *hostname, int port)
{
	int status;
	int flags;
	struct hostent *host;
	struct sockaddr_in host_addr;
	fd_set fds;
	struct timeval tm;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) 
		error_message("socket %s\n", strerror(errno));

	host = gethostbyname(hostname);
	if (host == NULL) {
		printf("! FATAL - invalid hostname \"%s\" %s\n", hostname, strerror(errno));
		exit(EXIT_FAILURE);
	}

	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(port);
	host_addr.sin_addr = *((struct in_addr *) host->h_addr);
	memset(&host_addr.sin_zero, 0, 8);

	status = connect(sock, (struct sockaddr *) &host_addr, sizeof(struct sockaddr));

	FD_ZERO(&fds);
	FD_SET(sock, &fds);
	tm.tv_sec = TCP_TIMEOUT;
	tm.tv_usec = 0;

	if (status == -1) {
		if (errno == EINPROGRESS) {
			flags = fcntl(sock, F_GETFL, 0);
			fcntl(sock, F_SETFL, flags | O_NONBLOCK);	
			status = select(sock + 1, &fds, &fds, NULL, &tm);
			if (status == 0) {
				cout << "! Timeout on " << hostname << " on port "<< port << endl;
				close(sock);
				return -1;
			} else if (status < 0) 
				close(sock);
				error_message("select() %s\n", strerror(errno));
		} else {
			close(sock);
			return -1;
		}
	}

	
	//close(sock);
	fcntl(sock, F_SETFL, flags);

	//status = connect(sock, (struct sockaddr *) &host_addr, sizeof(struct sockaddr));
	//if (status) 
		cout << "* Connected to " << hostname << " on port " << port << endl;
		
	return 1;
}


