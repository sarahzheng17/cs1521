// A simple Web server
// Compile with dcc mime_web_server.c serve_web_page.c -o web_server

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "serve_web_page.h"

char *extract_pathname_http_request(char *http_request);
void handle_request(int client_fd);

int main(int argc, char **argv) {

    // create a IPv4 TCP/IP socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    // reuse the socket immediately if we restart the server
    int option = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &option, sizeof(option));

    struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
        .ai_flags = AI_PASSIVE,
    };

    // construct a port number unlikely to be in use by another COMP1521 student
    // and convert it to a struct addrinfo for the local machine
    struct addrinfo *a;
    char port[6];
    snprintf(port, sizeof port, "%d", 32000 + geteuid() % 32768);
    int s = getaddrinfo(NULL, port, &hints, &a);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(1);
    }

    // attach the address to the socket
    if (bind(sock_fd, a->ai_addr, a->ai_addrlen) != 0) {
        perror("bind()");
        return 1;
    }

    // specify the maximum number of connections that can be queued for the socket
    if (listen(sock_fd, 8) != 0) {
        perror("listen()");
        return 1;
    }

    printf("\nFrom your web browser test these URLs:\n");
    printf("http://localhost:%s/example.html\n", port);
    printf("http://localhost:%s/bird.html\n\n", port);

    int client_fd;
    while ((client_fd = accept(sock_fd, NULL, NULL)) >= 0) {
        handle_request(client_fd);
    }

    close(sock_fd);

    return 0;
}

// handle 1 request for a web page
void handle_request(int client_fd) {
    // a real server might spawn a client process here to handle the connection
    // so it can accept another connection immediately

    char http_request[4096];
    int n_bytes = read(client_fd, http_request, (sizeof http_request) - 1);
    http_request[n_bytes] = '\0';
    printf("Received this HTTP request:\n%s", http_request);

    // create a stdio stream to client
    FILE *client_stream = fdopen(client_fd, "r+");
    if (client_stream == NULL) {
        perror("fdopen");
        close(client_fd);
        return;
    }

    char *pathname = extract_pathname_http_request(http_request);

    if (pathname == NULL) {
        // not a request we can handle
        fputs(HEADER_400, client_stream);
    } else {
        printf("calling serve_web_page(\"%s\")\n", pathname);
        serve_web_page(pathname, client_stream);
        free(pathname);
    }

    fclose(client_stream);
}

// return a malloced string containing pathname from http request
// NULL is return if not a GET request
// NULL is returned if .. in pathname
// NULL is returned if pathname endswith .c
char *extract_pathname_http_request(char *http_request) {

    char *prefix = "GET /";
    if (strncmp(http_request, prefix, strlen(prefix)) != 0) {
        return NULL;
    }

    char *path_start = http_request + strlen(prefix);
    char *following_space = strchr(path_start, ' ');
    if (following_space == NULL) {
        return NULL;
    }
    int pathname_length = following_space - path_start;
    if (pathname_length < 1) {
        return NULL;
    }

    char *pathname = strndup(path_start, pathname_length);

    if (pathname == NULL) {
        return NULL;
    }

    if (strstr(pathname, "..") != NULL) {
        // prevent directory traversal
        free(pathname);
        return NULL;
    }

    if (pathname_length > 1 && strcmp(pathname + pathname_length - 2, ".c") == 0) {
        // prevent C source being served
        free(pathname);
        return NULL;
    }

    return pathname;
}

