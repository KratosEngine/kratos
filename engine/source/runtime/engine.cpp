#include "runtime/engine.h"
#include "runtime/core/base/macro.h"

namespace Kratos
{
    void KratosEngine::startEngine(const std::string &config_file_path)
    {
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