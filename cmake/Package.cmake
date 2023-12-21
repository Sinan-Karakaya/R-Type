include(InstallRequiredSystemLibraries)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/r-type-game" DESTINATION "." COMPONENT applications)
install(
    FILES
    $<TARGET_FILE:sfml-window>
    $<TARGET_FILE:sfml-audio>
    $<TARGET_FILE:sfml-graphics>
    $<TARGET_FILE:sfml-system>
    $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
    $<TARGET_FILE:spdlog::spdlog>
    $<TARGET_FILE:fmt::fmt>
    $<TARGET_FILE:OpenAL::OpenAL>
    $<TARGET_FILE:unofficial::nativefiledialog::nfd>
    $<TARGET_FILE:${LUA_LIBRARIES}>
    DESTINATION .
    COMPONENT applications
)
install(DIRECTORY $<TARGET_FILE_DIR:editor>/assets DESTINATION "." COMPONENT dev)

# set packages executables
install(TARGETS editor RUNTIME DESTINATION "." COMPONENT dev)
install(TARGETS server RUNTIME DESTINATION "." COMPONENT serv)
install(TARGETS client RUNTIME DESTINATION "." COMPONENT cli)
install(TARGETS runtime RUNTIME DESTINATION "." COMPONENT applications)

set(CPACK_COMPONENTS_GROUPING IGNORE)
set(CPACK_COMPONENTS_ALL applications cli serv dev)
set(CPACK_PACKAGE_NAME "R-Type")
set(CPACK_PACKAGE_VENDOR "La table des 5")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/assets/installer\\\\installer_banner.bmp")

set(CPACK_DEBIAN_PACKAGE_NAME "r-type")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "La table des 5")
set(CPACK_DEBIAN_PACKAGE_CONTACT "sinan.karakaya@epitech.eu")
set(CPACK_DEBIAN_PACKAGE_VERSION "0.1")

if (WIN32)
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/assets/installer\\\\installer_icon.ico")
    set(CPACK_CREATE_DESKTOP_LINKS editor client server)
endif()

include(CPack)

cpack_add_component(applications
    REQUIRED
    DISPLAY_NAME "R-Type's runtime"
    DESCRIPTION "The library required to play the game."
    GROUP Runtime
    INSTALL_TYPES Full Primary Developer
)

cpack_add_component(cli
    DISPLAY_NAME "R-Type game"
    DESCRIPTION "To play the game with your friends."
    GROUP Client
    INSTALL_TYPES Full Primary Developer
)

cpack_add_component(dev
    DISPLAY_NAME "R-Type's editor"
    DESCRIPTION "The editor for the game, to make your own levels."
    GROUP Development
    INSTALL_TYPES Full Developer
)

cpack_add_component(serv
    DISPLAY_NAME "R-Type's server"
    DESCRIPTION "All you need to host your own game."
    GROUP Hosting
    INSTALL_TYPES Full Hosting
)

cpack_add_component_group(Runtime
    EXPANDED
    DESCRIPTION "The core library that handles the game logic."
)

cpack_add_component_group(Client
    EXPANDED
    DESCRIPTION "All you need to play the game with your friends."
)

cpack_add_component_group(Development
    EXPANDED
    DESCRIPTION "All you need to make your own game and host it."
)

cpack_add_component_group(Development
    EXPANDED
    DESCRIPTION "All you need to make your own game and host it."
)
