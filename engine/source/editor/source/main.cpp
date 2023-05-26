#include <filesystem>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>

#include "runtime/engine.h"
#include "editor/include/editor.h"

int main(int argc, char **argv)
{
    std::filesystem::path executable_path(argv[0]);
    std::filesystem::path config_file_path = executable_path.parent_path() / "KratosEditor.ini";

    // create engine instance
    Kratos::KratosEngine *engine = new Kratos::KratosEngine();

    engine->startEngine(config_file_path.generic_string());
    engine->initialize();
    
    // create editor instance
    Kratos::KratosEditor* editor = new Kratos::KratosEditor();
    editor->initialize(engine);
    editor->run();

    //clean and destory
    editor->clear();
    engine->clear();
    engine->shutdownEngine();

    return 0;
}