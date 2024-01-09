/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** ClientNetworkHandler
*/

#ifndef CLIENTNETWORKHANDLER_HPP_
#define CLIENTNETWORKHANDLER_HPP_

#include "Runtime/IRuntime.hpp"
#include "Runtime/NetworkHandler.hpp"

#include "Network/IOContextHolder.hpp"
#include "Network/UDP/UDPClient.hpp"

#include "Serializer/Serializer.hpp"

#include "Utils/TimeUtils.hpp"

namespace RType::Runtime
{

    class RTYPE_EXPORT ClientNetworkHandler : public RType::Network::NetworkHandler
    {
    public:
        ClientNetworkHandler(std::shared_ptr<RType::Runtime::IRuntime> runtime);
        ~ClientNetworkHandler() override;

        void init(const std::string &ip, int port) override;
        void destroy() override;

        void update() override;

        void sendToServer(const RType::Network::Packet &packet);

        void setDisconnectCallback(std::function<void(const std::string &reason)> callback)
        {
            m_onDisconnect = callback;
        }
        float getLatency() const { return m_latency; }

    private:
        void packetsHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint);

        void entityShowHandler(RType::Network::Packet &packet);
        void entityHideHandler(RType::Network::Packet &packet);
        void entityMoveHandler(RType::Network::Packet &packet);
        void entityCreateHandler(RType::Network::Packet &packet);
        void entityDestroyHandler(RType::Network::Packet &packet);
        void entityUpdateHandler(RType::Network::Packet &packet);

        std::shared_ptr<RType::Runtime::IRuntime> m_runtime;

        std::unique_ptr<RType::Network::UDPClient> m_client;
        RType::Network::IOContextHolder m_ioContextHolder;

        std::function<void(const std::string &reason)> m_onDisconnect;

        RType::Runtime::ECS::Entity m_clientEntity;
        long m_lastPing;
        long m_lastReceivedPing;
        float m_latency;
    };
} // namespace RType::Runtime

#endif /* !CLIENTNETWORKHANDLER_HPP_ */
