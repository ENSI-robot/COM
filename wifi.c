#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define SERVER_IP "192.168.4.1" // Default IP for ESP32 in AP mode

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from PC\n";
    char buffer[1024] = {0};
    
    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }
    
    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }
    
    // Send data to the server
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    
    // Read response from the server
    int valread = read(sock, buffer, 1024);
    printf("Data received: %s\n", buffer);
    
    // Close the socket
    close(sock);
    
    return 0;
}