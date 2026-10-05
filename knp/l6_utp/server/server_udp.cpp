/* Creates a datagram server.  The port
number is passed as an argument.  This
server runs forever
Based on example: https://www.linuxhowtos.org/C_C++/socket.htm

Modified: Michael Alrøe
*/

#include <algorithm>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <cctype>

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int write_buffer(char command, char* buf, size_t size);

int main(int argc, char *argv[])
{
	printf("Starting UDP server...\n");
	int sock, n;
	socklen_t fromlen;
	struct sockaddr_in server;
	struct sockaddr_in from;
	char buf[256];

	sock=socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) error("ERROR, socket");

	bzero(&server,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(atoi("9000"));

	printf("Binding...\n");
	if (bind(sock,(struct sockaddr *)&server,sizeof(server))<0)
	    error("ERROR, binding");

	fromlen = sizeof(from);
	while (1) {
		printf("Receive...\n");
		
		n = recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*)&from,&fromlen);
		if (n < 0) error("ERROR, recvfrom");
        
		write_buffer(buf[0],buf,sizeof(buf));

		printf("Sending information\n");
		n = sendto(sock,buf, strlen(buf),0,(struct sockaddr*)&from,fromlen);
		
		if (n  < 0) error("ERROR, sendto");
		printf("\n");
	}

	return 0;
}



int write_buffer(char command, char* buf, size_t buf_size){
	buf[command] = std::tolower(buf[command]);

	printf("Got the command %c\n", command);
	
	int fd;
	int n;


	switch(command){
		case 'u':
			printf("Getting uptime\n");

			fd = open("/proc/uptime", O_RDONLY);
			if (fd < 0) error("ERROR, open file");
			
			n = read(fd,buf,buf_size);
			if (n < 0) error("ERROR, reading file");
			
			close(fd);
			return 0;

		case 'l':

			printf("Getting loadavg\n");
			
			fd = open("/proc/loadavg", O_RDONLY);
			if (fd < 0) error("ERROR, open file");
			
			n = read(fd,buf,buf_size);
			if (n < 0) error("ERROR, reading file");
			
			close(fd);
			return 0;

		default:
			printf("Error: no command sendt\n");
			char error[256] = "Error: no command sendt";
			std::move(error, error+256, buf);
			return 0;
	}

	return 0;

}