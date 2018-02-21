//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 20.02.18.
//

#include <gtest/gtest.h>
#include <random>

#include "Core/Math/Vector3.h"

double getRandomDouble()
{
    double lower_bound = -1000000;
    double upper_bound = 1000000;
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    std::default_random_engine re;
    return unif(re);
}

TEST(Vector3, Length)
{
    DSD::Vector3 a;

    for (int i = 0; i < 30; ++i)
    {
        auto x = getRandomDouble();
        auto y = getRandomDouble();
        auto z = getRandomDouble();
        a.set(x, y, z);
        ASSERT_DOUBLE_EQ(a.length(), sqrt(x*x + y*y + z*z));
    }
}

TEST(Vector3, LengthSquared)
{
    DSD::Vector3 a;

    for (int i = 0; i < 30; ++i)
    {
        auto x = getRandomDouble();
        auto y = getRandomDouble();
        auto z = getRandomDouble();
        a.set(x, y, z);
        ASSERT_DOUBLE_EQ(a.lengthSquared(), x*x + y*y + z*z);
    }
}

TEST(Vector3, Equals)
{
    for (int i = 0; i < 30; ++i)
    {
        DSD::Vector3 a(getRandomDouble(), getRandomDouble(), getRandomDouble());
        auto x = getRandomDouble();
        DSD::Vector3 b = a * x;
        ASSERT_TRUE(a == b / x);
    }
}