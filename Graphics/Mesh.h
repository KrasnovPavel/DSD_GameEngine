//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 11.12.17.
//

#ifndef DSD_GAMEENGINE_MESH_H
#define DSD_GAMEENGINE_MESH_H

#include <vector>

#include "Core/DSDBaseObject.h"
#include "Core/Math/Quaternion.h"
#include "Core/Math/Vector3.h"
#include "Triangle.h"

class Mesh : public DSDBaseObject
{
    REFLECTION(Mesh);
public:
    Mesh() {}

    Mesh(Mesh&& other) noexcept
            : position(other.position),
              rotation(other.rotation),
              scale(other.scale),
              triangles(other.triangles),
              DSDBaseObject(other) {}

    Mesh(const Mesh& other)
            : position(other.position),
              rotation(other.rotation),
              scale(other.scale),
              triangles(other.triangles),
              DSDBaseObject(other) {}

    void setMesh(const std::vector<Triangle>& triangles);

    double* vertexArray() const;

    inline std::size_t amountOfVerticles() const
    {
        return triangles.size() * 3;
    }

    Mesh& operator=(const Mesh& rhl)
    {
        position  = rhl.position;
        rotation  = rhl.rotation;
        triangles = rhl.triangles;
        return  *this;
    }

    SERIALIZABLE(Vector3, position, Vector3());
    SERIALIZABLE(Quaternion, rotation, Quaternion());
    SERIALIZABLE(Vector3, scale, Vector3());
    std::vector<Triangle> triangles;
};

#endif //DSD_GAMEENGINE_MESH_H
