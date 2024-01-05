/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketChangeScene
*/

#ifndef PACKETCHANGESCENE_HPP_
#define PACKETCHANGESCENE_HPP_

#include "Network/Packet.hpp"

namespace RType::Network
{
    class PacketChangeScene : public Packet {
      public:
        PacketChangeScene(const std::string &sceneName);
        PacketChangeScene(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketChangeScene() override = default;

        std::vector<char> serializeData() const override;

        const std::string &getSceneName() const { return m_sceneName; }

      private:
        std::string m_sceneName;
    };
} // namespace RType::Network

#endif /* !PACKETCHANGESCENE_HPP_ */
