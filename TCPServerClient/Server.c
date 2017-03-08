
// Program: TCPServer
// Subject: CMPE 207
// Assignment 1 - TCP client server
// Created by Team 8.



/*Write TCP client and server programs that the client passes a greeting message
 *to the server. The server receives the message, counts the number of characters
 *in the message, and sends the count back to the client. The client then
 *receives the value, compares it to its count, and prints out both the message
 *and the count.
 */

/*****SERVER PROGRAM*****/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define portno 5676 //The port number on which the server runs


/*
 **********************************************************************************************************
 Function Name : error
 Purpose	   : Function to display the error message from the program to standard error.
 Parameter     : character pointer which points to the starting of the message
 Return Value  : The program exits with the condition 1
 **********************************************************************************************************
 */


void error(const char *msg)
{
	perror(msg);
	printf ("%s", strerror(errno));
	exit(1);
}

/*
 **********************************************************************************************************
 Function Name : Main
 Purpose	   : Program starts here
 Parameter     : None
 Return Value  : Integer
 *********************************************************************************************************
 */

int main(int argc, char *argv[])
{
	//sockfd and newsockfd are the file descriptors
	//rwSuccess is the return value for read() and write() calls
	int sockfd, newsockfd, rwSuccess;
	size_t lengthOfMessageReceived;
	// To compute the length of the client socket
	socklen_t client_length;

	//The characters written on the socket is read into this buffer
	char buffer[BUFSIZ];

	//The Internet address of the server and the client is initialized
	struct sockaddr_in serv_addr, cli_addr;

	//To compute the process ID of the child which is generated during fork()
	pid_t childpid;

	//Creating a new socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");

	//Setting the value in the buffer to 0
	bzero((char *) &serv_addr, sizeof(serv_addr));


	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	//Binding socket to an address and checking if it is successful
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");

	//Listen on the socket for incoming connections
	listen(sockfd,5);

	//Loops forever, so that the server is always ready to listen to new connections
	for(;;){
		memset(&cli_addr, '\0', sizeof(cli_addr));
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &client_length);
		if (newsockfd < 0)
			error("ERROR on accept");

		//Creating a child process to proceed with the new client
		if ((childpid = fork()) == -1) {
			close(newsockfd);
		}
		else if(childpid > 0){
			close(newsockfd);
		}
		else if(childpid == 0){
			bzero(buffer,BUFSIZ);

			//Read the message sent by the client
			rwSuccess = recvfrom(newsockfd, buffer, BUFSIZ, 0, (struct sockaddr *) &cli_addr, &client_length);
			if (rwSuccess < 0) error("ERROR reading from socket");
			lengthOfMessageReceived = strlen(buffer);


			//Write back to the client
			rwSuccess = sendto(newsockfd, &lengthOfMessageReceived, sizeof(lengthOfMessageReceived), 0,
					(struct sockaddr *)&cli_addr, sizeof(struct sockaddr_in));
			if (rwSuccess < 0)
				error("ERROR writing to socket");

			//Close the child when the task is completed
			close(newsockfd);

		}
	}

	//Close the server when it is no longer required [cntrl+c]
	close(sockfd);
	return 0;
}
