#pragma once

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

#ifndef KS_PLATFORM_WIN
#define KS_PLATFORM_WIN 0
#endif
#ifndef KS_PLATFORM_IPHONE
#define KS_PLATFORM_IPHONE 0
#endif
#ifndef KS_PLATFORM_OSX
#define KS_PLATFORM_OSX 0
#endif
#ifndef KS_PLATFORM_ANDROID
#define KS_PLATFORM_ANDROID 0
#endif
#ifndef KS_PLATFORM_NACL
#define KS_PLATFORM_NACL 0
#endif
#ifndef KS_PLATFORM_LINUX
#define KS_PLATFORM_LINUX 0
#endif

/* Find the arch type */
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#define KS_ARCHITECTURE_64 1
#else
#define KS_ARCHITECTURE_32 1
#endif

// Endian
#ifndef KS_BIG_ENDIAN
#if (defined(__APPLE__) && defined(__BIG_ENDIAN__)) || KS_PLATFORM_WIN
#define KS_BIG_ENDIAN 1
#define KS_LITTLE_ENDIAN 0
#else
#define KS_BIG_ENDIAN 0
#define KS_LITTLE_ENDIAN 1
#endif
#endif
