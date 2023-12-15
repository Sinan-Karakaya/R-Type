/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#ifndef PACKETENTITYDIE_HPP_
#define PACKETENTITYDIE_HPP_

#include "../Packet.hpp"

namespace RType::Network
{
    class PacketEntityDie : public Packet
    {
    public:
        PacketEntityDie(uint32_t entityId);
        PacketEntityDie(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketEntityDie() override = default;

        std::vector<char> serializeData() const override;

        uint32_t getEntityId() const { return m_entityId; };

    private:
        uint32_t m_entityId;
    };
} // namespace RType::Network

#endif /* !PACKETENTITYDIE_HPP_ */
