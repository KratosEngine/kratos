#pragma once

#include "runtime/core/math/math.h"

namespace Kratos
{
    class Matrix3X3;
    class Vector3
    {
    public:
        // special points
        const static Vector3 ms_Up;
        const static Vector3 ms_Right;
        const static Vector3 ms_Front;
        const static Vector3 ms_Zero;
        const static Vector3 ms_One;

        union
        {
            KSREAL m[3];
            struct
            {
                KSREAL x, y, z;
            };
        };

        Vector3();
        Vector3(KSREAL _x, KSREAL _y, KSREAL _z);

        /*************************************inline************************************************/
        inline void Set(KSREAL _x, KSREAL _y, KSREAL _z);
        inline KSREAL GetLength() const;                         // 长度
        inline KSREAL GetSqrLength() const;                      // 长度平方
        inline void Negate();                                    // 乘以-1
        inline void Normalize();                                 // 单位化
        inline void Cross(const Vector3 &v1, const Vector3 &v2); // 叉积
        KSREAL Dot(const Vector3 &v) const;                      // 点积

        KSREAL AngleWith(Vector3 &v);                      // 两个向量的夹角(弧度)
        void Create(const Vector3 &v1, const Vector3 &v2); // 构造向量从点v1到v2
        bool IsParallel(const Vector3 &Vector) const;      // 两个向量是否平行

        /*            N     _
               \	/|\   /|
            Dir	\	 |   /  Reflect
                _\|  |  /
        --------------------------
        */
        Vector3 ReflectDir(const Vector3 &N) const;

        Vector3 operator*(KSREAL scalar) const;
        Vector3 operator/(KSREAL scalar) const;
        Vector3 operator+(KSREAL scalar) const;
        Vector3 operator-(KSREAL scalar) const;

        Vector3 operator+(const Vector3 &v) const;
        Vector3 operator-(const Vector3 &v) const;
        Vector3 operator/(const Vector3 &v) const;
        Vector3 operator*(const Vector3 &v) const;
        void operator/=(const Vector3 &v);
        void operator*=(const Vector3 &v);

        Vector3 operator*(const Matrix3X3 &matirx) const;

        /********************************distance******************************************/
        KSREAL SquaredDistance(const Vector3 &Point) const; // 点和点距离
    };

} // namespace Kratos
