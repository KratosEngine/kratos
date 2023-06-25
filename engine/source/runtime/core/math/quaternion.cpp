#include "runtime/core/math/quaternion.h"

namespace Kratos
{
    quaternion::quaternion(void)
    {
        x = 0.0f,
        y = 0.0f,
        z = 0.0f,
        w = 1.0f;
    }

    quaternion::quaternion(KSREAL _x, KSREAL _y, KSREAL _z, KSREAL _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    void quaternion::Set(KSREAL _x, KSREAL _y, KSREAL _z, KSREAL _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    void quaternion::Normalize(void)
    {
        KSREAL m = Math::sqrt(x * x + y * y + z * z + w * w);
        KSREAL Invm = 1.0f / m;
        x *= Invm;
        y *= Invm;
        z *= Invm;
        w *= Invm;
    }

    KSREAL quaternion::Dot(const quaternion& q) const
    {
        return (w * q.w + x * q.x + y * q.y + z * q.z);
    }

    quaternion quaternion::operator~(void) const
    {
        return quaternion(-x, -y, -z, w);
    }

}