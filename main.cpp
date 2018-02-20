#include <GL/gl.h>
#include <GL/glut.h>

#include <vector>

#include "Logging/Logger.h"
#include "Phisics/Collision/CollisionChecker.h"
#include "Phisics/Collision/CollisionSphere.h"
#include "Phisics/Collision/CollisionBox.h"

std::vector<CollisionVolume*> objects;

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
    float material[] = {1,1,1,1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material);
    glVertexPointer(3, GL_DOUBLE, 0, gridXZ);
    glDrawArrays(GL_LINES, 0, 84);

    glPopMatrix();
    float material1[] = {0,0,0,0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material1);
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
//    glOrtho(-100,100,-100,100,-100,100);
    gluLookAt(0, 70, 70, 0, 0, 0, 0, 1, 0);

    drawGrid();

    for (auto obj : objects)
    {
        obj->debugDraw(true);
    }

    glutSwapBuffers();
}

void phisicsStep()
{
    objects.at(0)->moveOn(Vector3(0.05, 0, 0));
    objects.at(1)->moveOn(Vector3(-0.05, 0, 0));
    auto manifolds = CollisionChecker::checkAll(objects);
    if (!manifolds->empty())
    {
        Logger::Log(manifolds->at(0)->first->position().toString() +
                    manifolds->at(0)->second->position().toString());
    }
    delete manifolds;
}

void repaint(void)
{
    phisicsStep();
    glutPostRedisplay();
}

void initLight()
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightAmbient[]  = {0.0, 0.0, 0.0, 1.0};
    GLfloat lightDiffuse[]  = {0.7, 0.7, 0.7, 1.0};
    GLfloat lightSpecular[] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    float pos[4] = {100, 100, 100, 0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glClearColor(0.1, 0.1, 0.1, 1);
}

void initScene()
{
    genGridXZ();
    objects.push_back(new CollisionSphere(Vector3(-20,0,0), 10));
    objects.push_back(new CollisionSphere(Vector3(20,0,0), 10));
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);

    glutCreateWindow("DSDGameEngine");
    glutDisplayFunc(display);
    glutIdleFunc(repaint);

    glEnable (GL_DEPTH_TEST);

    initLight();
    initScene();

    glutMainLoop();

    Logger::JoinThread();

    return 0;
}
