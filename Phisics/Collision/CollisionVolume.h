//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 12.02.18.
//

#ifndef DSD_GAMEENGINE_COLLISIONVOLUME_H
#define DSD_GAMEENGINE_COLLISIONVOLUME_H

#include "AABB.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Quaternion.h"

#ifndef NDEBUG
#include <GL/gl.h>
#include <GL/glut.h>
#endif

namespace DSD
{
    enum class CollisionType
    {
        SPHERE,
        BOX,
        POINT
    };

    class CollisionVolume : public DSDBaseObject
    {
    REFLECTION(CollisionVolume);
    public:
        CollisionVolume() : CollisionVolume(Vector3(), Quaternion())
        {}

        CollisionVolume(const Vector3 &position, const Quaternion &rotation) :
                DSDBaseObject(),
                m_position(position),
                m_rotation(rotation),
                isAABBChanged(true)
        {}

        CollisionVolume(const CollisionVolume &other) :
                DSDBaseObject(other),
                m_position(other.m_position),
                m_rotation(other.m_rotation),
                isAABBChanged(other.isAABBChanged)
        {}

        CollisionVolume(CollisionVolume &&other) noexcept :
                DSDBaseObject(other),
                m_position(other.m_position),
                m_rotation(other.m_rotation),
                isAABBChanged(other.isAABBChanged)
        {}

        CollisionVolume &operator=(const CollisionVolume &rhs)
        {
            m_position = rhs.m_position;
            m_rotation = rhs.m_rotation;
            static_cast<DSDBaseObject *>(this)->operator=(rhs);
            return *this;
        }

        inline void setPosition(const Vector3 &newPosition)
        {
            m_position = newPosition;
            isAABBChanged = true;
        }

        inline void setRotation(const Quaternion &newRotation)
        {
            m_rotation = newRotation;
            isAABBChanged = true;
        }

        inline const Vector3 &position() const
        {
            return m_position;
        }

        inline const Quaternion &rotation() const
        {
            return m_rotation;
        }

        inline void moveOn(const Vector3 &distance)
        {
            m_position += distance;
        }

        inline void rotateOn(const Quaternion &angle)
        {
            m_rotation *= angle;
        }

        const AABB &getAABB()
        {
            if (isAABBChanged) calculateAABB();

            return m_aabb;
        }

        virtual void debugDraw(bool drawAABB);

        virtual CollisionType type() const
        {
            return CollisionType::POINT;
        }

    protected:
        double *generateVertices(const Vector3 &min, const Vector3 &max);

        Vector3 m_position;
        Quaternion m_rotation;

        virtual void calculateAABB();

        bool isAABBChanged = false;
        AABB m_aabb;
    };
}

#endif //DSD_GAMEENGINE_COLLISIONVOLUME_H
