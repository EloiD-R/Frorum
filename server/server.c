#include "server.h"


int createServerSocket(){
    // Create socket and check if it did it well, if not write it in logs and close program.
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Manage errors
    if(serverSocket == NETWORK_FUNCTIONS_ERROR_CODE){
        writeLog("Error while creating socket", ERROR);
        return ERROR;
    } else{
        writeLog( "Created successfully socket", LOG);
        return serverSocket;
    }
}


struct sockaddr_in createServerSockaddr_inStruct(){
    // Creating a sockaddr_in struct to store the IP and PORT.
    struct sockaddr_in serverSocket_address;
    memset(&serverSocket_address, 0, sizeof(serverSocket_address));

    serverSocket_address.sin_family = AF_INET;
    serverSocket_address.sin_addr.s_addr = INADDR_ANY;
    serverSocket_address.sin_port = htons(PORT);

    return serverSocket_address;
}


int bindServerSocket(int serverSocket, struct sockaddr_in serverSocket_address){
    // Bind socket and check if it did it well, if not close the program.
    int serverBindReturn = bind(serverSocket, (struct sockaddr*)&serverSocket_address, sizeof(serverSocket_address));
    // Check if message is gone well, write result in log file.
    if(serverBindReturn == NETWORK_FUNCTIONS_ERROR_CODE){
        writeLog("Error while binding", ERROR);
        return ERROR;
    } else{
        writeLog("Bound successfully the right port", LOG);
        printf("Bound port successfully");
        return 0;
    }
}


int listenForConnections(int serverSocket){
    // Listen for incoming connection and check if it did it well, if not close the program.
    int serverListenReturn = 1;
    while (serverListenReturn == 1){
        serverListenReturn = listen(serverSocket, SOMAXCONN);
    }
    // Check if message is gone well, write result in log file.
    if(serverListenReturn == NETWORK_FUNCTIONS_ERROR_CODE){
        writeLog("Error while listening", ERROR);
        return ERROR;
    } else{
        writeLog("Listened successfully and found 1 client", LOG);
        printf("\nListened successfully and found 1 client.");
        return 0;
    }
}


int acceptSocketConnection(int serverSocket, struct sockaddr_in serverSocketAddress, socklen_t serverSocketAddressLength){
    // Accept connection and check if it did it well, if not close the program.
    int clientSocket= accept(serverSocket, (struct sockaddr*)&serverSocketAddress, &serverSocketAddressLength);

    // Check if message is gone well, write result in log file.
    if(clientSocket == NETWORK_FUNCTIONS_ERROR_CODE){
        writeLog("Error while accepting client", ERROR);
        return ERROR;
    } else{
        writeLog("Accepted a new client successfully", LOG);
        printf("\nNew client accepted.");
        return clientSocket;
    }
}


// This function is making server to receive a message from a client
char* receiveMessage(int clientSocket){
    // Create a buffer to store the received message.
    char* buffer = (char*)malloc(MAX_BUFFER_SIZE);

    // Check if server received a message and if it did it well.
    ssize_t clientMessage = recv(clientSocket, buffer, sizeof(buffer), 0);

    // Check if client close connection.
    if(clientMessage == 0){
        writeLog("Client closed connection", LOG);
        printf("\nClient closed the connection\n");
        buffer[1] = '\0';
        return buffer;

    } else if (clientMessage != -1){ // If not and a message was received, print the message.
        buffer[clientMessage] = '\0';

        writeLog("Message received successfully from client", LOG);

        return buffer;
    }

    // Check if message is gone well, write result in log file.
    if(clientMessage == NETWORK_FUNCTIONS_ERROR_CODE){
        writeLog("Error while receiving", ERROR);
        free(buffer);
        closeProgramIfNeeded(ERROR);
    }
}


// This function is making the server to send a message to a client.
int sendMessage(int socket, char* message){
    // Send message :
    int sent_message = send(socket, message, strlen(message), 0);

    // Error handling :
    if(sent_message == NETWORK_FUNCTIONS_ERROR_CODE){
        writeLog("Error while sending", ERROR);
        return ERROR;
    } else{
        writeLog("Message sent successfully to server",  LOG);
        return 0;
    }
}


// This function is called to write logs in logs.txt
int writeLog(char* logMessage, int flag){
    // Open the file to write logs into
    FILE* logFile = NULL;
    logFile = fopen("./logs.txt", "a");

    // Get current timestamp.
    time_t timestamp = time( NULL );

    // Check if logs file had been opened.
    if(logFile != NULL) {
        // Check if the log is an error or a success.
        if(flag == ERROR){
            fprintf(logFile, "\n----------------------------------\nError : %s, function returned : %s, error occurred at time : %ld (timestamp)\n----------------------------------\n", strerror(errno), logMessage,  timestamp);
            fclose(logFile);
            return 1; // Function return code for writing successfully an error.
        } else{
            fprintf(logFile, "LOG : %s, occurred at time : %ld (timestamp)\n", logMessage, timestamp);
            fclose(logFile);
            return 0; // Function return code for writing successfully a log.
        }
    } else{
        perror("opening logs file");
        fclose(logFile);
        return -1; // Function return code for THE error.
    }
}


// Check if the program encountered a fatal error, if yes close it.
int closeProgramIfNeeded(int returnCode){
        if(returnCode == ERROR){
            printf("\n--------------------------------------------------\nFATAL ERROR, go check logs, program closing in 3s.\n--------------------------------------------------\n");
            sleep(3);
            exit(EXIT_FAILURE);
        } else{
            return 0; // Code for no errors
        }
}


// Create an instance of the server (will be useful for multithreading later (i think))
SocketPair createServerInstance() {
    SocketPair sockets;
    sockets.serverSocket = createServerSocket();
    if (sockets.serverSocket == ERROR) {
        closeProgramIfNeeded(ERROR);
    }

    struct sockaddr_in serverSockaddr_in = createServerSockaddr_inStruct();
    socklen_t serverSockaddr_inLength = sizeof(serverSockaddr_in);

    int bound = bindServerSocket(sockets.serverSocket, serverSockaddr_in);
    if (bound == ERROR) {
        closeProgramIfNeeded(ERROR);
    }

    printf("\nListening for incoming connections [...]");
    listenForConnections(sockets.serverSocket);

    sockets.clientSocket = acceptSocketConnection(sockets.serverSocket, serverSockaddr_in, serverSockaddr_inLength);
    if (sockets.clientSocket == ERROR) {
        closeProgramIfNeeded(ERROR);
    }

    return sockets;
}
