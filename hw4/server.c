#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
	 //	 char *correct = "fork";
	 
     struct sockaddr_in serv_addr, cli_addr;
     int n;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = 8000;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
	 
	 //listening for clients...
	 printf("Listening for client...\n");
     listen(sockfd, 5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
	 else
		 printf("Client connected.\n");
		 
     bzero(buffer, sizeof(buffer));

	 sprintf(buffer, "What is both an eating utensil and a unix call?");
	 n = write(newsockfd, buffer, sizeof(buffer));
	 if(n < 0) error("ERROR writing to socket");
	 bzero(buffer, sizeof(buffer));
	 
	 //reading from the client
     n = read(newsockfd, buffer, sizeof(buffer));
     if (n < 0) error("ERROR reading from socket");
	 
	 if(strcmp(buffer, "fork\n")==0){
		 printf("Client was correct");
		 sprintf(buffer, "Correct!");
	 }
	 else{
		 printf("Client was wrong");
		 sprintf(buffer, "Wrong. The answer is fork");
	 }

	 //sending a message received notification to client
     n = write(newsockfd, buffer, sizeof(buffer));
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return 0; 
}
