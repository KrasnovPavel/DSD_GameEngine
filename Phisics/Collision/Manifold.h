//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 19.02.18.
//

#ifndef DSD_GAMEENGINE_MANIFOLD_H
#define DSD_GAMEENGINE_MANIFOLD_H

#include "Core/DSDBaseObject.h"
#include "CollisionVolume.h"

namespace DSD
{
    class Manifold : public DSDBaseObject
    {
    REFLECTION(Manifold);
    public:
        Manifold() : Manifold(nullptr, nullptr)
        {}

        Manifold(CollisionVolume *first, CollisionVolume *second)
                : DSDBaseObject(), first(first), second(second)
        {}

        Manifold(const Manifold &other) = default;

        Manifold(Manifold &&other) noexcept : DSDBaseObject(other), first(other.first), second(other.second)
        {}

        Manifold &operator=(const Manifold &rhs)
        {
            first = rhs.first;
            second = rhs.second;
            static_cast<DSDBaseObject *>(this)->operator=(rhs);
            return *this;
        }

        CollisionVolume *first;
        CollisionVolume *second;
    };
}

#endif //DSD_GAMEENGINE_MANIFOLD_H
