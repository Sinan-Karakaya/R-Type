/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketEntityUpdate
*/

#ifndef PACKETENTITYUPDATE_HPP_
#define PACKETENTITYUPDATE_HPP_

#include "Network/Packet.hpp"

namespace RType::Network
{
    class PacketEntityUpdate : public Packet
    {
    public:
        PacketEntityUpdate(RType::Utils::UUID entityUuid, const std::string &components);
        PacketEntityUpdate(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketEntityUpdate() override = default;

        std::vector<char> serializeData() const override;

        RType::Utils::UUID getEntityUuid() const { return m_entityUuid; }
        std::string getComponents() const { return m_components; }

    private:
        RType::Utils::UUID m_entityUuid;
        std::string m_components;
    };
} // namespace RType::Network

#endif /* !PACKETENTITYUPDATE_HPP_ */
