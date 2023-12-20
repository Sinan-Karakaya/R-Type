/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** ClientNetworkHandler
*/

#ifndef CLIENTNETWORKHANDLER_HPP_
#define CLIENTNETWORKHANDLER_HPP_

#include "Runtime.hpp"
#include "Runtime/NetworkHandler.hpp"

#include "Network/UDPClient.hpp"
#include "Network/IOContextHolder.hpp"

#include "Utils/TimeUtils.hpp"

namespace RType::Runtime {
    class Runtime;

    class ClientNetworkHandler : public RType::Network::NetworkHandler {
    public:
        ClientNetworkHandler(std::unique_ptr<RType::Runtime::Runtime> runtime);
        ~ClientNetworkHandler() override;

        void init(const std::string &ip, int port) override;
        void destroy() override;
        
        void update() override;

        void sendToServer(const RType::Network::Packet &packet);

    private:
        std::unique_ptr<RType::Runtime::Runtime> m_runtime;

        std::unique_ptr<RType::Network::UDPClient> m_client;
        RType::Network::IOContextHolder m_ioContextHolder;

        long m_lastPing;
    };
}

#endif /* !CLIENTNETWORKHANDLER_HPP_ */
