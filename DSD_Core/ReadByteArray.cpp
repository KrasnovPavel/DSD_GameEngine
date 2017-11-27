//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 12.11.17.
//


#include "ReadByteArray.h"

template <>
double ReadByteArray::read()
{
    return baseConversion<double>();
}

template <>
std::size_t ReadByteArray::read()
{
    return baseConversion<std::size_t>();
}

template <>
unsigned ReadByteArray::read()
{
    return baseConversion<unsigned>();
}

template <>
std::string ReadByteArray::read()
{
    const std::size_t size_t_size /*:)*/ = sizeof(std::size_t);
    checkLength(size_t_size);
    std::size_t strSize = 0;
    std::memcpy(&strSize, (m_array+m_pos), size_t_size);
    m_pos += size_t_size;
    checkLength(strSize);
    std::string result(m_array+m_pos, strSize);
    m_pos += strSize;
    return result;
}
