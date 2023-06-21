#pragma once

#include <string>

#include <EASTL/shared_ptr.h>

namespace Kratos
{
    class FileSystem;
    class LogSystem;
    class WindowSystem;

    /// Manage the lifetime and creation/destruction order of all global system
    class RuntimeGlobalContext
    {
    public:
        // create all global systems and initialize these systems
        void startSystems(const std::string &config_file_path);
        // destroy all global systems
        void shutdownSystems();

    public:
        eastl::shared_ptr<FileSystem> m_file_system;
        eastl::shared_ptr<LogSystem> m_logger_system;
        eastl::shared_ptr<WindowSystem> m_window_system;
    };

    extern RuntimeGlobalContext g_runtime_global_context;
}