//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 20.02.18.
//

#ifndef DSD_GAMEENGINE_FUNCTIONS_H
#define DSD_GAMEENGINE_FUNCTIONS_H

#include "GTestAlmostEqual.h"

namespace DSD
{
    namespace Math
    {
        inline bool almostEqual(const double& lhs, const double& rhs)
        {
            const FloatingPoint<double> left(lhs), right(rhs);
            return left.AlmostEquals(right);
        }
    }
}

#endif //DSD_GAMEENGINE_FUNCTIONS_H
