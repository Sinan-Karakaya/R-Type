/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Config2
*/

#include "Config.hpp"

namespace RType::Server
{
    Config::Config(const std::string &file) : m_file(file)
    {
        std::ifstream stream(file);
        std::string line;

        std::unordered_map<std::string, std::string> defaultValues = {
            {"LISTEN_IP", "0.0.0.0"}, {"PORT", "4242"}, {"PROJECT_PATH", "."}};

        if (!stream.is_open()) {
            SERVER_LOG_INFO("Config file {0} not found, creating default one", file);
            saveDefault(defaultValues);
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
        for (auto &it : defaultValues) {
            if (m_fields.find(it.first) == m_fields.end()) {
                SERVER_LOG_INFO("Config file {0} missing field {1}, adding default value {2}", file, it.first,
                                it.second);
                m_fields[it.first] = it.second;
            }
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

} // namespace RType::Server
