//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 11.12.17.
//

#include "Mesh.h"

INIT_REFLECTION(Mesh)

void Mesh::setMesh(const std::vector<Triangle>& triangles)
{
    this->triangles = triangles;
};

std::pair<double*, std::size_t> Mesh::vertexArray() const
{
    auto* verticles = new double[triangles.size()*9];
    for (unsigned i = 0; i < triangles.size(); ++i)
    {
        double* arr = triangles.at(i).vertexArrayTranslated(position, rotation);
        std::memcpy(verticles + i*9, arr, sizeof(double)*9);
        delete[] arr;
    }
    return std::make_pair(verticles, sizeof(double)*9*triangles.size());
}