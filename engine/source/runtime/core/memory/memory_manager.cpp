#include "runtime/core/memory/memory_manager.h"

using namespace Kratos;
KSMemManager::KSMemManager()
{
}
KSMemManager::~KSMemManager()
{
}
KSCriticalSection KSMemManager::ms_MemLock;

// ===========================================KSCMem===========================================
KSCMem::KSCMem()
{
}
KSCMem::~KSCMem()
{
}
void *KSCMem::Allocate(ks_usize_t uiSize, ks_usize_t uiAlignment, bool bIsArray)
{
    KSCriticalSection::Locker Temp(ms_MemLock);
    // 不需要字节对齐的使用默认malloc分配内存，否则使用_aligned_malloc(c17默认支持，c11、c14需要自己实现)
    if (uiAlignment == 0)
    {
        return malloc(uiSize);
    }
    else
    {
#if KS_PLATFORM == KS_PLATFORM_WIN
        return _aligned_malloc(uiSize, uiAlignment);
#else
        return aligned_alloc(uiSize, uiAlignment);
#endif
    }
}

void KSCMem::Deallocate(char *pcAddr, ks_usize_t uiAlignment, bool bIsArray)
{
    KSCriticalSection::Locker Temp(ms_MemLock);
    if (uiAlignment == 0)
    {
        free(pcAddr);
    }
    else
    {
#if KS_PLATFORM == KS_PLATFORM_WIN
        _aligned_free(pcAddr);
#else
        free(pcAddr);
#endif
    }
}

// ===========================================KSMemTBB===========================================

// #include <scalable_allocator.h>
KSMemTBB::KSMemTBB()
{
}
KSMemTBB::~KSMemTBB()
{
}

void *KSMemTBB::Allocate(ks_usize_t uiSize, ks_usize_t uiAlignment, bool bIsArray)
{
    return malloc(uiSize);
    // if (uiAlignment != 0)
    // {
    //     // uiAlignment = Max(uiSize >= 16 ? (ks_usize_t)16 : (ks_usize_t)8, uiAlignment);
    //     return scalable_aligned_malloc(uiSize, uiAlignment);
    // }
    // else
    // {
    //     return scalable_malloc(uiSize);
    // }
}
void KSMemTBB::Deallocate(char *pcAddr, ks_usize_t uiAlignment, bool bIsArray)
{
    free(pcAddr);
    // if (!pcAddr)
    // {
    //     return;
    // }
    // if (uiAlignment != 0)
    // {
    //     scalable_aligned_free(pcAddr);
    // }
    // else
    // {
    //     scalable_free(pcAddr);
    // }
}

// ===========================================KSCMem===========================================
KSStackMem::KSStackMem(ks_usize_t uiDefaultChunkSize)
{
    KSMAC_ASSERT(uiDefaultChunkSize > sizeof(FTaggedMemory));
    Top = nullptr;
    End = nullptr;
    DefaultChunkSize = uiDefaultChunkSize;
    TopChunk = nullptr;
    UnusedChunks = nullptr;
    NumMarks = 0;
}
KSStackMem::~KSStackMem()
{
    FreeChunks(nullptr);
    while (UnusedChunks)
    {
        void *Old = UnusedChunks;
        UnusedChunks = UnusedChunks->Next;
        KSMemObject::GetMemManager().Deallocate((char *)Old, 0, true);
    }
    KSMAC_ASSERT(NumMarks == 0);
}

ks_uint8_t *KSStackMem::AllocateNewChunk(ks_usize_t MinSize)
{
    FTaggedMemory *Chunk = nullptr;
    for (FTaggedMemory **Link = &UnusedChunks; *Link; Link = &(*Link)->Next)
    {
        // Find existing chunk.
        if ((*Link)->DataSize >= MinSize)
        {
            Chunk = *Link;
            *Link = (*Link)->Next;
            break;
        }
    }
    if (!Chunk)
    {
        // Create new chunk.
        ks_usize_t DataSize = Max(MinSize, DefaultChunkSize - sizeof(FTaggedMemory));
        Chunk = (FTaggedMemory *)KSMemObject::GetMemManager().Allocate(DataSize + sizeof(FTaggedMemory), 0, true);
        Chunk->DataSize = DataSize;
    }

    Chunk->Next = TopChunk;
    TopChunk = Chunk;
    Top = Chunk->Data;
    End = Top + Chunk->DataSize;
    return Top;
}

void KSStackMem::FreeChunks(FTaggedMemory *NewTopChunk)
{
    while (TopChunk != NewTopChunk)
    {
        FTaggedMemory *RemoveChunk = TopChunk;
        TopChunk = TopChunk->Next;
        RemoveChunk->Next = UnusedChunks;
        UnusedChunks = RemoveChunk;
    }
    Top = nullptr;
    End = nullptr;
    if (TopChunk)
    {
        Top = TopChunk->Data;
        End = Top + TopChunk->DataSize;
    }
}

void *KSStackMem::Allocate(ks_usize_t uiSize, ks_usize_t uiAlignment, bool bIsArray)
{
    // Debug checks.
    KSMAC_ASSERT(uiSize >= 0);
#ifdef _DEBUG
    if (uiAlignment > 0)
    {
        KSMAC_ASSERT((uiAlignment & (uiAlignment - 1)) == 0);
    }
#endif
    KSMAC_ASSERT(Top <= End);
    KSMAC_ASSERT(NumMarks > 0);

    // Try to get memory from the current chunk.
    ks_uint8_t *Result = Top;
    if (uiAlignment > 0)
    {
        Result = (ks_uint8_t *)(((ks_usize_t)Top + (uiAlignment - 1)) & ~(uiAlignment - 1));
    }
    Top = Result + uiSize;

    // Make sure we didn't overflow.
    if (Top > End)
    {
        // We'd pass the end of the current chunk, so allocate a new one.
        AllocateNewChunk(uiSize + uiAlignment);
        Result = Top;
        if (uiAlignment > 0)
        {
            Result = (ks_uint8_t *)(((ks_usize_t)Top + (uiAlignment - 1)) & ~(uiAlignment - 1));
        }
        Top = Result + uiSize;
    }
    return Result;
}
void KSStackMem::Clear()
{
    FreeChunks(nullptr);
}

// ===========================================KSMemManager===========================================
KSMemObject::KSMemObject()
{
    GetCMemManager();
    GetMemManager();
    GetStackMemManager();
}

KSMemObject::~KSMemObject()
{
}

KSMemManager &KSMemObject::GetMemManager()
{
    static KSMemTBB g_MemManager;
    return g_MemManager;
}
KSMemManager &KSMemObject::GetCMemManager()
{
    static KSCMem g_MemManager;
    return g_MemManager;
}
KSStackMem &KSMemObject::GetStackMemManager()
{
    // static KSTlsValue g_TlsValue;
    // void *pTlsValue = g_TlsValue.GetThreadValue();
    // if (!pTlsValue)
    // {
    //     pTlsValue = KS_NEW KSStackMem();
    //     g_TlsValue.SetThreadValue(pTlsValue);
    // }
    // return *((KSStackMem *)pTlsValue);
    static KSStackMem g_StackMemManager;
    return g_StackMemManager;
}
