#pragma once

#include <memory>

namespace Kratos
{
    class WindowSystem;

    struct ApplicationUIInitInfo
    {
        std::shared_ptr<WindowSystem> window_system;
    };

    class KSApplication
    {
    public:
        virtual void initialize(ApplicationUIInitInfo init_info) = 0;
        virtual void preRender() = 0;
    };
}