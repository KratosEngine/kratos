#include <filesystem>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <new>

#include "runtime/engine.h"
#include "editor/include/editor.h"

//https://github.com/electronicarts/EASTL/blob/master/doc/FAQ.md
//In its default configuration, the only thing you need to provide to make EASTL work is to define implementations of the following operator new functions:  
void* operator new[](size_t size, const char* pName, int flags, unsigned     debugFlags, const char* file, int line)
{
    return malloc(size);
}

void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
    return malloc(size);
}


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