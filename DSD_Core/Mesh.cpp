//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 11.12.17.
//

#include "Mesh.h"

INIT_REFLECTION(Mesh)

void Mesh::setMesh(const std::vector<Triangle>& triangles)
{
    this->triangles = triangles;
};

std::pair<double*, std::size_t> Mesh::vertexArray()
{
    auto* verticles = new double[triangles.size()*9];
    for (unsigned i = 0; i < triangles.size(); ++i)
    {
        double* arr = triangles.at(i).vertexArray();
        std::memcpy(verticles + i*9, arr, sizeof(double)*9);
        delete[] arr;
        for (unsigned j = 0; j < 3; ++j )
        {
            verticles[i+j] += position.x;
            verticles[i+j+1] += position.y;
            verticles[i+j+2] += position.z;
        }
    }
    return std::make_pair(verticles, sizeof(double)*9*triangles.size());
}