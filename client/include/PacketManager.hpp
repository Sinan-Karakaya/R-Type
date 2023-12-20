/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PacketManager.hpp
*/

#ifndef PACKETMANAGER_HPP_
#define PACKETMANAGER_HPP_

#include "Runtime/IRuntime.hpp"
#include "SFML/Window.hpp"
#include "UDPClient.hpp"
#include "utils/IOContextHolder.hpp"

namespace RType::Client
{
    class PacketManager
    {
    public:
        PacketManager(Runtime::IRuntime &runtime, Network::UDPClient &udpClient, uint32_t &clientId);
        ~PacketManager();

        void handlePackets(Network::Packet &packet);

    private:
        void handleHelloClient(Network::Packet &packet);
        void handleEntitySpawn(Network::Packet &packet);
        void handleEntityDie(Network::Packet &packet);
        void handleEntityMove(Network::Packet &packet);

        void sendAckPacket(Network::Packet &packet);

        Runtime::IRuntime &runtime;
        Network::UDPClient &udpClient;
        uint32_t &clientId;
    };
} // namespace RType::Client

#endif /* !PACKETMANAGER_HPP_ */
