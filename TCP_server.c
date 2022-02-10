#include <stdio.h>
#include <stdlib.h>

// include types and sockets for definitions about the socket functions that we are using
#include <sys/types.h>
#include <sys/socket.h>	    // most of the functionality and API we will be using
#include <unistd.h>         

// store address information
#include <netinet/in.h>

int main() {
    
    // string to hold the data we are going to send to all the clients
    char server_message[256] = "You have reached the server!";

    // create server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;    // constant that will resolve to any IP address on the local machine

    // bind the socket to our specialzed IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    listen(server_socket, 5);        // second parameter is how many clients can be waiting for this socket at any point in time

    // create an integer to hold the client socket
    // when you accept a connection what you get back is the client socket that you will then write to
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);   // (socket we are accepting connections on, structure of client, size of client)

    // send the message
    send(client_socket, server_message, sizeof(server_message), 0);    // (client, data, size, optional flags parameter)

    // close the socket
    close(server_socket);
    return 0;
}