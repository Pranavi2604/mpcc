#ifndef client_fun_H
#define client_fun_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#define MAX_CLIENTS 100

FILE *log_file;

time_t t;

void send_message(int sockfd,const char *message);
void *receive_messages(void *arg); 
void encryption(char *text);
void decryption(char *text);


#endif 
