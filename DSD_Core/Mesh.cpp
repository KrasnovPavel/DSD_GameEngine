//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 11.12.17.
//

#include "Mesh.h"

INIT_REFLECTION(Mesh)

void Mesh::setMesh(const std::vector<Triangle>& triangles)
{
    this->triangles = triangles;
};

std::pair<float*, std::size_t> Mesh::vertexArray()
{
    auto* verticles = new float[triangles.size()*9];
    for (unsigned i = 0; i < triangles.size(); ++i)
    {
        float* arr = triangles.at(i).vertexArray();
        std::memcpy(verticles + i*9, arr, sizeof(float)*9);
        delete[] arr;
        for (unsigned j = 0; j < 3; ++j )
        {
            verticles[i+j] += position.x;
            verticles[i+j+1] += position.y;
            verticles[i+j+2] += position.z;
        }
    }
    return std::make_pair(verticles, sizeof(float)*9*triangles.size());
}