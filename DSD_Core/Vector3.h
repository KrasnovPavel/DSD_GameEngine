//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 29.11.17.
//

#ifndef DSD_VECTOR3_H
#define DSD_VECTOR3_H

#include <cmath>

#include "DSDBaseObject.h"

class Vector3 : public DSDBaseObject
{
    REFLECTION(Vector3);
public:
    Vector3() : DSDBaseObject() {}

    explicit Vector3(Vector3&& other)
        : x(other.x), y(other.y), z(other.z) {}

    Vector3(const double& x, const double& y, const double& z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    static double dot(const Vector3& first, const Vector3& second);

    double dot(const Vector3 &other) const
    {
        return Vector3::dot(*this, other);
    }

    inline double length()
    {
        return std::sqrt(m_x*m_x, m_y*m_y, m_z*m_z);
    }

    inline double distance(const Vector3& other) const
    {
        return ((*this) - other).length();
    }

    inline bool operator ==(const Vector3& rhs)
    {
        return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
    }

    inline bool operator !=(const Vector3& rhs)
    {
        return !(*this == rhs);
    }

    inline Vector3& operator -=(const Vector3& rhs)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    inline Vector3& operator +=(const Vector3& rhs)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    inline Vector3& operator *=(const double& rhs)
    {
        x *= other;
        y *= other;
        z *= other;
        return *this;
    }

    inline Vector3& operator /=(const double& rhs)
    {
        x /= other;
        y /= other;
        z /= other;
        return *this;
    }

    friend inline Vector3 operator +(Vector3 lhs, const Vector3& rhs)
     {
       lhs += rhs;
       return lhs;
     }

    friend inline Vector3 operator -(Vector3 lhs, const Vector3& rhs)
     {
       lhs -= rhs;
       return lhs;
     }

    friend inline Vector3 operator *(Vector3 lhs, const double& rhs)
     {
       lhs *= rhs;
       return lhs;
     }

    friend inline Vector3 operator /(Vector3 lhs, const double& rhs)
     {
       lhs /= rhs;
       return lhs;
     }

    SERIALIZABLE(double, x, 0);
    SERIALIZABLE(double, y, 0);
    SERIALIZABLE(double, z, 0);
};
INIT_REFLECTION(Vector3);

double Vector3::dot(const Vector3& first, const Vector3& second)
{
    return first.x * second.x + first.y * second.y + first.z * second.z;
}

#endif //DSD_VECTOR3_H
