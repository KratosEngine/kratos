#pragma once

#include "runtime/core/math/math_macro.h"

namespace Kratos
{
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

}