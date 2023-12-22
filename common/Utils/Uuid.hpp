/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Uuid
*/

#ifndef UUID_HPP_
#define UUID_HPP_

#include <random>

#define UUID_SIZE 36

namespace RType::Utils
{
    using UUID = std::string;

    class UUIDS
    {
    public:
        static UUID generate()
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 15);

            const char *lut = "0123456789abcdef";
            std::string uuid = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";

            for (int i = 0; i < UUID_SIZE; ++i) {
                if (uuid[i] == 'x')
                    uuid[i] = lut[dis(gen)];
                else if (uuid[i] == 'y')
                    uuid[i] = lut[(dis(gen) & 0x03) | 0x08];
            }
            return uuid;
        }
    };
} // namespace RType::Utils

#endif /* !UUID_HPP_ */
