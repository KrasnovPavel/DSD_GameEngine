//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 20.02.18.
//

#include <gtest/gtest.h>
#include <random>

#include "Core/Math/Vector3.h"
#include "Core/Math/Vector4.h"
#include "Core/Math/Quaternion.h"

double getRandomDouble()
{
    double lower_bound = -1000000000;
    double upper_bound = 1000000000;
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    std::default_random_engine re;
    return unif(re);
}

TEST(Vector3, Init)
{
    DSD::Vector3 a;
    DSD::Vector3 b;

    for (int i = 0; i < 100; ++i)
    {
        auto x = getRandomDouble();
        auto y = getRandomDouble();
        auto z = getRandomDouble();
        a.set(x, y, z);
        b = DSD::Vector3(x, y, z);
        DSD::Vector3 c(x, y, z);
        DSD::Vector3 d(c);
        ASSERT_TRUE(a.x == x && a.y == y && a.z == z);
        ASSERT_TRUE(b.x == x && b.y == y && b.z == z);
        ASSERT_TRUE(c.x == x && c.y == y && c.z == z);
        ASSERT_TRUE(d.x == x && d.y == y && d.z == z);
    }
}

TEST(Vector3, Length)
{
    DSD::Vector3 a;

    for (int i = 0; i < 100; ++i)
    {
        auto x = getRandomDouble();
        auto y = getRandomDouble();
        auto z = getRandomDouble();
        a.set(x, y, z);
        ASSERT_DOUBLE_EQ(a.length(), sqrt(x*x + y*y + z*z));
        ASSERT_DOUBLE_EQ(a.lengthSquared(), x*x + y*y + z*z);
    }
}

TEST(Vector3, Distance)
{
    DSD::Vector3 a;
    DSD::Vector3 b;

    for (int i = 0; i < 100; ++i)
    {
        auto x = getRandomDouble();
        auto y = getRandomDouble();
        auto z = getRandomDouble();
        auto x1 = getRandomDouble();
        auto y1 = getRandomDouble();
        auto z1 = getRandomDouble();
        a.set(x, y, z);
        b.set(x1, y1, z1);
        ASSERT_DOUBLE_EQ(a.distance(b), sqrt((x-x1)*(x-x1) + (y-y1)*(y-y1) + (z-z1)*(z-z1)));
        ASSERT_DOUBLE_EQ(DSD::Vector3::distance(a, b), sqrt((x-x1)*(x-x1) + (y-y1)*(y-y1) + (z-z1)*(z-z1)));
    }
}

TEST(Vector3, Equals)
{
    DSD::Vector3 a;

    for (int i = 0; i < 30; ++i)
    {
        a.set(getRandomDouble(), getRandomDouble(), getRandomDouble());
        auto x = getRandomDouble();
        DSD::Vector3 b = a * x;
        ASSERT_TRUE(a == b / x);
        ASSERT_FALSE(a != b / x);
    }
}

TEST(Vector3, Operators)
{
    DSD::Vector3 a;
    DSD::Vector3 b;
    DSD::Vector3 d;

    for (int i = 0; i < 30; ++i)
    {
        auto x = getRandomDouble();
        auto y = getRandomDouble();
        auto z = getRandomDouble();
        auto x1 = getRandomDouble();
        auto y1 = getRandomDouble();
        auto z1 = getRandomDouble();
        auto c = getRandomDouble();
        a.set(x, y, z);
        b.set(x1, y1, z1);
        d = a - b;
        ASSERT_TRUE(d.x == x-x1 && d.y == y-y1 && d.z == z-z1);
        d = a;
        d -= b;
        ASSERT_TRUE(d.x == x-x1 && d.y == y-y1 && d.z == z-z1);
        d = a + b;
        ASSERT_TRUE(d.x == x+x1 && d.y == y+y1 && d.z == z+z1);
        d = a;
        d += b;
        ASSERT_TRUE(d.x == x+x1 && d.y == y+y1 && d.z == z+z1);
        d = a * c;
        ASSERT_TRUE(d.x == x*c && d.y == y*c && d.z == z*c);
        d = a;
        d *= c;
        ASSERT_TRUE(d.x == x*c && d.y == y*c && d.z == z*c);
        d = a / c;
        ASSERT_TRUE(d.x == x/c && d.y == y/c && d.z == z/c);
        d = a;
        d /= c;
        ASSERT_TRUE(d.x == x/c && d.y == y/c && d.z == z/c);
    }
};

TEST(Vector3, Norm)
{
    DSD::Vector3 a;
    for (int i = 0; i < 30; ++i)
    {
        auto x = getRandomDouble();
        auto y = getRandomDouble();
        auto z = getRandomDouble();
        auto l = sqrt(x*x + y*y + z*z);
        a.set(x, y, z);
        ASSERT_TRUE(a.normalized().x == x/l && a.normalized().y == y/l && a.normalized().z == z/l);
        ASSERT_TRUE(a.x == x && a.y == y && a.z == z);
        a.normalize();
        ASSERT_TRUE(a.x == x/l && a.y == y/l && a.z == z/l);
    }
}

TEST(Vector3, Dot)
{
    DSD::Vector3 a;
    DSD::Vector3 b;
    double c;

    for (int i = 0; i < 100; ++i)
    {
        auto x = getRandomDouble();
        auto y = getRandomDouble();
        auto z = getRandomDouble();
        auto x1 = getRandomDouble();
        auto y1 = getRandomDouble();
        auto z1 = getRandomDouble();
        a.set(x, y, z);
        b.set(x1, y1, z1);
        c = a.dot(b);
        ASSERT_TRUE(c == x*x1 + y*y1 + z*z1);
        c = DSD::Vector3::dot(a, b);
        ASSERT_TRUE(c == x*x1 + y*y1 + z*z1);
    }
}

TEST(Vector3, Cross)
{
    DSD::Vector3 a;
    DSD::Vector3 b;
    DSD::Vector3 c;

    for (int i = 0; i < 100; ++i)
    {
        auto x = getRandomDouble();
        auto y = getRandomDouble();
        auto z = getRandomDouble();
        auto x1 = getRandomDouble();
        auto y1 = getRandomDouble();
        auto z1 = getRandomDouble();
        a.set(x, y, z);
        b.set(x1, y1, z1);
        c = a.cross(b);
        ASSERT_TRUE(c == DSD::Vector3(y*z1 - z*y1, z1*x - x1*z, x*y1 - x1*y));
        c = DSD::Vector3::cross(a, b);
        ASSERT_TRUE(c == DSD::Vector3(y*z1 - z*y1, z1*x - x1*z, x*y1 - x1*y));
    }
}

TEST(Vector4, Init)
{
    DSD::Vector4 a;
    DSD::Vector4 b;

    for (int i = 0; i < 100; ++i)
    {
        auto x = getRandomDouble();
        auto y = getRandomDouble();
        auto z = getRandomDouble();
        auto w = getRandomDouble();
        a.set(x, y, z, w);
        b = DSD::Vector4(x, y, z, w);
        DSD::Vector4 c(x, y, z, w);
        DSD::Vector4 d(c);
        ASSERT_TRUE(a.x == x && a.y == y && a.z == z && a.w == w);
        ASSERT_TRUE(b.x == x && b.y == y && b.z == z && a.w == w);
        ASSERT_TRUE(c.x == x && c.y == y && c.z == z && a.w == w);
        ASSERT_TRUE(d.x == x && d.y == y && d.z == z && a.w == w);
    }
}

TEST(Vector4, Length)
{
    DSD::Vector4 a;

    for (int i = 0; i < 100; ++i)
    {
        auto x = getRandomDouble();
        auto y = getRandomDouble();
        auto z = getRandomDouble();
        auto w = getRandomDouble();
        a.set(x, y, z, w);
        ASSERT_DOUBLE_EQ(a.length(), sqrt(x*x + y*y + z*z + w*w));
    }
}

TEST(Vector4, Distance)
{
    DSD::Vector4 a;
    DSD::Vector4 b;

    for (int i = 0; i < 100; ++i)
    {
        auto x = getRandomDouble();
        auto y = getRandomDouble();
        auto z = getRandomDouble();
        auto w = getRandomDouble();
        auto x1 = getRandomDouble();
        auto y1 = getRandomDouble();
        auto z1 = getRandomDouble();
        auto w1 = getRandomDouble();
        a.set(x, y, z, w);
        b.set(x1, y1, z1, w1);
        ASSERT_DOUBLE_EQ(a.distance(b), sqrt((x-x1)*(x-x1) + (y-y1)*(y-y1) + (z-z1)*(z-z1) + (w-w1)*(w-w1)));
        ASSERT_DOUBLE_EQ(DSD::Vector4::distance(a, b), sqrt((x-x1)*(x-x1) + (y-y1)*(y-y1) + (z-z1)*(z-z1) + (w-w1)*(w-w1)));
    }
}

TEST(Vector4, Equals)
{
    DSD::Vector4 a;

    for (int i = 0; i < 30; ++i)
    {
        a.set(getRandomDouble(), getRandomDouble(), getRandomDouble(), getRandomDouble());
        auto x = getRandomDouble();
        DSD::Vector4 b = a * x;
        ASSERT_TRUE(a == b / x);
        ASSERT_FALSE(a != b / x);
    }
}

TEST(Vector4, Operators)
{
    DSD::Vector4 a;
    DSD::Vector4 b;
    DSD::Vector4 d;

    for (int i = 0; i < 30; ++i)
    {
        auto x = getRandomDouble();
        auto y = getRandomDouble();
        auto z = getRandomDouble();
        auto w = getRandomDouble();
        auto x1 = getRandomDouble();
        auto y1 = getRandomDouble();
        auto z1 = getRandomDouble();
        auto w1 = getRandomDouble();
        auto c = getRandomDouble();
        a.set(x, y, z, w);
        b.set(x1, y1, z1, w1);
        d = a - b;
        ASSERT_TRUE(d.x == x-x1 && d.y == y-y1 && d.z == z-z1 && d.w == w-w1);
        d = a;
        d -= b;
        ASSERT_TRUE(d.x == x-x1 && d.y == y-y1 && d.z == z-z1 && d.w == w-w1);
        d = a + b;
        ASSERT_TRUE(d.x == x+x1 && d.y == y+y1 && d.z == z+z1 && d.w == w+w1);
        d = a;
        d += b;
        ASSERT_TRUE(d.x == x+x1 && d.y == y+y1 && d.z == z+z1 && d.w == w+w1);
        d = a * c;
        ASSERT_TRUE(d.x == x*c && d.y == y*c && d.z == z*c && d.w == w*c);
        d = a;
        d *= c;
        ASSERT_TRUE(d.x == x*c && d.y == y*c && d.z == z*c && d.w == w*c);
        d = a / c;
        ASSERT_TRUE(d.x == x/c && d.y == y/c && d.z == z/c && d.w == w/c);
        d = a;
        d /= c;
        ASSERT_TRUE(d.x == x/c && d.y == y/c && d.z == z/c && d.w == w/c);
    }
};
