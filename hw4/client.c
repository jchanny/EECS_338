#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
  	portno = 8000;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname("127.0.0.1");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

	//receive message from socket
	n = read(sockfd, buffer, sizeof(buffer));
	if(n < 0)
		error("ERROR reading from socket");
	printf("%s\n", buffer);
   
	//this is for writing to socket
	bzero(buffer, sizeof(buffer));
    fgets(buffer, sizeof(buffer), stdin);
    n = write(sockfd, buffer, sizeof(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer, strlen(buffer));
	
	//reading again from socket
    n = read(sockfd, buffer, sizeof(buffer));
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n", buffer);
    close(sockfd);
    return 0;
}
