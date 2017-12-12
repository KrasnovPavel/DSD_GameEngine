//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 29.11.17.
//

#ifndef DSD_GAMEENGINE_VECTOR3_H
#define DSD_GAMEENGINE_VECTOR3_H

#include <cmath>

#include "DSDBaseObject.h"

class Vector3 : public DSDBaseObject
{
    REFLECTION(Vector3);
public:
    Vector3() {}

    Vector3(Vector3&& other) noexcept
        : x(other.x), y(other.y), z(other.z), DSDBaseObject(other) {}

    Vector3(const Vector3& other)
        : x(other.x), y(other.y), z(other.z), DSDBaseObject(other) {}

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
        return std::sqrt(x*x + y*y + z*z);
    }

    inline bool operator ==(const Vector3& rhs)
    {   //TODO: Epsilon check
        return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
    }

    inline bool operator !=(const Vector3& rhs)
    {
        return !(*this == rhs);
    }

    inline Vector3& operator -=(const Vector3& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    inline Vector3& operator +=(const Vector3& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    inline Vector3& operator *=(const double& rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    inline Vector3& operator /=(const double& rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
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

    inline double distance(const Vector3& other) const
    {
        return ((*this) - other).length();
    }

    inline Vector3& operator=(const Vector3& rhl)
    {
        x = rhl.x;
        y = rhl.y;
        z = rhl.z;
        return *this;
    }

    SERIALIZABLE(double, x, 0);
    SERIALIZABLE(double, y, 0);
    SERIALIZABLE(double, z, 0);
};

#endif //DSD_GAMEENGINE_VECTOR3_H
