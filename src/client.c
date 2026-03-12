//implementation based off https://www.geeksforgeeks.org/c/socket-programming-cc/
//biggest difference is I changed the protocol from TCP to UDP

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main()
{
    int status, valread, client_fd;          
    struct sockaddr_in server_addr;
    char* msg = "hello from my mac";
    char buffer[1024] = { 0 };

    //SOCK_DGRAM specifies UDP communication, which is used in production DNS servers

    if((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("\n socket creation error \n");
	return -1;
    }
    
    server_addr.sin_family = AF_INET; //AF_INET is the "address family constant" for IPv4       
    server_addr.sin_port = htons(PORT); //converts ip port from hosts byte order to big endian

    //inet_pton - internet presentation to network
    //converts string ip addr to compact binary big endian    
    //127.0.0.1 is IPv4 localhost - meaning this code just messages myself over the network

    if(inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        printf("\n invalid address \n");
        return -1;
    }

    //casts sockaddr_in ptr to sockaddr ptr - which is legal bc sockaddr and sockaddr_in are part of a union
 
    if ((status = connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0) {
        printf("\n connection failed \n");
    }
    
    send(client_fd, msg, strlen(msg), 0); //send msg
    printf("msg sent\n"); 
    valread = read(client_fd, buffer, 1024-1); //recieve msg
    printf("%s\n", buffer); //print msg
    close(client_fd);
    return 0;
}
