/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#ifndef PACKETENTITYSHOW_HPP_
#define PACKETENTITYSHOW_HPP_

#include "Network/Packet.hpp"

namespace RType::Network
{
    class PacketEntityShow : public Packet
    {
    public:
        PacketEntityShow(uint32_t entityId, float x, float y);
        PacketEntityShow(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketEntityShow() override = default;

        std::vector<char> serializeData() const override;

        uint32_t getEntityId() const { return m_entityId; };
        float getX() const { return m_x; };
        float getY() const { return m_y; };

    private:
        uint32_t m_entityId;
        float m_x;
        float m_y;
    };
} // namespace RType::Network

#endif /* !PACKETENTITYSHOW_HPP_ */
