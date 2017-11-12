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