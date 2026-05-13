#ifndef SOCKET_H
#define SOCKET_H

#include <cstdint>
#include <optional>
#include <span>

namespace snc_socket {
    typedef std::uint32_t snc_ipv4;
    typedef std::uint16_t snc_port;
    class SNC_ClientSocket {
        public:
        // May throw std::runtime_error
        SNC_ClientSocket(snc_port port, snc_ipv4 target_ip, snc_port target_port);
        ~SNC_ClientSocket();
        // Returns amount of bytes sent if operation succeeded
        std::optional<std::size_t> send(std::span<const std::byte> data);
        // Returns amount of bytes received if operation succeded
        std::optional<std::size_t> recv(std::span<std::byte> data);
        private:
        int fd;
    };
}

#endif