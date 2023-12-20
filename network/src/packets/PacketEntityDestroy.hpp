/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketEntityDestroy
*/

#ifndef PACKETENTITYDESTROY_HPP_
#define PACKETENTITYDESTROY_HPP_

#include "../Packet.hpp"

namespace RType::Network {
    class PacketEntityDestroy : public Packet {
      public:
        PacketEntityDestroy(uint32_t entityId);
        PacketEntityDestroy(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketEntityDestroy() override = default;

        std::vector<char> serializeData() const override;

        uint32_t getEntityId() const { return m_entityId; }

      private:
        uint32_t m_entityId;
    };
}

#endif /* !PACKETENTITYDESTROY_HPP_ */
