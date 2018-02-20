//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 29.11.17.
//

#ifndef DSD_GAMEENGINE_VECTOR4_H
#define DSD_GAMEENGINE_VECTOR4_H

#include <cmath>

#include "Core/DSDBaseObject.h"

namespace DSD
{
/**
 * @addtogroup Math
 * @{
 */

    /**
     * @brief Implements vector and operations with it in four-dimensional space.
     */
    class Vector4 : public DSDBaseObject
    {
    REFLECTION(Vector4);
    public:
        /**
         * @brief Default constructor
         * @details Fills values with zeroes.
         */
        Vector4()
        {}

        /**
         * @brief Default copy-constructor
         * @param other
         */
        Vector4(Vector4 &&other) noexcept
                : x(other.x), y(other.y), z(other.z), w(other.w)
        {}

        /**
         * @brief Default move-constructor
         * @param other
         */
        Vector4(const Vector4 &other)
                : x(other.x), y(other.y), z(other.z), w(other.w)
        {}

        /**
         * @brief Constructor
         * @details Constructs new object and sets values.
         * @param x 1-st coordinate
         * @param y 2-nd coordinate
         * @param z 3-rd coordinate
         * @param w 4-th coordinate
         */
        Vector4(const double &x, const double &y, const double &z, const double &w)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        /**
         * @brief Sets coordinates
         * @param x 1-st coordinate
         * @param y 2-nd coordinate
         * @param z 3-rd coordinate
         * @param w 4-th coordinate
         */
        inline void set(const double &x, const double &y, const double &z, const double &w)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        /**
         * @brief Calculates cross product of two vectors
         * @param first
         * @param second
         * @return first\f$\bullet\f$second
         */
        static double dot(const Vector4 &first, const Vector4 &second);

        /**
         * @brief Calculates dot product of this and other given vectors
         * @param other
         * @return first\f$\bullet\f$other
         */
        inline double dot(const Vector4 &other) const
        {
            return Vector4::dot(*this, other);
        }

        /**
         * @brief Calculates length(magnitude) of this vector.
         * @return
         */
        inline double length() const
        {
            return std::sqrt(x * x + y * y + z * z + w * w);
        }

        /**
         * @brief Checks if two vectors are equivalent.
         * @param rhs
         * @return
         */
        inline bool operator==(const Vector4 &rhs) const
        {   //TODO: Epsilon check
            return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w);
        }

        /**
         * @brief Checks if two vectors are not equivalent.
         * @param rhs
         * @return
         */
        inline bool operator!=(const Vector4 &rhs) const
        {
            return !(*this == rhs);
        }

        /**
         * @brief Subtracts other vector from this and applies result to this vector.
         * @param rhs
         * @return Changed this vector.
         */
        inline Vector4 &operator-=(const Vector4 &rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            w -= rhs.w;
            return *this;
        }

        /**
         * @brief Adds other vector to this and applies result to this vector.
         * @param rhs
         * @return Changed this vector.
         */
        inline Vector4 &operator+=(const Vector4 &rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            w += rhs.w;
            return *this;
        }

        /**
         * @brief Multiplies this vector on double value and applies result to this vector.
         * @param rhs
         * @return Changed this vector.
         */
        inline Vector4 &operator*=(const double &rhs)
        {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            w *= rhs;
            return *this;
        }

        /**
         * @brief Divides this vector by double value and applies result to this vector.
         * @param rhs
         * @return Changed this vector.
         */
        inline Vector4 &operator/=(const double &rhs)
        {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            w /= rhs;
            return *this;
        }

        /**
         * @brief Adds other vector to this.
         * @param lhs
         * @param rhs
         * @return New vector = lhs + rhs.
         */
        friend inline Vector4 operator+(Vector4 lhs, const Vector4 &rhs)
        {
            lhs += rhs;
            return lhs;
        }

        /**
         * @brief Subtracts other vector from this.
         * @param lhs
         * @param rhs
         * @return New vector = lhs - rhs.
         */
        friend inline Vector4 operator-(Vector4 lhs, const Vector4 &rhs)
        {
            lhs -= rhs;
            return lhs;
        }

        /**
         * @brief Changes sign of all vector values.
         * @param rhs
         * @return New vector = -rhs.
         */
        friend inline Vector4 operator-(Vector4 rhs)
        {
            rhs *= -1;
            return rhs;
        }

        /**
         * @brief Multiplies this vector on double value.
         * @param lhs
         * @param rhs
         * @return New vector = lhs * rhs
         */
        friend inline Vector4 operator*(Vector4 lhs, const double &rhs)
        {
            lhs *= rhs;
            return lhs;
        }

        /**
         * @brief Divides this vector by double value.
         * @param lhs
         * @param rhs
         * @return New vector = lhs / rhs
         */
        friend inline Vector4 operator/(Vector4 lhs, const double &rhs)
        {
            lhs /= rhs;
            return lhs;
        }

        /**
         * @brief Calculates distance between this vector and other in four-dimentional space.
         * @param other
         * @return
         */
        inline double distance(const Vector4 &other) const
        {
            return ((*this) - other).length();
        }

        /**
         * @brief Calculates distance between two vectors in four-dimensional space.
         * @param first
         * @param second
         * @return
         */
        static inline double distance(const Vector4 &first, const Vector4 &second)
        {
            return first.distance(second);
        }

        /**
         *
         * @param rhl
         * @return
         */
        Vector4 &operator=(const Vector4 &rhl)
        {
            x = rhl.x;
            y = rhl.y;
            z = rhl.z;
            w = rhl.w;
            return *this;
        }

        /**
         * @brief Normalizes this vector.
         * @return
         */
        virtual Vector4 &normalize()
        {
            (*this) /= this->length();
            return *this;
        }

        /**
         * @brief Returns normalized version of this vector.
         * @return
         */
        virtual Vector4 normalized() const
        {
            return (*this) / this->length();
        }

        /**
         * @brief Represents vector values as std::string.
         * @return
         */
        std::string toString() const override;

        SERIALIZABLE(double, x, 0);
        SERIALIZABLE(double, y, 0);
        SERIALIZABLE(double, z, 0);
        SERIALIZABLE(double, w, 0);
    };
}
/**
 * @}
 */

#endif //DSD_GAMEENGINE_VECTOR4_H
