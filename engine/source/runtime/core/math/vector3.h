#pragma once

#include "runtime/core/math/math.h"

namespace Kratos
{
    class matrix3X3;
    class vector3   //表示一个三维向量｜一个点
    {
    public:
        // special points
        const static vector3 ms_Up;
        const static vector3 ms_Right;
        const static vector3 ms_Front;
        const static vector3 ms_Zero;
        const static vector3 ms_One;

        union
        {
            KSREAL m[3];
            struct
            {
                KSREAL x, y, z;
            };
        };

        vector3();
        vector3(KSREAL _x, KSREAL _y, KSREAL _z);

        /*************************************inline************************************************/
        inline void Set(KSREAL _x, KSREAL _y, KSREAL _z);
        inline KSREAL GetLength() const;                         // 长度
        inline KSREAL GetSqrLength() const;                      // 长度平方
        inline void Negate();                                    // 乘以-1
        inline void Normalize();                                 // 单位化
        inline void Cross(const vector3 &v1, const vector3 &v2); // 叉积
        KSREAL Dot(const vector3 &v) const;                      // 点积

        KSREAL AngleWith(vector3 &v);                      // 两个向量的夹角(弧度)
        void Create(const vector3 &v1, const vector3 &v2); // 构造向量从点v1到v2
        bool IsParallel(const vector3 &Vector) const;      // 两个向量是否平行

        /*            N     _
               \	/|\   /|
            Dir	\	 |   /  Reflect
                _\|  |  /
        --------------------------
        */
        vector3 ReflectDir(const vector3 &N) const;

        vector3 operator*(KSREAL scalar) const;
        vector3 operator/(KSREAL scalar) const;
        vector3 operator+(KSREAL scalar) const;
        vector3 operator-(KSREAL scalar) const;

        vector3 operator+(const vector3 &v) const;
        vector3 operator-(const vector3 &v) const;
        vector3 operator/(const vector3 &v) const;
        vector3 operator*(const vector3 &v) const;
        void operator/=(const vector3 &v);
        void operator*=(const vector3 &v);

        vector3 operator*(const matrix3X3 &matirx) const;

        /********************************distance******************************************/
        KSREAL SquaredDistance(const vector3 &Point) const; // 点和点距离
    };

} // namespace Kratos
