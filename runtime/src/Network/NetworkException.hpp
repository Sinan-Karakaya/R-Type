/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** NetworkException
*/

#ifndef NETWORKEXCEPTION_HPP_
#define NETWORKEXCEPTION_HPP_

#include <exception>
#include <string>

namespace RType::Network
{

    class NetworkException : public std::exception
    {
    public:
        NetworkException(const std::string &message) : _message(message) {};
        ~NetworkException() override = default;

    public:
        const char *what() const noexcept override { return _message.c_str(); };

    private:
        std::string _message;
    };

    class PacketException : public NetworkException
    {
    public:
        PacketException(const std::string &message) : NetworkException(message) {};
        ~PacketException() override = default;
    };

    class ConnectionException : public NetworkException
    {
    public:
        ConnectionException(const std::string &message) : NetworkException(message) {};
        ~ConnectionException() override = default;
    };
} // namespace RType::Network

#endif /* !NETWORKEXCEPTION_HPP_ */
