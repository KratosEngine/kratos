
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
}