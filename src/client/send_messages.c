#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "/home2/user19/mp/include/functions.h"


void send_message(int sockfd,const char *message) {
    if (send(sockfd, message, strlen(message), 0) < 0) {
        perror("Send failed");
    }
}
