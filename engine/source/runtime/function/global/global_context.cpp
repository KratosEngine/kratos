
#include "runtime/function/global/global_context.h"
#include "runtime/engine.h"
#include "core/log/log_system.h"
#include "runtime/platform/file_service/file_service.h"
#include "runtime/function/application/window_system.h"

namespace Kratos
{
    RuntimeGlobalContext g_runtime_global_context;

    void RuntimeGlobalContext::startSystems(const std::string &config_file_path)
    {
        m_file_system = eastl::make_shared<FileSystem>();

        m_logger_system = eastl::make_shared<LogSystem>();

        m_window_system = eastl::make_shared<WindowSystem>();
        WindowCreateInfo window_create_info;
        m_window_system->initialize(window_create_info);
    }

    void RuntimeGlobalContext::shutdownSystems()
    {
        m_logger_system.reset();

        m_file_system.reset();

        m_window_system.reset();
    }

}
