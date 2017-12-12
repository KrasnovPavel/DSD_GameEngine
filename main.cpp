#include <string>
#include <thread>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "DSD_Core/DSDBaseObject.h"
#include "DSD_Core/Mesh.h"


int main()
{
    Mesh m;
    std::vector<Triangle> tr {Triangle(Vector3(0, 0.5, 0), Vector3(0.5, -0.5, 0), Vector3(-0.5, -0.5, 0)),
                              Triangle(Vector3(-0.5, 0.5, 0), Vector3(0, -0.5, 0), Vector3(-1, -0.5, 0)),
                              Triangle(Vector3(0.5, 0.5, 0), Vector3(1, -0.5, 0), Vector3(0, -0.5, 0))};
    m.setMesh(tr);

    std::pair<float*, std::size_t> mm = m.vertexArray();

    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "DSDGameEngine", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mm.second, mm.first, GL_STATIC_DRAW);
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    const char* vertex_shader =
            "#version 400\n"
                    "in vec3 vp;"
                    "void main() {"
                    "  gl_Position = vec4(vp, 1.0);"
                    "}";
    const char* fragment_shader =
            "#version 400\n"
                    "out vec4 frag_colour;"
                    "void main() {"
                    "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
                    "}";
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, m.amountOfVerticles());
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

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
