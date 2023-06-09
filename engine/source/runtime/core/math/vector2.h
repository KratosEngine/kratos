
#pragma once

#include "runtime/core/math/math.h"

namespace Kratos
{
    class vector2
    {
    public:
        union
        {
            KSREAL m[2];
            struct
            {
                KSREAL x, y;
            };
        };

        vector2(void);
        vector2(KSREAL _x, KSREAL _y);

        // arithmetic updates
        void operator+=(const vector2 &rhs);
        void operator-=(const vector2 &rhs);

        void operator*=(KSREAL scalar);
        void operator/=(KSREAL scalar);
        void operator+=(KSREAL scalar);
        void operator-=(KSREAL scalar);

        /** Calculates the dot (scalar) product of this vector with another.
        @remarks
        The dot product can be used to calculate the angle between 2
        vectors. If both are unit vectors, the dot product is the
        cosine of the angle; otherwise the dot product must be
        divided by the product of the lengths of both vectors to get
        the cosine of the angle. This result can further be used to
        calculate the distance of a point from a plane.
        @param
        vec Vector with which to calculate the dot product (together
        with this one).
        @returns
        A KSREAL representing the dot product value.
        */
        KSREAL dotProduct(const vector2 &rhs) const;

        bool operator==(const vector2 &rhs) const;

        // arithmetic operations
        vector2 operator*(KSREAL scalar) const;
        vector2 operator/(KSREAL scalar) const;
        vector2 operator+(KSREAL scalar) const;
        vector2 operator-(KSREAL scalar) const;

		vector2 operator + (const vector2 &rhs)const;
		vector2 operator - (const vector2 &rhs)const;

        inline void Set(KSREAL _x, KSREAL _y);

        //Normalizes the vector
        inline void Normalize();
    };
    
} // namespace Kratos
