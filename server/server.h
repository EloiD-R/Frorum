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


// Defines :
    // Server IP and PORT.
    #define SERVER_IP "127.0.0.1"
    #define PORT 8080

    // Max message length :
    #define MAX_BUFFER_SIZE 1024


// Prototypes:
int createServerSocket();
struct sockaddr_in createServerSockaddr_inStruct();
void bindServerSocket(int server_socket, struct sockaddr_in server_socket_address);
void listenForConnections(int server_socket);
int acceptSocketConnection(int server_socket, struct sockaddr_in server_socket_address, socklen_t server_socket_address_length);
void receiveMessage(int server_socket, int server_accept_return);


#endif //SERVER_H
