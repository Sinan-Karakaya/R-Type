/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** UDPClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include "UDP.hpp"
#include <iostream>
#include <string>

namespace RType::Network
{
    class UDPClient : public UDP
    {
    public:
        UDPClient(const std::string &address, short port);
        ~UDPClient() = default;

        void sendToServer(std::vector<char> &data);
        void startReceiveFromServer();
    };
} // namespace RType::Network

#endif /* !UDPCLIENT_HPP_ */
