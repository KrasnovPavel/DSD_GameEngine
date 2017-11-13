//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 12.11.17.
//

#ifndef DSD_GAMEENGINE_BYTEARRAY_H
#define DSD_GAMEENGINE_BYTEARRAY_H

#include <stdexcept>
#include <string>

class ReadByteArray
{
public:
    ReadByteArray(const char* const array, const unsigned& length) : m_array(array), m_length(length) {}

    constexpr const unsigned& length()
    {
        return m_length;
    }

    template <typename t>
    t read();

private:
    inline void checkLength(std::size_t size) const
    {
        if (m_pos + size >= m_length) throw (std::out_of_range("ReadByteArray::read"));
    }
    const char* const m_array;
    const unsigned m_length;
    unsigned m_pos = 0;
};


#endif //DSD_GAMEENGINE_BYTEARRAY_H
