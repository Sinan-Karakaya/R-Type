/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** ClientNetworkHandler
*/

#include "ClientNetworkHandler.hpp"

namespace RType::Runtime {
    ClientNetworkHandler::ClientNetworkHandler(std::unique_ptr<RType::Runtime::Runtime> runtime)
        : m_runtime(std::move(runtime))
    {
    }

    ClientNetworkHandler::~ClientNetworkHandler()
    {
        destroy();
    }

    void ClientNetworkHandler::init(const std::string &ip, int port)
    {
        m_client = std::make_unique<RType::Network::UDPClient>(*m_ioContextHolder, ip, port);

        m_client->receiveData([this](RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint) {
            RTYPE_LOG_CRITICAL("Received packet {0} from server !", packet.getType());
        });
        m_ioContextHolder.run();

        m_lastPing = Utils::TimeUtils::getCurrentTimeMillis();
    }

    void ClientNetworkHandler::destroy()
    {
        m_ioContextHolder.stop();
    }

    void ClientNetworkHandler::update()
    {
        if (Utils::TimeUtils::getCurrentTimeMillis() - m_lastPing > 1000) {
            m_lastPing = Utils::TimeUtils::getCurrentTimeMillis();
            sendToServer(RType::Network::PacketPing());
        }
    }

    void ClientNetworkHandler::sendToServer(const RType::Network::Packet &packet)
    {
        m_client->sendToServer(packet);
    }
} // namespace RType::Runtime

