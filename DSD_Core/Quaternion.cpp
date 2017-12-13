//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 07.12.17.
//

#include "Quaternion.h"

INIT_REFLECTION(Quaternion);

Quaternion::Quaternion(const double &angle, const Vector3 &axis)
{
    vector = axis * std::sin(angle/2);
    scalar = std::cos(angle/2);
    normalize();
}

Quaternion::Quaternion(const double &roll, const double &pitch, const double &yaw)
{
    Quaternion r = Quaternion(roll, Vector3(1, 0, 0));
    Quaternion p = Quaternion(roll, Vector3(0, 1, 0));
    Quaternion y = Quaternion(roll, Vector3(0, 0, 1));

    *this = r * p * y;
    normalize();
}

Vector3& Quaternion::rotateVector(Vector3 &vector) const
{
    Quaternion v(0, vector.x, vector.y, vector.z);
//    Quaternion tmp, inv = inverted();
//    tmp.scalar = vector.dot(v.vector);
//    tmp.vector = Vector3::cross(vector, v.vector) + vector*v.scalar + v.vector*scalar;
//    vector = Vector3::cross(tmp.vector, inv.vector) + tmp.vector*inv.scalar + inv.vector*tmp.scalar;
    vector = (*this * v * inverted()).vector;
    return vector;
}

Vector3 Quaternion::rotatedVector(Vector3 vector) const
{
    return rotateVector(vector);
}

Quaternion &Quaternion::operator*=(const Quaternion &rhs)
{
//    double tmp = vector.dot(rhs.vector);
//    vector = Vector3::cross(vector, rhs.vector) + vector*rhs.scalar + rhs.vector*scalar;
//    scalar = tmp;
    Quaternion res;
    res.scalar = scalar * rhs.scalar - vector.x * rhs.vector.x - vector.y * rhs.vector.y - vector.z * rhs.vector.z;
    res.vector.x = scalar * rhs.vector.x + vector.x * rhs.scalar + vector.y * rhs.vector.z - vector.z * rhs.vector.y;
    res.vector.y = scalar * rhs.vector.y - vector.x * rhs.vector.z + vector.y * rhs.scalar + vector.z * rhs.vector.x;
    res.vector.z = scalar * rhs.vector.z + vector.x * rhs.vector.y - vector.y * rhs.vector.x + vector.z * rhs.scalar;
//    res.normalize();
    *this = res;
    return *this;
}

