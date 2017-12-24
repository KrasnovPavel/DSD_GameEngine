#include <string>
#include <thread>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "Core/DSDBaseObject.h"
#include "Graphics/Mesh.h"
#include "Graphics/Parsers/MeshParserSTL.h"

#define ORTHO_SCALE 50.

Mesh m;
double angle = 0;

void display(void)
{
    GLuint win_width, win_height;
    GLfloat win_aspect;

    win_width  = glutGet(GLUT_WINDOW_WIDTH);
    win_height = glutGet(GLUT_WINDOW_HEIGHT);
    win_aspect = (float)win_width/(float)win_height;

    glViewport(0, 0, win_width, win_height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-win_aspect * ORTHO_SCALE,
            win_aspect * ORTHO_SCALE,
            -ORTHO_SCALE,
            ORTHO_SCALE,
            1000., -1000.);
    angle += 0.02;
    auto tmp = m.rotation.toAxisAngle();
    glTranslated(m.position.x, m.position.y, m.position.z);
    glRotated(tmp.second * 180. * M_1_PI, tmp.first.x, tmp.first.y, tmp.first.z);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    glEnableClientState(GL_VERTEX_ARRAY);
    double* arr = m.vertexArray();
    glVertexPointer(3, GL_DOUBLE, 0, arr);
    glDrawArrays(GL_TRIANGLES, 0, m.amountOfVerticles());
    delete[] arr;

    glPopMatrix();

    glutSwapBuffers();
}

void repaint(void)
{
    m.rotation *= Quaternion(0.005, Vector3(0, 1, 0));
//    m.position -= Vector3(0, 0, 0.02);
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    MeshParserSTL mp("model.stl");
    m.setMesh(mp.parce());

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    glutCreateWindow("DSDGameEngine");
    glutDisplayFunc(display);
    glutIdleFunc(repaint);
    glEnable (GL_DEPTH_TEST);

    glutMainLoop();


    Logger::JoinThread();

    return 0;
}
