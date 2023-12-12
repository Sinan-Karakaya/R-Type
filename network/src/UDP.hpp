/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** UDP
*/

#ifndef UDP_HPP_
#define UDP_HPP_

#include <asio.hpp>
#include <string>
#include <vector>

#include "utils/Logger.hpp"
#include "PacketFactory.hpp"

namespace RType::Network
{
    class UDP
    {
    public:
        /**
         * @brief Construct a new UDP object
         *
         * @param io_context context of the io service
         * @param port port to listen on, 0 to let the system choose one
         */
        UDP(asio::io_context &io_context, const short &port);
        virtual ~UDP();

        /**
         * @brief Send asynchronously a packet to an endpoint
         *
         * @param packet The packet to send
         * @param endpoint  The endpoint to send the packet to
         * @param handler callback function called when the packet is sent
         */
        void sendData(const Packet &packet, const asio::ip::udp::endpoint &endpoint,
                      const std::function<void(std::error_code, std::size_t)> &handler = nullptr);

        /**
         * @brief Receive asynchronously a packet, receiveData call itself
         * when a packet is received to be ready to receive the next one
         *
         * @param handler callback function called when a packet is received,
         * the packet and the sender endpoint are passed as parameters
         */
        void receiveData(const std::function<void(Packet &, asio::ip::udp::endpoint &endpoint)> &handler);

    protected:
        asio::ip::udp::socket m_socket;

        std::array<char, 4096> m_recvBuffer;
        asio::ip::udp::endpoint m_senderEndpoint;

    private:
        PacketFactory m_packetFactory;
    };
} // namespace RType::Network

#endif /* !UDP_HPP_ */
