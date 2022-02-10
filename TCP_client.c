// Programmer: Jordan DeGiacomo
// 

#include <stdio.h>
#include <stdlib.h>

// include types and sockets for definitions about the socket functions that we are using
#include <sys/types.h>
#include <sys/socket.h>	    // most of the functionality and API we will be using
#include <unistd.h>         

// store address information
#include <netinet/in.h>

int main() {
	
// creation of the socket, store result of socket call here
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);       // socket function call, (AF_INET constant defined, SOCK_STREAM = TCP socket, specified the protocol)

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;    // sets the family of the address so it knows what type of address were working with
    server_address.sin_port = htons(9002);  // specify the port (could pass it in as an int), htnos converts the int to the right data format
    server_address.sin_addr.s_addr = INADDR_ANY;              // server_address structure holding some info about the address, sin.addr structure containing one field holding data of address itself
    
    // call connect fuction, returns an integer of success/failure, 0 = ok, -1 = not ok
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    // check for error with connection
    if (connection_status == -1) {
        printf("There was an error making a connection to the remote socket \n\n");
    }
    
    // call the receive function, pass the socket to the recv function
    // need some place to hold the data, char server_respose, optional flags parameter left at 0
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    // print out the data that we received back
    printf("the server sent the data: %s\n", server_response);

    // and then close the socket
    close(network_socket);

    return 0;
}
