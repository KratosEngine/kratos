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

	inline int KSRand() { return rand(); }
	inline void KSRandInit(int Seed) { srand(Seed); }
	inline KSREAL KSFRand() { return KSRand() / (KSREAL)RAND_MAX; }
	// inline unsigned int Rounding(KSREAL fNum)
	// {
	// 	return unsigned int(fNum + 0.5f);
	// }

	/** Return true if value is finite (not NaN and not Infinity). */
	inline bool IsFinite(KSREAL A)
	{
		return ((*(unsigned int *)&A) & 0x7F800000) != 0x7F800000;
	}
	inline bool IsNegativeFloat(const KSREAL &A)
	{
		return ((*(unsigned int *)&A) >= (unsigned int)0x80000000); // Detects sign bit.
	}

	inline unsigned int CalcAlign(unsigned int n, unsigned int align)
	{
		return ((n + align - 1) & (~(align - 1)));
	}

	inline KSREAL RadianToAngle(KSREAL Radian)
	{
		// return ( Radian * 180.0f ) / Math_PI;
		return 57.29578f * Radian;
	}
	inline KSREAL AngleToRadian(KSREAL Angle)
	{
		// return ( Angle * Math_PI ) /  180.0f;
		return 0.01745329f * Angle;
	}
	inline bool IsTwoPower(unsigned int uiN)
	{
		return !(uiN & (uiN - 1));
	}

	inline unsigned short FloatToHalf(KSREAL Value)
	{
		unsigned int Result;

		unsigned int IValue = ((unsigned int *)(&Value))[0];
		unsigned int Sign = (IValue & 0x80000000U) >> 16U;
		IValue = IValue & 0x7FFFFFFFU; // Hack off the sign

		if (IValue > 0x47FFEFFFU)
		{
			// The number is too large to be represented as a half.  Saturate to infinity.
			Result = 0x7FFFU;
		}
		else
		{
			if (IValue < 0x38800000U)
			{
				// The number is too small to be represented as a normalized half.
				// Convert it to a denormalized value.
				unsigned int Shift = 113U - (IValue >> 23U);
				IValue = (0x800000U | (IValue & 0x7FFFFFU)) >> Shift;
			}
			else
			{
				// Rebias the exponent to represent the value as a normalized half.
				IValue += 0xC8000000U;
			}

			Result = ((IValue + 0x0FFFU + ((IValue >> 13U) & 1U)) >> 13U) & 0x7FFFU;
		}
		return (unsigned short)(Result | Sign);
	}

	inline KSREAL HalfToFloat(unsigned short Value)
	{
		unsigned int Mantissa;
		unsigned int Exponent;
		unsigned int Result;

		Mantissa = (unsigned int)(Value & 0x03FF);

		if ((Value & 0x7C00) != 0) // The value is normalized
		{
			Exponent = (unsigned int)((Value >> 10) & 0x1F);
		}
		else if (Mantissa != 0) // The value is denormalized
		{
			// Normalize the value in the resulting KSREAL
			Exponent = 1;

			do
			{
				Exponent--;
				Mantissa <<= 1;
			} while ((Mantissa & 0x0400) == 0);

			Mantissa &= 0x03FF;
		}
		else // The value is zero
		{
			Exponent = (unsigned int)-112;
		}

		Result = ((Value & 0x8000) << 16) | // Sign
				 ((Exponent + 112) << 23) | // Exponent
				 (Mantissa << 13);			// Mantissa

		return *(KSREAL *)&Result;
	}

	//=====================================Compress=====================================
	// f must [0,1]
	inline unsigned int CompressUnitFloat(KSREAL f, unsigned int Bit = 16)
	{
		unsigned int nIntervals = 1 << Bit;
		KSREAL scaled = f * (nIntervals - 1);
		unsigned int rounded = (unsigned int)(scaled + 0.5f);
		if (rounded > nIntervals - 1)
		{
			rounded = nIntervals - 1;
		}
		return rounded;
	}
	inline unsigned int CompressFloat(KSREAL f, KSREAL Max, KSREAL Min, unsigned int Bit = 16)
	{
		KSREAL Unitf = (f - Min) / (Max - Min);
		return CompressUnitFloat(Unitf, Bit);
	}
	inline KSREAL DecompressUnitFloat(unsigned int quantized, unsigned int Bit = 16)
	{
		unsigned int nIntervals = 1 << Bit;
		KSREAL IntervalSize = 1.0f / (nIntervals - 1);

		return quantized * IntervalSize;
	}
	inline KSREAL DecompressFloat(unsigned int quantized, KSREAL Max, KSREAL Min, unsigned int Bit = 16)
	{
		KSREAL Unitf = DecompressUnitFloat(quantized, Bit);
		return (Min + Unitf * (Max - Min));
	}

	inline KSREAL ClampAxis(KSREAL Angle)
	{
		// returns Angle in the range (-360,360)
		Angle = FMOD(Angle, 360.f);

		if (Angle < 0.f)
		{
			// shift to [0,360) range
			Angle += 360.f;
		}

		return Angle;
	}

	inline KSREAL NormalizeAxis(KSREAL Angle)
	{
		// returns Angle in the range [0,360)
		Angle = ClampAxis(Angle);

		if (Angle > 180.f)
		{
			// shift to (-180,180]
			Angle -= 360.f;
		}

		return Angle;
	}
	inline int FastLog2(int x)
	{
		float fx;
		unsigned int ix, exp;
		fx = (float)x;
		ix = *(unsigned int *)&fx;
		exp = (ix >> 23) & 0xFF;
		return exp - 127;
	}
	//-360.....360 can use
	inline KSREAL ClampAngle(KSREAL AngleDegrees, KSREAL MinAngleDegrees, KSREAL MaxAngleDegrees)
	{
		KSREAL MaxDelta = ClampAxis(MaxAngleDegrees - MinAngleDegrees) * 0.5f; // 0..180
		KSREAL RangeCenter = ClampAxis(MinAngleDegrees + MaxDelta);			   // 0..360
		KSREAL DeltaFromCenter = NormalizeAxis(AngleDegrees - RangeCenter);	   // -180..180

		// maybe clamp to nearest edge
		if (DeltaFromCenter > MaxDelta)
		{
			return NormalizeAxis(RangeCenter + MaxDelta);
		}
		else if (DeltaFromCenter < -MaxDelta)
		{
			return NormalizeAxis(RangeCenter - MaxDelta);
		}

		// already in range, just return it
		return NormalizeAxis(AngleDegrees);
	}

	inline KSREAL FastAtan2(KSREAL Y, KSREAL X)
	{
		// return atan2f(Y,X);
		//  atan2f occasionally returns NaN with perfectly valid input (possibly due to a compiler or library bug).
		//  We are replacing it with a minimax approximation with a max relative error of 7.15255737e-007 compared to the C library function.
		//  On PC this has been measured to be 2x faster than the std C version.
		const KSREAL absX = FABS(X);
		const KSREAL absY = FABS(Y);
		const bool yAbsBigger = (absY > absX);
		KSREAL t0 = yAbsBigger ? absY : absX; // Max(absY, absX)
		KSREAL t1 = yAbsBigger ? absX : absY; // Min(absX, absY)

		if (t0 == 0.f)
			return 0.f;

		KSREAL t3 = t1 / t0;
		KSREAL t4 = t3 * t3;

		static const KSREAL c[7] = {
			+7.2128853633444123e-03f,
			-3.5059680836411644e-02f,
			+8.1675882859940430e-02f,
			-1.3374657325451267e-01f,
			+1.9856563505717162e-01f,
			-3.3324998579202170e-01f,
			+1.0f};

		t0 = c[0];
		t0 = t0 * t4 + c[1];
		t0 = t0 * t4 + c[2];
		t0 = t0 * t4 + c[3];
		t0 = t0 * t4 + c[4];
		t0 = t0 * t4 + c[5];
		t0 = t0 * t4 + c[6];
		t3 = t0 * t3;

		t3 = yAbsBigger ? (0.5f * Math_PI) - t3 : t3;
		t3 = (X < 0.0f) ? Math_PI - t3 : t3;
		t3 = (Y < 0.0f) ? -t3 : t3;

		return t3;
	}

	inline KSREAL Fmod(KSREAL X, KSREAL Y)
	{
		if (FABS(Y) <= EPSILON_E8)
		{
			return 0.f;
		}
		const float Div = (X / Y);
		// All floats where abs(f) >= 2^23 (8388608) are whole numbers so do not need truncation, and avoid overflow in TruncToFloat as they get even larger.
		const float Quotient = FABS(Div) < 8388608.f ? int(Div) : Div;
		float IntPortion = Y * Quotient;

		// Rounding and imprecision could cause IntPortion to exceed X and cause the result to be outside the expected range.
		// For example Fmod(55.8, 9.3) would result in a very small negative value!
		if (FABS(IntPortion) > FABS(X))
		{
			IntPortion = X;
		}

		const float Result = X - IntPortion;
		return Result;
	}

	inline void SinCos(float *ScalarSin, float *ScalarCos, float Value)
	{
		// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
		KSREAL quotient = (Math_INV_PI * 0.5f) * Value;
		if (Value >= 0.0f)
		{
			quotient = (KSREAL)((int)(quotient + 0.5f));
		}
		else
		{
			quotient = (KSREAL)((int)(quotient - 0.5f));
		}
		KSREAL y = Value - (2.0f * Math_PI) * quotient;

		// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
		KSREAL sign;
		if (y > Math_PI2)
		{
			y = Math_PI - y;
			sign = -1.0f;
		}
		else if (y < -Math_PI2)
		{
			y = -Math_PI - y;
			sign = -1.0f;
		}
		else
		{
			sign = +1.0f;
		}

		KSREAL y2 = y * y;

		// 11-degree minimax approximation
		*ScalarSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

		// 10-degree minimax approximation
		KSREAL p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
		*ScalarCos = sign * p;
	}

	// Note:  We use Math_FASTASIN_VSPI2 instead of HALF_PI inside of FastASin(), since it was the value that accompanied the minimax coefficients below.
	// It is important to use exactly the same value in all places inside this function to ensure that FastASin(0.0f) == 0.0f.
	// For comparison:
	//		Math_PI2				== 1.57079632679f == 0x3fC90FDB
	//		Math_HALF_PI3			== 1.5707963050f  == 0x3fC90FDA

	/**
	 * Computes the ASin of a scalar value.
	 *
	 * @param Value  input angle
	 * @return ASin of Value
	 */
	inline KSREAL FastAsin(float Value)
	{
		// Clamp input to [-1,1].
		bool nonnegative = (Value >= 0.0f);
		KSREAL x = Math::abs(Value);
		KSREAL omx = 1.0f - x;
		if (omx < 0.0f)
		{
			omx = 0.0f;
		}
		KSREAL root = SQRT(omx);
		// 7-degree minimax approximation
		KSREAL result = ((((((-0.0012624911f * x + 0.0066700901f) * x - 0.0170881256f) * x + 0.0308918810f) * x - 0.0501743046f) * x + 0.0889789874f) * x - 0.2145988016f) * x + Math_FASTASIN_VSPI2;
		result *= root; // acos(|x|)
		// acos(x) = pi - acos(-x) when x < 0, asin(x) = pi/2 - acos(x)
		return (nonnegative ? Math_FASTASIN_VSPI2 - result : result - Math_FASTASIN_VSPI2);
	}

} // namespace Kratos