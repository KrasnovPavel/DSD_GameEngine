//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 17.12.17.
//

#include "MeshParser.h"


MeshParser::MeshParser(const std::string &filename) : m_filename(filename)
{
    std::ifstream in(filename, std::ios::ate|std::ios::in|std::ios::binary);
    if (in.is_open())
    {
        m_dataSize = in.tellg();
        m_data = new char[m_dataSize];
        in.seekg(0, std::ios::beg);
        in.read(m_data, m_dataSize);
        in.close();
    }
    else throw FileOpeningFaliure(filename);
}

MeshParser::~MeshParser()
{
    if (m_data)
        delete[] m_data;
}

bool MeshParser::checkFormat() const
{
    return (!m_format.empty()) &&
           (0 == m_filename.compare(m_filename.length() - m_format.length(), m_format.length(), m_format));

}
