#include "server.h"

int main(){
    int server_socket = createServerSocket();

    struct sockaddr_in serverSockaddr_in = createServerSockaddr_inStruct();
    socklen_t serverSockaddr_inLength = sizeof(serverSockaddr_in);

    bindServerSocket(server_socket, serverSockaddr_in);

    listenForConnections(server_socket);

    int server_accept_return = acceptSocketConnection(server_socket, serverSockaddr_in, serverSockaddr_inLength);




    // Main loop:
    while (1) {
        receiveMessage(server_socket, server_accept_return);
    }

    // CLose socket before exiting.
    close(server_socket);

    return 0;
}