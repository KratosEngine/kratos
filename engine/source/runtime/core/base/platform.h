#pragma once

#ifndef _DEBUG
#define _DEBUG 0
#endif

#define KS_PLATFORM_WIN 1
#define KS_PLATFORM_LINUX 2
#define KS_PLATFORM_OSX 3
#define KS_PLATFORM_IPHONE 4
#define KS_PLATFORM_ANDROID 5
#define KS_PLATFORM_NACL 6

/* Finds the current platform */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(__WIN32__) || defined(_WIN32) || defined(_WINDOWS) || defined(WIN) || defined(_WIN64) || defined(__WIN64__)
#define KS_PLATFORM KS_PLATFORM_WIN
//////////////////////////////////////////////////////////////////////////
#elif defined(__APPLE_CC__) || defined(__APPLE__) || defined(__OSX__)
#if defined(__arm__) || (TARGET_IPHONE_SIMULATOR)
#define KS_PLATFORM KS_PLATFORM_IPHONE
#else
#define KS_PLATFORM KS_PLATFORM_OSX
#endif
//////////////////////////////////////////////////////////////////////////
#elif defined(__ANDROID__)
#define KS_PLATFORM KS_PLATFORM_ANDROID
//////////////////////////////////////////////////////////////////////////
#elif defined(__native_client__)
#define KS_PLATFORM KS_PLATFORM_NACL
#elif defined(linux) || defined(__linux__)
#define KS_PLATFORM KS_PLATFORM_LINUX
#endif

#define KS_ARCHITECTURE_32 1
#define KS_ARCHITECTURE_64 2

/* Find the arch type */
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__) || defined(__arch64__) || defined(_LP64)
#define KS_ARCHITECTURE KS_ARCHITECTURE_64
#else
#define KS_ARCHITECTURE KS_ARCHITECTURE_32
#endif

#define KS_LITTLE_ENDIAN 0
#define KS_BIG_ENDIAN 1

// Endian
#if (defined(__APPLE__) && defined(__BIG_ENDIAN__)) || KS_PLATFORM == KS_PLATFORM_WIN
#define KS_ENDIAN KS_BIG_ENDIAN
#else
#define KS_ENDIAN KS_LITTLE_ENDIAN
#endif

/*
 * Types that are (so far) the same on all platforms
 */
typedef signed   char          ks_int8_t;
typedef unsigned char          ks_uint8_t;
typedef signed   short int     ks_int16_t;
typedef unsigned short int     ks_uint16_t;

#if KS_PLATFORM == KS_PLATFORM_WIN
#include <stdio.h>
#include <tchar.h>
#include <memory.h>
#include <assert.h>
#include <sys/stat.h>
// #include <atlsimpstr.h>
#include <intrin.h>
#include <string.h>
#include <windows.h>
#pragma warning(disable : 4251) // 去除模板导出编译的警告
#pragma warning(disable : 4595)
#define KS_TCHAR TCHAR
#define KS_DWORD DWORD
#else
#include <stdio.h>
#include <string.h>
#include <thread>
#include <mutex>
// #include <cstring>
#define KS_TCHAR char
#define KS_DWORD unsigned int
#endif // KS_PLATFORM_WIN

#ifndef _MSC_VER
#ifdef __cplusplus
#define ks_inline inline
#else
#define ks_inline
#endif
#else
#define ks_inline __forceinline
#endif

#if KS_ARCHITECTURE == KS_ARCHITECTURE_64
#define ks_ssize_t signed long long
#define ks_usize_t unsigned long long
#else
#define ks_ssize_t signed int
#define ks_usize_t unsigned int
#endif

#include "runtime/core/base/macro.h"
namespace Kratos
{
    inline void KSMemset(void *pDest, int iC, ks_usize_t uiCount)
    {
        memset(pDest, iC, uiCount);
    }

    inline void KSStrCopy(KS_TCHAR *pDest, unsigned int uiCount, const KS_TCHAR *pSource)
    {
#if KS_PLATFORM == KS_PLATFORM_WIN
        _tcscpy_s(pDest, uiCount, pSource);
#else
        strncpy(pDest, pSource, uiCount);
        return;
#endif
    }

    inline unsigned int KSStrLen(const KS_TCHAR *pStr)
    {
#if KS_PLATFORM == KS_PLATFORM_WIN
        return (unsigned int)_tcslen(pStr);
#else
        return 0;
#endif
    }

    inline unsigned int KSTlsAlloc()
    {
#if KS_PLATFORM == KS_PLATFORM_WIN
        return TlsAlloc();
#else
        // LOG_WARN("No Implement!");
        return 0;
#endif
    }
    inline void *KSGetTlsValue(unsigned int TlsSolt)
    {
#if KS_PLATFORM == KS_PLATFORM_WIN
        return TlsGetValue(TlsSolt);
#else
        // LOG_WARN("No Implement!");
        return nullptr;
#endif
    }
    inline bool KSSetTlsValue(unsigned int TlsSolt, void *TlsValue)
    {
#if KS_PLATFORM == KS_PLATFORM_WIN
        return TlsSetValue(TlsSolt, TlsValue);
#else
        // LOG_WARN("No Implement!");
        return false;
#endif
    }
    inline bool KSTlsFree(unsigned int TlsSolt)
    {
#if KS_PLATFORM == KS_PLATFORM_WIN
        return TlsFree(TlsSolt);
#else
        // LOG_WARN("No Implement!");
        return false;
#endif
    }

    template <typename T>
    inline T ABS(T t)
    {
        return t < 0 ? -t : t;
    }
    template <typename T>
    inline T Min(T t0, T t1)
    {
        return t0 < t1 ? t0 : t1;
    }
    template <typename T>
    inline T Max(T t0, T t1)
    {
        return t0 > t1 ? t0 : t1;
    }
    template <typename T>
    inline T Clamp(T Value, T Max, T Min)
    {
        if (Value >= Max)
        {
            return Max;
        }
        if (Value <= Min)
        {
            return Min;
        }
        return Value;
    }
    template <class T>
    inline void Swap(T &t1, T &t2)
    {
        T temp;
        temp = t1;
        t1 = t2;
        t2 = temp;
    }
}
