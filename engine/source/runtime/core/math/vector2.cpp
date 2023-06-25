
#include "runtime/core/math/vector2.h"

namespace Kratos
{
    vector2::vector2()
    {
        x = 0;
        y = 0;
    }

    vector2::vector2(KSREAL _x, KSREAL _y)
    {
        x = _x;
        y = _y;
    }

    void vector2::operator+=(const vector2 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
    }

    void vector2::operator-=(const vector2 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
    }

    void vector2::operator*=(KSREAL scalar)
    {
        x *= scalar;
        y *= scalar;
    }

    void vector2::operator/=(KSREAL scalar)
    {
        x /= scalar;
        y /= scalar;
    }

    void vector2::operator+=(KSREAL scalar)
    {
        x += scalar;
        y += scalar;
    }

    void vector2::operator-=(KSREAL scalar)
    {
        x -= scalar;
        y -= scalar;
    }

    KSREAL vector2::dotProduct(const vector2 &rhs) const
    {
        return (x * rhs.x + y * rhs.y);
    }

    bool vector2::operator==(const vector2 &rhs) const
    {
        for (unsigned int i = 0; i < 2; i++)
        {
            if (Math::abs(m[i] - rhs.m[i]) > EPSILON_E4)
            {
                return false;
            }
        }
        return true;
    }

    vector2 vector2::operator*(KSREAL scalar) const
    {
        return vector2(x * scalar, y * scalar);
    }

    vector2 vector2::operator/(KSREAL scalar) const
    {
        return vector2(x / scalar, y / scalar);
    }

    vector2 vector2::operator+(KSREAL scalar) const
    {
        return vector2(x + scalar, y + scalar);
    }

    vector2 vector2::operator-(KSREAL scalar) const
    {
        return vector2(x - scalar, y - scalar);
    }

    vector2 vector2::operator+(const vector2 &rhs) const
    {
        return vector2(x + rhs.x, y + rhs.y);
    }

    vector2 vector2::operator-(const vector2 &rhs) const
    {
        return vector2(x - rhs.x, y - rhs.y);
    }

    inline void vector2::Set(KSREAL _x, KSREAL _y)
    {
        x = _x;
        y = _y;
    }

    // 对于任何非零向量。向量除以它的大小（模）
    inline void vector2::Normalize()
    {
        KSREAL scalar = x * x + y * y;
        if (scalar > EPSILON_E4)
        {
            scalar = (KSREAL)1.0f / Math::sqrt(scalar);
            x *= scalar;
            y *= scalar;
        }
        else
        {
            Set(0.0f, 0.0f);
        }
    }
    
} // namespace Kratos
