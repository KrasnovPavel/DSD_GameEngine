//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 18.02.18.
//

#ifndef DSD_GAMEENGINE_COLLISIONAABB_H
#define DSD_GAMEENGINE_COLLISIONAABB_H

#include <algorithm>

#include "Core/DSDBaseObject.h"
#include "Core/Math/Vector3.h"

namespace DSD
{
    class AABB : public DSDBaseObject
    {
    REFLECTION(AABB);
    public:
        AABB() : AABB(Vector3(), Vector3())
        {};

        AABB(const AABB &other) : DSDBaseObject(other), min(other.min), max(other.max)
        {}

        AABB(AABB &&other) : DSDBaseObject(other), min(other.min), max(other.max)
        {}

        AABB(Vector3 min, Vector3 max) : DSDBaseObject()
        {
            this->min.x = std::min(min.x, max.x);
            this->min.y = std::min(min.y, max.y);
            this->min.z = std::min(min.z, max.z);
            this->max.x = std::max(min.x, max.x);
            this->max.y = std::max(min.y, max.y);
            this->max.z = std::max(min.z, max.z);
        }

        AABB &operator=(const AABB &rhs)
        {
            min = rhs.min;
            max = rhs.max;
            static_cast<DSDBaseObject *>(this)->operator=(rhs);
            return *this;
        }

        static bool isCollide(const AABB &first, const AABB &second)
        {
            double d1x = second.min.x - first.max.x;
            double d1y = second.min.y - first.max.y;
            double d1z = second.min.z - first.max.z;
            double d2x = first.min.x - second.max.x;
            double d2y = first.min.y - second.max.y;
            double d2z = first.min.z - second.max.z;

            if (d1x > 0.0f ||
                d1y > 0.0f ||
                d1z > 0.0f ||
                d2x > 0.0f ||
                d2y > 0.0f ||
                d2z > 0.0f)
                return false;

            return true;
        }

        SERIALIZABLE(Vector3, min, Vector3());
        SERIALIZABLE(Vector3, max, Vector3());
    };
}

#endif //DSD_GAMEENGINE_COLLISIONAABB_H
