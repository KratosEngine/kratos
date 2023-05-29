
#include "runtime/core/math/matrix3X3.h"

namespace Kratos
{
    const Matrix3X3 Matrix3X3::ms_CameraViewRight = Matrix3X3(0.0f, 0.0f, -1.0f,
                                                              0.0f, 1.0f, 0.0f,
                                                              1.0f, 0.0f, 0.0f);
    const Matrix3X3 Matrix3X3::ms_CameraViewLeft = Matrix3X3(0.0f, 0.0f, 1.0f,
                                                             0.0f, 1.0f, 0.0f,
                                                             -1.0f, 0.0f, 0.0f);
    const Matrix3X3 Matrix3X3::ms_CameraViewUp = Matrix3X3(1.0f, 0.0f, 0.0f,
                                                           0.0f, 0.0f, -1.0f,
                                                           0.0f, 1.0f, 0.0f);
    const Matrix3X3 Matrix3X3::ms_CameraViewDown = Matrix3X3(1.0f, 0.0f, 0.0f,
                                                             0.0f, 0.0f, 1.0f,
                                                             0.0f, -1.0f, 0.0f);
    const Matrix3X3 Matrix3X3::ms_CameraViewFront = Matrix3X3(1.0f, 0.0f, 0.0f,
                                                              0.0f, 1.0f, 0.0f,
                                                              0.0f, 0.0f, 1.0f);
    const Matrix3X3 Matrix3X3::ms_CameraViewBack = Matrix3X3(-1.0f, 0.0f, 0.0f,
                                                             0.0f, 1.0f, 0.0f,
                                                             0.0f, 0.0f, -1.0f);

    Matrix3X3::Matrix3X3()
    {
        Identity();
    }

    Matrix3X3::Matrix3X3(KSREAL m00, KSREAL m01, KSREAL m02,
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

    inline void Matrix3X3::Identity(void)
    {
        KSMemset(m, 0, sizeof(Matrix3X3));
        _00 = _11 = _22 = 1.0f;
    }

    inline void Matrix3X3::TransposeOf(const Matrix3X3 &matirx)
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

    inline void Matrix3X3::InverseOf(const Matrix3X3 &matirx)
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

    inline KSREAL Matrix3X3::Det() const
    {
        return (M[0][0] * (M[1][1] * M[2][2] - M[2][1] * M[1][2]) -
                M[0][1] * (M[1][0] * M[2][2] - M[2][0] * M[1][2]) +
                M[0][2] * (M[1][0] * M[2][1] - M[2][0] * M[1][1]));
    }

} // namespace Kratos
