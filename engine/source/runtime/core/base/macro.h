#pragma once

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <chrono>
#include <thread>

#include "runtime/core/log/log_system.h"
#include "runtime/function/global/global_context.h"

#ifndef _DEBUG
#define _DEBUG 0
#endif
#ifndef KS_PLATFORM_WIN
#define KS_PLATFORM_WIN 0
#endif
#ifndef KS_PLATFORM_LINUX
#define KS_PLATFORM_LINUX 0
#endif
#ifndef KS_PLATFORM_OSX
#define KS_PLATFORM_OSX 0
#endif
#ifndef KS_PLATFORM_IPHONE
#define KS_PLATFORM_IPHONE 0
#endif
#ifndef KS_PLATFORM_ANDROID
#define KS_PLATFORM_ANDROID 0
#endif
#ifndef KS_PLATFORM_NACL
#define KS_PLATFORM_NACL 0
#endif

/* Finds the current platform */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(__WIN32__) || defined(_WIN32) || defined(_WINDOWS) || defined(WIN) || defined(_WIN64) || defined(__WIN64__)
#define KS_PLATFORM_WIN 1
//////////////////////////////////////////////////////////////////////////
#elif defined(__APPLE_CC__) || defined(__APPLE__) || defined(__OSX__)
#if defined(__arm__) || (TARGET_IPHONE_SIMULATOR)
#define KS_PLATFORM_IPHONE 1
#else
#define KS_PLATFORM_OSX 1
#endif
//////////////////////////////////////////////////////////////////////////
#elif defined(__ANDROID__)
#define KS_PLATFORM_ANDROID 1
//////////////////////////////////////////////////////////////////////////
#elif defined(__native_client__)
#define KS_PLATFORM_NACL 1
#elif defined(linux) || defined(__linux__)
#define KS_PLATFORM_LINUX 1
#endif

#ifndef KS_ARCHITECTURE_32
#define KS_ARCHITECTURE_32 0
#endif
#ifndef KS_ARCHITECTURE_64
#define KS_ARCHITECTURE_64 0
#endif
/* Find the arch type */
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__) || defined(__arch64__) || defined(_LP64)
#define KS_ARCHITECTURE_64 1
#else
#define KS_ARCHITECTURE_32 1
#endif

#ifndef KS_LITTLE_ENDIAN
#define KS_LITTLE_ENDIAN 0
#endif
#ifndef KS_BIG_ENDIAN
#define KS_BIG_ENDIAN 0
#endif
// Endian
#if (defined(__APPLE__) && defined(__BIG_ENDIAN__)) || KS_PLATFORM_WIN
#define KS_BIG_ENDIAN 1
#else
#define KS_LITTLE_ENDIAN 1
#endif

// log macro
#define LOG_HELPER(LOG_LEVEL, ...) \
        g_runtime_global_context.m_logger_system->log(LOG_LEVEL, "[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__);

#define LOG_DEBUG(...) LOG_HELPER(LogSystem::LogLevel::debug, __VA_ARGS__);

#define LOG_INFO(...) LOG_HELPER(LogSystem::LogLevel::info, __VA_ARGS__);

#define LOG_WARN(...) LOG_HELPER(LogSystem::LogLevel::warn, __VA_ARGS__);

#define LOG_ERROR(...) LOG_HELPER(LogSystem::LogLevel::error, __VA_ARGS__);

#define LOG_FATAL(...) LOG_HELPER(LogSystem::LogLevel::fatal, __VA_ARGS__);

#define PolitSleep(_ms) std::this_thread::sleep_for(std::chrono::milliseconds(_ms));

#define PolitNameOf(name) #name

#ifdef _DEBUG
#define KSMAC_ASSERT(statement) assert(statement)
#else
#define KSMAC_ASSERT(statement)
#endif

/*
 * Types that are (so far) the same on all platforms
 */
typedef signed char ks_int8_t;
typedef unsigned char ks_uint8_t;
typedef signed short int ks_int16_t;
typedef unsigned short int ks_uint16_t;

#if KS_PLATFORM_WIN
#include <tchar.h>
#include <memory.h>
#include <assert.h>
#include <sys/stat.h>
#include <intrin.h>
#include <windows.h>
#pragma warning(disable : 4251) // 去除模板导出编译的警告
#pragma warning(disable : 4595)
#define KS_TCHAR TCHAR
#define KS_DWORD DWORD
#else
#include <thread>
#include <mutex>
#include <ctype.h>
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

#if KS_ARCHITECTURE_64
#define ks_ssize_t signed long long
#define ks_usize_t unsigned long long
#else
#define ks_ssize_t signed int
#define ks_usize_t unsigned int
#endif
namespace Kratos
{
        inline void KSMemset(void *pDest, int iC, ks_usize_t uiCount)
        {
                memset(pDest, iC, uiCount);
        }

        inline void KSStrCopy(KS_TCHAR *pDest, unsigned int uiCount, const KS_TCHAR *pSource)
        {
#if KS_PLATFORM_WIN
                _tcscpy_s(pDest, uiCount, pSource);
#else
                strncpy(pDest, pSource, uiCount);
#endif
        }

        inline int KSStrCmp(const TCHAR *String1, const TCHAR *String2)
        {
#ifdef KS_PLATFORM_WIN
                return _tcscmp(String1, String2);
#else
                return;
#endif
        }
        inline int KSStrnCmp(const TCHAR *String1, const TCHAR *String2, unsigned int uiMaxNum)
        {
#ifdef KS_PLATFORM_WIN
                return _tcsncmp(String1, String2, uiMaxNum);
#else
                return;
#endif
        }

        inline unsigned int KSStrLen(const KS_TCHAR *pStr)
        {
#if KS_PLATFORM_WIN
                return (unsigned int)_tcslen(pStr);
#else
                return (unsigned int)strlen(pStr);
#endif
        }

        inline void KSStrcat(KS_TCHAR *pDest, unsigned int uiCount, const KS_TCHAR *pSource)
        {
#if KS_PLATFORM_WIN
                _tcscat_s(pDest, uiCount, pSource);
#else
                strncat(pDest, pSource, uiCount);
#endif
        }

        inline bool KSMemcpy(void *pDest, const void *pSrc, ks_usize_t uiCountSize, ks_usize_t uiDestBufferSize = 0)
        {
                if (!uiDestBufferSize)
                {
                        uiDestBufferSize = uiCountSize;
                }
#if KS_PLATFORM_WIN
                return (memcpy_s(pDest, uiDestBufferSize, pSrc, uiCountSize) == 0);
#else
#define __STDC_WANT_LIB_EXT1__ 1
#ifdef __STDC_LIB_EXT1__
                int r = memcpy_s(pDest, uiDestBufferSize, pSrc, uiCountSize);
                return r == 0;
#endif
#endif
        }

        inline bool KSIsSpace(int c)
        {
#if KS_PLATFORM_WIN
                return _istspace(c);
#else
                return isspace(c);
#endif
        }

        inline void KSScanf(KS_TCHAR *Buf, const KS_TCHAR *_Format, va_list pArgs)
        {
#if KS_PLATFORM_WIN
                _stscanf_s(Buf, _Format, pArgs);
#else
#define __STDC_WANT_LIB_EXT1__ 1
#ifdef __STDC_LIB_EXT1__
                sscanf_s(Buf, _Format, pArgs);
#endif
#endif
        }

        inline unsigned int KSTlsAlloc()
        {
#if KS_PLATFORM_WIN
                return TlsAlloc();
#else
                // LOG_WARN("No Implement!");
                return 0;
#endif
        }
        inline void *KSGetTlsValue(unsigned int TlsSolt)
        {
#if KS_PLATFORM_WIN
                return TlsGetValue(TlsSolt);
#else
                // LOG_WARN("No Implement!");
                return nullptr;
#endif
        }
        inline bool KSSetTlsValue(unsigned int TlsSolt, void *TlsValue)
        {
#if KS_PLATFORM_WIN
                return TlsSetValue(TlsSolt, TlsValue);
#else
                // LOG_WARN("No Implement!");
                return false;
#endif
        }
        inline bool KSTlsFree(unsigned int TlsSolt)
        {
#if KS_PLATFORM_WIN
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
