#pragma once

#include "RType.hpp"
#include "Runtime/ECS/Components/Components.hpp"
#include "Runtime/ECS/Registry.hpp"

#include "Config.hpp"
#include <memory>

#include "UDPServer.hpp"
#include "utils/IOContextHolder.hpp"

RType::Runtime::IRuntime *RuntimeEntry();
void RuntimeDestroy(RType::Runtime::IRuntime *runtime);

namespace RType::Server
{
    struct Client {
        uint32_t id;
        long lastPing;
    };

    class Server
    {
        using Runtime = RType::Runtime::IRuntime;
        using Registry = RType::Runtime::ECS::Registry;

    public:
        Server();
        ~Server();
        void run();

        void networkHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint);
        void networkClientsTimeoutChecker();
        void networkSendAll(RType::Network::Packet &packet);

        void networkEntityMoveHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint);

    private:
        long m_startingTimestamp;

        std::string m_fileProject;
        unsigned int m_port;

        bool m_running;
        std::unique_ptr<Runtime> m_runtime;
        void *m_libHandle;

        RType::Network::IOContextHolder m_ioContext;
        std::unique_ptr<RType::Network::UDPServer> m_udpServer;
        std::unordered_map<asio::ip::udp::endpoint, Client> m_clients;

        std::unique_ptr<Config> m_config;
    };
}; // namespace RType::Server
