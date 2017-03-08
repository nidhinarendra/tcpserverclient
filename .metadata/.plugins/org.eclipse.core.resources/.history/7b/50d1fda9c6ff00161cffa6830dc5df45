/*Write TCP client and server programs that the client passes a greeting message
 *to the server. The server receives the message, counts the number of characters
 *in the message, and sends the count back to the client. The client then
 *receives the value, compares it to its count, and prints out both the message
 *and the count.
 */

/*****CLIENT PROGRAM *****/

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
	int sockfd, portno, rwSuccess;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char storageBuffer[256];

	if (argc < 3) {
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}

	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
		error("ERROR opening socket");

	server = gethostbyname(argv[1]);

	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR connecting");

	printf("Please enter the welcome message: ");
	bzero(storageBuffer,256);
	fgets(storageBuffer, 256, stdin);
	int lengthOfMessageSent = strlen(storageBuffer);

	rwSuccess = write(sockfd, storageBuffer, strlen(storageBuffer));
	if (rwSuccess < 0)
		error("ERROR writing to socket");


	int reponse_value;
	rwSuccess = read(sockfd, &reponse_value, 255);
	if (rwSuccess < 0)
		error("ERROR reading from socket");

	if (reponse_value == lengthOfMessageSent){
		printf("Message: %s\n", storageBuffer);
		printf("Length: %d\n", reponse_value);
	}
	else {
		printf("Error: client sent the data of length %d "
				"and the length sent by the server is %d \n",
				lengthOfMessageSent, reponse_value);
	}

	close(sockfd);
	return 0;
}
