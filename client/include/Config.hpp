/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Config
*/

#ifndef CONFIG2_HPP_
#define CONFIG2_HPP_

#include <string>
#include <unordered_map>

#include "RType.hpp"

namespace RType::Client
{
    class Config
    {
    public:
        Config(const std::string &file);
        ~Config();

        std::string &getField(const std::string &field);
        void setField(const std::string &field, const std::string &value);

        void save();

        void saveDefault(const std::unordered_map<std::string, std::string> &fields);

    private:
        std::string m_file;

        std::unordered_map<std::string, std::string> m_fields;
    };
} // namespace RType::Client

#endif /* !CONFIG2_HPP_ */
