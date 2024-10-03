#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define INPUT_BUFSIZE 512
#define PORT 4488

char *usrinput(void) {
    char *buf = malloc(INPUT_BUFSIZE * sizeof(char));
    int c, i;

    for (i = 0; i < INPUT_BUFSIZE - 1; i++) {
        c = getchar();

        if (c == '\n' || c == EOF) {
            break;
        }

        buf[i] = c;
    }

    buf[i + 1] = '\0';
    return buf;
}

int main(void) {
    printf("Welcome to the chatroom!\n");

    printf("Enter your name to start chatting: ");

    char *input = usrinput();

    printf("You inputed: %s\n", input);

    free(input);

    server();
}
