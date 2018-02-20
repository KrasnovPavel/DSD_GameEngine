//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 12.02.18.
//

#ifndef DSD_GAMEENGINE_COLLISIONBOX_H
#define DSD_GAMEENGINE_COLLISIONBOX_H

#include <algorithm>

#include "CollisionVolume.h"

namespace DSD
{
    class CollisionBox : public CollisionVolume
    {
    REFLECTION(CollisionBox);
    public:
        CollisionBox() : CollisionBox(0, 0, 0, Vector3(), Quaternion())
        {}

        CollisionBox(const double &x, const double &y, const double &z, const Vector3 &position,
                     const Quaternion &rotation)
                : CollisionVolume(position, rotation), m_x(x), m_y(y), m_z(z)
        {}

        void setX(const double &newX)
        {
            m_x = newX;
            isAABBChanged = true;
        }

        void setY(const double &newY)
        {
            m_y = newY;
            isAABBChanged = true;
        }

        void setZ(const double &newZ)
        {
            m_z = newZ;
            isAABBChanged = true;
        }

        inline const double &x() const
        {
            return m_x;
        }

        inline const double &y() const
        {
            return m_y;
        }

        inline const double &z() const
        {
            return m_z;
        }

        void debugDraw(bool drawAABB) override;

        CollisionType type() const override
        {
            return CollisionType::BOX;
        }

    protected:
        void calculateAABB() override;

        double m_x = 0, m_y = 0, m_z = 0;
    };
}

#endif //DSD_GAMEENGINE_COLLISIONBOX_H
