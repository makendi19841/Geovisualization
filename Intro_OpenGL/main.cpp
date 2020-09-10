#include <windows.h> 
#include <gl/gl.h> 
#include "glut.h"


void RenderScene(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 1);
	glVertex2f(0.5f, 0.0f);
	glColor3f(0, 1, 0);
	glVertex2f(0.0f, 0.5f);
	glColor3f(1, 0, 0);
	glVertex2f(-0.5f, 0.0f);
	glEnd();
	glFlush();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(-0.3f, 0.3f);
	glVertex2f(-0.8f, 0.3f);
	glVertex2f(-0.8f, 0.3f);
	glVertex2f(-0.8f, 0.8f);
	glVertex2f(-0.8f, 0.8f);
	glVertex2f(-0.3f, 0.8f);
	glVertex2f(-0.3f, 0.8f);
	glVertex2f(-0.3f, 0.3f);
	glEnd();
	glFlush();

	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.9, -0.6);
	glVertex2f(-0.6, -0.6);
	glVertex2f(-0.6, -0.6);
	glVertex2f(-0.6, -0.3);
	glVertex2f(-0.6, -0.3);
	glVertex2f(-0.9, -0.3);
	glVertex2f(-0.9, -0.3);
	glVertex2f(-0.9, -0.6);
	glEnd();
	glFlush();

	glColor3f(0.5f, 0.5f, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.3, 0.4);
	glVertex2f(0.5, 0.4);
	glVertex2f(0.5, 0.4);
	glVertex2f(0.6, 0.6);
	glVertex2f(0.6, 0.6);
	glVertex2f(0.5, 0.8);
	glVertex2f(0.5, 0.8);
	glVertex2f(0.3, 0.8);
	glVertex2f(0.3, 0.8);
	glVertex2f(0.2, 0.6);
	glVertex2f(0.2, 0.6);
	glVertex2f(0.3, 0.4);
	glEnd();
	glFlush();

	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glVertex2f(-0.1, -0.2);
	glVertex2f(0.1, -0.2);
	glVertex2f(0.3, -0.2);

	glEnd();
	glFlush();
	glColor3f(1.0f, 1.0, 1.0f);
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glVertex2f(0.0, -0.2);
	glVertex2f(0.2, -0.2);
	glVertex2f(0.4, -0.2);
	glEnd();
	glFlush();
}




void ChangeSize(GLsizei width, GLsizei height)
{
	if (height == 0)
		height = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat AspectRatio = (GLfloat)width / (GLfloat)height;
	GLfloat multiple = 100;

	if (width <= height)
		gluOrtho2D(-1.0, 1.0, -1.0 / AspectRatio, 1.0 / AspectRatio);
	else
		gluOrtho2D(-1.0 / AspectRatio, 1.0 / AspectRatio, -1.0, 1.0);

	glViewport(0, 0, width, height);
}


void main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // display mode settings   
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(720, 720);
	glutCreateWindow("First OpenGL"); //creates window with a tittle
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();

}
