/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketEntityCreate
*/

#ifndef PACKETENTITYCREATE_HPP_
#define PACKETENTITYCREATE_HPP_

#include "Network/Packet.hpp"

namespace RType::Network
{
    class PacketEntityCreate : public Packet
    {
    public:
        PacketEntityCreate(RType::Utils::UUID entityUuid, const std::string &path, float x = 0, float y = 0);
        PacketEntityCreate(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketEntityCreate() override = default;

        std::vector<char> serializeData() const override;

        RType::Utils::UUID getEntityUuid() const { return m_entityUuid; }
        const std::string &getPath() const { return m_path; }

        float getX() const { return m_x; }
        float getY() const { return m_y; }

    private:
        RType::Utils::UUID m_entityUuid;
        std::string m_path;

        float m_x;
        float m_y;
    };
} // namespace RType::Network

#endif /* !PACKETENTITYCREATE_HPP_ */
