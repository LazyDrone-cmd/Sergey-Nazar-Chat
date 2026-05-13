#include <iostream>
#include "snc_socket.hpp"
#include <span>
#include <cstring>

int main() {
    // Connecting to 127.0.0.1:8083
    snc_socket::SNC_ClientSocket client(0x7f000001, 8083);
    auto a = std::move(client);
    // The message being sent
    char buffer[1024] = "Hello from client!";
    // Sending the message (span + len (length of string + \0))
    if (!client.send(std::as_bytes(std::span(buffer, std::strlen(buffer) + 1))).has_value()) { return 1; }
    // Receiving the message
    if (!client.recv(std::as_writable_bytes(std::span(buffer))).has_value()) { return 1; }

    std::cout << buffer << std::endl;

    return 0;
}