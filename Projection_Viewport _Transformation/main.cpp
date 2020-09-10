/*Task1*/ 
/*Task2*/
/*Task3*/

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

//
///*Task2*/
//#include <windows.h> 
//#include <gl/gl.h> 
//#include "glut.h"
//
//
//void GreenRectangle()
//{
//	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(0.0f, 1.0f, 0.0f);
//	glRectf(-50.0f, 50.0f, 50.0f, -50.0f);
//	glEnd;
//	glFlush();
//}
//
///* void ChangeSize(GLsizei width, GLsizei height)
//{
//if (height == 0)
//height = 1;
//
//glMatrixMode(GL_PROJECTION);
//glLoadIdentity();
//GLfloat AspectRatio = (GLfloat)width / (GLfloat)height;
//
//if (width <= height)
//gluOrtho2D(-1.0, 1.0, -1.0 / AspectRatio, 1.0 / AspectRatio);
//else
//gluOrtho2D(-1.0 / AspectRatio, 1.0 / AspectRatio, -1.0, 1.0);
//
//glViewport(0, 0, width / 2, height / 2);
//} */
//
//void ChangeSize(GLsizei width, GLsizei height)
//{
//	if (height == 0)
//		height = 1;
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	GLfloat AspectRatio = (GLfloat)width / (GLfloat)height;
//	GLfloat mutiple = 100;
//
//	if (width <= height)
//		gluOrtho2D(-1.0*mutiple, 1.0*mutiple, -1.0 / AspectRatio*mutiple, 1.0 / AspectRatio*mutiple);
//	else
//		gluOrtho2D(-1.0 / AspectRatio*mutiple, 1.0 / AspectRatio*mutiple, -1.0*mutiple, 1.0*mutiple);
//
//	glViewport(0, 0, width / 2, height / 2);
//}
//
//
//
//void main(void)
//{
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // display mode settings   
//	glutInitWindowPosition(200, 100);
//	glutInitWindowSize(720, 720);
//	glutCreateWindow("First OpenGL"); //creates window with a tittle
//	glutDisplayFunc(GreenRectangle);
//	glutReshapeFunc(ChangeSize);
//	glutMainLoop();
//
//}
//
///*Task3*/
//#include <windows.h> 
//#include <gl/gl.h> 
//#include "glut.h"
//
//
//void RenderScene(void) {
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glColor3f(0.0f, 1.0f, 0.0f);
//
//	glPushMatrix();
//
//	// Rotate triangle from the task 1 given the scenario in task 3
//	glPushMatrix();                     // drawing the rotated triangle on the z-axis: 1.0f
//	glRotatef(180, 0.0f, 0.0f, 1.0f);   // drawing the rotated triangle
//
//
//	glBegin(GL_TRIANGLES);
//	glColor3f(0, 0, 1);
//	glVertex2f(0.5f, 0.0f);
//	glColor3f(0, 1, 0);
//	glVertex2f(0.0f, 0.5f);
//	glColor3f(1, 0, 0);
//	glVertex2f(-0.5f, 0.0f);
//	glEnd();
//
//	glPopMatrix();                       // drawing the rotated triangle
//
//										 //////////////////////////////////////////////////////////////////////////
//	glPushMatrix();
//	glTranslatef(1.16f, 0.0f, 0.0f);  // tanslate the red line square
//
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glBegin(GL_LINES);
//	glVertex2f(-0.3f, 0.3f);
//	glVertex2f(-0.8f, 0.3f);
//	glVertex2f(-0.8f, 0.3f);
//	glVertex2f(-0.8f, 0.8f);
//	glVertex2f(-0.8f, 0.8f);
//	glVertex2f(-0.3f, 0.8f);
//	glVertex2f(-0.3f, 0.8f);
//	glVertex2f(-0.3f, 0.3f);
//	glEnd();
//
//	glPopMatrix();
//
//
//	////////////////////////////////////////////////////////////////////////////
//	glPushMatrix();                      // Translated yellow square from the task 1 given the scenario in task 3
//	glTranslatef(1.20f, -0.20f, 0.0f);  // drawing the x-translated square
//
//	glColor3f(1.0f, 1.0f, 0.0f);
//	glBegin(GL_QUADS);
//	glVertex2f(-0.9, -0.6);
//	glVertex2f(-0.6, -0.6);
//	glVertex2f(-0.6, -0.6);
//	glVertex2f(-0.6, -0.3);
//	glVertex2f(-0.6, -0.3);
//	glVertex2f(-0.9, -0.3);
//	glVertex2f(-0.9, -0.3);
//	glVertex2f(-0.9, -0.6);
//	glEnd();
//	glPopMatrix();                      // drawing the x-translated square
//
//
//										////////////////////////////////////////////////////////////////////////////
//	glPushMatrix();                      // Translate polygon from x and y axis
//	glTranslatef(0.21f, -0.05f, 0.0f);
//
//	glColor3f(0.5f, 0.5f, 1.0);
//	glBegin(GL_POLYGON);
//	glVertex2f(0.3, 0.4);
//	glVertex2f(0.5, 0.4);
//	glVertex2f(0.5, 0.4);
//	glVertex2f(0.6, 0.6);
//	glVertex2f(0.6, 0.6);
//	glVertex2f(0.5, 0.8);
//	glVertex2f(0.5, 0.8);
//	glVertex2f(0.3, 0.8);
//	glVertex2f(0.3, 0.8);
//	glVertex2f(0.2, 0.6);
//	glVertex2f(0.2, 0.6);
//	glVertex2f(0.3, 0.4);
//	glEnd();
//	glPopMatrix();
//
//	////////////////////////////////////////////////////////////////////////////
//	glPushMatrix();
//	glPushMatrix();
//	glTranslatef(-1.1f, -0.18f, 0.0f);
//	glRotatef(90, 0.0f, 0.0f, 1.0f);   // drawing the rotated triangle
//
//	glColor3f(1.0f, 1.0f, 1.0f);
//	glPointSize(4.0f);
//	glBegin(GL_POINTS);
//	glVertex2f(-0.1, -0.2);
//	glVertex2f(0.1, -0.2);
//	glVertex2f(0.3, -0.2);
//
//	glColor3f(1.0f, 1.0, 1.0f);
//	glPointSize(2.0f);
//	glBegin(GL_POINTS);
//	glVertex2f(0.0, -0.2);
//	glVertex2f(0.2, -0.2);
//	glVertex2f(0.4, -0.2);
//	glEnd();
//	glPopMatrix();
//	glPopMatrix();
//	glFlush();
//}
//
//
//
//
//
//
//void main(void)
//{
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // display mode settings   
//	glutInitWindowPosition(200, 100);
//	glutInitWindowSize(720, 720);
//	glutCreateWindow("First OpenGL"); //creates window with a tittle
//	glutDisplayFunc(RenderScene);
//	glutMainLoop();
//
//}
