The program is created to establish a client server connection. 
The client sends a welcome message to the server. 
The server calculates the length of the message and sends the length back to the client. 
The client compares the value sent by the server to its own message length and 
displays both the message and the length. The length includes the null character at the end of the message
The server is capable of serving multiple clients.

Follow the below procedure to run the program.
1) Compile the program using the following command
terminal> make
Both the programs are compiled and th server is running

2) Open a new terminal and type 
terminal> ./client
client program starts running

3) Enter a welcome message on the client terminal

4) The message and the length of the message will be displayed on the client terminal.

5) Client exits with return value of 1 if successful, 
otherwise client exits with appropriate error message.

6) To test a few more cases, repeat steps (2), (3) and (4)

-------------------------------------------------------------
Example testcase1:

terminal> make
newterminal> ./client
Please enter the welcome message: Hello World
Message: Hello World
Length: 12
-------------------------------------------------------------

Example testcase2:

terminal> make
newterminal> ./client
Please enter the welcome message: Good Morning
Message: Good Morning
Length: 13

newterminal> ./client
Please enter the welcome message: Have a good day
Message: Have a good day
Length: 15
