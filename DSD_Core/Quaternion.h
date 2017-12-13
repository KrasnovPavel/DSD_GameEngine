//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 07.12.17.
//

#ifndef DSD_GAMEENGINE_QUATERNION_H
#define DSD_GAMEENGINE_QUATERNION_H

#include <cmath>

#include "DSDBaseObject.h"
#include "Vector3.h"

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
        return std::sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z + scalar*scalar);
    }

    inline Quaternion& normalize()
    {
        (*this) /= this->length();
        return *this;
    }

    inline Quaternion normalized() const
    {
        return (*this) / this->length();
    }

    Quaternion& operator=(const Quaternion& rhl)
    {
        vector = rhl.vector;
        scalar = rhl.scalar;
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
        return  Quaternion(scalar, -vector);
    }

private:
    Quaternion(const double& w, const double& x, const double& y, const double& z)
            : scalar(w), vector(x, y, z) {}

    inline Quaternion& operator /=(const double& rhs)
    {
        vector.x /= rhs;
        vector.y /= rhs;
        vector.z /= rhs;
        scalar /= rhs;
        return *this;
    }

    friend inline Quaternion operator /(Quaternion lhs, const double& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    SERIALIZABLE(Vector3, vector, Vector3());
    SERIALIZABLE(double, scalar, 1);
};

#endif //DSD_GAMEENGINE_QUATERNION_H

