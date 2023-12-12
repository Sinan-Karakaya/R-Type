/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** NetworkManager
*/

#include "NetworkManager.hpp"

namespace RType {
    NetworkManager::NetworkManager(const short &port)
        : m_ioContext(), m_udpServer(*m_ioContext, port)
    {}

    NetworkManager::~NetworkManager()
    {
        this->stop();
    }

    void NetworkManager::run()
    {
        SERVER_LOG_INFO("Starting NetworkManager...");
        m_thread = std::thread([this, &ioContext = m_ioContext, &udpServer = m_udpServer] {
            SERVER_LOG_INFO("Ready to receive incoming packets");
            udpServer.startReceive([this](RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint) {
                std::cout << packet.getType() << "from" << endpoint.address().to_string() << std::endl;
            });
            ioContext.run();
        });
    }

    void NetworkManager::stop()
    {
        SERVER_LOG_INFO("Stopping NetworkManager...");
        m_ioContext.stop();
        m_thread.join();
    }

}
