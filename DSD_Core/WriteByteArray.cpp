//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 12.11.17.
//

#include "WriteByteArray.h"

#include <cstring>

template <>
void WriteByteArray::write(const double& var)
{
    static const std::size_t size = sizeof(double);
    checkLength(size);
    std::memcpy((m_array+m_pos), &var, size);
    m_pos += size;
}

template <>
void WriteByteArray::write(const std::string& var)
{
    static const std::size_t size_t_size /*:)*/ = sizeof(std::size_t);
    checkLength(size_t_size);
    static const std::size_t strSize = var.size();
    std::memcpy((m_array+m_pos), &strSize, size_t_size);
    m_pos += size_t_size;
    checkLength(strSize);
    std::memcpy((m_array+m_pos), var.c_str(), strSize);
    m_pos += strSize;
}