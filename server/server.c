#include "server.h"

int main() {
    // Create socket and check if it did it well
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1) {
        perror("Error while creating socket");
        close(server_socket);
        exit(EXIT_FAILURE);
    } else{
        printf("Socket created successfully");
    }


    // Creating a sockaddr_in struct to store the IP and PORT.
    struct sockaddr_in server_socket_address;
    socklen_t server_socket_address_length = sizeof(server_socket_address);
    server_socket_address.sin_family = AF_INET;
    server_socket_address.sin_addr.s_addr = INADDR_ANY;
    server_socket_address.sin_port = htons(PORT);


    // Bind socket and check if it did it well.
    int server_bind_return = bind(server_socket, (struct sockaddr*)&server_socket_address, sizeof(server_socket_address));
    if(server_bind_return == -1) {
        perror("Error while binding");
        close(server_socket);
        exit(EXIT_FAILURE);
    } else{
        printf("\nSocket bound successfully");
    }

    // Listen for incoming connection and check if it did it well.
    printf("\nListening for incoming connections [...]");
    int server_listen_return = listen(server_socket, SOMAXCONN);
    if(server_listen_return == -1) {
        perror("Error while listening");
        close(server_socket);
        exit(EXIT_FAILURE);
    } else{
        printf("\nSocket listened successfully ans found one client.");
    }


    // Accept connection and check if it did it well.
    int server_accept_return = accept(server_socket, (struct sockaddr*)&server_socket_address, &server_socket_address_length);
    if(server_accept_return == -1) {
        perror("Error while accepting request");
        close(server_socket);
        exit(EXIT_FAILURE);
    } else{
        printf("A client connected successfully.");
    }

    // Create a buffer to store the received message.
    char buffer[MAX_BUFFER_SIZE];

    // Main loop:
    while (1) {
        // Check if server received a message and if it did it well.
        ssize_t server_receive_return = recv(server_accept_return, buffer, sizeof(buffer), 0);
        if(server_receive_return == -1){
            perror("receive");
            break;
        }
        // Check if client close connection.
        if(server_receive_return == 0){
            printf("\nClient closed connection.\n");
            break;
        } else{ // If not and a message was received, print the message.
            buffer[server_receive_return] = '\0';
            printf("Received \"%s\" from client.", buffer);
        }
    }

    // CLose socket before exiting.
    close(server_socket);

    return 0;
}