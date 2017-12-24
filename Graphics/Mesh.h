//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 11.12.17.
//

#ifndef DSD_GAMEENGINE_MESH_H
#define DSD_GAMEENGINE_MESH_H

#include <vector>
#include <string>

#include "Core/DSDBaseObject.h"
#include "Core/Math/Quaternion.h"
#include "Core/Math/Vector3.h"

class Mesh : public DSDBaseObject
{
    REFLECTION(Mesh);
public:
    Mesh() : m_vertices(nullptr), m_normals(nullptr), m_amountOfVertices(0) {}

    explicit Mesh(const std::string& meshFileName,
                  const Vector3& position = Vector3(),
                  const Quaternion& rotation = Quaternion(),
                  const Vector3& scale = Vector3());

    Mesh(Mesh&& other) noexcept;

    Mesh(const Mesh& other);

    void setMesh(const std::string& meshFileName);

    inline const double* vertexArray() const
    {
        return m_vertices;
    }

    inline const double* normalArray()
    {
        return m_normals;
    }

    inline std::size_t amountOfVertices() const
    {
        return m_amountOfVertices;
    }

    void draw() const;

    Mesh& operator=(const Mesh& rhl);

    SERIALIZABLE(Vector3, position, Vector3());
    SERIALIZABLE(Quaternion, rotation, Quaternion());
    SERIALIZABLE(Vector3, scale, Vector3());

private:
    void copyVertices(double *vertices, double *normals, const std::size_t& amountOfVertices);

    SERIALIZABLE(std::string, m_meshFileName, "");
    double* m_vertices;
    double* m_normals;
    std::size_t m_amountOfVertices, m_amountOfData;
};

#endif //DSD_GAMEENGINE_MESH_H
