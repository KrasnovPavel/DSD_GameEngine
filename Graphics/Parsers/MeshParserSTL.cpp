//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 17.12.17.
//

#include "MeshParserSTL.h"

#include <iostream>
#include <istream>
#include <sstream>
#include <string>


MeshParserSTL::MeshParserSTL(const std::string &filename) : MeshParser(filename)
{
    m_format = ".stl";
    if (!checkFormat()) throw FileFormatError(filename);
    m_ss.clear();
    m_ss.str(std::string(m_data, m_dataSize));
    delete[] m_data;
}

std::vector<Triangle> MeshParserSTL::parce() const
{
    std::vector<Triangle> mesh;
    std::string str;
    m_ss >> str;
    if (str == "solid")
    {
        while (str != "facet") m_ss >> str;
        Vector3 normal;
        double x1, y1, z1, x2, y2, z2, x3, y3, z3;
        while (str != "endsolid")
        {
            if (str == "facet")
            {
                try
                {
                    m_ss >> str >> x1 >> y1 >> z1;
                    normal.set(x1, y1, z1);
                }
                catch (std::exception&)
                {
                    throw FileParcingError(m_filename, "ASCII STL formal invalid");
                }
            }
            else if (str == "outer")
            {
                m_ss >> str >> str >> x1 >> y1 >> z1 >> str >> x2 >> y2 >> z2 >> str >> x3 >> y3 >> z3;
                mesh.emplace_back(Triangle(Vector3(x1, y1, z1), Vector3(x2, y2, z2), Vector3(x3, y3, z3), normal));
            }
            else if (str != "endloop" && str != "endfacet" && !str.empty())
            {
                throw FileParcingError(m_filename, "ASCII STL formal invalid");
            }
            m_ss >> str;
        }
    }
    else throw FileParcingError(m_filename, "Only ASCII STL files supported");
    return mesh;
}
