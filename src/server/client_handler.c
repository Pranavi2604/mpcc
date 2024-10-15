// client_handler.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "/home2/user19/mp/include/functions.h"


extern int client_sockets[MAX_CLIENTS];
extern pthread_mutex_t mutex;

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    free(arg); // Free the allocated memory for client socket pointer
    char buffer[1024];

    // Add the new client socket to the list
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i] == 0) {
            client_sockets[i] = client_socket;
            break;
        }
    }
    pthread_mutex_unlock(&mutex);

    // Handle client communication
    while (1) {
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            break; // Connection closed
        }

        // Broadcast received message
        buffer[bytes_received] = '\0';
        printf("Received message: %s\n", buffer);
        broadcast_message(buffer, client_socket);
    }

    // Remove client socket from the list
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i] == client_socket) {
            client_sockets[i] = 0; // Mark as free
            break;
        }
    }
    pthread_mutex_unlock(&mutex);

    close(client_socket);
    return NULL;
}

