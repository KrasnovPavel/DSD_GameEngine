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
                  const Vector3& scale = Vector3(1, 1, 1));

    Mesh(Mesh&& rhl) noexcept;

    Mesh(const Mesh& rhl);

    ~Mesh();

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

    void setColor(float r, float g, float b, float a);

    inline const float* getColor()
    {
        return m_color;
    }

    Mesh& operator=(const Mesh& rhl);

    SERIALIZABLE(Vector3, position, Vector3());
    SERIALIZABLE(Quaternion, rotation, Quaternion());
    SERIALIZABLE(Vector3, scale, Vector3());

    bool solid = true;

private:
    void copyVertices(double *vertices,
                      double *normals,
                      const std::size_t& amountOfVertices,
                      double* gridVertices = nullptr);

    void copyColors(double* solidColors, double* gridColors, double const* color);

    void fillColors();

    void generateGrid();

    void drawSolid() const;

    void drawGrid() const;

    SERIALIZABLE(std::string, m_meshFileName, "");
    double* m_vertices;
    double* m_normals;
    double* m_gridVertices;
    float* m_color = new float[4];
    std::size_t m_amountOfVertices, m_amountOfData, m_amountOfGridData;
};

#endif //DSD_GAMEENGINE_MESH_H
