#include "editor/include/editor_global_context.h"

#include "runtime/function/application/window_system.h"

namespace Kratos
{
    EditorGlobalContext g_editor_global_context;

    void EditorGlobalContext::initialize(const EditorGlobalContextInitInfo &init_info)
    {
        g_editor_global_context.m_window_system = init_info.window_system;
        g_editor_global_context.m_engine_runtime = init_info.engine_runtime;
    }

    void EditorGlobalContext::clear()
    {
    }
} // namespace Kratos