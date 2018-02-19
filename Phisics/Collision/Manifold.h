//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 19.02.18.
//

#ifndef DSD_GAMEENGINE_MANIFOLD_H
#define DSD_GAMEENGINE_MANIFOLD_H

#include "CollisionVolume.h"

class Manifold
{
public:
    Manifold(CollisionVolume* first, CollisionVolume* second) : first(first), second(second) {};

    CollisionVolume* first;
    CollisionVolume* second;
};


#endif //DSD_GAMEENGINE_MANIFOLD_H
