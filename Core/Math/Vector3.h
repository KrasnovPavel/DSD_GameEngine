//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 29.11.17.
//

#ifndef DSD_GAMEENGINE_VECTOR3_H
#define DSD_GAMEENGINE_VECTOR3_H

#include <cmath>

#include "Core/DSDBaseObject.h"
#include "Functions.h"

namespace DSD
{
/**
 * @defgroup Math
 * @brief Mathematics implementation
 * @{
 */

    /**
     * @brief Implements vector and operations with it in three-dimensional space.
     */
    class Vector3 : public DSDBaseObject
    {
    REFLECTION(Vector3);
    public:
        /**
         * @brief Default constructor
         * @details Fills values with zeroes.
         */
        Vector3()
        {}

        /**
         * @brief Default copy-constructor
         * @param other
         */
        Vector3(Vector3 &&other) noexcept
                : x(other.x), y(other.y), z(other.z), DSDBaseObject(other)
        {}

        /**
         * @brief Default move-constructor
         * @param other
         */
        Vector3(const Vector3 &other)
                : x(other.x), y(other.y), z(other.z), DSDBaseObject(other)
        {}

        /**
         * @brief Constructor
         * @details Constructs new object and sets values.
         * @param x 1-st coordinate
         * @param y 2-nd coordinate
         * @param z 3-rd coordinate
         */
        inline Vector3(const double &x, const double &y, const double &z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        /**
         * @brief Sets coordinates
         * @param x 1-st coordinate
         * @param y 2-nd coordinate
         * @param z 3-rd coordinate
         */
        void set(const double &x, const double &y, const double &z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        /**
         * @brief Calculates cross product of two vectors
         * @param first
         * @param second
         * @return first\f$\bullet\f$second
         */
        static double dot(const Vector3 &first, const Vector3 &second);

        /**
         * @brief Calculates dot product of this and other given vectors
         * @param other
         * @return first\f$\bullet\f$other
         */
        inline double dot(const Vector3 &other) const
        {
            return Vector3::dot(*this, other);
        }

        /**
         * @brief Calculates cross product of two vectors
         * @param first
         * @param second
         * @return first\f$\times\f$second
         */
        static Vector3 cross(const Vector3 &first, const Vector3 &second);

        /**
         * @brief Calculates cross product of this and other given vectors
         * @param other
         * @return first\f$\times\f$other
         */
        Vector3 cross(const Vector3 &other) const
        {
            return Vector3::cross(*this, other);
        }

        /**
         * @brief Calculates length(magnitude) of this vector.
         * @return
         */
        inline double length() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        /**
         * @brief Calculates squared length(magnitude) of this vector.
         * @return
         */
        inline double lengthSquared() const
        {
            return x * x + y * y + z * z;
        }

        /**
         * @brief Checks if two vectors are equivalent.
         * @param rhs
         * @return
         */
        inline bool operator==(const Vector3 &rhs) const
        {
            return Math::almostEqual(x, rhs.x) && Math::almostEqual(y, rhs.y) && Math::almostEqual(z, rhs.z);
        }

        /**
         * @brief Checks if two vectors are not equivalent.
         * @param rhs
         * @return
         */
        inline bool operator!=(const Vector3 &rhs) const
        {
            return !(*this == rhs);
        }

        /**
         * @brief Subtracts other vector from this and applies result to this vector.
         * @param rhs
         * @return Changed this vector.
         */
        inline Vector3 &operator-=(const Vector3 &rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        /**
         * @brief Adds other vector to this and applies result to this vector.
         * @param rhs
         * @return Changed this vector.
         */
        inline Vector3 &operator+=(const Vector3 &rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        /**
         * @brief Multiplies this vector on double value and applies result to this vector.
         * @param rhs
         * @return Changed this vector.
         */
        inline Vector3 &operator*=(const double &rhs)
        {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }

        /**
         * @brief Divides this vector by double value and applies result to this vector.
         * @param rhs
         * @return Changed this vector.
         */
        inline Vector3 &operator/=(const double &rhs)
        {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }

        /**
         * @brief Adds other vector to this.
         * @param lhs
         * @param rhs
         * @return New vector = lhs + rhs.
         */
        friend inline Vector3 operator+(Vector3 lhs, const Vector3 &rhs)
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
        friend inline Vector3 operator-(Vector3 lhs, const Vector3 &rhs)
        {
            lhs -= rhs;
            return lhs;
        }

        /**
         * @brief Changes sign of all vector values.
         * @param rhs
         * @return New vector = -rhs.
         */
        friend inline Vector3 operator-(Vector3 rhs)
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
        friend inline Vector3 operator*(Vector3 lhs, const double &rhs)
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
        friend inline Vector3 operator/(Vector3 lhs, const double &rhs)
        {
            lhs /= rhs;
            return lhs;
        }

        /**
         * @brief Calculates distance between this vector and other in three-dimentional space.
         * @param other
         * @return
         */
        inline double distance(const Vector3 &other) const
        {
            return ((*this) - other).length();
        }

        /**
         * @brief Calculates distance between two vectors in three-dimensional space.
         * @param first
         * @param second
         * @return
         */
        static inline double distance(const Vector3 &first, const Vector3 &second)
        {
            return first.distance(second);
        }

        /**
         * @brief Copy-assignment operator
         * @param rhs
         * @return
         */
        inline Vector3 &operator=(const Vector3 &rhs)
        {
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            static_cast<DSDBaseObject *>(this)->operator=(rhs);
            return *this;
        }

        /**
         * @brief Normalizes this vector.
         * @return
         */
        inline Vector3 &normalize()
        {
            (*this) /= this->length();
            return *this;
        }

        /**
         * @brief Returns normalized version of this vector.
         * @return
         */
        inline Vector3 normalized() const
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
    };
}
/**
 * @}
 */

#endif //DSD_GAMEENGINE_VECTOR3_H
