#pragma once

#include <list>

#include "RType.hpp"
#include "Runtime/ECS/Components/Components.hpp"
#include "Runtime/ECS/Registry.hpp"

#include "Config.hpp"
#include "Utils.hpp"
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
        std::list<std::unique_ptr<RType::Network::Packet>> packetsQueue;
    };

    class Server
    {
        using Runtime = RType::Runtime::IRuntime;
        using Registry = RType::Runtime::ECS::Registry;

    public:
        Server();
        ~Server();
        void run();

        void handleCommand(const std::string &command);

        /**
         * @brief Main function called to handle network packets
         *
         * @param packet received packet
         * @param endpoint sender endpoint
         */
        void networkHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint);

        /**
         * @brief Check for all connected clients if they are still connected
         * (if they sent a packet in the last 5 seconds)
         */
        void networkClientsTimeoutChecker();

        /**
         * @brief Called when a client disconnect
         * Delete the entity associated with the client
         * Send a PLAYERDIE packet to all clients
         *
         * @param endpoint
         */
        void networkClientDisconnect(asio::ip::udp::endpoint &endpoint);

        /**
         * @brief Send a packet to all connected clients
         *
         * @param packet packet to send
         */
        void networkSendAll(RType::Network::Packet &packet);

        /**
         * @brief Function called when a client send a ENTITYMOVE packet
         * Include all the logic to move the entity (check collision, etc...)
         * Also check for cheat (if the client try to move to faster or to far)
         *
         * @param packet packet received (ENTITYMOVE)
         * @param endpoint sender endpoint
         */
        void networkEntityMoveHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint);

        Client &initClient(asio::ip::udp::endpoint &endpoint);

        void sendPacketToClient(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint);

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
        std::unordered_map<asio::ip::udp::endpoint, std::thread> m_clientsThread;

        std::unique_ptr<Config> m_config;
        std::thread m_commandThread;
    };
}; // namespace RType::Server
