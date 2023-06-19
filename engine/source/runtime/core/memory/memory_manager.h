#pragma once

#include "runtime/core/base/macro.h"
#include "runtime/core/system/synchronize.h"

// #include <new.h>
#define KS_NEW new
#define KS_DELETE delete
#include <type_traits>

namespace Kratos
{
    template <typename T>
    struct TRemoveReference
    {
        typedef T Type;
    };
    template <typename T>
    struct TRemoveReference<T &>
    {
        typedef T Type;
    };
    template <typename T>
    struct TRemoveReference<T &&>
    {
        typedef T Type;
    };
    template <typename T>
    ks_inline T &&Forward(typename TRemoveReference<T>::Type &Obj)
    {
        return (T &&)Obj;
    }

    template <typename T>
    ks_inline T &&Forward(typename TRemoveReference<T>::Type &&Obj)
    {
        return (T &&)Obj;
    }

#define HAS_TRIVIAL_CONSTRUCTOR(T) std::is_trivially_constructible<T>::value
#define HAS_TRIVIAL_DESTRUCTOR(T) std::is_trivially_destructible<T>::value
#define HAS_TRIVIAL_ASSIGN(T) std::is_trivially_assignable<T>::value
#define HAS_TRIVIAL_COPY(T) std::is_trivially_copyable<T>::value
#define IS_POD(T) std::is_pod<T>::value
#define IS_ENUM(T) std::is_enum<T>::value
#define IS_EMPTY(T) std::is_empty<T>::value

    /**
     * TIsFloatType
     */
    template <typename T>
    struct TIsFloatType
    {
        enum
        {
            Value = std::is_floating_point<T>::value
        };
    };

    /**
     * TIsIntegralType
     */
    template <typename T>
    struct TIsIntegralType
    {
        enum
        {
            Value = std::is_integral<T>::value
        };
    };

    /**
     * TIsArithmeticType
     */
    template <typename T>
    struct TIsArithmeticType
    {
        enum
        {
            Value = std::is_arithmetic<T>::value
        };
    };

    /**
     * TIsNativePointerType
     * @todo - exclude member pointers
     */
    template <typename T>
    struct TIsNativePointerType
    {
        enum
        {
            Value = std::is_pointer<T>::value
        };
    };

    /**
     * TIsVoidType
     */
    template <typename T>
    struct TIsVoidType
    {
        enum
        {
            Value = std::is_void<T>::value
        };
    };

    /**
     * TIsPODType
     */
    template <typename T>
    struct TIsPODType
    {
        enum
        {
            Value = IS_POD(T)
        };
    };

    /**
     * TIsFundamentalType
     */
    template <typename T>
    struct TIsFundamentalType
    {
        enum
        {
            Value = std::is_fundamental<T>::Value
        };
    };

    template <typename T>
    struct ValueBase
    {
        enum
        {
            NeedsConstructor = !HAS_TRIVIAL_CONSTRUCTOR(T) && !TIsPODType<T>::Value
        };
        enum
        {
            NeedsDestructor = !HAS_TRIVIAL_DESTRUCTOR(T) && !TIsPODType<T>::Value
        };
    };

    template <class T>
    inline T Align(const T Ptr, ks_usize_t Alignment)
    {
        return (T)(((ks_usize_t)Ptr + Alignment - 1) & ~(Alignment - 1));
    }
    template <class T>
    inline T Align1(const T Ptr, ks_usize_t Alignment)
    {
        return (T)((ks_usize_t)Ptr + Alignment - (Ptr & (Alignment - 1)));
    }

    class KSMemManager
    {
    public:
        KSMemManager();
        virtual ~KSMemManager() = 0;
        virtual void *Allocate(ks_usize_t uiSize, ks_usize_t uiAlignment, bool bIsArray) = 0;
        virtual void Deallocate(char *pcAddr, ks_usize_t uiAlignment, bool bIsArray) = 0;

    protected:
        static KSCriticalSection ms_MemLock;
    };

    class KSCMem : public KSMemManager
    {
    public:
        KSCMem();
        ~KSCMem();
        virtual void *Allocate(ks_usize_t uiSize, ks_usize_t uiAlignment, bool bIsArray);
        virtual void Deallocate(char *pcAddr, ks_usize_t uiAlignment, bool bIsArray);
    };

    // TBB:https://www.intel.com/content/www/us/en/developer/tools/oneapi/onetbb.html#gs.t3scl5
    class KSMemTBB : public KSMemManager
    {
    public:
        KSMemTBB();
        ~KSMemTBB();

        virtual void *Allocate(ks_usize_t uiSize, ks_usize_t uiAlignment, bool bIsArray);
        virtual void Deallocate(char *pcAddr, ks_usize_t uiAlignment, bool bIsArray);
    };

    class KSStackMem : public KSMemManager
    {
    public:
        KSStackMem(ks_usize_t uiDefaultChunkSize = 65536);
        ~KSStackMem();
        void *Allocate(ks_usize_t uiSize, ks_usize_t uiAlignment, bool bIsArray);
        void Deallocate(char *pcAddr, ks_usize_t uiAlignment, bool bIsArray)
        {
            return;
        }
        template <class T>
        friend class KSStackMemAlloc;
        friend class VSStackMemTag;
        // 每帧结束或者开始的时候调用
        void Clear();

    private:
        // Types.
        struct FTaggedMemory
        {
            FTaggedMemory *Next;
            ks_usize_t DataSize;
            ks_uint8_t Data[1];
        };

        // Variables.
        ks_uint8_t *Top;             // Top of current chunk (Top<=End).
        ks_uint8_t *End;             // End of current chunk.
        ks_usize_t DefaultChunkSize; // Maximum chunk size to allocate.
        FTaggedMemory *TopChunk;     // Only chunks 0..ActiveChunks-1 are valid.

        /** The memory chunks that have been allocated but are currently unused. */
        FTaggedMemory *UnusedChunks;

        /** The number of marks on this stack. */
        size_t NumMarks;

        /**
         * Allocate a new chunk of memory of at least MinSize size,
         * and return it aligned to Align. Updates the memory stack's
         * Chunks table and ActiveChunks counter.
         */
        ks_uint8_t *AllocateNewChunk(ks_usize_t MinSize);

        /** Frees the chunks above the specified chunk on the stack. */
        /*移除这个chunk和这个chunk之前的所有chunk*/
        void FreeChunks(FTaggedMemory *NewTopChunk);
    };

    // if the class has memory alloc , you must inherit from KSMemObject , so you can use the MemManager any where
    class KSMemObject
    {
    public:
        KSMemObject();
        ~KSMemObject();
        static KSStackMem &GetStackMemManager();
        static KSMemManager &GetMemManager();
        static KSMemManager &GetCMemManager();
    };

    template <class T>
    class KSStackMemAlloc : public KSMemObject
    {
    public:
        // Constructors.
        KSStackMemAlloc(ks_usize_t uiNum = 0, ks_usize_t uiAlignment = 0)
        {
            if (uiNum > 0)
            {
                KSStackMem &StackMem = GetStackMemManager();
                m_uiNum = uiNum;
                Top = StackMem.Top;
                SavedChunk = StackMem.TopChunk;
                // Track the number of outstanding marks on the stack.
                StackMem.NumMarks++;

                m_pPtr = (T *)StackMem.Allocate(uiNum * sizeof(T), uiAlignment, 0);
                VSMAC_ASSERT(m_pPtr);
                if (ValueBase<T>::NeedsConstructor)
                {
                    for (unsigned int i = 0; i < uiNum; i++)
                    {
                        KS_NEW(m_pPtr + i)
                        T();
                    }
                }
            }
        }

        /** Destructor. */
        ~KSStackMemAlloc()
        {

            if (m_uiNum > 0)
            {
                KSStackMem &StackMem = GetStackMemManager();

                if (ValueBase<T>::NeedsDestructor)
                {
                    for (unsigned int i = 0; i < m_uiNum; i++)
                    {
                        (m_pPtr + i)->~T();
                    }
                }

                // Track the number of outstanding marks on the stack.
                --StackMem.NumMarks;

                // Unlock any new chunks that were allocated.
                if (SavedChunk != StackMem.TopChunk)
                    StackMem.FreeChunks(SavedChunk);

                // Restore the memory stack's state.
                StackMem.Top = Top;

                // Ensure that the mark is only popped once by clearing the top pointer.
                Top = nullptr;
            }
        }

        inline T *GetPtr() const
        {
            return m_pPtr;
        }
        inline ks_usize_t GetNum() const
        {
            return m_uiNum;
        }

    private:
        ks_uint8_t *Top;
        KSStackMem::FTaggedMemory *SavedChunk;
        T *m_pPtr;
        ks_usize_t m_uiNum;
    };

    class KSDefaultContainerMem
    {
    public:
        KSDefaultContainerMem()
        {
        }
        virtual ~KSDefaultContainerMem()
        {
        }
        virtual void *Allocate(ks_usize_t uiSize, ks_usize_t uiAlignment, bool bIsArray)
        {
            return KSMemObject::GetMemManager().Allocate(uiSize, uiAlignment, bIsArray);
        }
        virtual void Deallocate(char *pcAddr, ks_usize_t uiAlignment, bool bIsArray)
        {
            return KSMemObject::GetMemManager().Deallocate(pcAddr, uiAlignment, bIsArray);
        }
    };

    class KSStackContainerMem
    {
    public:
        KSStackContainerMem()
        {
        }
        virtual ~KSStackContainerMem()
        {
        }
        virtual void *Allocate(unsigned int uiSize, unsigned int uiAlignment, bool bIsArray)
        {
            return KSMemObject::GetStackMemManager().Allocate(uiSize, uiAlignment, bIsArray);
        }
        virtual void Deallocate(char *pcAddr, unsigned int uiAlignment, bool bIsArray)
        {
            return KSMemObject::GetStackMemManager().Deallocate(pcAddr, uiAlignment, bIsArray);
        }
    };

    class VSStackMemTag : public KSMemObject
    {
    public:
        // Constructors.
        VSStackMemTag()
        {
            KSStackMem &StackMem = GetStackMemManager();
            StackMem.NumMarks++;
            Top = StackMem.Top;
            SavedChunk = StackMem.TopChunk;
        }

        /** Destructor. */
        ~VSStackMemTag()
        {
            KSStackMem &StackMem = GetStackMemManager();

            // Unlock any new chunks that were allocated.
            if (SavedChunk != StackMem.TopChunk)
                StackMem.FreeChunks(SavedChunk);

            // Restore the memory stack's state.
            StackMem.Top = Top;
            StackMem.NumMarks--;
        }

    private:
        ks_uint8_t *Top;
        KSStackMem::FTaggedMemory *SavedChunk;
    };
}

inline void *operator new(size_t uiSize)
{
    return Kratos::KSMemObject::GetMemManager().Allocate(uiSize, 0, false);
}
inline void *operator new[](size_t uiSize)
{
    return Kratos::KSMemObject::GetMemManager().Allocate(uiSize, 0, true);
}

inline void operator delete(void *pvAddr)
{
    return Kratos::KSMemObject::GetMemManager().Deallocate((char *)pvAddr, 0, false);
}
inline void operator delete[](void *pvAddr)
{
    return Kratos::KSMemObject::GetMemManager().Deallocate((char *)pvAddr, 0, true);
}

#define KSMAC_DELETE(p) \
    if (p)              \
    {                   \
        KS_DELETE p;    \
        p = 0;          \
    }
#define KSMAC_DELETEA(p) \
    if (p)               \
    {                    \
        KS_DELETE[] p;   \
        p = 0;           \
    }
#define KSMAC_DELETEAB(p, num)        \
    if (p)                            \
    {                                 \
        for (int i = 0; i < num; i++) \
            KSMAC_DELETEA(p[i]);      \
        KSMAC_DELETEA(p);             \
    }

// use by inner mac
template <typename T>
inline void KSDelete(T *&p)
{
    if (p)
    {
        KS_DELETE p;
        p = 0;
    }
}
template <typename T>
inline void KSDeleteA(T *&p)
{
    if (p)
    {
        KS_DELETE[] p;
        p = 0;
    }
}
template <typename T, typename N>
inline void KSDeleteAB(T *&p, N num)
{
    if (p)
    {
        for (int i = 0; i < num; i++)
            KSMAC_DELETEA(p[i]);
        KSMAC_DELETEA(p);
    }
}
