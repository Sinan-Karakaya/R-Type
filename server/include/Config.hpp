#pragma once

#include <string>

namespace RType
{
    class Config
    {
    public:
        Config();
        ~Config() = default;
        void VerifConfig();
        int getPort();
        std::string getFileProject();

    private:
        std::string VerifyFile(const std::string &fileProject);
        int CheckValidPort(const std::string &port);

    private:
        std::string m_fileProject;
        unsigned int m_port;
    };
}; // namespace RType
