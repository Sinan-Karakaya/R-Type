/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketEntityDestroy
*/

#ifndef PACKETENTITYDESTROY_HPP_
#define PACKETENTITYDESTROY_HPP_

#include "../Packet.hpp"

namespace RType::Network
{
    class PacketEntityDestroy : public Packet
    {
    public:
        PacketEntityDestroy(RType::Utils::UUID entityUuid);
        PacketEntityDestroy(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketEntityDestroy() override = default;

        std::vector<char> serializeData() const override;

        RType::Utils::UUID getEntityUuid() const { return m_entityUuid; }

    private:
        RType::Utils::UUID m_entityUuid;
    };
} // namespace RType::Network

#endif /* !PACKETENTITYDESTROY_HPP_ */
