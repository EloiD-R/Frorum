# Archi
## Archi-global :
> Chat will be anonymous so no need to manage accounts
> headers :
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


## Archi-réseau :
> - Serv : (localhost puis rpi)
> - client : (+server)
> - msg en json
> server send a messages he receives from a client to everyone (so chat is temporary), if you quit and join back you will not have the ancient messages

## Archi-tree :
> - chat:
>    - client
>      - front 
>        - CLI.c
>        - CLI.h
>      - back
>        - client.c
>        - client.h
>        - server.c
>        - server.h
>      - main.c
>      - main.h
>      
>      - server
>        - main.c
>        - server.c
>        - server.h

### --------------------------------------------------------------------------------------------------------------------

# Divide to win :
> - make the client able to send messages
>   - create client socket
>   - connect socket to server
>   - send message to server
>   - close socket to reuse it

> - make the server able to receive messages
>   - create server socket
>   - bind port
>   - listen for a connection
>   - accept the connection
>   - read message
>   - close

> - make the client able to receive messages
>   - create a client server socket
>   - create server socket
>   - bind port
>   - listen for a connection
>   - accept the connection
>   - read message
>   - print it on screen
>   - make the server send to all connected users the message when received

### --------------------------------------------------------------------------------------------------------------------

# TODO :
> // I made the TODO-LIST at a moment where i was already working on the project for a little moment, so it does not contain all the steps

> - [X] make client able to receive message(s) and display them
> - [X] remake architecture (make code look good and be in functions)
>  - [X] client
>  - [X] server
> - [X] manage logs in a better way
> - [ ] remake architecture (again) but in a really better way now i have more code
> - [ ] add a ping thing
> - [ ] recode getMessage function in a better way
> - [ ] make server resending what he receives
> - [ ] make server able to receive more than one connection
> - [ ] make server treating information to remove bad words for example
> - [ ] host server on my rpi
> - [ ] we'll see this later when i'll be moving from Frorum ultra light to Frorum Light
