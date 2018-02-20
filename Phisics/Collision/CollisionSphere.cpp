//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 20.02.18.
//

#include "CollisionSphere.h"

using namespace DSD;

INIT_REFLECTION(CollisionSphere);

void CollisionSphere::debugDraw(bool drawAABB)
{
    CollisionVolume::debugDraw(drawAABB);

    double vertices[32 * 3];
    Quaternion q;
    for (int i = 0; i < 32; ++i) {
        auto tmp = q.rotatedVector(Vector3(0, 0, m_radius));
        vertices[3 * i] = tmp.x;
        vertices[3 * i + 1] = tmp.y;
        vertices[3 * i + 2] = tmp.z;
        q *= Quaternion(M_PI / 16, 0, 0);
    }

    std::vector<Quaternion> quads = {Quaternion(), Quaternion(0, M_PI / 2, 0), Quaternion(0, 0, M_PI / 2)};
    for (auto &quad : quads) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        auto tmp = (m_rotation * quad).toAxisAngle();
        glTranslated(m_position.x, m_position.y, m_position.z);
        glRotated(tmp.second * 180. * M_1_PI, tmp.first.x, tmp.first.y, tmp.first.z);
        glPushMatrix();

        float color[4] = {1.f, 1.f, 1.f, 1.f};
        glEnableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, vertices);
        glMaterialfv(GL_FRONT, GL_SPECULAR, color);
        glDrawArrays(GL_LINE_LOOP, 0, 32);
        glPopMatrix();
    }
};
