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

    class MemoryManager
    {
    public:
        MemoryManager();
        virtual ~MemoryManager() = 0;
        virtual void *Allocate(ks_usize_t uiSize, ks_usize_t uiAlignment, bool bIsArray) = 0;
        virtual void Deallocate(char *pcAddr, ks_usize_t uiAlignment, bool bIsArray) = 0;

    protected:
        static KSCriticalSection ms_MemLock;
    };

}