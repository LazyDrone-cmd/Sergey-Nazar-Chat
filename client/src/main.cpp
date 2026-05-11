#include <iostream>
#include "socket.h"

int main() {
    int socket = custom_socket();
    custom_bind(socket);
    custom_listen(socket);
    int client = custom_accept(socket);

    size_t buffer_size = 2048;
    char *buffer = (char *)malloc(sizeof(char) * buffer_size);
    size_t msg_size;
    while (true) {
        msg_size = custom_recv(client, buffer, buffer_size);
        if (msg_size > 0) {
            std::cout << buffer << std::endl;
        }
    }

    return 0;
}