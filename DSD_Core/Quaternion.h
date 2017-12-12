//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 07.12.17.
//

#ifndef DSD_GAMEENGINE_QUATERNION_H
#define DSD_GAMEENGINE_QUATERNION_H

#include "Vector3.h"
#include "Vector4.h"

class Quaternion : public Vector4
{
    REFLECTION(Quaternion);
public:
    Quaternion() : Vector4() {}

    void rotateVector(Vector3& vector);

    Vector3 rotatedVector(const Vector3& vector);
};

#endif //DSD_GAMEENGINE_QUATERNION_H

