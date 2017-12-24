//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 11.12.17.
//

#include <GL/gl.h>
#include <GL/glut.h>

#include "Mesh.h"
#include "MeshParser.h"

INIT_REFLECTION(Mesh)

Mesh::Mesh(const std::string& meshFileName, const Vector3 &position, const Quaternion &rotation, const Vector3 &scale)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    setMesh(meshFileName);
}

Mesh::Mesh(Mesh &&other) noexcept : DSDBaseObject(other)
{
    position = other.position;
    rotation = other.rotation;
    scale    = other.scale;
    copyVertices(other.m_vertices, other.m_normals, other.m_amountOfVertices);
}

Mesh::Mesh(const Mesh &other) : DSDBaseObject(other)
{
    position = other.position;
    rotation = other.rotation;
    scale    = other.scale;
    copyVertices(other.m_vertices, other.m_normals, other.m_amountOfVertices);
}

void Mesh::setMesh(const std::string &meshFileName)
{
    m_meshFileName = meshFileName;
    auto tmp = MeshParser::parse(meshFileName);
    copyVertices(tmp.first.data(), tmp.second.data(), tmp.first.size()/3);
}

Mesh &Mesh::operator=(const Mesh &rhl)
{
    position = rhl.position;
    rotation = rhl.rotation;
    scale    = rhl.scale;
    copyVertices(rhl.m_vertices, rhl.m_normals, rhl.m_amountOfVertices);
    return  *this;
}

void Mesh::copyVertices(double *vertices, double *normals, const std::size_t& amountOfVertices)
{
    delete m_vertices;
    delete m_normals;
    m_amountOfVertices = amountOfVertices;
    m_amountOfData = m_amountOfVertices * 3;
    m_vertices = new double[m_amountOfData];
    m_normals = new double[m_amountOfData];
    memcpy(m_vertices, vertices, m_amountOfData * sizeof(double));
    memcpy(m_normals, normals, m_amountOfData * sizeof(double));
}

void Mesh::draw() const
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    auto tmp = rotation.toAxisAngle();
    glTranslated(position.x, position.y, position.z);
    glRotated(tmp.second * 180. * M_1_PI, tmp.first.x, tmp.first.y, tmp.first.z);

    glPushMatrix();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, m_vertices);
    glNormalPointer(GL_DOUBLE, 0, m_normals);
    glDrawArrays(GL_TRIANGLES, 0, m_amountOfVertices);

    glPopMatrix();
}
