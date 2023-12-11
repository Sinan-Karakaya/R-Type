/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#include "PacketHelloServer.hpp"

namespace RType::Network
{

    PacketHelloServer::PacketHelloServer() : Packet(PacketType::HELLOSERVER) {}

    PacketHelloServer::PacketHelloServer(float version, std::string projectName)
        : Packet(PacketType::HELLOSERVER), m_version(version), m_projectName(projectName)
    {
        m_dataSize = sizeof(float) + m_projectName.size();
    }

    PacketHelloServer::PacketHelloServer(std::vector<char> &buffer) : Packet(buffer)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        std::memcpy(&m_version, data, sizeof(float));
        data += sizeof(float);
        m_projectName = std::string(data);
    }

    PacketHelloServer::PacketHelloServer(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        std::memcpy(&m_version, data, sizeof(float));
        data += sizeof(float);
        m_projectName = std::string(data);
    }

    std::vector<char> PacketHelloServer::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(float) + m_projectName.size());
        char *data = buffer.data();

        std::memcpy(data, &m_version, sizeof(float));
        data += sizeof(float);

        std::memcpy(data, m_projectName.c_str(), m_projectName.size());

        return buffer;
    }

} // namespace RType::Network
