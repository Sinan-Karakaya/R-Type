/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketControllableMove
*/

#ifndef PACKETCONTROLLABLEMOVE_HPP_
#define PACKETCONTROLLABLEMOVE_HPP_

#include "Network/Packet.hpp"

namespace RType::Network
{
    class PacketControllableMove : public Packet
    {
    public:
        PacketControllableMove(uint32_t entityId, float x, float y, float x_dir, float y_dir);
        PacketControllableMove(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketControllableMove() override = default;

        std::vector<char> serializeData() const override;

        uint32_t getEntityId() const { return m_entityId; };
        float getX() const { return m_x; };
        float getY() const { return m_y; };
        float getXDir() const { return m_x_dir; };
        float getYDir() const { return m_y_dir; };

    private:
        uint32_t m_entityId;
        float m_x;
        float m_y;
        float m_x_dir;
        float m_y_dir;
    };
} // namespace RType::Network

#endif /* !PACKETCONTROLLABLEMOVE_HPP_ */
