#include <netinet/in.h>
#ifdef __linux__
#include <sys/socket.h>
#elifdef _WIN64
// Windows includes
#endif

#ifdef __linux__
int custom_socket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

int custom_bind(int socket) {
    sockaddr_in addr = sockaddr_in {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8083);
    addr.sin_addr.s_addr = INADDR_ANY;
    return bind(socket, (sockaddr *)&addr, sizeof(addr));
}

int custom_listen(int socket) {
    return listen(socket, 1);
}

int custom_accept(int socket) {
    return accept(socket, nullptr, 0);
}

ssize_t custom_send(int socket, void *buffer, size_t buffer_size) {
    return send(socket, buffer, buffer_size, 0);
}

ssize_t custom_recv(int socket, void *buffer, size_t buffer_size) {
    return recv(socket, buffer, buffer_size, 0);
}
#elifdef _WIN64
// Windows methods
#endif