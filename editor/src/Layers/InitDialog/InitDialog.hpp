#pragma once

#include <nfd.h>

#ifdef _WIN32
    #include <windows.h>
    #include <winstring.h>
#endif

#include "Editor.hpp"
#include "Layers/ILayer.hpp"

namespace RType::Editor
{
class InitDialog : public ILayer
{
  public:
    InitDialog()
    {
        OnAttach();
    }
    ~InitDialog() override
    {
        OnDetach();
    }

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;
    void OnRender() override;

  private:
    void f_openDialog();

  private:
    bool m_create = false;
    char m_projectName[512] = {0};

    nfdchar_t *m_path = nullptr;
};
} // namespace RType::Editor
