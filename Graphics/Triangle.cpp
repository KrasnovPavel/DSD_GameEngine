//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 11.12.17.
//

#include "Triangle.h"

INIT_REFLECTION(Triangle)

double *Triangle::vertexArrayTranslated(const Vector3& position, const Quaternion& rotation) const
{
//    Vector3 first = rotation.rotatedVector(firstVertex) + position;
//    Vector3 second = rotation.rotatedVector(secondVertex) + position;
//    Vector3 third = rotation.rotatedVector(thirdVertex) + position;

    auto* verticles = new double[9]
            {
                    firstVertex.x,  firstVertex.y,  firstVertex.z,
                    secondVertex.x, secondVertex.y, secondVertex.z,
                    thirdVertex.x,  thirdVertex.y,  thirdVertex.z,
            };
    return verticles;
};