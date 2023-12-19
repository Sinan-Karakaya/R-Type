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

    class Client
    {
    public:
        Client() = default;
        Client(uint32_t id) : m_id(id), m_lastPing(Utils::getCurrentTimeMillis()) {}
        ~Client() = default;

        uint32_t getId() const { return m_id; }
        long getLastPing() const { return m_lastPing; }
        std::vector<std::shared_ptr<RType::Network::Packet>> &getWantedAckPackets() { return m_wantedAckPackets; }
        bool isConnected() const { return m_isConnected; }

        void setLastPing(long lastPing) { m_lastPing = lastPing; }
        void setConnected(bool connected) { m_isConnected = connected; }

    private:
        uint32_t m_id;
        long m_lastPing;
        std::vector<std::shared_ptr<RType::Network::Packet>> m_wantedAckPackets;
        bool m_isConnected = true;
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
        void networkSendAll(const RType::Network::Packet &packet);

        /**
         * @brief Function called when a client send a ENTITYMOVE packet
         * Include all the logic to move the entity (check collision, etc...)
         * Also check for cheat (if the client try to move to faster or to far)
         *
         * @param packet packet received (ENTITYMOVE)
         * @param endpoint sender endpoint
         */
        void networkEntityMoveHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint);

        void networkAckHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint);

        Client &initClient(asio::ip::udp::endpoint &endpoint);

        void clientThread(Client &client, asio::ip::udp::endpoint &endpoint);

        void sendPacketToClient(const RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint);

    private:
        long m_startingTimestamp;

        std::string m_fileProject;
        unsigned int m_port;

        bool m_running;
        std::unique_ptr<Runtime> m_runtime;
        void *m_libHandle;
        std::vector<RType::Runtime::ECS::Entity> m_controlledEntities;

        RType::Network::IOContextHolder m_ioContext;
        std::unique_ptr<RType::Network::UDPServer> m_udpServer;
        std::unordered_map<asio::ip::udp::endpoint, Client> m_clients;
        std::unordered_map<asio::ip::udp::endpoint, std::thread> m_clientsThreads;

        std::unique_ptr<Config> m_config;
        std::thread m_commandThread;
    };
}; // namespace RType::Server
