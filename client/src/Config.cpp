/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Config2
*/

#include "Config.hpp"

namespace RType::Client
{
    Config::Config(const std::string &file) : m_file(file)
    {
        std::ifstream stream(file);
        std::string line;

        if (!stream.is_open()) {
            SERVER_LOG_INFO("Config file {0} not found, creating default one", file);
            saveDefault({{"SERVER_IP", "127.0.0.1"}, {"SERVER_PORT", "4242"}});
            stream.open(file);
            if (!stream.is_open())
                throw std::runtime_error("Cannot open config file");
        }
        while (std::getline(stream, line)) {
            if (line.empty() || line[0] == '#')
                continue;
            size_t pos = line.find('=');
            if (pos == std::string::npos)
                throw std::runtime_error("Invalid config file");
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            m_fields[key] = value;
        }
    }

    Config::~Config() {}

    std::string &Config::getField(const std::string &field)
    {
        auto it = m_fields.find(field);

        static std::string defaultString;

        if (it == m_fields.end())
            return defaultString;
        return it->second;
    }

    void Config::setField(const std::string &field, const std::string &value)
    {
        m_fields[field] = value;
    }

    void Config::save()
    {
        std::ofstream stream(m_file);

        if (!stream.is_open())
            throw std::runtime_error("Cannot open config file");
        for (auto &it : m_fields)
            stream << it.first << "=" << it.second << std::endl;
    }

    void Config::saveDefault(const std::unordered_map<std::string, std::string> &fields)
    {
        std::ofstream stream(m_file);

        if (!stream.is_open())
            throw std::runtime_error("Cannot open config file");
        for (auto &it : fields)
            stream << it.first << "=" << it.second << std::endl;
    }

} // namespace RType::Client
