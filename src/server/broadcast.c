// broadcast.c

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "/home2/user19/mp/include/server_fun.h"


#define MAX_CLIENTS 100

extern int client_sockets[MAX_CLIENTS];
extern pthread_mutex_t mutex;

void broadcast_message(const char *message, int sender_id) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i] != 0 && client_sockets[i] != sender_id) {
            send(client_sockets[i], message, strlen(message), 0);
        }
    }
    pthread_mutex_unlock(&mutex);
}
