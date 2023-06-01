#pragma once

namespace Kratos
{
    struct EditorGlobalContextInitInfo
    {
        class WindowSystem *window_system;
        class KratosEngine *engine_runtime;
    };

    class EditorGlobalContext
    {
    public:
        class WindowSystem *m_window_system{nullptr};
        class KratosEngine *m_engine_runtime{nullptr};

    public:
        void initialize(const EditorGlobalContextInitInfo &init_info);
        void clear();
    };

    extern EditorGlobalContext g_editor_global_context;
} // namespace Kratos