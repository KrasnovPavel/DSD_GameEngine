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