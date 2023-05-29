#include "runtime/core/math/vector3.h"
#include "runtime/core/math/matrix3X3.h"

namespace Kratos
{
    const Vector3 Vector3::ms_Up = Vector3(0.0f, 1.0f, 0.0f);
    const Vector3 Vector3::ms_Right = Vector3(1.0f, 0.0f, 0.0f);
    const Vector3 Vector3::ms_Front = Vector3(0.0f, 0.0f, 1.0f);
    const Vector3 Vector3::ms_Zero = Vector3(0.0f, 0.0f, 0.0f);
    const Vector3 Vector3::ms_One = Vector3(1.0f, 1.0f, 1.0f);

    Vector3::Vector3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector3::Vector3(KSREAL _x, KSREAL _y, KSREAL _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    /*************************************inline************************************************/
    inline void Vector3::Set(KSREAL _x, KSREAL _y, KSREAL _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    inline KSREAL Vector3::GetLength() const
    {
        return Math::sqrt(x * x + y * y + z * z);
    }

    inline KSREAL Vector3::GetSqrLength() const
    {
        return (x * x + y * y + z * z);
    }

    inline void Vector3::Negate()
    {
        x = -x;
        y = -y;
        z = -z;
    }

    inline void Vector3::Normalize()
    {
        KSREAL scalar = x * x + y * y + z * z;
        if (scalar > EPSILON_E4)
        {
            scalar = (KSREAL)1.0f / SQRT(scalar);
            x *= scalar;
            y *= scalar;
            z *= scalar;
        }
        else
        {
            *this = Vector3::ms_Zero;
        }
    }

    inline void Vector3::Cross(const Vector3 &v1, const Vector3 &v2)
    {
        x = v1.y * v2.z - v1.z * v2.y;
        y = v1.z * v2.x - v1.x * v2.z;
        z = v1.x * v2.y - v1.y * v2.x;
    }

    KSREAL Vector3::Dot(const Vector3 &v) const
    {
        return (v.x * x + v.y * y + v.z * z);
    }

    KSREAL Vector3::AngleWith(Vector3 &v)
    {
        return (KSREAL)acos(((*this).Dot(v)) / (this->GetLength() * v.GetLength()));
    }

    inline void Vector3::Create(const Vector3 &v1, const Vector3 &v2)
    {

        x = v2.x - v1.x;
        y = v2.y - v1.y;
        z = v2.z - v1.z;
    }

    bool Vector3::IsParallel(const Vector3 &Vector) const
    {
        KSREAL t0, t1;
        bool temp = 0;
        t0 = x * Vector.y;
        t1 = y * Vector.x;

        if (Math::abs(t0 - t1) > EPSILON_E4)
            temp = 1;

        t0 = y * Vector.z;
        t1 = z * Vector.y;

        if (Math::abs(t0 - t1) > EPSILON_E4 && temp)
            return 1;
        else
            return 0;
    }

    Vector3 Vector3::ReflectDir(const Vector3 &N) const
    {
        return N * Dot(N) * 2 + *this;
    }

    Vector3 Vector3::operator*(KSREAL scalar) const
    {

        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 Vector3::operator/(KSREAL scalar) const
    {

        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    Vector3 Vector3::operator+(KSREAL scalar) const
    {

        return Vector3(x + scalar, y + scalar, z + scalar);
    }

    Vector3 Vector3::operator-(KSREAL scalar) const
    {

        return Vector3(x - scalar, y - scalar, z - scalar);
    }

    Vector3 Vector3::operator+(const Vector3 &v) const
    {

        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 Vector3::operator-(const Vector3 &v) const
    {

        return Vector3(x - v.x, y - v.y, z - v.z);
    }
    Vector3 Vector3::operator/(const Vector3 &v) const
    {

        return Vector3(x / v.x, y / v.y, z / v.z);
    }

    Vector3 Vector3::operator*(const Vector3 &v) const
    {

        return Vector3(x * v.x, y * v.y, z * v.z);
    }

    void Vector3::operator/=(const Vector3 &v)
    {

        x /= v.x;
        y /= v.y;
        z /= v.z;
    }

    void Vector3::operator*=(const Vector3 &v)
    {
        x *= v.x;
        y *= v.y, z *= v.z;
    }

    Vector3 Vector3::operator*(const Matrix3X3 &matirx) const
    {
        Vector3 vcResult;
        vcResult.x = x * matirx._00 + y * matirx._10 + z * matirx._20;
        vcResult.y = x * matirx._01 + y * matirx._11 + z * matirx._21;
        vcResult.z = x * matirx._02 + y * matirx._12 + z * matirx._22;
        return vcResult;
    }

} // namespace Kratos