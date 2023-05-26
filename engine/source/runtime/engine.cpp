#include "runtime/engine.h"
#include "runtime/core/base/macro.h"

#include "runtime/function/global/global_context.h"

namespace Kratos
{
    void KratosEngine::startEngine(const std::string &config_file_path)
    {
        g_runtime_global_context.startSystems(config_file_path);
        LOG_INFO("engine start");
    }

    void KratosEngine::shutdownEngine()
    {
        LOG_INFO("engine shutdown");
    }

    void KratosEngine::initialize()
    {
    }

    void KratosEngine::clear()
    {
    }

    void KratosEngine::run()
    {
    }

    bool KratosEngine::tickOneFrame(float delta_time)
    {
        return true;
    }
}