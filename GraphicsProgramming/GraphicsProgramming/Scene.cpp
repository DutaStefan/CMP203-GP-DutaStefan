#include "Scene.h"

// Scene constructor, initializes OpenGL
Scene::Scene(Input* in) : wireframeMode(false) { // Initialize wireframeMode to false
	input = in;
	initialiseOpenGL();
}

void Scene::handleInput(float dt) {
	// Check for 'r' key press
	if (input->isKeyDown('r')) {
		wireframeMode = !wireframeMode; // Toggle wireframe mode
		if (wireframeMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Enable wireframe mode
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Disable wireframe mode
		}
	}
}

void Scene::update(float dt)
{
	// update scene related variables.
	handleInput(dt);
	calculateFPS();
}

void Scene::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Define vertices for the triangle strip
	std::vector<Vertex> pentagonVertices = {
		Vertex(Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)),   // Top vertex (Red)
		Vertex(Vector3(0.951f, 0.309f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)), // Top right vertex (Green)
		Vertex(Vector3(0.588f, -0.809f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)), // Bottom right vertex (Blue)
		Vertex(Vector3(-0.588f, -0.809f, 0.0f), Vector3(1.0f, 1.0f, 0.0f)), // Bottom left vertex (Yellow)
		Vertex(Vector3(-0.951f, 0.309f, 0.0f), Vector3(1.0f, 0.0f, 1.0f))  // Top left vertex (Magenta)
	};


	// Render the triangle strip
	//drawTriangleStrip(stripVertices);
	//drawTriangleFan(fanVertices);
	drawPolygon(pentagonVertices);

	renderTextOutput();
	glutSwapBuffers();
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blending function
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Scene::resize(int w, int h)
{
	width = w;
	height = h;
	if (h == 0) h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(fov, ratio, nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}

void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame * 1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

void Scene::renderTextOutput()
{
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	int j = strlen(string);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	glColor3f(1.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width / (float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}

