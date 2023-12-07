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

    void UDP::receiveData(std::function<void(Packet &, asio::ip::udp::endpoint &endpoint)> handler)
    {
        m_socket.async_receive_from(asio::buffer(m_recvBuffer), m_senderEndpoint,
                                    [this, handler](std::error_code error, std::size_t bytesRecvd) {
            std::vector<char> data(m_recvBuffer.begin(), m_recvBuffer.begin() + bytesRecvd);
                if (error) {
                    NETWORK_LOG_ERROR("Failed to receive data: {0}", error.message());
                    return;
                }

                std::unique_ptr<Packet> packet;
                try {
                    packet = m_packetFactory.createPacket(data, bytesRecvd);
                } catch (PacketException &e) {
                    NETWORK_LOG_WARN("Failed to get packet from buffer: {0}", e.what());
                }
                if (packet.get() != nullptr) {
                    handler(*packet, m_senderEndpoint);
                }

            receiveData(handler); // Continue listening
        });
    }

} // namespace RType::Network
