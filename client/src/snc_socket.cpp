#include "snc_socket.hpp"
#include <stdexcept>

#ifdef __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace snc_socket {
    SNC_ClientSocket::SNC_ClientSocket(snc_ipv4 target_ip, snc_port target_port) {
        this->fd = socket(AF_INET, SOCK_STREAM, 0);
        if (this->fd == -1) { throw std::runtime_error("Couldn't acquire the socket"); }
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(target_port);
        addr.sin_addr.s_addr = htonl(target_ip);
        if (connect(this->fd, (sockaddr *)&addr, sizeof(addr)) == -1) {
            close(this->fd);
            throw std::runtime_error("Couldn't connect to target");
        }
    }
    SNC_ClientSocket::~SNC_ClientSocket() {
        close(this->fd);
    }
    std::optional<std::size_t> SNC_ClientSocket::send(std::span<const std::byte> data) {
        ssize_t num_of_bytes = ::send(this->fd, data.data(), data.size_bytes(), 0);
        if (num_of_bytes == -1) { return std::nullopt; }
        return static_cast<std::size_t>(num_of_bytes);
    }
    std::optional<std::size_t> SNC_ClientSocket::recv(std::span<std::byte> data) {
        ssize_t num_of_bytes = ::recv(this->fd, data.data(), data.size_bytes(), 0);
        if (num_of_bytes == -1) { return std::nullopt; }
        return static_cast<std::size_t>(num_of_bytes);
    }
}
#elif defined(_WIN32)
// Windows implementation
#endif
