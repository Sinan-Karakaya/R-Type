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
    /**
     * @brief Object holding an asio::io_context
     * IoContext is used to run asynchronous operations on
     * sockets
     */
    class IOContextHolder
    {
    public:
        IOContextHolder() = default;
        ~IOContextHolder() = default;

        /**
         * @brief Get the io_context
         *
         * @return asio::io_context&
         */
        asio::io_context &operator*() { return m_ioContext; }

        /**
         * @brief Call run on the io_context
         *
         */
        void run() { m_ioContext.run(); }

        void stop() { m_ioContext.stop(); }

    private:
        asio::io_context m_ioContext;
    };
} // namespace RType::Network

#endif /* !IOCONTEXTHOLDER_HPP_ */
