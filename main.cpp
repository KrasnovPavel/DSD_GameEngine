#include <string>
#include <GL/gl.h>
#include <GL/glut.h>

#include "Logging/Logger.h"
#include "Graphics/Mesh.h"

Mesh m("model.stl");
Mesh m1("model1.stl");

double gridXZ[252];

void genGridXZ()
{
    for (int i = 0; i < 21; ++i)
    {
        gridXZ[i*6]   = -100;
        gridXZ[i*6+1] = 0;
        gridXZ[i*6+2] = -100 + i*10;
        gridXZ[i*6+3] = 100;
        gridXZ[i*6+4] = 0;
        gridXZ[i*6+5] = -100 + i*10;
    }

    for (int i = 0; i < 21; ++i)
    {
        gridXZ[126+i*6]   = -100 + i*10;
        gridXZ[126+i*6+1] = 0;
        gridXZ[126+i*6+2] = -100;
        gridXZ[126+i*6+3] = -100 + i*10;
        gridXZ[126+i*6+4] = 0;
        gridXZ[126+i*6+5] = 100;
    }
}

void drawGrid()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    glEnableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, gridXZ);
    glDrawArrays(GL_LINES, 0, 84);

    glPopMatrix();
}

void display(void)
{
    GLuint winWidth, winHeight;
    GLdouble winAspect;

    winWidth  = glutGet(GLUT_WINDOW_WIDTH);
    winHeight = glutGet(GLUT_WINDOW_HEIGHT);
    winAspect = (double)winWidth/(double)winHeight;

    glViewport(0, 0, winWidth, winHeight);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, winAspect, 1, 1000);
    gluLookAt(0, 70, 70, 0, 0, 0, 0, 1, 0);

    drawGrid();

    m.draw();
    m1.draw();

    glutSwapBuffers();
}

void repaint(void)
{
//    m.rotation *= Quaternion(0.005, Vector3(0, 1, 0));
    m1.rotation *= Quaternion(0.005, Vector3(0, 0, 1));
    m1.position -= Vector3(0, 0, 1);
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    m1.position = Vector3(0, 0, 100);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);

    glutCreateWindow("DSDGameEngine");
    glutDisplayFunc(display);
    glutIdleFunc(repaint);
    glEnable (GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float pos[4] = {100, 100, 100, 0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glClearColor(0.1, 0.1, 0.1, 1);

    genGridXZ();

    glutMainLoop();

    Logger::JoinThread();

    return 0;
}
