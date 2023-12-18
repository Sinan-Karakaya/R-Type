#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "imgui-SFML.h"
#include "imgui.h"

#include "RType.hpp"

#include "IconsFontAwesome4.h"
#include "KeyMap.hpp"

typedef struct project_s {
    std::string name = "";
    std::string path = "";

    bool shouldLoad = false;
    bool shouldCreate = false;
} project_t;

extern project_t g_projectInfos;
extern std::int32_t g_currentEntitySelected;
