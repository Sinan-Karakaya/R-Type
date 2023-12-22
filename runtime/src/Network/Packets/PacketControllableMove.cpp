/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PacketControllableMove
*/

#include "PacketControllableMove.hpp"

namespace RType::Network
{
    PacketControllableMove::PacketControllableMove(uint32_t entityId, float x, float y, float x_dir, float y_dir)
        : Packet(PacketType::CONTROLLABLEMOVE), m_entityId(entityId), m_x(x), m_y(y), m_x_dir(x_dir), m_y_dir(y_dir)
    {
        m_dataSize = sizeof(uint32_t) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float);
    }

    PacketControllableMove::PacketControllableMove(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type), m_entityId(0), m_x(0), m_y(0), m_x_dir(0), m_y_dir(0)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        std::memcpy(&m_entityId, data, sizeof(uint32_t));
        data += sizeof(uint32_t);
        std::memcpy(&m_x, data, sizeof(float));
        data += sizeof(float);
        std::memcpy(&m_y, data, sizeof(float));
        data += sizeof(float);
        std::memcpy(&m_x_dir, data, sizeof(float));
        data += sizeof(float);
        std::memcpy(&m_y_dir, data, sizeof(float));
    }

    std::vector<char> PacketControllableMove::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(uint32_t) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float));
        char *data = buffer.data();

        std::memcpy(data, &m_entityId, sizeof(uint32_t));
        data += sizeof(uint32_t);
        std::memcpy(data, &m_x, sizeof(float));
        data += sizeof(float);
        std::memcpy(data, &m_y, sizeof(float));
        data += sizeof(float);
        std::memcpy(data, &m_x_dir, sizeof(float));
        data += sizeof(float);
        std::memcpy(data, &m_y_dir, sizeof(float));
        return buffer;
    }
} // namespace RType::Network
