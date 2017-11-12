//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 12.11.17.
//

#ifndef DSD_GAMEENGINE_WRITEBYTEARRAY_H
#define DSD_GAMEENGINE_WRITEBYTEARRAY_H

#include <stdexcept>

class WriteByteArray
{
public:
    explicit WriteByteArray(const unsigned& length) : m_array(new char(length)), m_length(length) {}

    ~WriteByteArray()
    {
        delete[] m_array;
    }

    constexpr const unsigned& length()
    {
        return m_length;
    }

    template <typename t>
    void write(const t& var);

    constexpr const char* data()
    {
        return m_array;
    }

    void reset(const unsigned& newSize)
    {
        delete[] m_array;
        m_length = newSize;
        m_array = new char(m_length);
    }

private:
    char* m_array;
    unsigned m_length;
    unsigned m_pos = 0;

    void checkLength(std::size_t size)
    {
        if (m_pos+size >= m_length) throw(std::out_of_range("WriteByteArray::operator<<"));
    }
};



#endif //DSD_GAMEENGINE_WRITEBYTEARRAY_H
