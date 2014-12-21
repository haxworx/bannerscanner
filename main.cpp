#include "Connection.h"
#include "UserInput.h"

#define PROGRAM_NAME "httpd_scan"


void usage(void)
{
	cout << "Usage: " << endl;
	cout << PROGRAM_NAME << ": <hostname> <start port> <end port>" << endl;
	cout << "Snoop for open SSH servers on non-standard ports. " << endl << endl;

	exit(0);
}

void show_menu(void)
{
	cout << endl << "(C++) HTTP Daemon Scanner v.0.0.1" << endl;
	cout << "--[netstar <al@haxlab.net>]------"  << endl << endl;
	cout << "Please choose a command: " << endl << endl;
	cout << "Commands (h) change hostname (r) port range (s) scan (q) quit" << endl;
	cout << "> ";
}

void test_ports(int s, int l)
{
	if ( s <= 0 || s > l || l > 65535)  {
		cerr << "Invalid port range!" << endl << endl;
		exit (0);
	}
}

void port_scan(char *hostname, int start_port, int end_port)
{
	Connection c;	

	for (int i = start_port; i <= end_port; i++) {
		int res = c.Connect(hostname, i);
		if (res > 0) {
			char *http_get = "GET / HTTP 1.0\r\n\r\n";
			c.Send(http_get, strlen(http_get));						
			char *banner = c.Receive(8192);
			cout << banner << endl;	
			c.Disconnect();
		}
		
	}
}

int main(int argc, char **argv)
{	
	
	Input i;
	char ch;	

	char *hostname = "localhost";
	int start_port = 1;
	int end_port = 65535;

	show_menu();

	do {	
		ch = (char) i.ReadChar();
	
		switch (ch) {

			case 'h':
				cout << "Enter hostname (" << hostname << "): ";
				hostname = strdup(i.ReadString());
				cout << "Successfully changed hostname!" << endl;
				show_menu();
			break;
			case 'r':
				cout << "Enter start port (" << start_port << "): ";
				cin >> start_port;

				cout << "Enter ending port (" << end_port << "): ";
				cin >> end_port;

				test_ports(start_port, end_port);

				cout << "Successfully changed ports! " << endl;
				
				show_menu();
			break;
	
			case 's':
				port_scan(hostname, start_port, end_port);	
				show_menu();
			break;

			default:
				show_menu();
			break;
		};
			
	} while (ch != 'q');

	cout << "Bye!" << endl;

	return 0;
}
