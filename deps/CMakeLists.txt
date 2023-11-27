find_package(SFML 2.6.1 COMPONENTS graphics audio network window system REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(unofficial-nativefiledialog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(asio CONFIG REQUIRED)
find_package(Lua REQUIRED)      # adding the CONFIG here doesnt work for some reason
find_package(sol2 CONFIG REQUIRED)