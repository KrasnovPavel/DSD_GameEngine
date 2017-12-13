//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 11.12.17.
//

#include "Vector3.h"

INIT_REFLECTION(Vector3);

double Vector3::dot(const Vector3& first, const Vector3& second)
{
    return first.x * second.x + first.y * second.y + first.z * second.z;
}

Vector3 Vector3::cross(const Vector3 &first, const Vector3 &second)
{
    return Vector3(first.y*second.z-first.z*second.y,
                   first.z*second.x-first.x*second.z,
                   first.x*second.y-first.y*second.x);
}
