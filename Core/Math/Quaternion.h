//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 07.12.17.
//

#ifndef DSD_GAMEENGINE_QUATERNION_H
#define DSD_GAMEENGINE_QUATERNION_H

#include <cmath>

#include "Core/DSDBaseObject.h"
#include "Vector3.h"
#include "Vector4.h"

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
    Quaternion() {}

    /**
     * @brief Constructs quaternion by angle and axis of rotation.
     * @param angle
     * @param axis
     */
    Quaternion(const double& angle, const Vector3& axis);

    /**
     * @brief Constructs quaternion by Euler angles.
     * @param roll
     * @param pitch
     * @param yaw
     */
    Quaternion(const double& roll, const double& pitch, const double& yaw);

    /**
     * @brief Rotates given vector on this quaternion.
     * @param vector
     * @return
     */
    Vector3& rotateVector(Vector3& vector) const;

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
    Quaternion& operator *=(const Quaternion& rhs);

    /**
     * @brief Multiplies two quaternions.
     * @param lhs
     * @param rhs
     * @return
     */
    friend inline Quaternion operator *(Quaternion lhs, const Quaternion& rhs)
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
        return 1/m_invLength;
    }

    /**
     * @brief Normalizes this quaternion.
     * @return
     */
    inline Quaternion& normalize()
    {
        (*this) = normalized();
        calculate();
        return *this;
    }

    /**
     * @brief Returns normalised quaternion.
     * @return
     */
    inline Quaternion normalized() const
    {
        return (*this) * m_invLength;
    }

    /**
     *
     * @param rhl
     * @return
     */
    Quaternion& operator=(const Quaternion& rhl)
    {
        vector = rhl.vector;
        scalar = rhl.scalar;
        calculate();
        return *this;
    }

    /**
     * @brief Checks if two quaternoins are equality.
     * @param rhs
     * @return
     */
    inline bool operator ==(const Quaternion& rhs) const
    {   //TODO: Epsilon check
        return (vector == rhs.vector) && (scalar == rhs.scalar);
    }

    /**
     * @brief Checks if two quaternoins are not equality.
     * @param rhs
     * @return
     */
    inline bool operator !=(const Quaternion& rhs) const
    {
        return !(*this == rhs);
    }

    /**
     * @brief Returns inverted quaternion.
     * @return
     */
    inline Quaternion inverted() const
    {
        return Quaternion(scalar, -vector);
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
    void calculate();

    Quaternion(const double& w, const double& x, const double& y, const double& z);

    inline Quaternion& operator *=(const double& rhs)
    {
        vector.x *= rhs;
        vector.y *= rhs;
        vector.z *= rhs;
        scalar *= rhs;
        calculate();
        return *this;
    }

    friend inline Quaternion operator *(Quaternion lhs, const double& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    SERIALIZABLE(Vector3, vector, Vector3());
    SERIALIZABLE(double, scalar, 1);
    double m_invLength, m_angle;
    Vector3 m_axis;
};

/**
 * @}
 */
#endif //DSD_GAMEENGINE_QUATERNION_H

