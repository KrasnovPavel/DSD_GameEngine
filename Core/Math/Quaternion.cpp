//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 07.12.17.
//

#include "Quaternion.h"

using namespace DSD;

INIT_REFLECTION(Quaternion);

Quaternion::Quaternion(const double &angle, const Vector3 &axis)
{
    m_vector = axis.normalized() * std::sin(angle/2);
    scalar = std::cos(angle/2);
    normalize();
}

Quaternion::Quaternion(const double &roll, const double &pitch, const double &yaw)
{
    Quaternion r = Quaternion(roll, Vector3(1, 0, 0));
    Quaternion p = Quaternion(pitch, Vector3(0, 1, 0));
    Quaternion y = Quaternion(yaw, Vector3(0, 0, 1));

    *this = r * p * y;
    normalize();
}

Vector3& Quaternion::rotateVector(Vector3 &vector) const
{
    Quaternion v(0, vector.x, vector.y, vector.z);
    vector = (*this * v * inverted()).m_vector;

    return vector;
}

Vector3 Quaternion::rotatedVector(Vector3 vector) const
{
    return rotateVector(vector);
}

Quaternion &Quaternion::operator*=(const Quaternion &rhs)
{
    double tmp = scalar * rhs.scalar - m_vector.dot(rhs.m_vector);
    m_vector = Vector3::cross(m_vector, rhs.m_vector) + m_vector*rhs.scalar + rhs.m_vector*scalar;
    scalar = tmp;
    return *this;
}

std::pair<Vector3, double> Quaternion::toAxisAngle() const
{
    return std::make_pair(m_vector / std::sqrt(1-scalar*scalar), 2*std::acos(scalar));
}

std::string Quaternion::toString() const
{
    auto tmp = toAxisAngle();
    return "{" + tmp.first.toString() + ", " + std::to_string(tmp.second * 180 * M_1_PI) + "}";
}

