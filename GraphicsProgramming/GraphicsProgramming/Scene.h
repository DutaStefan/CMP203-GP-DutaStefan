// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "Vector3.h"


struct Vertex
{
	Vector3 position;
	Vector3 color;

	Vertex() {}
	Vertex(Vector3 pos, Vector3 cl)
	{
		position = pos;
		color = cl;
	}
};

class Scene {

public:
	Scene(Input* in);
	// Main render function
	void render();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);


protected:
	// configure opengl render pipeline
	void initialiseOpenGL();
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();

	// For access to user input.
	Input* input;

	bool wireframeMode;

	void drawTriangleStrip(std::vector<Vertex> vertices) {
		glBegin(GL_TRIANGLE_STRIP);
		for (const auto& vertex : vertices) {
			glColor3f(vertex.color.x, vertex.color.y, vertex.color.z);
			glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
		}
		glEnd();
	}

	void Scene::drawTriangleFan(std::vector<Vertex> vertices) {
		glBegin(GL_TRIANGLE_FAN); // Start drawing a triangle fan
		for (const auto& vertex : vertices) {
			glColor3f(vertex.color.x, vertex.color.y, vertex.color.z); // Set color for the vertex
			glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z); // Set position for the vertex
		}
		glEnd(); // End drawing
	}

	void Scene::drawQuad(Vertex v1, Vertex v2, Vertex v3, Vertex v4) {
		glBegin(GL_QUADS); // Start drawing a quad
		glColor3f(v1.color.x, v1.color.y, v1.color.z); // Set color for vertex 1
		glVertex3f(v1.position.x, v1.position.y, v1.position.z); // Set position for vertex 1

		glColor3f(v2.color.x, v2.color.y, v2.color.z); // Set color for vertex 2
		glVertex3f(v2.position.x, v2.position.y, v2.position.z); // Set position for vertex 2

		glColor3f(v3.color.x, v3.color.y, v3.color.z); // Set color for vertex 3
		glVertex3f(v3.position.x, v3.position.y, v3.position.z); // Set position for vertex 3

		glColor3f(v4.color.x, v4.color.y, v4.color.z); // Set color for vertex 4
		glVertex3f(v4.position.x, v4.position.y, v4.position.z); // Set position for vertex 4
		glEnd(); // End drawing
	}

	//void Scene::drawQuad(Vertex v1, Vertex v2, Vertex v3, Vertex v4) {
	//	// Draw the first triangle
	//	//drawTriangle(v1, v2, v3);

	//	// Draw the second triangle
	//	//drawTriangle(v1, v4, v3);
	//}

	void Scene::drawPolygon(const std::vector<Vertex>& vertices) {
		glBegin(GL_POLYGON); // Start drawing a polygon
		for (const auto& vertex : vertices) {
			glColor3f(vertex.color.x, vertex.color.y, vertex.color.z); // Set color for the vertex
			glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z); // Set position for the vertex
		}
		glEnd(); // End drawing
	}

	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

};



#endif