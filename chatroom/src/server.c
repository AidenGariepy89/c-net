#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "server.h"

void server(void) {
    struct addrinfo hints, *res, *rv;
    struct sockaddr_storage their_addr;
    int status, sockfd, newfd;
    int yes = 1;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(NULL, SERVER_PORT, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(1);
    }

    for (rv = res; rv != NULL; rv = rv->ai_next) {
        if ((sockfd = socket(rv->ai_family, rv->ai_socktype, rv->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("server: setsockopt");
            exit(1);
        }

        if (bind(sockfd, rv->ai_addr, rv->ai_addrlen) == -1) {
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(res);

    if (rv == NULL) {
        fprintf(stderr, "Failed to bind!\n");
        exit(1);
    }

    if (listen(sockfd, SERVER_BACKLOG) == -1) {
        perror("server: listen");
        exit(1);
    }

    while (1) {
        socklen_t sin_size = sizeof(their_addr);
        newfd = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size);
        if (newfd == -1) {
            perror("server: accept");
            exit(1);
        }

        if (send(newfd, "Greetings!\n", 12, 0) == -1) {
            perror("server: send");
            exit(1);
        }

        close(newfd);
    }
}
