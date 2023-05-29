
#pragma once

#include "runtime/core/math/Math.h"

namespace Kratos
{
    class Vector2
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

        Vector2(void);
        Vector2(KSREAL _x, KSREAL _y);

        // arithmetic updates
        void operator+=(const Vector2 &rhs);
        void operator-=(const Vector2 &rhs);

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
        KSREAL dotProduct(const Vector2 &rhs) const;

        bool operator==(const Vector2 &rhs) const;

        // arithmetic operations
        Vector2 operator*(KSREAL scalar) const;
        Vector2 operator/(KSREAL scalar) const;
        Vector2 operator+(KSREAL scalar) const;
        Vector2 operator-(KSREAL scalar) const;

		Vector2 operator + (const Vector2 &rhs)const; 
		Vector2 operator - (const Vector2 &rhs)const; 

        inline void Set(KSREAL _x, KSREAL _y);

        //Normalizes the vector
        inline void Normalize();
    };
    
} // namespace Kratos
