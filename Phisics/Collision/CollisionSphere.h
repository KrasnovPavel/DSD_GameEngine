//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 12.02.18.
//

#ifndef DSD_GAMEENGINE_COLLISIONSPHERE_H
#define DSD_GAMEENGINE_COLLISIONSPHERE_H

#include <cmath>
#include <vector>

#include "CollisionVolume.h"

namespace DSD
{
    class CollisionSphere : public CollisionVolume
    {
    REFLECTION(CollisionSphere);
    public:
        CollisionSphere() : CollisionSphere(Vector3(), 0, Quaternion())
        {}

        CollisionSphere(const Vector3 &position, const double &radius, const Quaternion &rotation = Quaternion())
                : CollisionVolume(position, rotation), m_radius(radius)
        {}

        void setRadius(const double &newRadius)
        {
            m_radius = newRadius;
            isAABBChanged = true;
        }

        inline const double &radius() const
        {
            return m_radius;
        }

        void debugDraw(bool drawAABB) override;

        CollisionType type() const override
        {
            return CollisionType::SPHERE;
        }

    protected:
        void calculateAABB() override
        {
            Vector3 tmp(m_radius, m_radius, m_radius);
            m_aabb = AABB(m_position - tmp, m_position + tmp);
        }

        SERIALIZABLE(double, m_radius, 0);
    };
}

#endif //DSD_GAMEENGINE_COLLISIONSPHERE_H
