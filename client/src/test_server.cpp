/*
 * Simple loopback server for testing purposes
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <cstring>

// NOTE: Works only on linux yet
int main() {
    // Creating socket
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == -1) {
        std::cerr << "Socket acquiring error: " << std::strerror(errno) << std::endl;
        return 1;
    }

    // Binding the socket to 127.0.0.1:8083
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8083);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server, (sockaddr *)&addr, sizeof(addr)) == -1) {
        std::cerr << "Socket binding error: " << std::strerror(errno) << std::endl;
        close(server);
        return 1;
    }

    // Awaiting a connection
    if (listen(server, 1) == -1) {
        std::cerr << "Listening error: " << std::strerror(errno) << std::endl;
        close(server);
        return 1;
    }
    // Accepting the conection
    int client = accept(server, NULL, NULL);
    if (client == -1) {
        std::cerr << "Accepting client error: " << std::strerror(errno) << std::endl;
        close(server);
        return 1;
    }

    // Receiving a message (and printing it)
    // The message must be \0 terminated
    char buffer[1024];
    ssize_t message_size = recv(client, buffer, sizeof(buffer), 0);
    if (message_size == -1) {
        std::cerr << "Receiving error: " << std::strerror(errno) << std::endl;
        close(server);
        return 1;
    }
    std::cout << buffer << std::endl;
    
    // Sending received message back
    if (send(client, buffer, message_size, 0) == -1) {
        std::cerr << "Sending error: " << std::strerror(errno) << std::endl;
        close(server);
        return 1;
    }

    close(client);
    close(server);

    return 0;
}