/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** ServerNetworkHandler
*/

#ifndef SERVERNETWORKHANDLER_HPP_
#define SERVERNETWORKHANDLER_HPP_

#include <unordered_map>

#include "Runtime/IRuntime.hpp"
#include "Runtime/NetworkHandler.hpp"

#include "Network/IOContextHolder.hpp"
#include "Network/UDPServer.hpp"

#include "Utils/TimeUtils.hpp"

namespace RType::Runtime
{
    struct ServerNetworkClient {
        uint32_t id;
        long lastPing;
        bool isConnected;
        long lastAckCheck;
        std::vector<std::shared_ptr<RType::Network::Packet>> wantedAckPackets;
    };

    class RTYPE_EXPORT ServerNetworkHandler : public RType::Network::NetworkHandler
    {
    public:
        ServerNetworkHandler(std::shared_ptr<RType::Runtime::IRuntime> &runtime);
        ~ServerNetworkHandler() override;

        void init(const std::string &ip, int port) override;
        void destroy() override;

        void update() override;

        void send(const RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint, bool ack = true);
        void sendToAll(const RType::Network::Packet &packet);

    private:
        void packetsHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint);

        void ackHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint);
        void entityMoveHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint);

        ServerNetworkClient &initClient(asio::ip::udp::endpoint &endpoint);
        void destroyClient(asio::ip::udp::endpoint &endpoint);

        void clientsTimeoutChecker();

        std::shared_ptr<RType::Runtime::IRuntime> m_runtime;

        std::unique_ptr<RType::Network::UDPServer> m_server;
        RType::Network::IOContextHolder m_ioContextHolder;

        std::vector<RType::Runtime::ECS::Entity> m_controllableEntities;

        std::unordered_map<asio::ip::udp::endpoint, ServerNetworkClient> m_clients;

        std::unordered_map<RType::Runtime::ECS::Entity, RType::Runtime::ECS::Components::Transform> m_transformsCache;
    };
} // namespace RType::Runtime

#endif /* !SERVERNETWORKHANDLER_HPP_ */
