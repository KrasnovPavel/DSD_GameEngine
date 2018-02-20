//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 20.02.18.
//

#include "CollisionVolume.h"

using namespace DSD;

INIT_REFLECTION(CollisionVolume);

double *CollisionVolume::generateVertices(const Vector3 &min, const Vector3 &max)
{
    auto vertices = new double[48];
    vertices[0] = min.x;
    vertices[1] = min.y;
    vertices[2] = min.z;

    vertices[3] = max.x;
    vertices[4] = min.y;
    vertices[5] = min.z;

    vertices[6] = max.x;
    vertices[7] = max.y;
    vertices[8] = min.z;

    vertices[9] = min.x;
    vertices[10] = max.y;
    vertices[11] = min.z;

    vertices[12] = min.x;
    vertices[13] = min.y;
    vertices[14] = max.z;

    vertices[15] = max.x;
    vertices[16] = min.y;
    vertices[17] = max.z;

    vertices[18] = max.x;
    vertices[19] = max.y;
    vertices[20] = max.z;

    vertices[21] = min.x;
    vertices[22] = max.y;
    vertices[23] = max.z;

    vertices[24] = min.x;
    vertices[25] = min.y;
    vertices[26] = min.z;

    vertices[27] = min.x;
    vertices[28] = min.y;
    vertices[29] = max.z;

    vertices[30] = max.x;
    vertices[31] = min.y;
    vertices[32] = min.z;

    vertices[33] = max.x;
    vertices[34] = min.y;
    vertices[35] = max.z;

    vertices[36] = min.x;
    vertices[37] = max.y;
    vertices[38] = min.z;

    vertices[39] = min.x;
    vertices[40] = max.y;
    vertices[41] = max.z;

    vertices[42] = max.x;
    vertices[43] = max.y;
    vertices[44] = min.z;

    vertices[45] = max.x;
    vertices[46] = max.y;
    vertices[47] = max.z;

    return vertices;
}

void CollisionVolume::debugDraw(bool drawAABB)
{
    if (drawAABB) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();

        //Generating vertices
        double *vertices = generateVertices(getAABB().min, getAABB().max);

        float color[4] = {0.f, 0.f, 1.f, 1.f};

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
}

void CollisionVolume::calculateAABB()
{
    m_aabb = AABB(position(), position());
};
