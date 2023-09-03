#ifndef CLIENT_H
#define CLIENT_H

// Include libs :
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <pthread.h>

// Defines :
    // Server IP and PORT.
    #define SERVER_IP "127.0.0.1"
    #define PORT 8080

    // Max message length.
    #define MAX_BUFFER_SIZE 1024

// Prototypes:
int createClientSocket();
struct sockaddr_in connectToServer(int clientSocket);
void* sendMessage(void* clientSocket);
void* receiveMessage(void*  clientSocket);

#endif //CLIENT_H
