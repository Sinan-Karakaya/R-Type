/*
** EPITECH PROJECT, 2023
** Project
** File description:
** client
*/

#include "RType.hpp"
#include "Client.hpp"
#include "Modules/modules.hpp"

int main(int ac, char **av)
{
    if ((ac == 2 && (std::string(av[1]) == "--help" || std::string(av[1]) == "-h")) || (ac != 1)) {
        std::cout << "Usage: ./client" << std::endl;
        return 84;
    }

    std::unique_ptr<RType::Client::Client> client;

    try {
        client = std::make_unique<RType::Client::Client>();
    } catch (std::exception &e) {
        CLIENT_LOG_ERROR("Exception caught during start: {0}", e.what());
        return 84;
    }
    client->run();
    return 0;
}
