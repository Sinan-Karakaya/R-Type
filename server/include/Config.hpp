/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Config2
*/

#ifndef CONFIG2_HPP_
#define CONFIG2_HPP_

#include <string>
#include <unordered_map>

#include "RType.hpp"

namespace RType::Server
{
    class Config
    {
    public:
        /**
         * @brief Config class represents a configuration file.
         *
         * This class is responsible for reading and parsing a configuration file.
         * It provides methods to access the configuration values.
         *
         * @param file The path to the configuration file.
         */
        Config(const std::string &file);
        ~Config();

        /**
         * @brief Retrieves the value of a specific field.
         *
         * @param field The name of the field to retrieve.
         * @return A reference to the value of the field.
         */
        std::string &getField(const std::string &field);
        /**
         * @brief Sets the value of a field in the configuration.
         *
         * @param field The name of the field to set.
         * @param value The value to set for the field.
         */
        void setField(const std::string &field, const std::string &value);

        /**
         * @brief Saves the configuration settings.
         */
        void save();

        /**
         * Saves the default values for the given fields.
         *
         * @param fields The map of field names and their default values.
         */
        void saveDefault(const std::unordered_map<std::string, std::string> &fields);

    private:
        std::string m_file;

        std::unordered_map<std::string, std::string> m_fields;
    };
} // namespace RType::Server

#endif /* !CONFIG2_HPP_ */
