#include "runtime/core/math/vector3.h"

namespace Kratos
{
    KSREAL vector3::SquaredDistance(const vector3 &Point) const
    {
        return (x * Point.x + y * Point.y + z * Point.z);
    }
    
} // namespace Kratos
