/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** main
*/

#include "Server.hpp"
#include <iostream>
#include <memory>

/**
 * Do not add any other functions than main() here.
 * This is required for the tests to work.
 */

int main(int ac, char **av)
{
    if ((ac == 2 && (std::string(av[1]) == "--help" || std::string(av[1]) == "-h"))) {
        std::cout << "Usage: ./server" << std::endl;
        return 0;
    }
    std::unique_ptr<RType::Server::Server> server;
    try {
        server = std::make_unique<RType::Server::Server>();
    } catch (std::exception &e) {
        SERVER_LOG_ERROR("Exception caught during start: {0}", e.what());
    }
    server->run();
    return 0;
}
