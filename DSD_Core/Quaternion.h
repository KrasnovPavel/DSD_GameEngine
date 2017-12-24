//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 07.12.17.
//

#ifndef DSD_GAMEENGINE_QUATERNION_H
#define DSD_GAMEENGINE_QUATERNION_H

#include <cmath>

#include "DSDBaseObject.h"
#include "Vector3.h"
#include "Vector4.h"

class Quaternion : public DSDBaseObject
{
    REFLECTION(Quaternion);
public:
    Quaternion() {}

    Quaternion(const double& angle, const Vector3& axis);

    Quaternion(const double& roll, const double& pitch, const double& yaw);

    Vector3& rotateVector(Vector3& vector) const;

    Vector3 rotatedVector(Vector3 vector) const;

    Quaternion& operator *=(const Quaternion& rhs);

    friend inline Quaternion operator *(Quaternion lhs, const Quaternion& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline double length() const
    {
        return 1/m_invLength;
    }

    inline Quaternion& normalize()
    {
        (*this) = normalized();
        calculate();
        return *this;
    }

    inline Quaternion normalized() const
    {
        return (*this) * m_invLength;
    }

    Quaternion& operator=(const Quaternion& rhl)
    {
        vector = rhl.vector;
        scalar = rhl.scalar;
        calculate();
        return *this;
    }

    inline bool operator ==(const Quaternion& rhs) const
    {   //TODO: Epsilon check
        return (vector == rhs.vector) && (scalar == rhs.scalar);
    }

    inline bool operator !=(const Quaternion& rhs) const
    {
        return !(*this == rhs);
    }

    inline Quaternion inverted() const
    {
        return Quaternion(scalar, -vector);
    }

    std::pair<Vector3, double> toAxisAngle() const;

    std::string toString() const override;

private:
    void calculate();

    Quaternion(const double& w, const double& x, const double& y, const double& z);

    inline Quaternion& operator *=(const double& rhs)
    {
        vector.x *= rhs;
        vector.y *= rhs;
        vector.z *= rhs;
        scalar *= rhs;
        calculate();
        return *this;
    }

    friend inline Quaternion operator *(Quaternion lhs, const double& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    SERIALIZABLE(Vector3, vector, Vector3());
    SERIALIZABLE(double, scalar, 1);
    double m_invLength, m_angle;
    Vector3 m_axis;
};

#endif //DSD_GAMEENGINE_QUATERNION_H

