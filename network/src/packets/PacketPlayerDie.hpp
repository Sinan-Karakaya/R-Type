/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#ifndef PACKETPLAYERDIE_HPP_
#define PACKETPLAYERDIE_HPP_

#include "../Packet.hpp"

namespace RType::Network
{
    class PacketPlayerDie : public Packet
    {
    public:
        PacketPlayerDie(int entityId);
        PacketPlayerDie(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketPlayerDie() override = default;

        std::vector<char> serializeData() const override;

        int getEntityId() const { return m_entityId; };

    private:
        int m_entityId;
    };
} // namespace RType::Network

#endif /* !PACKETPLAYERDIE_HPP_ */
