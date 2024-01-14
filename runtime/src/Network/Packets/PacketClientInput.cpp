/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketClientInput
*/

#include "PacketClientInput.hpp"

namespace RType::Network
{
    PacketClientInput::PacketClientInput(const std::string &input) : Packet(CLIENTINPUT), m_input(input)
    {
        m_dataSize = m_input.size();
    }

    PacketClientInput::PacketClientInput(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        m_input = std::string(data, size - getHeaderSize());
    }

    std::vector<char> PacketClientInput::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(m_input.size());
        char *data = buffer.data();

        std::memcpy(data, m_input.c_str(), m_input.size());
        return buffer;
    }

} // namespace RType::Network
