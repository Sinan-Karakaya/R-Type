#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "imgui-SFML.h"
#include "imgui.h"

#include "RType.hpp"

typedef struct project_s {
    std::string name = "";
    std::string path = "";

    bool shouldLoad = false;
    bool shouldCreate = false;
} project_t;

extern project_t g_projectInfos;
