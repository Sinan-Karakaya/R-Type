/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketChangeScene
*/

#include "PacketChangeScene.hpp"

namespace RType::Network
{
    PacketChangeScene::PacketChangeScene(const std::string &sceneName) : Packet(CHANGESCENE), m_sceneName(sceneName)
    {
        m_dataSize = m_sceneName.size();
    }

    PacketChangeScene::PacketChangeScene(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        m_sceneName = std::string(data, size - getHeaderSize());
    }

    std::vector<char> PacketChangeScene::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(m_sceneName.size());
        char *data = buffer.data();

        std::memcpy(data, m_sceneName.c_str(), m_sceneName.size());
        return buffer;
    }
} // namespace RType::Network
