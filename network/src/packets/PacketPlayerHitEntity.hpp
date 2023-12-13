/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#ifndef PACKETPLAYERHITENTITY_HPP_
#define PACKETPLAYERHITENTITY_HPP_

#include "../Packet.hpp"

namespace RType::Network
{
    class PacketPlayerHitEntity : public Packet
    {
    public:
        PacketPlayerHitEntity(int entityId, int score);
        PacketPlayerHitEntity(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketPlayerHitEntity() override = default;

        std::vector<char> serializeData() const override;

        int getEntityId() const { return m_entityId; };
        int getScore() const { return m_score; };

    private:
        int m_entityId;
        int m_score;
    };
} // namespace RType::Network

#endif /* !PACKETPLAYERHITENTITY_HPP_ */
