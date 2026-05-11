#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>

// Creating ipv4 TCP socket 
int custom_socket();

// Binding a socket to 0.0.0.0:8083
int custom_bind(int socket);

// Starts listening
int custom_listen(int socket);

// Accept a connection
int custom_accept(int socket);

// Send a message
ssize_t custom_send(int socket, void *buffer, size_t buffer_size);

// Receive a message
ssize_t custom_recv(int socket, void *buffer, size_t buffer_size);

#endif