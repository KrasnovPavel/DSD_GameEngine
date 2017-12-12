#include <string>
#include <thread>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "DSD_Core/DSDBaseObject.h"
#include "DSD_Core/Mesh.h"

#define ORTHO_SCALE 2.

std::pair<double*, std::size_t> mm;
Mesh m;

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
            -1., 1.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, mm.first);
    glDrawArrays(GL_TRIANGLES, 0, m.amountOfVerticles());

    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char* argv[])
{
    std::vector<Triangle> tr {Triangle(Vector3(0, 0.5, 0),    Vector3(0.5, -0.5, 0), Vector3(-0.5, -0.5, 0)),
                              Triangle(Vector3(-0.5, 0.5, 0), Vector3(0, -0.5, 0),   Vector3(-1, -0.5, 0)),
                              Triangle(Vector3(0.5, 0.5, 0),  Vector3(1, -0.5, 0),   Vector3(0, -0.5, 0))};
    m.setMesh(tr);

    mm.first = m.vertexArray().first;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    glutCreateWindow("DSDGameEngine");
    glutDisplayFunc(display);

    glutMainLoop();

//    SerializationController sc;
//
//    FileController::writeToFile("test.sav", sc.serialize());
//
//    ReadByteArray rarr = FileController::readFromFile("test.sav");
//    sc.deserialize(rarr);
//
//    std::vector<DSDBaseObject*> newObjects = sc.newObjects();

    Logger::JoinThread();

    return 0;
}
