#pragma once

namespace RType::Editor {
    class ILayer {
    public:
        virtual ~ILayer() = default;

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;
    };
}