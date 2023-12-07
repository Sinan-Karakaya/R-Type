/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** UDP
*/

#include "UDP.hpp"

namespace RType::Network
{
    UDP::UDP(asio::io_context &io_context, short port)
        : m_socket(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
    {
    }

    UDP::~UDP() {}

    void UDP::sendData(Packet &packet, const asio::ip::udp::endpoint &endpoint)
    {
        std::vector<char> data = packet.serialize();
        m_socket.async_send_to(asio::buffer(data), endpoint, [this](std::error_code error, std::size_t bytes_sent) {
            if (error)
                NETWORK_LOG_ERROR("Failed to send data: {0}", error.message());
        });
    }

    void UDP::receiveData(std::function<void(std::error_code, std::size_t, Packet &)> handler)
    {
        m_socket.async_receive_from(asio::buffer(m_recvBuffer), m_senderEndpoint,
            [this, handler](std::error_code error, std::size_t bytesRecvd) {
                std::vector<char> data(m_recvBuffer.begin(), m_recvBuffer.begin() + bytesRecvd);

                uint32_t packetSize = Packet::getPacketSizeFromBuffer(data);
                if (packetSize > bytesRecvd) {
                    NETWORK_LOG_WARN("Packet size is bigger than received bytes");
                    return;
                }



                receiveData(handler); // Continue listening
        });
    }

} // namespace RType::Network
