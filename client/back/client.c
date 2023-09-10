#include "client.h"


int createClientSocket(){
    // Create client socket and write result if logs, if it did it wrong close the program.
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == -1){
        writeLog(client_socket, "Error while creating socket", client_socket, 1);
    } else{
        writeLog(client_socket, "Socket created successfully", client_socket, 2);
    }
    return client_socket;
}


struct sockaddr_in connectToServer(int clientSocket){
    // Create a sockaddr_in struct to store the address and port the socket will be connected to.
    struct sockaddr_in client_socket_address;
    socklen_t client_socket_address_length = sizeof(client_socket_address);
    client_socket_address.sin_family = AF_INET;
    client_socket_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    client_socket_address.sin_port = htons(PORT);

    // Connect client to server and check if it did it well, write result in log, if it didn't work write it in logs file.
    int client_connection_return = connect(clientSocket, (struct sockaddr *)&client_socket_address, client_socket_address_length);

    if(client_connection_return == -1){
        writeLog(client_connection_return, "Error while connecting", clientSocket, 1);
    } else{
        writeLog(client_connection_return, "Client connected successfully to server", clientSocket, 2);
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

    if(sent_message == -1){
        writeLog(sent_message, "Error while sending", socket, 1);
    } else{
        writeLog(sent_message, "Message sent successfully to server", socket, 2);
    }

    pthread_exit(NULL);
}


void* receiveMessage(void* arg){
    int socket = *((int*)arg);

    // Receive message :
    char buffer[MAX_BUFFER_SIZE];
    ssize_t receiving_message_return = recv(socket, buffer, strlen(buffer), 0);

    if(receiving_message_return == -1){
        writeLog(receiving_message_return, "Error while receiving", socket, 1);
    } else{
        writeLog(receiving_message_return, "Message received successfully from server", socket, 2);
    }

    pthread_exit(NULL);
}


int writeLog(int functionReturn, char* logMessage, int socket, int flag){
    FILE* logFile = NULL;
    logFile = fopen("./logs.txt", "a");

    if(logFile != NULL) {
        if(flag == 1){
            if (functionReturn == -1) {
                time_t timestamp = time( NULL );
                fprintf(logFile, "Error : %s, time : %ld\n", strerror(errno), timestamp);
                printf("\nFatal Error, closing program in 3s.\n");
                sleep(3);
                close(socket);
                exit(EXIT_FAILURE);
            }
        } else{
            time_t timestamp = time( NULL );
            fprintf(logFile, "LOG : %s, time : %ld\n", logMessage, timestamp);
        }
    } else{
        perror("\nFATAL ERROR : can't open logs file, closing program in 3s.\n");
        sleep(3);
        close(socket);
        exit(EXIT_FAILURE);
    }

    fclose(logFile);
}