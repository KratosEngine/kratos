#pragma once

#include "runtime/core/math/Math.h"
#include "runtime/core/math/vector3.h"

namespace Kratos
{
    class Matrix3X3
    {
    public:
        const static Matrix3X3 ms_CameraViewRight;
        const static Matrix3X3 ms_CameraViewLeft;
        const static Matrix3X3 ms_CameraViewUp;
        const static Matrix3X3 ms_CameraViewDown;
        const static Matrix3X3 ms_CameraViewFront;
        const static Matrix3X3 ms_CameraViewBack;

        union
        {
            KSREAL m[9];
            struct
            {
                KSREAL _00, _01, _02;
                KSREAL _10, _11, _12;
                KSREAL _20, _21, _22;
            };
            KSREAL M[3][3];
        };

        Matrix3X3();
        Matrix3X3(KSREAL m00, KSREAL m01, KSREAL m02,
                  KSREAL m10, KSREAL m11, KSREAL m12,
                  KSREAL m20, KSREAL m21, KSREAL m22);

        Matrix3X3 operator*(KSREAL scalar) const;
        Matrix3X3 operator+(KSREAL scalar) const;
        Matrix3X3 operator-(KSREAL scalar) const;
        Matrix3X3 operator+(const Matrix3X3 &matirx) const;
        Matrix3X3 operator-(const Matrix3X3 &matirx) const;

        void operator*=(KSREAL scalar);
        void operator+=(KSREAL scalar);
        void operator-=(KSREAL scalar);
        void operator+=(const Matrix3X3 &matirx);
        void operator-=(const Matrix3X3 &matirx);
        bool operator==(const Matrix3X3 &v) const;

        void CreateRot(const Vector3 &U, const Vector3 &V, const Vector3 &N); // 创建旋转矩阵
        void CreateScale(KSREAL fX, KSREAL fY, KSREAL fZ);                    // 创建缩放矩阵

        /*********************************** inline *************************************/
        inline void Identity(void);                                // 单位矩阵
        inline void TransposeOf(const Matrix3X3 &matirx);          // 转置
        inline void InverseOf(const Matrix3X3 &matirx);            // 求逆
        inline KSREAL Det() const;                                 // 求判别式
        inline Matrix3X3 operator*(const Matrix3X3 &matirx) const; // 矩阵相乘
        inline Vector3 operator*(const Vector3 &vc) const;         // 矩阵和向量乘
    };

} // namespace Kratos
