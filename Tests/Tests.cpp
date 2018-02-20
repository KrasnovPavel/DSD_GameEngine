//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 20.02.18.
//

#include <gtest/gtest.h>
#include "Core/Math/Vector3.h"

TEST(Vector3, Length)
{
    DSD::Vector3 a(3, 4, 0);

    ASSERT_DOUBLE_EQ(a.length(), 5);
}