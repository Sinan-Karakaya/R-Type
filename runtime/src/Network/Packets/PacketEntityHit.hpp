/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#ifndef PACKETENTITYHIT_HPP_
#define PACKETENTITYHIT_HPP_

#include "Network/Packet.hpp"

namespace RType::Network
{
    class PacketEntityHit : public Packet
    {
    public:
        PacketEntityHit(uint32_t entityId);
        PacketEntityHit(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketEntityHit() override = default;

        std::vector<char> serializeData() const override;

        uint32_t getEntityId() const { return m_entityId; };

    private:
        uint32_t m_entityId;
    };
} // namespace RType::Network

#endif /* !PACKETENTITYHIT_HPP_ */
