#ifndef SERVER_H
#define SERVER_H


// Include libs :
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <pthread.h>
    #include <time.h>
    #include <errno.h>


// Defines :
    // Server IP and PORT.
    #define SERVER_IP "127.0.0.1"
    #define PORT 8081

    // Max message length :
    #define MAX_BUFFER_SIZE 1024

    // Error code for all sockets function :
    #define NETWORK_FUNCTIONS_ERROR_CODE - 1

    // Defining flags for writeLog :
    #define ERROR 1
    #define LOG 2


// Structs :
    // Define a struct for the createServerInstance function to return the two sockets.
    typedef struct {
        int clientSocket;
        int serverSocket;
    }SocketPair;
SocketPair createServerInstance();

// Prototypes:
int createServerSocket();
struct sockaddr_in createServerSockaddr_inStruct();
int bindServerSocket(int serverSocket, struct sockaddr_in serverSocket_address);
int listenForConnections(int serverSocket);
int acceptSocketConnection(int serverSocket, struct sockaddr_in serverSocket_address, socklen_t serverSocketAddressLength);
char* receiveMessage(int clientSocket);
int sendMessage(int socket, char* message);
int writeLog(char* logMessage, int flag);
int closeProgramIfNeeded(int returnCode);


#endif //SERVER_H
