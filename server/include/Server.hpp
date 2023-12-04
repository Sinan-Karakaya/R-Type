#pragma once

#include <asio.hpp>

class Server
{
public:
    Server();
    void run();

private:
    std::string VerifyFile(const std::string &fileProject);
    int CheckValidPort(const std::string &port);
    void VerifConfig();
    std::string m_fileProject;
    unsigned int m_port;
    bool m_running;
};
