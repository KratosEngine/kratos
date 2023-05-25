#include <filesystem>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>

#include "runtime/engine.h"

int main(int argc, char **argv)
{
    std::filesystem::path executable_path(argv[0]);
    std::filesystem::path config_file_path = "";

    // create engine instance
    Kratos::KratosEngine *engine = new Kratos::KratosEngine();

    engine->startEngine(config_file_path.generic_string());
    engine->initialize();

    
    engine->clear();
    engine->shutdownEngine();

    return 0;
}