#pragma once

#include <string>

namespace Kratos
{
    class KratosEngine
    {

    public:
        void startEngine(const std::string& config_file_path);
        void shutdownEngine();

        void initialize();
        void clear();

        void run();
        bool tickOneFrame(float delta_time);
    };
}