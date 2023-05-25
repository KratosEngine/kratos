
#include "runtime/function/global/global_context.h"
#include "runtime/engine.h"
#include "core/log/log_system.h"
#include "runtime/platform/file_service/file_service.h"


namespace Kratos
{
    RuntimeGlobalContext g_runtime_global_context;

    void RuntimeGlobalContext::startSystems(const std::string &config_file_path)
    {
        m_file_system = std::make_shared<FileSystem>();

        m_logger_system = std::make_shared<LogSystem>();
    }

    void RuntimeGlobalContext::shutdownSystems()
    {
        m_logger_system.reset();

        m_file_system.reset();
    }

}
