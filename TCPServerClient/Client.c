// Program: TCPClient
// Subject: CMPE 207
// Assignment 1 - TCP client server
// Created by Team 8.


/*Write TCP client and server programs that the client passes a greeting message
 *to the server. The server receives the message, counts the number of characters
 *in the message, and sends the count back to the client. The client then
 *receives the value, compares it to its count, and prints out both the message
 *and the count.
 */

/*****CLIENT PROGRAM*****/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define portno 5676  //The port number on which the server is running

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
	exit(0);
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
	//sockfd is the file descriptors
	//rwSuccess is the return value for read() and write() calls
	//Response value is the value got from the server
	int sockfd, rwSuccess, reponse_value;

	//The Internet address of the server is initialized
	struct sockaddr_in serv_addr;

	//An entry in the hosts database.
	struct hostent *server;
	socklen_t server_length; //server address

	//The characters written on the socket is read into this buffer
	char storageBuffer[BUFSIZ];
	const char* host = "localhost";

	//Creating a new socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
		error("ERROR opening socket");

	server = gethostbyname(host);

	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}


	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	//Connecting to the server
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR connecting");

	printf("Please enter the welcome message: ");
	bzero(storageBuffer,256);
	fgets(storageBuffer, 256, stdin);

	//calculating the length of the message sent to server and stored in buffer
	int lengthOfMessageSent = strlen(storageBuffer);

	//Write the message onto the socket to the server

	rwSuccess = sendto(sockfd, &storageBuffer, sizeof(storageBuffer), 0,
			(struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));
	if (rwSuccess < 0)
		error("ERROR writing to socket");

	//Reading the response from the server
	rwSuccess = recvfrom(sockfd, &reponse_value,  sizeof(reponse_value), 0, (struct sockaddr *) &serv_addr, &server_length);

	if (rwSuccess < 0)
		error("ERROR reading from socket");

	//Comparing the length sent by server and the length calculated by the client
	if (reponse_value == lengthOfMessageSent){
		printf("Message: %s", storageBuffer);
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
