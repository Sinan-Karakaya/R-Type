#pragma once

#include <string>

#ifdef _WIN32
    #include <windows.h>
    #define rtype_api __declspec(dllexport)
#elif __GNUC__
    #include <dlfcn.h>
    #define rtype_api
#endif

namespace RType::Utils::Modules
{

    inline void *LoadSharedLibrary(const char *libName, int iMode = 2)
    {
#ifdef __GNUC__
        std::string formattedLibName = "lib" + std::string(libName);
#else
        std::string formattedLibName = libName;
#endif
#ifdef _WIN32
        (void)iMode;
        formattedLibName += ".dll";
        return (void *)LoadLibrary(formattedLibName.c_str());
#elif __APPLE__
        formattedLibName += ".dylib";
        return dlopen(formattedLibName.c_str(), iMode);
#elif __GNUC__
        formattedLibName += ".so";
        return dlopen(formattedLibName.c_str(), iMode);
#endif
    }

    inline void *GetFunction(void *libHandle, const char *funcName)
    {
#ifdef _WIN32
        return (void *)GetProcAddress((HINSTANCE)libHandle, funcName);
#elif __GNUC__
        return dlsym(libHandle, funcName);
#endif
    }

    inline bool FreeSharedLibrary(void *libHandle)
    {
#ifdef _WIN32
        return FreeLibrary((HINSTANCE)libHandle);
#elif __GNUC__
        return dlclose(libHandle);
#endif
    }

} // namespace RType::Utils::Modules
