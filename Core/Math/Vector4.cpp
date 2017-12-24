//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 11.12.17.
//

#include "Vector4.h"

INIT_REFLECTION(Vector4);

double Vector4::dot(const Vector4& first, const Vector4& second)
{
    return first.x * second.x + first.y * second.y + first.z * second.z + first.w * second.w;
}