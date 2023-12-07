/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** NetworkException
*/

#ifndef NETWORKEXCEPTION_HPP_
#define NETWORKEXCEPTION_HPP_

#include <string>
#include <exception>

namespace RType::Network {

    class NetworkException : public std::exception {
    public:
        NetworkException(std::string const &message) : _message(message) {};
        ~NetworkException() override = default;

    public:
        const char *what() const noexcept override { return _message.c_str(); };

    private:
        std::string _message;
    };

    class PacketException : public NetworkException {
    public:
        PacketException(std::string const &message) : NetworkException(message) {};
        ~PacketException() override = default;
    };
}

#endif /* !NETWORKEXCEPTION_HPP_ */
