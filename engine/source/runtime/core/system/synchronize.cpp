
#include "runtime/core/system/synchronize.h"

using namespace Kratos;

unsigned int KSSynchronize::WaitAll(KSSynchronize **pSynchronize, unsigned int uiNum, bool bWaitAll, KS_DWORD dwMilliseconds)
{
#if KS_PLATFORM_WIN
    KSMAC_ASSERT(uiNum >= 1 && uiNum <= MAXIMUM_WAIT_OBJECTS);
    static HANDLE handle[MAXIMUM_WAIT_OBJECTS];
    for (unsigned int i = 0; i < uiNum; i++)
    {
        handle[i] = (HANDLE)pSynchronize[i]->GetHandle();
    }
    KS_DWORD dw = WaitForMultipleObjects(uiNum, handle, bWaitAll, dwMilliseconds);
    switch (dw)
    {
    case WAIT_FAILED:
        return WF_FAILED;
    case WAIT_TIMEOUT:
        return WF_TIMEOUT;
    case WAIT_OBJECT_0:
        return WF_OBJECT0;
    }
    return WF_FAILED;
#else
    LOG_WARN("no thread implement");
#endif
}

void KSSynchronize::SafeOutputDebugString(const KS_TCHAR *pcString, ...)
{
    // KSCriticalSection::Locker Temp(g_SafeOutputString);
#if KS_PLATFORM_WIN
    char *pArgs;
    pArgs = (char *)&pcString + sizeof(pcString);
    // _vstprintf_s(VSSystem::ms_sLogBuffer, LOG_BUFFER_SIZE, pcString, pArgs);
    // OutputDebugString(VSSystem::ms_sLogBuffer);
#else
    LOG_WARN("no thread implement");
#endif
}

KSSemaphore::KSSemaphore(unsigned int uiCount, unsigned int MaxCount)
{
    KSMAC_ASSERT(uiCount <= MaxCount);
#if KS_PLATFORM_WIN
    m_Semaphore = CreateSemaphore(nullptr, uiCount, MaxCount, nullptr);
    KSMAC_ASSERT(m_Semaphore);
#else
    LOG_WARN("no thread implement");
#endif
    m_uiMaxCount = MaxCount;
}
//----------------------------------------------------------------------------
KSSemaphore::~KSSemaphore()
{
#if KS_PLATFORM_WIN
    BOOL closed = CloseHandle((HANDLE)m_Semaphore);
    KSMAC_ASSERT(closed);
#else
    LOG_WARN("no thread implement");
#endif
    m_Semaphore = nullptr;
}
//----------------------------------------------------------------------------
void KSSemaphore::Enter()
{
#if KS_PLATFORM_WIN
    KS_DWORD result = WaitForSingleObject((HANDLE)m_Semaphore, INFINITE);
    KSMAC_ASSERT(result);
#else
    LOG_WARN("no thread implement");
#endif
    // result:
    //   WAIT_ABANDONED (0x00000080)
    //   WAIT_OBJECT_0  (0x00000000), signaled
    //   WAIT_TIMEOUT   (0x00000102), [not possible with INFINITE]
    //   WAIT_FAILED    (0xFFFFFFFF), not signaled
}
//----------------------------------------------------------------------------
void KSSemaphore::Leave(unsigned int uiReleaseCount)
{
#if KS_PLATFORM_WIN
    BOOL released = ReleaseSemaphore((HANDLE)m_Semaphore, uiReleaseCount, nullptr);
    KSMAC_ASSERT(released);
#else
    LOG_WARN("no thread implement");
#endif
}

KSMutex::KSMutex()
{
#if KS_PLATFORM_WIN
    m_Mutex = CreateMutex(nullptr, FALSE, nullptr);
#else
    LOG_WARN("no thread implement");
#endif
    KSMAC_ASSERT(m_Mutex);
}
//----------------------------------------------------------------------------
KSMutex::~KSMutex()
{
#if KS_PLATFORM_WIN
    BOOL closed = CloseHandle((HANDLE)m_Mutex);
    KSMAC_ASSERT(closed);
#else
    LOG_WARN("no thread implement");
#endif
    m_Mutex = nullptr;
}
//----------------------------------------------------------------------------
void KSMutex::Enter()
{
#if KS_PLATFORM_WIN
    KS_DWORD result = WaitForSingleObject((HANDLE)m_Mutex, INFINITE);
    KSMAC_ASSERT(result != WAIT_FAILED);
#else
    LOG_WARN("no thread implement");
#endif
    // result:
    //   WAIT_ABANDONED (0x00000080)
    //   WAIT_OBJECT_0  (0x00000000), signaled
    //   WAIT_TIMEOUT   (0x00000102), [not possible with INFINITE]
    //   WAIT_FAILED    (0xFFFFFFFF), not signaled
}
//----------------------------------------------------------------------------
void KSMutex::Leave()
{
#if KS_PLATFORM_WIN
    BOOL released = ReleaseMutex((HANDLE)m_Mutex);
    KSMAC_ASSERT(released);
#else
    LOG_WARN("no thread implement");
#endif
}

KSEvent::KSEvent(void)
{
    Event = nullptr;
}

/**
 * Cleans up the event handle if valid
 */
KSEvent::~KSEvent(void)
{
    if (Event != nullptr)
    {
#if KS_PLATFORM_WIN
        CloseHandle(Event);
#else
        LOG_WARN("no thread implement");
#endif
    }
}

/**
 * Waits for the event to be signaled before returning
 */
void KSEvent::Lock(void)
{
#if KS_PLATFORM_WIN
    WaitForSingleObject(Event, INFINITE);
#else
    LOG_WARN("no thread implement");
#endif
}

/**
 * Triggers the event so any waiting threads are allowed access
 */
void KSEvent::Unlock(void)
{
#if KS_PLATFORM_WIN
    PulseEvent(Event);
#else
    LOG_WARN("no thread implement");
#endif
}

/**
 * Creates the event. Manually reset events stay triggered until reset.
 * Named events share the same underlying event.
 *
 * @param bIsManualReset Whether the event requires manual reseting or not
 * @param InName Whether to use a commonly shared event or not. If so this
 * is the name of the event to share.
 *
 * @return Returns TRUE if the event was created, FALSE otherwise
 */
bool KSEvent::Create(bool bIsManualReset, const KS_TCHAR *InName)
{
    // Create the event and default it to non-signaled
#if KS_PLATFORM_WIN
    Event = CreateEvent(nullptr, bIsManualReset, 0, InName);
    return Event != nullptr;
#else
    LOG_WARN("no thread implement");
#endif
}

/**
 * Triggers the event so any waiting threads are activated
 */
void KSEvent::Trigger(void)
{
#if KS_PLATFORM_WIN
    SetEvent(Event);
#else
    LOG_WARN("no thread implement");
#endif
}

/**
 * Resets the event to an untriggered (waitable) state
 */
void KSEvent::Reset(void)
{
#if KS_PLATFORM_WIN
    ResetEvent(Event);
#else
    LOG_WARN("no thread implement");
#endif
}

/**
 * Triggers the event and resets the triggered state NOTE: This behaves
 * differently for auto-reset versus manual reset events. All threads
 * are released for manual reset events and only one is for auto reset
 */
void KSEvent::Pulse(void)
{
#if KS_PLATFORM_WIN
    PulseEvent(Event);
#else
    LOG_WARN("no thread implement");
#endif
}

/**
 * Waits for the event to be triggered
 *
 * @param WaitTime Time in milliseconds to wait before abandoning the event
 * (KS_DWORD)-1 is treated as wait infinite
 *
 * @return TRUE if the event was signaled, FALSE if the wait timed out
 */
bool KSEvent::Wait(KS_DWORD WaitTime)
{
#if KS_PLATFORM_WIN
    return WaitForSingleObject(Event, WaitTime) == WAIT_OBJECT_0;
#else
    LOG_WARN("no thread implement");
#endif
}
bool KSEvent::IsTrigger()
{
    return Wait(0);
}

// KSTlsValue::KSTlsValue()
// {
//     KSCriticalSection::Locker Temp(m_CriticalSection);
//     m_uiSlot = KSTlsAlloc();
//     KSMAC_ASSERT(m_uiSlot != 0XFFFFFFFF);
// }
// KSTlsValue::~KSTlsValue()
// {
//     KSMAC_ASSERT(m_uiSlot != 0XFFFFFFFF);
//     for (unsigned int i = 0; i < m_uiThreadValueNum; i++)
//     {
//         KSDelete(m_pThreadValue[i]);
//     }
//     KSTlsFree(m_uiSlot);
// }
// void KSTlsValue::SetThreadValue(void *pValue)
// {
//     KSCriticalSection::Locker Temp(m_CriticalSection);
//     m_pThreadValue[m_uiThreadValueNum] = (KSStackMem *)pValue;
//     m_uiThreadValueNum++;
//     KSSetTlsValue(m_uiSlot, pValue);
// }
// void *KSTlsValue::GetThreadValue()
// {
//     return KSGetTlsValue(m_uiSlot);
// }
