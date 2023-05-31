#include "runtime/core/memory/memory_manager.h"

using namespace Kratos;
MemoryManager::MemoryManager()
{
}
MemoryManager::~MemoryManager()
{
}
KSCriticalSection MemoryManager::ms_MemLock;
