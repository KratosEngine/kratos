
#include <string.h>

#include "runtime/core/math/matrix3X3.h"

namespace Kratos
{
    const matrix3X3 matrix3X3::ms_CameraViewRight = matrix3X3(0.0f, 0.0f, -1.0f,
                                                              0.0f, 1.0f, 0.0f,
                                                              1.0f, 0.0f, 0.0f);
    const matrix3X3 matrix3X3::ms_CameraViewLeft = matrix3X3(0.0f, 0.0f, 1.0f,
                                                             0.0f, 1.0f, 0.0f,
                                                             -1.0f, 0.0f, 0.0f);
    const matrix3X3 matrix3X3::ms_CameraViewUp = matrix3X3(1.0f, 0.0f, 0.0f,
                                                           0.0f, 0.0f, -1.0f,
                                                           0.0f, 1.0f, 0.0f);
    const matrix3X3 matrix3X3::ms_CameraViewDown = matrix3X3(1.0f, 0.0f, 0.0f,
                                                             0.0f, 0.0f, 1.0f,
                                                             0.0f, -1.0f, 0.0f);
    const matrix3X3 matrix3X3::ms_CameraViewFront = matrix3X3(1.0f, 0.0f, 0.0f,
                                                              0.0f, 1.0f, 0.0f,
                                                              0.0f, 0.0f, 1.0f);
    const matrix3X3 matrix3X3::ms_CameraViewBack = matrix3X3(-1.0f, 0.0f, 0.0f,
                                                             0.0f, 1.0f, 0.0f,
                                                             0.0f, 0.0f, -1.0f);

    matrix3X3::matrix3X3()
    {
        Identity();
    }

    matrix3X3::matrix3X3(KSREAL m00, KSREAL m01, KSREAL m02,
                         KSREAL m10, KSREAL m11, KSREAL m12,
                         KSREAL m20, KSREAL m21, KSREAL m22)
    {
        _00 = m00;
        _01 = m01;
        _02 = m02;
        _10 = m10;
        _11 = m11;
        _12 = m12;
        _20 = m20;
        _21 = m21;
        _22 = m22;
    }

    matrix3X3 matrix3X3::operator*(KSREAL scalar) const
    {
        matrix3X3 Temp;
        Temp.m[0] = m[0] * scalar;
        Temp.m[1] = m[1] * scalar;
        Temp.m[2] = m[2] * scalar;
        Temp.m[3] = m[3] * scalar;
        Temp.m[4] = m[4] * scalar;
        Temp.m[5] = m[5] * scalar;
        Temp.m[6] = m[6] * scalar;
        Temp.m[7] = m[7] * scalar;
        Temp.m[8] = m[8] * scalar;

        return Temp;
    }

    matrix3X3 matrix3X3::operator+(KSREAL scalar) const
    {
        matrix3X3 Temp;
        Temp.m[0] = m[0] + scalar;
        Temp.m[1] = m[1] + scalar;
        Temp.m[2] = m[2] + scalar;
        Temp.m[3] = m[3] + scalar;
        Temp.m[4] = m[4] + scalar;
        Temp.m[5] = m[5] + scalar;
        Temp.m[6] = m[6] + scalar;
        Temp.m[7] = m[7] + scalar;
        Temp.m[8] = m[8] + scalar;

        return Temp;
    }

    matrix3X3 matrix3X3::operator-(KSREAL scalar) const
    {
        matrix3X3 Temp;
        Temp.m[0] = m[0] - scalar;
        Temp.m[1] = m[1] - scalar;
        Temp.m[2] = m[2] - scalar;
        Temp.m[3] = m[3] - scalar;
        Temp.m[4] = m[4] - scalar;
        Temp.m[5] = m[5] - scalar;
        Temp.m[6] = m[6] - scalar;
        Temp.m[7] = m[7] - scalar;
        Temp.m[8] = m[8] - scalar;

        return Temp;
    }

    matrix3X3 matrix3X3::operator+(const matrix3X3 &matirx) const
    {

        matrix3X3 Temp;
        Temp.m[0] = m[0] + matirx.m[0];
        Temp.m[1] = m[1] + matirx.m[1];
        Temp.m[2] = m[2] + matirx.m[2];
        Temp.m[3] = m[3] + matirx.m[3];
        Temp.m[4] = m[4] + matirx.m[4];
        Temp.m[5] = m[5] + matirx.m[5];
        Temp.m[6] = m[6] + matirx.m[6];
        Temp.m[7] = m[7] + matirx.m[7];
        Temp.m[8] = m[8] + matirx.m[8];

        return Temp;
    }

    matrix3X3 matrix3X3::operator-(const matrix3X3 &matirx) const
    {

        matrix3X3 Temp;
        Temp.m[0] = m[0] - matirx.m[0];
        Temp.m[1] = m[1] - matirx.m[1];
        Temp.m[2] = m[2] - matirx.m[2];
        Temp.m[3] = m[3] - matirx.m[3];
        Temp.m[4] = m[4] - matirx.m[4];
        Temp.m[5] = m[5] - matirx.m[5];
        Temp.m[6] = m[6] - matirx.m[6];
        Temp.m[7] = m[7] - matirx.m[7];
        Temp.m[8] = m[8] - matirx.m[8];

        return Temp;
    }

    void matrix3X3::operator*=(KSREAL scalar)
    {
        m[0] = m[0] * scalar;
        m[1] = m[1] * scalar;
        m[2] = m[2] * scalar;
        m[3] = m[3] * scalar;
        m[4] = m[4] * scalar;
        m[5] = m[5] * scalar;
        m[6] = m[6] * scalar;
        m[7] = m[7] * scalar;
        m[8] = m[8] * scalar;
    }

    void matrix3X3::operator+=(KSREAL scalar)
    {
        m[0] = m[0] + scalar;
        m[1] = m[1] + scalar;
        m[2] = m[2] + scalar;
        m[3] = m[3] + scalar;
        m[4] = m[4] + scalar;
        m[5] = m[5] + scalar;
        m[6] = m[6] + scalar;
        m[7] = m[7] + scalar;
        m[8] = m[8] + scalar;
    }

    void matrix3X3::operator-=(KSREAL scalar)
    {
        m[0] = m[0] - scalar;
        m[1] = m[1] - scalar;
        m[2] = m[2] - scalar;
        m[3] = m[3] - scalar;
        m[4] = m[4] - scalar;
        m[5] = m[5] - scalar;
        m[6] = m[6] - scalar;
        m[7] = m[7] - scalar;
        m[8] = m[8] - scalar;
    }

    void matrix3X3::operator+=(const matrix3X3 &matirx)
    {
        m[0] = m[0] + matirx.m[0];
        m[1] = m[1] + matirx.m[1];
        m[2] = m[2] + matirx.m[2];
        m[3] = m[3] + matirx.m[3];
        m[4] = m[4] + matirx.m[4];
        m[5] = m[5] + matirx.m[5];
        m[6] = m[6] + matirx.m[6];
        m[7] = m[7] + matirx.m[7];
        m[8] = m[8] + matirx.m[8];
    }
    /*----------------------------------------------------------------*/
    void matrix3X3::operator-=(const matrix3X3 &matirx)
    {
        m[0] = m[0] - matirx.m[0];
        m[1] = m[1] - matirx.m[1];
        m[2] = m[2] - matirx.m[2];
        m[3] = m[3] - matirx.m[3];
        m[4] = m[4] - matirx.m[4];
        m[5] = m[5] - matirx.m[5];
        m[6] = m[6] - matirx.m[6];
        m[7] = m[7] - matirx.m[7];
        m[8] = m[8] - matirx.m[8];
    }

    bool matrix3X3::operator==(const matrix3X3 &v) const
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                if (Math::abs(M[i][j] - v.M[i][j]) > EPSILON_E4)
                {
                    return false;
                }
            }
        }
        return true;
    }

    void matrix3X3::CreateRot(const vector3 &U, const vector3 &V, const vector3 &N)
    {
        _00 = U.x;
        _01 = U.y;
        _02 = U.z;

        _10 = V.x;
        _11 = V.y;
        _12 = V.z;

        _20 = N.x;
        _21 = N.y;
        _22 = N.z;
    }

    void matrix3X3::CreateScale(KSREAL fX, KSREAL fY, KSREAL fZ)
    {
        Identity();
        _00 = fX;
        _11 = fY;
        _22 = fZ;
    }

    /*********************************** inline *************************************/
    inline void matrix3X3::Identity(void)
    {
        memset(m, 0, sizeof(matrix3X3));
        _00 = _11 = _22 = 1.0f;
    }

    inline void matrix3X3::TransposeOf(const matrix3X3 &matirx)
    {
        _00 = matirx._00;
        _10 = matirx._01;
        _20 = matirx._02;

        _01 = matirx._10;
        _11 = matirx._11;
        _21 = matirx._12;

        _02 = matirx._20;
        _12 = matirx._21;
        _22 = matirx._22;
    }

    inline void matrix3X3::InverseOf(const matrix3X3 &matirx)
    {
        KSREAL det = matirx.Det();

        if (Math::abs(det) < EPSILON_E4)
            return;

        KSREAL det_inv = 1.0f / det;

        M[0][0] = det_inv * (matirx.M[1][1] * matirx.M[2][2] - matirx.M[2][1] * matirx.M[1][2]);
        M[1][0] = -det_inv * (matirx.M[1][0] * matirx.M[2][2] - matirx.M[2][0] * matirx.M[1][2]);
        M[2][0] = det_inv * (matirx.M[1][0] * matirx.M[2][1] - matirx.M[2][0] * matirx.M[1][1]);

        M[0][1] = -det_inv * (matirx.M[0][1] * matirx.M[2][2] - matirx.M[2][1] * matirx.M[0][2]);
        M[1][1] = det_inv * (matirx.M[0][0] * matirx.M[2][2] - matirx.M[2][0] * matirx.M[0][2]);
        M[2][1] = -det_inv * (matirx.M[0][0] * matirx.M[2][1] - matirx.M[2][0] * matirx.M[0][1]);

        M[0][2] = det_inv * (matirx.M[0][1] * matirx.M[1][2] - matirx.M[1][1] * matirx.M[0][2]);
        M[1][2] = -det_inv * (matirx.M[0][0] * matirx.M[1][2] - matirx.M[1][0] * matirx.M[0][2]);
        M[2][2] = det_inv * (matirx.M[0][0] * matirx.M[1][1] - matirx.M[1][0] * matirx.M[0][1]);
    }

    inline KSREAL matrix3X3::Det() const
    {
        return (M[0][0] * (M[1][1] * M[2][2] - M[2][1] * M[1][2]) -
                M[0][1] * (M[1][0] * M[2][2] - M[2][0] * M[1][2]) +
                M[0][2] * (M[1][0] * M[2][1] - M[2][0] * M[1][1]));
    }

    inline matrix3X3 matrix3X3::operator*(const matrix3X3 &matirx) const
    {
        matrix3X3 mResult;
        mResult.M[0][0] = 0;
        mResult.M[1][1] = 0;
        mResult.M[2][2] = 0;

        for (unsigned char i = 0; i < 3; i++)
            for (unsigned char j = 0; j < 3; j++)
                for (unsigned int k = 0; k < 3; k++)
                    mResult.M[i][j] += M[i][k] * matirx.M[k][j];

        return mResult;
    }

    inline vector3 matrix3X3::operator*(const vector3 &vc) const
    {
        return vc * (*this);
    }

} // namespace Kratos
