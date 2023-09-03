#include "client.h"


int createClientSocket(){
    // Create client socket and write result if logs, if it did it wrong close the program.
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == -1){
        perror("Error while creating client socket");
        close(client_socket);
        exit(EXIT_FAILURE);
    } else{
        printf("Socket created successfully.");
    }
    return client_socket;
}


struct sockaddr_in connectToServer(int clientSocket){
        // Create a sockaddr_in struct to store the adress and port the socket will be connected to.
        struct sockaddr_in client_socket_address;
        socklen_t client_socket_address_length = sizeof(client_socket_address);
        client_socket_address.sin_family = AF_INET;
        client_socket_address.sin_addr.s_addr = inet_addr(SERVER_IP);
        client_socket_address.sin_port = htons(PORT);

        // Connect client to server and check if it did it well, write result in log, if it didn't work write it in logs file.
        int client_connection_return = connect(clientSocket, (struct sockaddr *)&client_socket_address, client_socket_address_length);
        if(client_connection_return == -1){
            perror("Error while connecting");
            close(clientSocket);
            exit(EXIT_FAILURE);
        } else{
            printf("\nSocket connected successfully.");
        }
    return client_socket_address;
}


void* sendMessage(void* arg){
    int socket = *((int*)arg);

    // Send message :
    char message[MAX_BUFFER_SIZE] = "TEST";
    char buffer;
    printf("\nPress ENTER to send \"TEST\"");
    scanf("%c", &buffer);
    int sent_message = send(socket, message, strlen(message), 0);

    // Check if message is gone well, write result in log, if it didn't work write it in logs file.
    if (sent_message == -1 /*failure code*/) {
        perror("Error while sending");
        close(socket);
        exit(EXIT_FAILURE);
    } else {
        // If yes print a message to say that it is good.
        printf("\nMessage have been sent : \"%s\" to '%s' on port '%d'\n", message, SERVER_IP, PORT);
    }
    pthread_exit(NULL);
}


void* receiveMessage(void* arg){
    int socket = *((int*)arg);

    // Receive message :
    char buffer[MAX_BUFFER_SIZE];
    ssize_t receiving_message_return = recv(socket, buffer, strlen(buffer), 0);

    // Check if message was sent correctly, write result in log, if it didn't work write it in logs file.
    if (receiving_message_return == -1 /*failure code*/) {
        perror("buffer while receiving");
        close(socket);
        exit(EXIT_FAILURE);
    } else {
        // If yes print the message to screen.
        printf("\nSMessage : %s", buffer);
    }
    pthread_exit(NULL);
}
