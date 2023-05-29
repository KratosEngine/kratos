#pragma once

#include <cmath>

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
#else ifdef KSDOUBLE
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

#define EPSILON_E3 (KSREAL)(1E-3)
#define EPSILON_E4 (KSREAL)(1E-4)
#define EPSILON_E5 (KSREAL)(1E-5)
#define EPSILON_E6 (KSREAL)(1E-6)
#define EPSILON_E8 (KSREAL)(1E-8)

}