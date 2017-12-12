//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 11.12.17.
//

#ifndef DSD_GAMEENGINE_TRIANGLE_H
#define DSD_GAMEENGINE_TRIANGLE_H

#include <vector>

#include "DSDBaseObject.h"
#include "Vector3.h"
#include "Quaternion.h"

class Triangle : public DSDBaseObject
{
    REFLECTION(Triangle);
public:
    Triangle() {}

    Triangle(Triangle&& other) noexcept
            : firstVertex(other.firstVertex),
              secondVertex(other.secondVertex),
              thirdVertex(other.thirdVertex),
              normalVector(other.normalVector),
              DSDBaseObject(other) {}

    Triangle(const Triangle& other)
            : firstVertex(other.firstVertex),
              secondVertex(other.secondVertex),
              thirdVertex(other.thirdVertex),
              normalVector(other.normalVector),
              DSDBaseObject(other) {}

    Triangle(const Vector3& first, const Vector3& second, const Vector3& third, const Vector3& normal = Vector3())
            : firstVertex(first),
              secondVertex(second),
              thirdVertex(third),
              normalVector(normal) {}

    Triangle& operator=(const Triangle& rhl)
    {
        normalVector = rhl.normalVector;
        firstVertex  = rhl.firstVertex;
        secondVertex = rhl.secondVertex;
        thirdVertex  = rhl.thirdVertex;
        return *this;
    }

    double* vertexArray()
    {
        auto* verticles = new double[9]
                {
                        firstVertex.x, firstVertex.y, firstVertex.z,
                        secondVertex.x, secondVertex.y, secondVertex.z,
                        thirdVertex.x, thirdVertex.y, thirdVertex.z,
                };
        return verticles;
    }

    SERIALIZABLE(Vector3, normalVector, Vector3());
    SERIALIZABLE(Vector3, firstVertex, Vector3());
    SERIALIZABLE(Vector3, secondVertex, Vector3());
    SERIALIZABLE(Vector3, thirdVertex, Vector3());
};

#endif //DSD_GAMEENGINE_TRIANGLE_H

