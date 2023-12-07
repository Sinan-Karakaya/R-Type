/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** IOContextHolder
*/

#ifndef IOCONTEXTHOLDER_HPP_
#define IOCONTEXTHOLDER_HPP_

#include <asio.hpp>

namespace RType::Network
{
    class IOContextHolder
    {
    public:
        IOContextHolder() = default;
        ~IOContextHolder() = default;

        asio::io_context &operator*() { return m_ioContext; }

        void run() { m_ioContext.run(); }

    private:
        asio::io_context m_ioContext;
    };
} // namespace RType::Network

#endif /* !IOCONTEXTHOLDER_HPP_ */
