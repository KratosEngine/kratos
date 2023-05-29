#pragma once

#include "runtime/core/math/math.h"

namespace Kratos
{
    class Quaternion
    {
    public:
        union
        {
            KSREAL m[4];
            struct
            {
                KSREAL x, y, z, w;
            };
        };

        Quaternion(void);
        Quaternion(KSREAL _x, KSREAL _y, KSREAL _z, KSREAL _w);
        void Set(KSREAL _x, KSREAL _y, KSREAL _z, KSREAL _w);

        void Normalize(void);

        Quaternion operator ~(void) const;
    };

} // namespace Kratos