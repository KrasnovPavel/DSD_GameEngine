//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 19.02.18.
//

#include "CollisionChecker.h"

std::vector<Manifold*> *CollisionChecker::checkAll(const std::vector<CollisionVolume *> &volumes)
{
    auto result = new std::vector<Manifold*>();

    for (int i = 0; i < volumes.size(); ++i)
    {
        for (int j = i+1; j < volumes.size(); ++j)
        {
            auto manifold = checkVolumes(volumes.at(i), volumes.at(j));
            if (manifold)
            {
                result->push_back(manifold);
            }
        }
    }
    return result;
}

Manifold* CollisionChecker::check(CollisionSphere *first, CollisionSphere *second)
{
    if ((first->position() - second->position()).lengthSquared() <= std::pow((first->radius() + second->radius()), 2))
        return new Manifold(first, second);

    return nullptr;
}

Manifold* CollisionChecker::check(CollisionBox *first, CollisionSphere *second)
{
    if (AABB::isCollide(first->getAABB(), second->getAABB()))
    {

    }

    return nullptr;
}

Manifold* CollisionChecker::check(CollisionSphere *first, CollisionBox *second)
{
    return check(second, first);
}

Manifold* CollisionChecker::check(CollisionBox *first, CollisionBox *second)
{
    if (AABB::isCollide(first->getAABB(), second->getAABB()))
    {

    }

    return nullptr;
}

Manifold *CollisionChecker::checkVolumes(CollisionVolume *first, CollisionVolume *second)
{
    switch (first->type())
    {
        case CollisionType::SPHERE:
            switch (second->type())
            {
                case CollisionType::SPHERE:
                    return check(static_cast<CollisionSphere*>(first), static_cast<CollisionSphere*>(second));
                case CollisionType::BOX:
                    return check(static_cast<CollisionSphere*>(first), static_cast<CollisionBox*>(second));
            }
        case CollisionType::BOX:
            switch (second->type())
            {
                case CollisionType::SPHERE:
                    return check(static_cast<CollisionBox*>(first), static_cast<CollisionSphere*>(second));
                case CollisionType::BOX:
                    return check(static_cast<CollisionBox*>(first), static_cast<CollisionBox*>(second));
            }
    }
    return nullptr;
}
