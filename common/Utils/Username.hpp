/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Username
*/

#pragma once

#include <cstring>
#include <string>

#ifdef _WIN32
    #include <Lmcons.h>
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

namespace RType::Utils
{

    inline char *getUsername()
    {
#ifdef _WIN32
        char username[UNLEN + 1];
        DWORD username_len = UNLEN + 1;
        GetUserName(username, &username_len);
#else
        char username[256];
        getlogin_r(username, 256);
#endif
        return strdup(username);
    }

} // namespace RType::Utils
