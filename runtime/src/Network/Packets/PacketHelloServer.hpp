/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#ifndef PACKETHELLOSERVER_HPP_
#define PACKETHELLOSERVER_HPP_

#include "Network/Packet.hpp"

namespace RType::Network
{
    /**
     * @brief 4.1 PacketHelloServer
     * /---------------------------------------------------------\
     * | Name                           | Size (in bits) | Value |
     * |--------------------------------|----------------|-------|
     * | Type                           | 8              | 0     |
     * | Runtime version (1.0|1.1, etc) | 32             |       |
     * | Project name                   | 8 * length     |       |
     * \---------------------------------------------------------/
     */
    class RTYPE_EXPORT PacketHelloServer : public Packet
    {
    public:
        PacketHelloServer(float version, std::string projectName);
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
