/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketEntityMove
*/

#ifndef PACKETENTITYMOVE_HPP_
#define PACKETENTITYMOVE_HPP_

#include "Network/Packet.hpp"

namespace RType::Network
{
    class PacketEntityMove : public Packet
    {
    public:
        PacketEntityMove(RType::Utils::UUID entityUuid, float x, float y, float x_dir, float y_dir);
        PacketEntityMove(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketEntityMove() override = default;

        std::vector<char> serializeData() const override;

        RType::Utils::UUID getEntityUuid() const { return m_entityUuid; };
        float getX() const { return m_x; };
        float getY() const { return m_y; };
        float getXDir() const { return m_x_dir; };
        float getYDir() const { return m_y_dir; };

    private:
        RType::Utils::UUID m_entityUuid;
        float m_x;
        float m_y;
        float m_x_dir;
        float m_y_dir;
    };
} // namespace RType::Network

#endif
