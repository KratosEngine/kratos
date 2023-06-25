#pragma once

#include "runtime/core/math/math.h"

namespace Kratos
{
    class quaternion
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

        quaternion(void);
        quaternion(KSREAL _x, KSREAL _y, KSREAL _z, KSREAL _w);
        void Set(KSREAL _x, KSREAL _y, KSREAL _z, KSREAL _w);

        void Normalize(void);
		//����
		KSREAL Dot(const quaternion& q)const;
        //����
        quaternion operator ~(void) const;
    };

} // namespace Kratos