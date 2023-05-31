#pragma once

#include "runtime/core/base/macro.h"

namespace Kratos
{
    class KSSynchronize
    {
    public:
        KSSynchronize() {}
        virtual ~KSSynchronize() {}
        virtual void *GetHandle() = 0;
        enum
        {
            WF_OBJECT0 = 0,
            WF_TIMEOUT = 256,
            WF_FAILED = 0xFFFFFFFF
        };
        static unsigned int WaitAll(KSSynchronize **pSynchronize, unsigned int uiNum, bool bWaitAll, KS_DWORD dwMilliseconds = (KS_DWORD)-1);
        static void SafeOutputDebugString(const KS_TCHAR *pcString, ...);
    };

    class KSCriticalSection
    {
#if KS_PLATFORM == KS_PLATFORM_WIN
        /**
         * The windows specific critical section
         */
        CRITICAL_SECTION CriticalSection; // Windows中的临界区，非常类似于c++11中的mutex
#else
        std::mutex _mutex;
#endif
    public:
        /**
         * Constructor that initializes the aggregated critical section
         */
        inline KSCriticalSection(void)
        {
#if KS_PLATFORM == KS_PLATFORM_WIN
            InitializeCriticalSection(&CriticalSection);
            SetCriticalSectionSpinCount(&CriticalSection, 4000);
#endif
        }

        /**
         * Destructor cleaning up the critical section
         */
        inline ~KSCriticalSection(void)
        {
#if KS_PLATFORM == KS_PLATFORM_WIN
            DeleteCriticalSection(&CriticalSection); // 离开Windows临界区，和mutex解锁一个道理
#else
            _mutex.unlock();
#endif
        }

        /**
         * Locks the critical section
         */
        inline void Lock(void)
        {
#if KS_PLATFORM == KS_PLATFORM_WIN
            // Spin first before entering critical section, causing ring-0 transition and context switch.
            EnterCriticalSection(&CriticalSection); // 进入Windows临界区，和mutex加锁一个道理
#else
            _mutex.lock();
#endif
        }

        /**
         * Attempt to take a lock and returns whether or not a lock was taken.
         *
         * @return true if a lock was taken, false otherwise.
         */
        inline bool TryLock()
        {
#if KS_PLATFORM == KS_PLATFORM_WIN
            if (TryEnterCriticalSection(&CriticalSection))
            {
                return true;
            }
#else
            if (_mutex.try_lock())
            {
                return true;
            }
#endif
            return false;
        }
        /**
         * Releases the lock on the critical seciton
         */
        inline void Unlock(void)
        {
#if KS_PLATFORM == KS_PLATFORM_WIN
            LeaveCriticalSection(&CriticalSection);
#else
            _mutex.unlock();
#endif
        }

        class Locker
        {
        public:
            Locker(KSCriticalSection &InCriticalSection)
                : CriticalSection(InCriticalSection)
            {
                CriticalSection.Lock();
            }
            ~Locker()
            {
                CriticalSection.Unlock();
            }

        private:
            KSCriticalSection &CriticalSection;
        };
    };

    class KSSemaphore : public KSSynchronize
    {
    public:
        KSSemaphore(unsigned int uiCount, unsigned int MaxCount);
        virtual ~KSSemaphore();

        virtual void Enter();
        virtual void Leave(unsigned int uiReleaseCount);
        virtual void *GetHandle()
        {
            return m_Semaphore;
        }

    protected:
        void *m_Semaphore;
        unsigned int m_uiMaxCount;
    };

    class KSMutex : public KSSynchronize
    {
    public:
        KSMutex();
        virtual ~KSMutex();

        virtual void Enter();
        virtual void Leave();
        virtual void *GetHandle()
        {
            return m_Mutex;
        }

    protected:
        void *m_Mutex;
    };

    class KSEvent : public KSSynchronize
    {
        /**
         * The handle to the event
         */
        void *Event;

    public:
        virtual void *GetHandle()
        {
            return Event;
        }
        /**
         * Constructor that zeroes the handle
         */
        KSEvent(void);

        /**
         * Cleans up the event handle if valid
         */
        virtual ~KSEvent(void);

        /**
         * Waits for the event to be signaled before returning
         */
        virtual void Lock(void);

        /**
         * Triggers the event so any waiting threads are allowed access
         */
        virtual void Unlock(void);

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
        virtual bool Create(bool bIsManualReset = false, const KS_TCHAR *InName = NULL);

        /**
         * Triggers the event so any waiting threads are activated
         */
        virtual void Trigger(void);

        /**
         * Resets the event to an untriggered (waitable) state
         */
        virtual void Reset(void);

        /**
         * Triggers the event and resets the triggered state NOTE: This behaves
         * differently for auto-reset versus manual reset events. All threads
         * are released for manual reset events and only one is for auto reset
         */
        virtual void Pulse(void);

        /**
         * Waits for the event to be triggered
         *
         * @param WaitTime Time in milliseconds to wait before abandoning the event
         * (KS_DWORD)-1 is treated as wait infinite
         *
         * @return TRUE if the event was signaled, FALSE if the wait timed out
         */
        virtual bool Wait(KS_DWORD WaitTime = (KS_DWORD)-1);

        virtual bool IsTrigger();
    };

}
