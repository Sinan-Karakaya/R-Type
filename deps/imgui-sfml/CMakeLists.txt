include(FetchContent)

set(SFML_VERSION 2.6.1)
set(IMGUI_TAG "v1.89.9-docking")
# set(IMGUI_SFML_VERSION 2.3)

# It's nice to get stripped-down release zips instead of cloning
# a repo and checking out a tag
FetchContent_Declare(
        SFML
        GIT_REPOSITORY "https://github.com/SFML/SFML.git"
        GIT_TAG ${SFML_VERSION}
)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
        GIT_TAG ${IMGUI_TAG}
)

# Or by tag...
# Using a custom ImGui-SFML that includes a TextEditor
FetchContent_Declare(
        imgui-sfml
        # GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_REPOSITORY https://github.com/mlbonniec/imgui-sfml.git
        GIT_TAG        2.6.x
        # GIT_COMMIT 5f54b69b6aee18db846c81633f86f78c2586dded
        # ^ or like this - sometimes it's better because FetchContent won't look
        # into remote to see if branch head was updated or not - good for stable
        # tags like 'vX.X' corresponding to releases
)

## finally, let's build

# SFML

if (NOT APPLE)
        option(SFML_BUILD_AUDIO "Build audio" ON)
else()
        option(SFML_BUILD_AUDIO "Build audio" OFF)
endif()

option(SFML_BUILD_NETWORK "Build network" ON)
FetchContent_MakeAvailable(sfml)

# Dear ImGui
FetchContent_MakeAvailable(imgui)

# ImGui-SFML
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" OFF)

FetchContent_MakeAvailable(imgui-sfml)
