#include "SolarScene.h"

// Scene constructor, initializes OpenGL
SolarScene::SolarScene(Input* in) : wireframeMode(false), rotation(0.0f) {
	input = in;
	initialiseOpenGL();
}

void SolarScene::handleInput(float dt) {
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

void SolarScene::update(float dt)
{
	// update scene related variables.

	rotation += 90.0f * dt; // Rotate 90 degrees per second (clockwise)
	if (rotation > 360.0f) {
		rotation -= 360.0f; // Keep the angle within 0-360 degrees
	}

	handleInput(dt);
	calculateFPS();
}

void SolarScene::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Define vertices for the triangle centered at the origin
	std::vector<Vertex> triangleVertices = {
		Vertex(Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)),   // Top vertex (Red)
		Vertex(Vector3(0.951f, -0.309f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)), // Bottom right vertex (Green)
		Vertex(Vector3(-0.951f, -0.309f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)) // Bottom left vertex (Blue)
	};
	// Draw the Sun with rotation
	glPushMatrix();
	glRotatef(rotation, 0.0f, 0.0f, 1.0f); // Rotate the Sun
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for the Sun
	drawCircle(0.0f, 0.0f, 0.0f, 1.0f, 36); // Draw the Sun
	glPopMatrix();

	// Draw Planet 1 
	glPushMatrix();
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(2.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	drawCircle(0.0f, 0.0f, 0.0f, 0.5f, 16);
	glPopMatrix();

	// Draw Planet 2 
	glPushMatrix();
	glRotatef(rotation * 0.75f, 0.0f, 0.0f, 1.0f);
	glTranslatef(3.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	drawCircle(0.0f, 0.0f, 0.0f, 0.5f, 16);

	// Draw Moon 1 
	glPushMatrix();
	glRotatef(rotation * 1.5f, 0.0f, 0.0f, 1.0f);
	glTranslatef(1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.5f, 0.0f);
	drawCircle(0.0f, 0.0f, 0.0f, 0.15f, 16); // Reduced size of Moon 1
	glPopMatrix();

	// Draw Moon 2 
	glPushMatrix();
	glRotatef(rotation * 1.5f, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 1.5f, 0.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	drawCircle(0.0f, 0.0f, 0.0f, 0.15f, 16); // Reduced size of Moon 2

	// Draw Moon 2's Moon (orbits Moon 2)
	glPushMatrix();
	glRotatef(rotation * 2.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.75f, 0.0f, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	drawCircle(0.0f, 0.0f, 0.0f, 0.075f, 16); // Reduced size of Moon 2's Moon
	glPopMatrix();






	// Apply translation
	//glTranslatef(2.0f, 0.0f, 0.0f);
	//glTranslatef(-0.0f, 1.0f, 0.0f);
	//glTranslatef(-2.0f, 1.0f, 0.0f);
	//glTranslatef(0.0f, 0.0f, -2.0f);

	//Apply scaling
	//glScalef(2, 2, 2);
	//glScalef(0.5, 0.5, 0.5);
	//glScalef(2, 0.5, 2);

	// Apply rotation around the Y axis
	//if (input->isKeyDown('o')) {
	//	glRotatef(80.0f, 0.0f, 1.0f, 0.0f); // Rotate in the positive direction
	//}
	//if (input->isKeyDown('p')) {
	//	glRotatef(-80.0f, 0.0f, 1.0f, 0.0f); // Rotate in the negative direction
	//}

	//glRotatef(rotation, 0.0f, 1.0f, 0.0f);
	//glRotatef(rotation, 0.0f, 0.0f, 1.0f);
	//glScalef(0.5, 0.5, 0.5);

	//drawTriangle(triangleVertices); // Draw the triangle

	renderTextOutput();
	glutSwapBuffers();
}

void SolarScene::initialiseOpenGL()
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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void SolarScene::resize(int w, int h)
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

void SolarScene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame * 1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}
	
void SolarScene::renderTextOutput()
{
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

void SolarScene::displayText(float x, float y, float r, float g, float b, char* string) {
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

