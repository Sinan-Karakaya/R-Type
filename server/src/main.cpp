#include "Server.hpp"
#include <iostream>

/**
 * Do not add any other functions than main() here.
 * This is required for the tests to work.
 */

int main(int ac, char **av)
{
    if ((ac == 2 && (std::string(av[1]) == "--help" || std::string(av[1]) == "-h"))) {
        std::cout << "Usage: ./server <port> <fileProject>" << std::endl;
        std::cout << "  <port>         Port to listen on" << std::endl;
        std::cout << "  <fileProject>  File containing the project to serve, the name is project.json" << std::endl;
        return 0;
    }
    try {
        Server server;
        server.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
