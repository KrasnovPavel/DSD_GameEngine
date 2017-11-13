//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 12.11.17.
//

#include <cstring>

#include "ReadByteArray.h"

template <>
double ReadByteArray::read()
{
    static const std::size_t size = sizeof(double);
    checkLength(size);
    double result = 0;
    std::memcpy(&result, (m_array+m_pos), size);
    m_pos += size;
    return result;
}

template <>
std::string ReadByteArray::read()
{
    static const std::size_t size_t_size /*:)*/ = sizeof(std::size_t);
    checkLength(size_t_size);
    std::size_t strSize = 0;
    std::memcpy(&strSize, (m_array+m_pos), size_t_size);
    m_pos += size_t_size;
    checkLength(strSize);
    std::string result(m_array+m_pos, strSize);
    m_pos += strSize;
    return result;
}