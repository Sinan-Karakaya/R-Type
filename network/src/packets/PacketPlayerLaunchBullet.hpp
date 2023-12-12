/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#ifndef PACKETPLAYERLAUNCHBULLTET_HPP_
#define PACKETPLAYERLAUNCHBULLTET_HPP_

#include "../Packet.hpp"

namespace RType::Network
{
    class PacketPlayerLaunchBullet : public Packet
    {
    public:
        PacketPlayerLaunchBullet(int entityId, float x, float y, float dirX, float dirY);
        PacketPlayerLaunchBullet(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketPlayerLaunchBullet() override = default;

        std::vector<char> serializeData() const override;

        int getEntityId() const { return m_entityId; };
        float getX() const { return m_x; };
        float getY() const { return m_y; };
        float getDirX() const { return m_dirX; };
        float getDirY() const { return m_dirY; };

    private:
        int m_entityId;
        float m_x;
        float m_y;
        float m_dirX;
        float m_dirY;
    };
} // namespace RType::Network

#endif /* !PACKETPLAYERLAUNCHBULLTET_HPP_ */
