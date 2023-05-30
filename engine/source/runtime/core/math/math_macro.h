#pragma once

#include <cmath>
#include "runtime/core/base/platform.h"
#include "runtime/core/system/system.h"

namespace Kratos
{

#define KSFLOAT // 精度
#ifdef KSFLOAT
#define KSREAL float
#define SIN(x) sinf(x)
#define COS(x) cosf(x)
#define TAN(x) tanf(x)
#define ASIN(x) asinf(x)
#define ACOS(x) acosf(x)
#define ATAN(x) atanf(x)
#define ATAN2(y, x) atan2f(y, x)
#define SQRT(x) sqrtf(x)
#define POW(x, y) powf(x, y)
#define CEIL(x) ceilf(x)
#define EXP(x) expf(x)
#define EXP2(x) POW(2.0f, x)
#define FMOD(x, y) fmodf(x, y)
#define FLOOR(x) floorf(x)
#define LOG(x) logf(x)
#define LOG2(x) LOG(x) * 1.4426950f
#define FABS(x) fabsf(x)
#else
#define KSREAL double
#define SIN(x) sin(x)
#define COS(x) cos(x)
#define TAN(x) tan(x)
#define ASIN(x) asin(x)
#define ACOS(x) acos(x)
#define ATAN(x) atan(x)
#define ATAN2(y, x) atan2(y, x)
#define SQRT(x) sqrt(x)
#define POW(x, y) pow(x, y)
#define CEIL(x) ceil(x);
#define EXP(x) exp(x);
#define EXP2(x) POW(2.0f, x)
#define FMOD(x, y) fmod(x, y)
#define FLOOR(x) floor(x)
#define LOG(x) log(x)
#define LOG2(x) LOG(x) * 1.4426950f
#define FABS(x) fabs(x)
#endif

// 用来判断两个物体的位置关系
#define KSFRONT			0
#define KSBACK			1
#define KSON			2
#define KSCLIPPED		3
#define KSCULLED		4
#define KSVISIBLE		5
#define KSINTERSECT		3
#define KSOUT			4
#define KSIN			5
#define KSNOINTERSECT	6


} // namespace Kratos