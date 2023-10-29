#pragma once

#ifdef _WIN32
    #include <windows.h>
    #define rtype_api __declspec(dllexport)
#elif __GNUC__
    #include <dlfcn.h>
    #define rtype_api
#endif

namespace RType::Utils::Modules {

void *LoadSharedLibrary(const char *libName, int iMode = 2) {
    std::string formattedLibName = libName;
    (void)iMode;

#ifdef _WIN32
    formattedLibName += ".dll";
    return (void *)LoadLibrary(formattedLibName.c_str());
#elif __GNUC__
    formattedLibName += ".so";
    return dlopen(formattedLibName.c_str(), iMode);
#endif
}

void *GetFunction(void *libHandle, const char *funcName) {
#ifdef _WIN32
    return (void *)GetProcAddress((HINSTANCE)libHandle, funcName);
#elif __GNUC__
    return dlsym(libHandle, funcName);
#endif
}

bool FreeSharedLibrary(void *libHandle) {
#ifdef _WIN32
    return FreeLibrary((HINSTANCE)libHandle);
#elif __GNUC__
    return dlclose(libHandle);
#endif
}

} // namespace RType::Utils::Modules
