/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** UDP
*/

#include "UDP.hpp"

namespace RType::Network
{
    UDP::UDP(short port) : m_socket(m_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)) {}

    UDP::UDP(const asio::ip::udp::endpoint &endpoint) : m_socket(m_context, endpoint) {}

    void UDP::sendData(std::vector<char> &data, const asio::ip::udp::endpoint &endpoint)
    {
        m_socket.async_send_to(asio::buffer(data), endpoint,
                               [this](std::error_code /*error*/, std::size_t /*bytes_sent*/) {
            // We don't need to implement this for now - 05/12/2023
        });
    }

    void UDP::receiveData(std::function<void(std::error_code, std::size_t, std::vector<char> &)> handler)
    {
        m_socket.async_receive_from(asio::buffer(m_recvBuffer), m_senderEndpoint,
                                    [this, handler](std::error_code error, std::size_t bytesRecvd) {
            std::vector<char> receivedData(m_recvBuffer.begin(), m_recvBuffer.begin() + bytesRecvd);
            handler(error, bytesRecvd, receivedData);
            receiveData(handler); // Continue listening
        });
    }

} // namespace RType::Network
