#include "runtime/core/math/Vector3.h"

namespace Kratos
{
    KSREAL Vector3::SquaredDistance(const Vector3 &Point) const
    {
        return (x * Point.x + y * Point.y + z * Point.z);
    }
    
} // namespace Kratos
