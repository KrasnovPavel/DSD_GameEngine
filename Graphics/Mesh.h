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

namespace DSD
{
/**
 * @defgroup Graphics
 * @{
 */

    /**
     * @brief Mesh of 3D graphics object.
     * @details Represents 3D object as array of triangles.
     */
    class Mesh : public DSDBaseObject
    {
    REFLECTION(Mesh);
    public:
        /**
         * @brief Defaults constructor
         */
        Mesh() : m_vertices(nullptr), m_normals(nullptr), m_amountOfVertices(0)
        {}

        /**
         * @brief Construct mesh by file name.
         * @details Parses data from file and construct new mesh object, and sets up translation.
         * @param meshFileName
         * @param position
         * @param rotation
         * @param scale
         */
        explicit Mesh(const std::string &meshFileName,
                      const Vector3 &position = Vector3(),
                      const Quaternion &rotation = Quaternion(),
                      const Vector3 &scale = Vector3(1, 1, 1));

        /**
         * @brief Copy constructor
         * @param rhl
         */
        Mesh(Mesh &&rhl) noexcept;

        /**
         * @brief Move constructor
         * @param rhl
         */
        Mesh(const Mesh &rhl);

        /**
         * @brief Destructor
         * @details Clears all memory.
         */
        ~Mesh();

        /**
         * @brief Parses data from file to this mesh object.
         * @param meshFileName
         */
        void setMesh(const std::string &meshFileName);

        /**
         * @brief Returns array of vertex for OpenGl.
         * @return
         */
        inline const double *vertexArray() const
        {
            return m_vertices;
        }

        /**
         * @brief Returns array of normals for OpenGl.
         * @return
         */
        inline const double *normalArray()
        {
            return m_normals;
        }

        /**
         * @brief Returns array of vertices in this object.
         * @return
         */
        inline std::size_t amountOfVertices() const
        {
            return m_amountOfVertices;
        }

        /**
         * @brief Draws this mesh in OpenGL context.
         */
        void draw() const;

        /**
         * @brief Sets color of this object.
         * @param r
         * @param g
         * @param b
         * @param a
         */
        void setColor(float r, float g, float b, float a);

        /**
         * @brief Returns color of mesh.
         * @return
         */
        inline const float *getColor()
        {
            return m_color;
        }

        /**
         *
         * @param rhl
         * @return
         */
        Mesh &operator=(const Mesh &rhl);

        /**
         * @brief Position of this mesh
         */
        SERIALIZABLE(Vector3, position, Vector3());

        /**
         * @brief Rotation of this mesh
         */
        SERIALIZABLE(Quaternion, rotation, Quaternion());

        /**
         * @brief Scale of this mesh
         */
        SERIALIZABLE(Vector3, scale, Vector3());

        /**
         * @brief Mode of drawing
         * @details If true draws lit, otherwise unlit.
         */
        bool solid = true;

    private:
        void copyVertices(double *vertices,
                          double *normals,
                          const std::size_t &amountOfVertices,
                          double *gridVertices = nullptr);

        void generateGrid();

        void drawSolid() const;

        void drawGrid() const;

        SERIALIZABLE(std::string, m_meshFileName, "");
        double *m_vertices;
        double *m_normals;
        double *m_gridVertices;
        float *m_color = new float[4];
        std::size_t m_amountOfVertices, m_amountOfData, m_amountOfGridData;
    };
}
/**
 * @}
 */

#endif //DSD_GAMEENGINE_MESH_H
