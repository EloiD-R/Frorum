#include "back/client.h"

int main(){
    // Create client socket and manage errors.
    int clientSocket = createClientSocket();

    // Connect client to server and manage errors.
    struct sockaddr_in clientSocketAdress = connectToServer(clientSocket);


    while (1){
        sendMessage(clientSocket);
    }

    close(clientSocket);

}