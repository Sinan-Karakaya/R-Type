#include <RType.hpp>

// Important: keep this before the include of asio.hpp
#ifdef _WIN32
    #include <windows.h>
    #include <winsock2.h>
#endif
#include <boost/asio.hpp>

int main()
{
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
