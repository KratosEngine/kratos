#pragma once

#include <string>

namespace Kratos
{
    class KratosEngine
    {

    public:
        void startEngine(const std::string& config_file_path);
        void shutdownEngine();
    };
}