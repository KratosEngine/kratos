
#include "runtime/core/math/vector2.h"

namespace Kratos
{
    Vector2::Vector2()
    {
        x = 0;
        y = 0;
    }

    Vector2::Vector2(KSREAL _x, KSREAL _y)
    {
        x = _x;
        y = _y;
    }

    void Vector2::operator+=(const Vector2 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
    }

    void Vector2::operator-=(const Vector2 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
    }

    void Vector2::operator*=(KSREAL scalar)
    {
        x *= scalar;
        y *= scalar;
    }

    void Vector2::operator/=(KSREAL scalar)
    {
        x /= scalar;
        y /= scalar;
    }

    void Vector2::operator+=(KSREAL scalar)
    {
        x += scalar;
        y += scalar;
    }

    void Vector2::operator-=(KSREAL scalar)
    {
        x -= scalar;
        y -= scalar;
    }

    KSREAL Vector2::dotProduct(const Vector2 &rhs) const
    {
        return (x * rhs.x + y * rhs.y);
    }

    bool Vector2::operator==(const Vector2 &rhs) const
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

    Vector2 Vector2::operator*(KSREAL scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 Vector2::operator/(KSREAL scalar) const
    {
        return Vector2(x / scalar, y / scalar);
    }

    Vector2 Vector2::operator+(KSREAL scalar) const
    {
        return Vector2(x + scalar, y + scalar);
    }

    Vector2 Vector2::operator-(KSREAL scalar) const
    {
        return Vector2(x - scalar, y - scalar);
    }

    Vector2 Vector2::operator+(const Vector2 &rhs) const
    {
        return Vector2(x + rhs.x, y + rhs.y);
    }

    Vector2 Vector2::operator-(const Vector2 &rhs) const
    {
        return Vector2(x - rhs.x, y - rhs.y);
    }

    inline void Vector2::Set(KSREAL _x, KSREAL _y)
    {
        x = _x;
        y = _y;
    }

    // 对于任何非零向量。向量除以它的大小（模）
    inline void Vector2::Normalize()
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
}