/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** TCP
*/

#include "TCP.hpp"

namespace RType::Network {
    void TCP::sendData(asio::ip::tcp::socket &socket, const Packet &packet)
    {
        std::vector<char> data;
        try {
            data = packet.serialize();
        } catch (std::exception &e) {
            NETWORK_LOG_ERROR("Failed to serialize packet: {0}", e.what());
            return;
        }
        socket.async_send(asio::buffer(data), [this, &socket](const asio::error_code &error, std::size_t) {
            if (error) {
                NETWORK_LOG_ERROR("Error when send: {0}", error.message());
                return;
            }
        });
    }

    void TCP::receiveData(asio::ip::tcp::socket &socket, std::function<void(Packet &)> callback)
    {
        socket.async_receive(asio::buffer(m_recvBuffer, 4096),
            [this, &socket, callback](const asio::error_code &error, std::size_t bytesRecvd) {
                if (error) {
                    NETWORK_LOG_ERROR("Error when receive: {0}", error.message());
                    return;
                }

                std::vector<char> data(m_recvBuffer.begin(), m_recvBuffer.begin() + bytesRecvd);

                std::unique_ptr<Packet> packet;
                try {
                    packet = m_packetFactory.createPacket(data, bytesRecvd);
                } catch (PacketException &e) {
                    NETWORK_LOG_WARN("Failed to get packet from buffer: {0}", e.what());
                }
                if (packet.get() != nullptr) {
                    callback(*packet);
                }

                receiveData(socket, callback);
            });
    }
}