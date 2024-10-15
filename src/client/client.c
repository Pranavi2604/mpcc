// client.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "/home2/user19/mp/include/functions.h"

#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change this if your server is on a different IP
    server_addr.sin_port = htons(5669);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        return 1;
    }

    // Start a thread to receive messages from the server
    pthread_t recv_thread;
    if (pthread_create(&recv_thread, NULL, receive_messages, (void *)&sockfd) != 0) {
        perror("Failed to create thread for receiving messages");
        close(sockfd);
        return 1;
    }

    // Detach the thread so it can run independently
    pthread_detach(recv_thread);

    // Main loop for sending messages
    while (1) {
        printf("Enter message: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
        send_message(sockfd, buffer);
    }

    close(sockfd);
    return 0;
}

