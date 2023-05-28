#include "runtime/core/math/math_macro.h"

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

        Vector2();
        Vector2(KSREAL _x, KSREAL _y);
    };
}