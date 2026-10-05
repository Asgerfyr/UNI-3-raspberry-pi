/* A simple client in the internet domain using TCP
The IP adresse and port number on server is passed as arguments 
Based on example: https://www.linuxhowtos.org/C_C++/socket.htm 

Modified: Michael Alrøe
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <fcntl.h>
#include <sys/socket.h>
#include <netdb.h> 

#define PORT "9000"
#define IP "172.16.15.2"

#define BUFSIZE 1000

int download_file(int sockfd ,char* filepath);

void error(const char *msg)
{
	printf("error%s",msg);
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	//initialice socket
	//##############################################
	printf("Starting client...\n");

	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	uint8_t buffer[BUFSIZE];
    
	portno = atoi(PORT);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	    error("ERROR opening socket: ");

	server = gethostbyname(IP);
	if (server == NULL) 
	    error("ERROR no such host");

	printf("Server at: %s, port: %s\n",IP, PORT);

	printf("Connect...\n");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
	    error("ERROR connecting");

	//#####################################################################

	printf("Please enter the file path: ");
	fgets((char*)buffer,sizeof(buffer),stdin);
	buffer[strcspn((char*)buffer, "\r\n")] = '\0';
	n = write(sockfd,buffer,strlen((char*)buffer));  // socket write
	if (n < 0) 
	    error("ERROR writing to socket");
    
    
    download_file(sockfd, (char*)buffer);
    
    
    bzero(buffer,sizeof(buffer));
	//n = read(sockfd,buffer,sizeof(buffer));  // socket read
	n = recv(sockfd, buffer, sizeof(buffer), MSG_WAITALL);  // waits for full buffer or connection close
	if (n < 0) 
	    error("ERROR reading from socket");
	printf("\n%s\n",(char*)buffer);

    printf("Closing client...\n\n");
	close(sockfd);
	return 0;
}


int download_file(int sockfd ,char* filepath){
    uint8_t buffer_rx[BUFSIZE];
    int n;
    

    //get file size
    //##############################################
    printf("getting the file size...\n\n");
    
    std::string str_file_size = "";
    
    char* c = new char{};
    //for loop untill end of string
    while(1){
        n = read(sockfd,c,1);  // socket read
		if(n == 0)continue;
        if (n < 0) error("ERROR reading from socket");
		printf("Got char %c \n",*c);
		if(*c == '\0') break;
		
		str_file_size += *c;
	}

	delete c;

	
	off_t size = static_cast<off_t>(std::stoll(str_file_size));

	printf("Got the file size of %i\n",(int)size);

	if(size == 0) error("no file to download");
	//#############################################################
	
	int fd = open(filepath, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
	if (fd < 0) 
	error("error creating file");

	off_t bites_left = size;
	while(bites_left){

		int read_bites = (bites_left > BUFSIZE)?BUFSIZE:bites_left;
		
		int bites = read(sockfd,buffer_rx,sizeof(read_bites));  // socket read
		
		uint16_t res = write(fd, buffer_rx, bites);
		if (res < 0) error("writing to file");
		
		bites_left -= bites;
		
		printf("Got %i bits: bites left %i", (int)bites, (int)bites_left);
		
	}
	
	
	printf("Done writing");

	return 0;

}
