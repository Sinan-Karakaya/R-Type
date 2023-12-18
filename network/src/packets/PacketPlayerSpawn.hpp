/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#ifndef PACKETPLAYERSPAWN_HPP_
#define PACKETPLAYERSPAWN_HPP_

#include "../Packet.hpp"

namespace RType::Network
{
    class PacketPlayerSpawn : public Packet
    {
    public:
        PacketPlayerSpawn(uint32_t entityId, uint8_t color, float x, float y);
        PacketPlayerSpawn(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketPlayerSpawn() override = default;

        std::vector<char> serializeData() const override;

        uint32_t getEntityId() const { return m_entityId; };
        uint8_t getColor() const { return m_color; };
        float getX() const { return m_x; };
        float getY() const { return m_y; };

    private:
        uint32_t m_entityId;
        uint8_t m_color;
        float m_x;
        float m_y;
    };
} // namespace RType::Network

#endif /* !PACKETPLAYERSPAWN_HPP_ */
