#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "commands.h"

#define MAX_PENDING 5
#define MAX_LINE    256

int main(int argc, char *argv[]) {
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    char response[MAX_LINE];
    int buf_len, addr_len;
    int s, new_s;

    // Check command line arguments to ensure correct usage
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    // Convert argument to integer port number
    int port = atoi(argv[1]);
    if (port <= 0) {
        fprintf(stderr, "Error: Invalid port number\n");
        exit(1);
    }

    // Setup address structure
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    // Create the socket
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("tcp_server: socket");
        exit(1);
    }

    // Bind the socket
    if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("tcp_server: bind");
        exit(1);
    }

    // Listen on the socket
    if (listen(s, MAX_PENDING) < 0) {
        perror("tcp_server: listen");
        exit(1);
    }

    printf("Server is running on port %d\n", port);

    // Accept and process connections indefinitely
    while (1) {
        if ((new_s = accept(s, (struct sockaddr *)&sin, (socklen_t *)&addr_len)) < 0) {
            perror("tcp_server: accept");
            continue;  // Continue accepting connections even if there's an error
        }
        while ((buf_len = recv(new_s, buf, sizeof(buf), 0)) > 0) {
            fputs("Received: ", stdout);
            fputs(buf, stdout);
            if (process(buf, response) < 0) {
                strcpy(response, "Invalid command\n");
            }
            send(new_s, response, strlen(response) + 1, 0);
        }
        close(new_s);
    }

    close(s);
    return 0;
}
