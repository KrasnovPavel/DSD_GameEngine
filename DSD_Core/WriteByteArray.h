//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 12.11.17.
//

#ifndef DSD_GAMEENGINE_WRITEBYTEARRAY_H
#define DSD_GAMEENGINE_WRITEBYTEARRAY_H

#include <cstring>
#include <stdexcept>

/**
 * @addtogroup Serialization
 * @{
 */

/**
 * @brief The WriteByteArray class
 * @details Class implements write-only byte array
 */
class WriteByteArray
{
public:
    /**
     * @brief WriteByteArray Default constructor
     * @details Doesn't allocate memory and can not be used.
     * For usage call WriteByteArray::reset(const std::size_t& newSize).
     */
    WriteByteArray() : m_array(nullptr), m_length(0) {}

    /**
     * @brief WriteByteArray Constructor
     * @details Allocate @a length bytes for writing.
     * @param length
     */
    explicit WriteByteArray(const std::size_t& length)
            : m_array(new char[length]), m_length(length) {}

    /**
     * @brief ~WriteByteArray Defult destructor
     */
    ~WriteByteArray()
    {
        delete[] m_array;
    }

    /**
     * @brief length Returns length of byte array
     * @return
     */
    inline const std::size_t& length() const
    {
        return m_length;
    }

    /**
     * @brief write Writes data
     * @details Writes presents @a var as byte array and writes it.
     * @throw std::out_of_range if sizeof( @a T ) more than bytes till end of array.
     * @param var Variable to write
     * @tparam T Type to write
     */
    template <typename t>
    void write(const t& var);

    /**
     * @brief data Returns const pointer to data
     * @return
     */
    inline const char* data() const
    {
        return m_array;
    }

    /**
     * @brief reset Reset byte array
     * @details Deletes old data and allocate @a newLength bytes for new byte array.
     * @param newLength
     */
    void reset(const std::size_t& newLength)
    {
        delete[] m_array;
        m_length = newLength;
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

/**
 * @}
 */

#endif //DSD_GAMEENGINE_WRITEBYTEARRAY_H
