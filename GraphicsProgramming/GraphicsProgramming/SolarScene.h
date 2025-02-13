#ifndef _SOLARSCENE_H
#define _SOLARSCENE_H

#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
#include <vector>
#include "Vector3.h"

struct Vertex {
    Vector3 position;
    Vector3 color;

    Vertex() {}
    Vertex(Vector3 pos, Vector3 cl) : position(pos), color(cl) {}
};

class SolarScene {
public:
    SolarScene(Input* in);
    void render();
    void handleInput(float dt);
    void update(float dt);
    void resize(int w, int h);

protected:
    void initialiseOpenGL();
    void displayText(float x, float y, float r, float g, float b, char* string);
    void renderTextOutput();
    void calculateFPS();

    Input* input;
    bool wireframeMode;
    float rotation;

    void SolarScene::drawTriangle(std::vector<Vertex> vertices) {
        glBegin(GL_TRIANGLE_FAN); // Start drawing a triangle fan
        for (const auto& vertex : vertices) {
            glColor3f(vertex.color.x, vertex.color.y, vertex.color.z); // Set color for the vertex
            glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z); // Set position for the vertex
        }
        glEnd(); // End drawing
    }

    void SolarScene::drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides)
    {
        int numberOfVertices = numberOfSides + 2;

        GLfloat twicePi = 2.0f * 3.14159256f;

        GLfloat* circleVerticesX = new GLfloat[numberOfVertices];
        GLfloat* circleVerticesY = new GLfloat[numberOfVertices];
        GLfloat* circleVerticesZ = new GLfloat[numberOfVertices];

        circleVerticesX[0] = x;
        circleVerticesY[0] = y;
        circleVerticesZ[0] = z;

        for (int i = 1; i < numberOfVertices; i++)
        {
            circleVerticesX[i] = x + (radius * cos(i * twicePi / numberOfSides));
            circleVerticesY[i] = y + (radius * sin(i * twicePi / numberOfSides));
            circleVerticesZ[i] = z;
        }

        GLfloat *allCircleVertices = new GLfloat [(numberOfVertices) * 3];

        for (int i = 0; i < numberOfVertices; i++)
        {
            allCircleVertices[i * 3] = circleVerticesX[i];
            allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
            allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
        }

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
        glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    int width, height;
    float fov, nearPlane, farPlane;
    int frame = 0, time, timebase = 0;
    char fps[40];
    char mouseText[40];
};

#endif