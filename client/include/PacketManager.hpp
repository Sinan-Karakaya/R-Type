/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PacketManager.hpp
*/

#include "Runtime/IRuntime.hpp"
#include "SFML/Window.hpp"
#include "UDPClient.hpp"
#include "utils/IOContextHolder.hpp"

namespace RType::Client
{
    class PacketManager
    {
    public:
        PacketManager() = delete;
        ~PacketManager() = delete;

        static void handlePackets(Network::Packet &packet, Runtime::IRuntime *runtime);

    private:
        static void handleHelloClient(Network::Packet &packet, Runtime::IRuntime *runtime);
        static void handleEntitySpawn(Network::Packet &packet, Runtime::IRuntime *runtime);
        static void handleEntityDie(Network::Packet &packet, Runtime::IRuntime *runtime);
        static void handleEntityMove(Network::Packet &packet, Runtime::IRuntime *runtime);
    };
} // namespace RType::Client
