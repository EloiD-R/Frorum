#include "server.h"

int createServerInstance(){
    int serverSocket = createServerSocket();
    if(serverSocket== ERROR){close(serverSocket); closeProgramIfNeeded(serverSocket);}

    struct sockaddr_in serverSockaddr_in = createServerSockaddr_inStruct();
    socklen_t serverSockaddr_inLength = sizeof(serverSockaddr_in);

    int bound = bindServerSocket(serverSocket, serverSockaddr_in);
    if(bound == ERROR){close(serverSocket); closeProgramIfNeeded(bound);}

    printf("\nListening for incoming connections [...]");
    listenForConnections(serverSocket);

    int clientSocket = acceptSocketConnection(serverSocket, serverSockaddr_in, serverSockaddr_inLength);
    if(clientSocket == ERROR){close(serverSocket); closeProgramIfNeeded(clientSocket);}

    return clientSocket, serverSocket;
}

int main() {
    int clientSocket, serverSocket = createServerInstance();
    int clientConnection = 0;

    // Main loop:
    while (clientConnection == 0){
        clientConnection = receiveMessage(clientSocket);
        if(clientConnection == 0){
            break;
        }
    }
    // CLose socket before exiting.
    close(serverSocket);

    return 0;
}