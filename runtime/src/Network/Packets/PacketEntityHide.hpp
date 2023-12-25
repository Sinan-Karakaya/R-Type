/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketEntityHide
*/

#ifndef PACKETENTITYHIDE_HPP_
#define PACKETENTITYHIDE_HPP_

#include "Network/Packet.hpp"

namespace RType::Network
{
    class PacketEntityHide : public Packet
    {
    public:
        PacketEntityHide(uint32_t entityId);
        PacketEntityHide(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketEntityHide() override = default;

        std::vector<char> serializeData() const override;

        uint32_t getEntityId() const { return m_entityId; };

    private:
        uint32_t m_entityId;
    };
} // namespace RType::Network

#endif /* !PACKETENTITYHIDE_HPP_ */
