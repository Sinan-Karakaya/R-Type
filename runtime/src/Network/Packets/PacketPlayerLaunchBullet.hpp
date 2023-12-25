/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#ifndef PACKETPLAYERLAUNCHBULLTET_HPP_
#define PACKETPLAYERLAUNCHBULLTET_HPP_

#include "Network/Packet.hpp"

namespace RType::Network
{
    class PacketPlayerLaunchBullet : public Packet
    {
    public:
        PacketPlayerLaunchBullet(uint32_t entityId);
        PacketPlayerLaunchBullet(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketPlayerLaunchBullet() override = default;

        std::vector<char> serializeData() const override;

        uint32_t getEntityId() const { return m_entityId; };

    private:
        uint32_t m_entityId;
    };
} // namespace RType::Network

#endif /* !PACKETPLAYERLAUNCHBULLTET_HPP_ */
