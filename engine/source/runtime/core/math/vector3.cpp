#include "runtime/core/math/vector3.h"
#include "runtime/core/math/matrix3X3.h"

namespace Kratos
{
    const vector3 vector3::ms_Up = vector3(0.0f, 1.0f, 0.0f);
    const vector3 vector3::ms_Right = vector3(1.0f, 0.0f, 0.0f);
    const vector3 vector3::ms_Front = vector3(0.0f, 0.0f, 1.0f);
    const vector3 vector3::ms_Zero = vector3(0.0f, 0.0f, 0.0f);
    const vector3 vector3::ms_One = vector3(1.0f, 1.0f, 1.0f);

    vector3::vector3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    vector3::vector3(KSREAL _x, KSREAL _y, KSREAL _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    /*************************************inline************************************************/
    inline void vector3::Set(KSREAL _x, KSREAL _y, KSREAL _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    inline KSREAL vector3::GetLength() const
    {
        return Math::sqrt(x * x + y * y + z * z);
    }

    inline KSREAL vector3::GetSqrLength() const
    {
        return (x * x + y * y + z * z);
    }

    inline void vector3::Negate()
    {
        x = -x;
        y = -y;
        z = -z;
    }

    inline void vector3::Normalize()
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
            *this = vector3::ms_Zero;
        }
    }

    inline void vector3::Cross(const vector3 &v1, const vector3 &v2)
    {
        x = v1.y * v2.z - v1.z * v2.y;
        y = v1.z * v2.x - v1.x * v2.z;
        z = v1.x * v2.y - v1.y * v2.x;
    }

    KSREAL vector3::Dot(const vector3 &v) const
    {
        return (v.x * x + v.y * y + v.z * z);
    }

    KSREAL vector3::AngleWith(vector3 &v)
    {
        return (KSREAL)acos(((*this).Dot(v)) / (this->GetLength() * v.GetLength()));
    }

    inline void vector3::Create(const vector3 &v1, const vector3 &v2)
    {

        x = v2.x - v1.x;
        y = v2.y - v1.y;
        z = v2.z - v1.z;
    }

    bool vector3::IsParallel(const vector3 &Vector) const
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

    vector3 vector3::ReflectDir(const vector3 &N) const
    {
        return N * Dot(N) * 2 + *this;
    }

    vector3 vector3::operator*(KSREAL scalar) const
    {

        return vector3(x * scalar, y * scalar, z * scalar);
    }

    vector3 vector3::operator/(KSREAL scalar) const
    {

        return vector3(x / scalar, y / scalar, z / scalar);
    }

    vector3 vector3::operator+(KSREAL scalar) const
    {

        return vector3(x + scalar, y + scalar, z + scalar);
    }

    vector3 vector3::operator-(KSREAL scalar) const
    {

        return vector3(x - scalar, y - scalar, z - scalar);
    }

    vector3 vector3::operator+(const vector3 &v) const
    {

        return vector3(x + v.x, y + v.y, z + v.z);
    }

    vector3 vector3::operator-(const vector3 &v) const
    {

        return vector3(x - v.x, y - v.y, z - v.z);
    }
    vector3 vector3::operator/(const vector3 &v) const
    {

        return vector3(x / v.x, y / v.y, z / v.z);
    }

    vector3 vector3::operator*(const vector3 &v) const
    {

        return vector3(x * v.x, y * v.y, z * v.z);
    }

    void vector3::operator/=(const vector3 &v)
    {

        x /= v.x;
        y /= v.y;
        z /= v.z;
    }

    void vector3::operator*=(const vector3 &v)
    {
        x *= v.x;
        y *= v.y, z *= v.z;
    }

    vector3 vector3::operator*(const matrix3X3 &matirx) const
    {
        vector3 vcResult;
        vcResult.x = x * matirx._00 + y * matirx._10 + z * matirx._20;
        vcResult.y = x * matirx._01 + y * matirx._11 + z * matirx._21;
        vcResult.z = x * matirx._02 + y * matirx._12 + z * matirx._22;
        return vcResult;
    }

} // namespace Kratos