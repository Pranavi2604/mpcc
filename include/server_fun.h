#ifndef server_fun__H
#define server_fun__H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#define MAX_CLIENTS 100
FILE *log_file;
time_t t;
void logger_init();
void logger(char *level, char *filename, int line_number, char *message, char *activity, char *event);
void broadcast_message(const char *message, int sender_id);
void *handle_client(void *arg);
int handle_authentication(int client_socket, const char *username, const char *password, int is_registration);
void encryption(char *text);
void decryption(char *text);
#endif
