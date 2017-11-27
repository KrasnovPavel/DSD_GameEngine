//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 12.11.17.
//

#ifndef DSD_GAMEENGINE_WRITEBYTEARRAY_H
#define DSD_GAMEENGINE_WRITEBYTEARRAY_H

#include <cstring>
#include <stdexcept>

class WriteByteArray
{
public:
    WriteByteArray() : m_array(nullptr), m_length(0) {}

    explicit WriteByteArray(const std::size_t& length)
            : m_array(new char[length]), m_length(length) {}

    ~WriteByteArray()
    {
        delete[] m_array;
    }

    inline const std::size_t& length() const
    {
        return m_length;
    }

    template <typename t>
    void write(const t& var);

    inline const char* data() const
    {
        return m_array;
    }

    void reset(const std::size_t& newSize)
    {
        delete[] m_array;
        m_length = newSize;
        m_array = new char[m_length];
        m_pos = 0;
    }

private:
    template<typename T>
    void basicConversion(const T& var);

    char* m_array;
    std::size_t m_length;
    std::size_t m_pos = 0;

    void checkLength(std::size_t size)
    {
        if (m_pos+size > m_length) throw(std::out_of_range("WriteByteArray::write"));
    }
};

template<typename T>
void WriteByteArray::basicConversion(const T& var)
{
    const std::size_t size = sizeof(T);
    checkLength(size);
    std::memcpy((m_array+m_pos), &var, size);
    m_pos += size;
}

#endif //DSD_GAMEENGINE_WRITEBYTEARRAY_H
