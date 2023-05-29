#pragma once

#include "runtime/core/math/math_macro.h"

namespace Kratos
{
	static const float Math_MIN_CHAR = (-128);
	static const float Math_MAX_CHAR = 127;
	static const float Math_MIN_INT32 = (-2147483647 - 1);
	static const float Math_MAX_INT32 = 2147483647;
	static const float Math_MIN_REAL = 1.175494351e-38F;
	static const float Math_MAX_REAL = 3.402823466e+38F;
	static const float Math_MAX_UINT32 = 0.99999f;
	static const float Math_REAL_1 = 0.99999f;
	static const float Math_PI = 3.1415926535897932f;
	static const float Math_2PI = 2.0f * Math_PI;
	static const float Math_PI2 = 0.5f * Math_PI;
	static const float Math_INV_PI = 0.31830988618f;
	static const float Math_FASTASIN_VSPI2 = 1.5707963050f;

	// 用来判断精度
	static const float EPSILON_E3 = (KSREAL)(1E-3);
	static const float EPSILON_E4 = (KSREAL)(1E-4);
	static const float EPSILON_E5 = (KSREAL)(1E-5);
	static const float EPSILON_E6 = (KSREAL)(1E-6);
	static const float EPSILON_E8 = (KSREAL)(1E-8);

	class Math
	{
	public:
		static KSREAL abs(KSREAL value) { return FABS(value); }
		/** Return true if value is NaN (not a number). */
		static bool isNan(KSREAL A)
		{
			return ((*(unsigned int *)&A) & 0x7FFFFFFF) > 0x7F800000;
		}
		static KSREAL sqrt(KSREAL value) { return SQRT(value); }
	};
} // namespace Kratos