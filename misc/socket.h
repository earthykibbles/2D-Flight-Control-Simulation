#pragma once
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

in {
    int sockfd, newsockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    char buffer[MAX_BUFFER_SIZE] = { 0 };

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return 1;
    }

    // Set server address
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind socket
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        std::cerr << "Binding failed" << std::endl;
        return 1;
    }

    // Listen for connections
    if (listen(sockfd, 5) < 0) {
        std::cerr << "Listening failed" << std::endl;
        return 1;
    }

    // Accept connection
    if ((newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len)) < 0) {
        std::cerr << "Acceptance failed" << std::endl;
        return 1;
    }

    // Receive and print data
    while (true) {
        int bytes_received = recv(newsockfd, buffer, MAX_BUFFER_SIZE, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            std::cout << "Received: " << buffer << std::endl;
        }
    }

    // Close sockets
    close(newsockfd);
    close(sockfd);

    return 0;
}