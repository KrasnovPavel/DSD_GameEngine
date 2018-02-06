//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 11.12.17.
//

#include "Vector4.h"

INIT_REFLECTION(Vector4);

double Vector4::dot(const Vector4& first, const Vector4& second)
{
    return first.x * second.x + first.y * second.y + first.z * second.z + first.w * second.w;
}

std::string Vector4::toString() const
{
    return "{" + std::to_string(x) + ", " + std::to_string(y)
           + ", " + std::to_string(z) +  ", " + std::to_string(w) + "}";
}
