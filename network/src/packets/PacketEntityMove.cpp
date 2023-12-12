/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PacketEntityMove
*/

#include "PacketEntityMove.hpp"

namespace RType::Network
{
    PacketEntityMove::PacketEntityMove(int entityId, float x, float y, float x_dir, float y_dir)
        : Packet(PacketType::ENTITYMOVE), m_entityId(entityId), m_x(x), m_y(y), m_x_dir(x_dir), m_y_dir(y_dir)
    {
        m_dataSize = sizeof(int) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float);
    }

    PacketEntityMove::PacketEntityMove(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(PacketType::ENTITYMOVE), m_entityId(0), m_x(0), m_y(0), m_x_dir(0), m_y_dir(0)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        std::memcpy(&m_entityId, data, sizeof(int));
        data += sizeof(int);
        std::memcpy(&m_x, data, sizeof(float));
        data += sizeof(float);
        std::memcpy(&m_y, data, sizeof(float));
        data += sizeof(float);
        std::memcpy(&m_x_dir, data, sizeof(float));
        data += sizeof(float);
        std::memcpy(&m_y_dir, data, sizeof(float));
    }

    std::vector<char> PacketEntityMove::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(int) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float));
        char *data = buffer.data();

        std::memcpy(data, &m_entityId, sizeof(int));
        data += sizeof(int);
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
