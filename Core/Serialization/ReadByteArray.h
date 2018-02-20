//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 12.11.17.
//

#ifndef DSD_GAMEENGINE_BYTEARRAY_H
#define DSD_GAMEENGINE_BYTEARRAY_H

#include <cstring>
#include <stdexcept>
#include <string>

namespace DSD
{
/**
 * @addtogroup Serialization
 * @{
 */

    /**
     * @brief The ReadByteArray class
     * @details Class implements read-only byte array
     */
    class ReadByteArray
    {
    public:
        /**
         * @brief ReadByteArray Constructor
         * @param array Byte array
         * @param length length of ByteArray
         */
        ReadByteArray(const char *const array, const std::size_t &length)
                : m_array(array), m_length(length)
        {}

        /**
         * @brief ~ReadByteArray Destructor
         * @details Deletes array was given in constructor.
         */
        ~ReadByteArray()
        {
            delete[] m_array;
        }

        /**
         * @brief length Returns length of byte array
         * @return
         */
        constexpr const std::size_t &length()
        {
            return m_length;
        }

        /**
         * @brief read Reads data
         * @details Reads sizeof( @a T ) bytes from array and casts it to T and returns.
         * @throw std::out_of_range if sizeof( @a T ) more than bytes till end of array.
         * @tparam T type to read
         * @return red variable
         */
        template<typename T>
        T read();

        /**
         * @brief isFinished Returns true if there is no more bytes to read.
         * @return
         */
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

        const char *const m_array;
        const std::size_t m_length;
        std::size_t m_pos = 0;
    };

    template<typename T>
    T ReadByteArray::baseConversion()
    {
        const std::size_t size = sizeof(T);
        checkLength(size);
        T result;
        std::memcpy(&result, (m_array + m_pos), size);
        m_pos += size;
        return result;
    }
}
/**
 * @}
 */

#endif //DSD_GAMEENGINE_BYTEARRAY_H
