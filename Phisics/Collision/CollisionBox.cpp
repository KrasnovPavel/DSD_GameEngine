//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 20.02.18.
//

#include "CollisionBox.h"

using namespace DSD;

INIT_REFLECTION(CollisionBox);

void CollisionBox::debugDraw(bool drawAABB)
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

void CollisionBox::calculateAABB()
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
};
