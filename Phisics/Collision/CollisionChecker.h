//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 19.02.18.
//

#ifndef DSD_GAMEENGINE_COLLISIONCHECKER_H
#define DSD_GAMEENGINE_COLLISIONCHECKER_H

#include <vector>

#include "CollisionBox.h"
#include "CollisionSphere.h"
#include "Manifold.h"

namespace DSD
{
    class CollisionChecker
    {
    public:
        static std::vector<Manifold *> *checkAll(const std::vector<CollisionVolume *> &volumes);

    private:
        static Manifold *checkVolumes(CollisionVolume *first, CollisionVolume *second);

        static Manifold *check(CollisionSphere *first, CollisionSphere *second);

        static Manifold *check(CollisionBox *first, CollisionSphere *second);

        static Manifold *check(CollisionSphere *first, CollisionBox *second);

        static Manifold *check(CollisionBox *first, CollisionBox *second);

        static Manifold *check(CollisionVolume *first, CollisionBox *second);

        static Manifold *check(CollisionBox *first, CollisionVolume *second);

        static Manifold *check(CollisionVolume *first, CollisionSphere *second);

        static Manifold *check(CollisionSphere *first, CollisionVolume *second);

        static Manifold *check(CollisionVolume *first, CollisionVolume *second);
    };
}

#endif //DSD_GAMEENGINE_COLLISIONCHECKER_H
