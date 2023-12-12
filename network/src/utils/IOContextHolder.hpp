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
        ~IOContextHolder() { stop(); };

        /**
         * @brief Get the io_context
         *
         * @return asio::io_context&
         */
        asio::io_context &operator*() { return m_ioContext; }

        /**
         * @brief Call run on the io_context, this
         * will start the io_context in a new thread
         */
        void run()
        {
            m_thread = std::thread([this] {
                m_ioContext.run();
            });
        }
    
        /**
         * @brief Stop the io_context
         * 
         */
        void stop()
        {
            m_ioContext.stop();
            if (m_thread.joinable())
                m_thread.join();
        }

    private:
        asio::io_context m_ioContext;
        std::thread m_thread;
    };
} // namespace RType::Network

#endif /* !IOCONTEXTHOLDER_HPP_ */
