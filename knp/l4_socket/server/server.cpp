/* A simple server in the internet domain using TCP
The port number is passed as an argument 
Based on example: https://www.linuxhowtos.org/C_C++/socket.htm 

Modified: Michael Alrøe
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>




#define BUFSIZE_RX 200
#define BUFSIZE_TX 1000

#define PORT "9000"

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int sendfile(int newsockfd,char* filepath);

int main(int argc, char *argv[])
{
	//initialiser server
	//###############################################################
	printf("Starting server...\n");

	int sockfd, newsockfd, portno;

	socklen_t clilen;
	uint8_t bufferRx[BUFSIZE_RX];
	uint8_t bufferTx[BUFSIZE_TX];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");

	printf("Binding...\n");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(PORT);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR on binding");

	printf("Listen...\n");
	listen(sockfd,5);
	
	clilen = sizeof(cli_addr);
	//###########################################################################

	for (;;)
	{
		printf("Accept...\n");
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); //block

		if (newsockfd < 0) error("ERROR on accept");
		else printf("Accepted\n");


		bzero(bufferRx,sizeof(bufferRx)); //set boffer 0

		n = read(newsockfd,bufferRx,sizeof(bufferRx)); //block
		if (n < 0) error("ERROR reading from socket");

		bufferRx[strcspn((char*)bufferRx, "\r\n")] = '\0';

		printf("File path: %s\n",(char*)bufferRx);

		int res = sendfile(newsockfd,(char*)bufferRx);
		if (n < 0) printf("file sendt error");

		printf("File is sendt\n");
			
		close(newsockfd);
	}
	close(sockfd);
	return 0; 
}


int sendfile(int newsockfd,char* filepath){
	uint8_t bufferTx[BUFSIZE_TX];

	int n;

	int fd = open(filepath,O_RDONLY);
	if(fd == -1){
		printf("File path: %s chould not open \n",(char*)filepath);

		snprintf((char*)bufferTx, sizeof(bufferTx), "0");
		
		n = write(newsockfd,bufferTx,strlen((char*)bufferTx)+sizeof(char));
		if (n < 0) error("ERROR writing to socket");
		
		printf("sendt 0\\0 for the file size of 0\n");

		return -1;
	}
	
	off_t  size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);

	printf("File: %s has a size of %i\n",(char*)filepath,(int)size);
	
	if(size == 0){
		printf("File: %s dosent have anything in it\n",(char*)filepath);
		
		snprintf((char*)bufferTx, sizeof(bufferTx), "0");
		
		n = write(newsockfd,bufferTx,strlen((char*)bufferTx)+sizeof(char));
		if (n < 0) error("ERROR writing to socket");
		
		return -1;
	}
	
	
	snprintf((char*)bufferTx, sizeof(bufferTx),"%i", size);
	
	n = write(newsockfd,bufferTx,strlen((char*)bufferTx)+sizeof(char));
	if (n < 0) error("ERROR writing to socket");
	
	printf("Filesize is sendt\n");
	
	off_t bites_left = size;
	
	while(bites_left){
		
		uint16_t read_bits = read(fd, bufferTx, sizeof(bufferTx));
		if (read_bits < 0) error("reading from file");
		if(read_bits == 0) break;
		
		printf("Read %i bits\n",(int)read_bits);
		
		
		n = write(newsockfd,bufferTx,read_bits);
		if (n < 0) error("ERROR writing to socket");
		printf("bytes sendt\n");
		
		
		bites_left - read_bits;

		printf("There i %i bits left\n\n", (int)bites_left);
		
	}

	return 0;

}