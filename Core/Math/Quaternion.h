//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 07.12.17.
//

#ifndef DSD_GAMEENGINE_QUATERNION_H
#define DSD_GAMEENGINE_QUATERNION_H

#include <cmath>

#include "Core/DSDBaseObject.h"
#include "Vector3.h"
#include "Vector4.h"

namespace DSD
{
/**
 * @addtogroup Math
 * @{
 */

    /**
     * @brief Implements quanternion math.
     */
    class Quaternion : public DSDBaseObject
    {
    REFLECTION(Quaternion);
    public:
        /**
         * @brief Default constructor
         * @details x = 0, y = 0, z = 0, w = 1.
         */
        Quaternion()
        {}


        /**
         * @brief Copy constructor
         * @param other
         */
        Quaternion(const Quaternion &other) :
                m_vector(other.m_vector), scalar(other.scalar)
        {}

        /**
         * @brief Constructs quaternion by angle and axis of rotation.
         * @param angle
         * @param axis
         */
        Quaternion(const double &angle, const Vector3 &axis);

        /**
         * @brief Constructs quaternion by Euler angles.
         * @param roll
         * @param pitch
         * @param yaw
         */
        Quaternion(const double &roll, const double &pitch, const double &yaw);

        /**
         * @brief Rotates given vector on this quaternion.
         * @param vector
         * @return
         */
        Vector3 &rotateVector(Vector3 &vector) const;

        /**
         * @brief Returns vector rotated on this quaternion.
         * @param vector
         * @return
         */
        Vector3 rotatedVector(Vector3 vector) const;

        /**
         * @brief Multiplies this quaternion on othis and applies result.
         * @param rhs
         * @return Changed this quaternion.
         */
        Quaternion &operator*=(const Quaternion &rhs);

        /**
         * @brief Multiplies two quaternions.
         * @param lhs
         * @param rhs
         * @return
         */
        friend inline Quaternion operator*(Quaternion lhs, const Quaternion &rhs)
        {
            lhs *= rhs;
            return lhs;
        }

        /**
         * @brief Returns length of this quaternion.
         * @return
         */
        inline double length() const
        {
            return 1 / std::sqrt(
                    m_vector.x * m_vector.x + m_vector.y * m_vector.y + m_vector.z * m_vector.z + scalar * scalar);
        }

        /**
         * @brief Normalizes this quaternion.
         * @return
         */
        inline Quaternion &normalize()
        {
            (*this) = normalized();
            return *this;
        }

        /**
         * @brief Returns normalised quaternion.
         * @return
         */
        inline Quaternion normalized() const
        {
            return (*this) * (1 / std::sqrt(
                    m_vector.x * m_vector.x + m_vector.y * m_vector.y + m_vector.z * m_vector.z + scalar * scalar));
        }

        /**
         *
         * @param rhl
         * @return
         */
        Quaternion &operator=(const Quaternion &rhl)
        {
            m_vector = rhl.m_vector;
            scalar = rhl.scalar;
            return *this;
        }

        /**
         * @brief Checks if two quaternions are equal.
         * @param rhs
         * @return
         */
        inline bool operator==(const Quaternion &rhs) const
        {   //TODO: Epsilon check
            return (m_vector == rhs.m_vector) && (scalar == rhs.scalar);
        }

        /**
         * @brief Checks if two quaternions are not equal.
         * @param rhs
         * @return
         */
        inline bool operator!=(const Quaternion &rhs) const
        {
            return !(*this == rhs);
        }

        /**
         * @brief Returns inverted quaternion.
         * @return
         */
        inline Quaternion inverted() const
        {
            return Quaternion(scalar, -m_vector.x, -m_vector.y, -m_vector.z);
        }

        /**
         * @brief Represents quaternion as axis and angle of rotation.
         * @return
         */
        std::pair<Vector3, double> toAxisAngle() const;

        /**
         * @brief Represents quaternion as std::string.
         * @return
         */
        std::string toString() const override;

    private:
        Quaternion(const double &w, const double &x, const double &y, const double &z)
                : scalar(w), m_vector(x, y, z)
        {}

        inline Quaternion &operator*=(const double &rhs)
        {
            m_vector.x *= rhs;
            m_vector.y *= rhs;
            m_vector.z *= rhs;
            scalar *= rhs;
            return *this;
        }

        friend inline Quaternion operator*(Quaternion lhs, const double &rhs)
        {
            lhs *= rhs;
            return lhs;
        }

        SERIALIZABLE(Vector3, m_vector, Vector3());
        SERIALIZABLE(double, scalar, 1);
    };
}
/**
 * @}
 */
#endif //DSD_GAMEENGINE_QUATERNION_H

