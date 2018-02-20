//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 12.11.17.
//

#include "WriteByteArray.h"

using namespace DSD;

template <>
void WriteByteArray::write(const double& var)
{
    basicConversion(var);
}

template <>
void WriteByteArray::write(const std::size_t& var)
{
    basicConversion(var);
}

template <>
void WriteByteArray::write(const unsigned& var)
{
    basicConversion(var);
}

template <>
void WriteByteArray::write(const std::string& var)
{
    const std::size_t size_t_size /*:)*/ = sizeof(std::size_t);
    checkLength(size_t_size);
    const std::size_t strSize = var.size();
    std::memcpy((m_array+m_pos), &strSize, size_t_size);
    m_pos += size_t_size;
    checkLength(strSize);
    std::memcpy((m_array+m_pos), var.c_str(), strSize);
    m_pos += strSize;
}
