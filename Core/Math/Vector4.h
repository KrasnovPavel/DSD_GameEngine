//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 29.11.17.
//

#ifndef DSD_GAMEENGINE_VECTOR4_H
#define DSD_GAMEENGINE_VECTOR4_H

#include <cmath>

#include "Core/DSDBaseObject.h"

class Vector4 : public DSDBaseObject
{
    REFLECTION(Vector4);
public:
    Vector4() {}

    Vector4(Vector4&& other) noexcept
        : x(other.x), y(other.y), z(other.z), w(other.w) {}

    Vector4(const Vector4& other)
        : x(other.x), y(other.y), z(other.z), w(other.w) {}

    Vector4(const double& x, const double& y, const double& z, const double& w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    inline void set(const double& x, const double& y, const double& z, const double& w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    static double dot(const Vector4& first, const Vector4& second);

    inline double dot(const Vector4 &other) const
    {
        return Vector4::dot(*this, other);
    }

    inline double length() const
    {
        return std::sqrt(x*x + y*y + z*z + w*w);
    }

    inline bool operator ==(const Vector4& rhs) const
    {   //TODO: Epsilon check
        return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w);
    }

    inline bool operator !=(const Vector4& rhs) const
    {
        return !(*this == rhs);
    }

    inline Vector4& operator -=(const Vector4& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    inline Vector4& operator +=(const Vector4& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    inline Vector4& operator *=(const double& rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        w *= rhs;
        return *this;
    }

    inline Vector4& operator /=(const double& rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        w /= rhs;
        return *this;
    }

    friend inline Vector4 operator +(Vector4 lhs, const Vector4& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    friend inline Vector4 operator -(Vector4 lhs, const Vector4& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    friend inline Vector4 operator *(Vector4 lhs, const double& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    friend inline Vector4 operator /(Vector4 lhs, const double& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline double distance(const Vector4& other) const
    {
        return ((*this) - other).length();
    }

    Vector4& operator=(const Vector4& rhl)
    {
        x = rhl.x;
        y = rhl.y;
        z = rhl.z;
        w = rhl.w;
        return *this;
    }

    virtual Vector4& normalize()
    {
        (*this) /= this->length();
        return *this;
    }

    virtual Vector4 normalized() const
    {
        return (*this) / this->length();
    }

    SERIALIZABLE(double, x, 0);
    SERIALIZABLE(double, y, 0);
    SERIALIZABLE(double, z, 0);
    SERIALIZABLE(double, w, 0);
};

#endif //DSD_GAMEENGINE_VECTOR4_H
