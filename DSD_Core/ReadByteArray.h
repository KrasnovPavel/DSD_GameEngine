//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 12.11.17.
//

#ifndef DSD_GAMEENGINE_BYTEARRAY_H
#define DSD_GAMEENGINE_BYTEARRAY_H

#include <cstring>
#include <stdexcept>
#include <string>

class ReadByteArray
{
public:
    ReadByteArray(const char* const array, const std::size_t& length) : m_array(array), m_length(length) {}

    ~ReadByteArray()
    {
        delete[] m_array;
    }

    constexpr const std::size_t& length()
    {
        return m_length;
    }

    template <typename T>
    T read();

    bool isFinished()
    {
        return m_pos == m_length;
    }

private:
    template<typename T>
    T baseConversion();

    inline void checkLength(std::size_t size) const
    {
        if (m_pos + size > m_length) throw (std::out_of_range("ReadByteArray::read"));
    }
    const char* const m_array;
    const std::size_t m_length;
    std::size_t m_pos = 0;
};

template<typename T>
T ReadByteArray::baseConversion()
{
    const std::size_t size = sizeof(T);
    checkLength(size);
    T result;
    std::memcpy(&result, (m_array+m_pos), size);
    m_pos += size;
    return result;
}


#endif //DSD_GAMEENGINE_BYTEARRAY_H
