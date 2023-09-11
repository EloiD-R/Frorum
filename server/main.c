#include "server.h"


int main() {
    // Main loop.
    while (1) {
        SocketPair sockets = createServerInstance();
        int clientSocket = sockets.clientSocket;
        int serverSocket = sockets.serverSocket;


        while (1) {

            char *receivedMessage = receiveMessage(clientSocket);

            if (receivedMessage[1] == '\0') {
                free(receivedMessage);
                break;
            } else if (receivedMessage[1] != -1) {
                printf("\nReceived : \"%s\" from client\n", receivedMessage);
                free(receivedMessage);
            }

        }

        // Close both client and server sockets before exiting.
        close(clientSocket);
        close(serverSocket);
    }
    return 0;
}
