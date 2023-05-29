#include "runtime/core/math/quaternion.h"

namespace Kratos
{
    Quaternion::Quaternion(void)
    {
        x = 0.0f,
        y = 0.0f,
        z = 0.0f,
        w = 1.0f;
    }

    Quaternion::Quaternion(KSREAL _x, KSREAL _y, KSREAL _z, KSREAL _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    void Quaternion::Set(KSREAL _x, KSREAL _y, KSREAL _z, KSREAL _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    void Quaternion::Normalize(void)
    {
        KSREAL m = Math::sqrt(x * x + y * y + z * z + w * w);
        KSREAL Invm = 1.0f / m;
        x *= Invm;
        y *= Invm;
        z *= Invm;
        w *= Invm;
    }

    Quaternion Quaternion::operator~(void) const
    {
        return Quaternion(-x, -y, -z, w);
    }

}