/*
** EPITECH PROJECT, 2023
** Project
** File description:
** client
*/

#include "Client.hpp"
#include "Modules/modules.hpp"
#include "RType.hpp"

int main(int ac, char **av)
{
    if (
        (ac == 2 && (std::string(av[1]) == "--help" || std::string(av[1]) == "-h")) ||
        (ac != 3)
    ) {
        std::cout << "Usage: ./client [IP] [PORT]" << std::endl;
        std::cout << "Ex. ./client 127.0.0.1 4242" << std::endl;
        return 84;
    }

    std::string ip = av[1];
    short port = static_cast<short>(std::stoi(av[2]));
    std::unique_ptr<RType::Client::Client> client;

    try {
        client = std::make_unique<RType::Client::Client>(ip, port);
    } catch (std::exception &e) {
        CLIENT_LOG_ERROR("Exception caught during start: {0}", e.what());
        return 84;
    }
    client->run();
    return 0;
}
