/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#ifndef PACKETENTITYSPAWN_HPP_
#define PACKETENTITYSPAWN_HPP_

#include "../Packet.hpp"

namespace RType::Network
{
    class PacketEntitySpawn : public Packet
    {
    public:
        PacketEntitySpawn(int entityId, uint8_t entityType, float x, float y);
        PacketEntitySpawn(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketEntitySpawn() override = default;

        std::vector<char> serializeData() const override;

        int getEntityId() const { return m_entityId; };
        uint8_t getEntityType() const { return m_entityType; };
        float getX() const { return m_x; };
        float getY() const { return m_y; };

    private:
        int m_entityId;
        uint8_t m_entityType;
        float m_x;
        float m_y;
    };
} // namespace RType::Network

#endif /* !PACKETENTITYSPAWN_HPP_ */
