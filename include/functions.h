// functions.h

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
 #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <unistd.h>
   #include <arpa/inet.h>
   #include <pthread.h>
#define MAX_CLIENTS 100

void broadcast_message(const char *message, int sender_id);
void *handle_client(void *arg);

void send_message(int sockfd, const char *message);
void *receive_messages(void *arg);

#endif // FUNCTIONS_H

