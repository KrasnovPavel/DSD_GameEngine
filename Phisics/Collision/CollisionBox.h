//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 12.02.18.
//

#ifndef DSD_GAMEENGINE_COLLISIONBOX_H
#define DSD_GAMEENGINE_COLLISIONBOX_H

#include <algorithm>

#include "CollisionVolume.h"

namespace DSD
{
    class CollisionBox : public CollisionVolume
    {
    public:
        CollisionBox(const double &x, const double &y, const double &z, const Vector3 &position,
                     const Quaternion &rotation)
                : CollisionVolume(position, rotation), m_x(x), m_y(y), m_z(z)
        {}

        void setX(const double &newX)
        {
            m_x = newX;
            isAABBChanged = true;
        }

        void setY(const double &newY)
        {
            m_y = newY;
            isAABBChanged = true;
        }

        void setZ(const double &newZ)
        {
            m_z = newZ;
            isAABBChanged = true;
        }

        inline const double &x() const
        {
            return m_x;
        }

        inline const double &y() const
        {
            return m_y;
        }

        inline const double &z() const
        {
            return m_z;
        }

        void debugDraw(bool drawAABB) override
        {
            CollisionVolume::debugDraw(drawAABB);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            auto tmp = m_rotation.toAxisAngle();
            glTranslated(m_position.x, m_position.y, m_position.z);
            glRotated(tmp.second * 180. * M_1_PI, tmp.first.x, tmp.first.y, tmp.first.z);
            glPushMatrix();

            Vector3 min(m_x * 0.5, m_y * 0.5, m_z * 0.5);
            Vector3 max(-m_x * 0.5, -m_y * 0.5, -m_z * 0.5);

            double *vertices = generateVertices(min, max);

            float color[4] = {1.f, 1.f, 1.f, 1.f};

            glEnableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);
            glVertexPointer(3, GL_DOUBLE, 0, vertices);
            glMaterialfv(GL_FRONT, GL_SPECULAR, color);
            glDrawArrays(GL_LINE_LOOP, 0, 4);
            glDrawArrays(GL_LINE_LOOP, 4, 4);
            glDrawArrays(GL_LINES, 8, 8);

            glPopMatrix();
            delete[] vertices;
        }

        CollisionType type() const override
        {
            return CollisionType::BOX;
        }

    protected:
        void calculateAABB() override
        {
            Vector3 p1(m_x * 0.5, m_y * 0.5, m_z * 0.5);
            Vector3 p2(m_x * 0.5, m_y * 0.5, -m_z * 0.5);
            Vector3 p3(m_x * 0.5, -m_y * 0.5, m_z * 0.5);
            Vector3 p4(m_x * 0.5, -m_y * 0.5, -m_z * 0.5);
            Vector3 p5(-m_x * 0.5, m_y * 0.5, m_z * 0.5);
            Vector3 p6(-m_x * 0.5, m_y * 0.5, -m_z * 0.5);
            Vector3 p7(-m_x * 0.5, -m_y * 0.5, m_z * 0.5);
            Vector3 p8(-m_x * 0.5, -m_y * 0.5, -m_z * 0.5);

            m_rotation.rotateVector(p1);
            m_rotation.rotateVector(p2);
            m_rotation.rotateVector(p3);
            m_rotation.rotateVector(p4);
            m_rotation.rotateVector(p5);
            m_rotation.rotateVector(p6);
            m_rotation.rotateVector(p7);
            m_rotation.rotateVector(p8);

            auto mmx = std::minmax({p1.x, p2.x, p3.x, p4.x, p5.x, p6.x, p7.x, p8.x});
            auto mmy = std::minmax({p1.y, p2.y, p3.y, p4.y, p5.y, p6.y, p7.y, p8.y});
            auto mmz = std::minmax({p1.z, p2.z, p3.z, p4.z, p5.z, p6.z, p7.z, p8.z});

            m_aabb = AABB(Vector3(mmx.first, mmy.first, mmz.first) + position(),
                          Vector3(mmx.second, mmy.second, mmz.second) + position());
        }

        double m_x = 0, m_y = 0, m_z = 0;
    };
}

#endif //DSD_GAMEENGINE_COLLISIONBOX_H
