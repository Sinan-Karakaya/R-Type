/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketEntityCreate
*/

#ifndef PACKETENTITYCREATE_HPP_
#define PACKETENTITYCREATE_HPP_

#include "../Packet.hpp"

namespace RType::Network
{
    class PacketEntityCreate : public Packet
    {
    public:
        PacketEntityCreate(uint32_t entityId, const std::string &path);
        PacketEntityCreate(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketEntityCreate() override = default;

        std::vector<char> serializeData() const override;

        uint32_t getEntityId() const { return m_entityId; }
        const std::string &getPath() const { return m_path; }

    private:
        uint32_t m_entityId;
        std::string m_path;
    };
} // namespace RType::Network

#endif /* !PACKETENTITYCREATE_HPP_ */
