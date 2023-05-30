#pragma once

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
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
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

#include <stdio.h>
#include <string.h>
#if KS_PLATFORM == KS_PLATFORM_WIN
#include <Windows.h>
#include <tchar.h>
#pragma warning(disable : 4251) // 去除模板导出编译的警告
#pragma warning(disable : 4595)
#define KS_TCHAR TCHAR
#else
#define KS_TCHAR char
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
