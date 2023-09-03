#include "back/client.h"

int main(){
    // Create client socket and manage errors.
    int clientSocket = createClientSocket();

    // Connect client to server and manage errors.
    struct sockaddr_in clientSocketAdress = connectToServer(clientSocket);

    // Use Pthread to handle receiving and sending at the same time.
    // Create the threads.
    pthread_t sendThread, receiveThread;
    pthread_create(&sendThread, NULL, *sendMessage, &clientSocket);
    pthread_create(&receiveThread, NULL, *receiveMessage, &clientSocket);

    while (1){
        pthread_join(sendThread, NULL);
        pthread_join(receiveThread, NULL);
    }

    close(clientSocket);

}