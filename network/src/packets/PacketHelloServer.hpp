/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#ifndef PACKETHELLOSERVER_HPP_
#define PACKETHELLOSERVER_HPP_

#include "Packet.hpp"

namespace RType::Network
{
    class PacketHelloServer : public Packet
    {
    public:
        PacketHelloServer();
        PacketHelloServer(float version, std::string projectName);
        PacketHelloServer(std::vector<char> &buffer);
        PacketHelloServer(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketHelloServer() override = default;

        std::vector<char> serializeData() const override;

        float getVersion() const { return m_version; };
        std::string getProjectName() const { return m_projectName; };

    private:
        float m_version;
        std::string m_projectName;
    };
} // namespace RType::Network

#endif /* !PACKETHELLOSERVER_HPP_ */
