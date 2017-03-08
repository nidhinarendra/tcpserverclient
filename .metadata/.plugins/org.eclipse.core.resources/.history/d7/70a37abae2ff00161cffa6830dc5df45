/*Write TCP client and server programs that the client passes a greeting message
 *to the server. The server receives the message, counts the number of characters
 *in the message, and sends the count back to the client. The client then
 *receives the value, compares it to its count, and prints out both the message
 *and the count.
 */

/*****SERVER PROGRAM *****/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//Function to display the errors whenever the system calls fail.
void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno,rwSuccess, lengthOfMessageReceived;
	socklen_t client_length;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;

	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
		error("ERROR opening socket");

	bzero((char *) &serv_addr, sizeof(serv_addr));

	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");

	listen(sockfd,5);
	client_length = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &client_length);

	if (newsockfd < 0)
		error("ERROR on accept");

	bzero(buffer,256);
	rwSuccess = read(newsockfd,buffer,255);

	if (rwSuccess < 0) error("ERROR reading from socket");
	//printf("The message: %s\n",buffer);
	lengthOfMessageReceived = strlen(buffer);
	//printf("%d\n", lengthOfMessageReceived);
	rwSuccess = write(newsockfd,&lengthOfMessageReceived,lengthOfMessageReceived);

	if (rwSuccess < 0) error("ERROR writing to socket");

	close(newsockfd);
	close(sockfd);

	return 0;
}
