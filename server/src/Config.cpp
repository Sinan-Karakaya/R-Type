#include "Config.hpp"
#include <memory>
#include <fstream>
#include <sstream>

namespace RType
{

Config::Config()
{
    this->m_port = 0;
    this->m_fileProject = "";
}

int Config::getPort()
{
    return this->m_port;
}

std::string Config::getFileProject()
{
    return this->m_fileProject;
}

void Config::VerifConfig()
{
    std::ifstream configFile("server.properties");

    if (!configFile.is_open())
        throw std::runtime_error("server.properties not found");
    std::string line;
    while (std::getline(configFile, line)) {
        std::istringstream iss(line);
        std::string key, value;
        std::getline(iss, key, '=');
        std::getline(iss, value);

        if (key == "PORT") {
            try {
                this->m_port = CheckValidPort(value);
            } catch (std::exception &e) {
                throw std::runtime_error("Invalid port");
            }
        } else if (key == "PROJECTDIR") {
            try {
                this->m_fileProject = VerifyFile(value);
            } catch (std::exception &e) {
                throw std::runtime_error("Invalid file");
            }
        }
    }
    configFile.close();
}

std::string Config::VerifyFile(const std::string &fileProject)
{
    std::ifstream configFile(fileProject);

    if (!configFile.is_open())
        throw std::runtime_error("File not found");
    configFile.close();
    if (fileProject.substr(fileProject.find_last_of(".") + 1) != "json")
        throw std::runtime_error("Invalid file");
    return fileProject;
}

int Config::CheckValidPort(const std::string &port)
{
    try {
        std::stoi(port);
    } catch (std::exception &e) {
        throw std::runtime_error("Invalid port");
    }
    int nb = std::stoi(port);
    if (nb < 1024 || nb > 65535)
        throw std::runtime_error("Invalid port");
    return std::stoi(port);
}
}
