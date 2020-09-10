/*Task1*/
/*Task2*/
/*Task3*/ //TODO
		  /*Task4*/ //TODO

					//#include <windows.h> 
					//#include <gl/gl.h> 
					//#include "glut.h"
					//
					//
					//void RenderScene(void);
					//void ChangeSize(GLsizei width, GLsizei height);
					//void DrawSquares();
					//void DrawPolygons();
					//void DrawPoints();
					//void DrawTriangles();
					//int model = 3;                                     //1- squares, 2-polygons, 3-points
					//
					//void keys(unsigned char key, int x, int y);
					//
					//
					//
					//void main(void)
					//{
					//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // display mode settings   
					//	glutInitWindowPosition(200, 100);
					//	glutInitWindowSize(720, 720);
					//	glutCreateWindow("Lab 4__Task1"); //creates window with a tittle
					//	glutDisplayFunc(RenderScene);     // Call back function defined in opengl
					//	glutKeyboardFunc(keys);
					//	glutReshapeFunc(ChangeSize);
					//	glutMainLoop();
					//
					//}
					//
					//
					//void ChangeSize(GLsizei width, GLsizei height)
					//{
					//	if (height == 0)
					//		height = 1;
					//
					//	glMatrixMode(GL_PROJECTION);
					//	glLoadIdentity();
					//	GLfloat AspectRatio = (GLfloat)width / (GLfloat)height;
					//	GLfloat multiple = 100;
					//
					//	if (width <= height)
					//		gluOrtho2D(-1.0, 1.0, -1.0 / AspectRatio, 1.0 / AspectRatio);
					//	else
					//		gluOrtho2D(-1.0 / AspectRatio, 1.0 / AspectRatio, -1.0, 1.0);
					//
					//	glViewport(0, 0, width, height);
					//}
					//
					//void DrawSquares() {
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
					//	glFlush();
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
					//	glFlush();
					//}
					//
					//void DrawPolygons() {
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
					//	glFlush();
					//}
					//
					//void DrawPoints() { /*draw points*/
					//
					//	glColor3f(1.0f, 1.0f, 1.0f);
					//	glPointSize(4.0f);
					//	glBegin(GL_POINTS);
					//	glVertex2f(-0.1, -0.2);
					//	glVertex2f(0.1, -0.2);
					//	glVertex2f(0.3, -0.2);
					//
					//	glEnd();
					//	glFlush();
					//
					//	glColor3f(1.0f, 1.0, 1.0f);
					//	glPointSize(2.0f);
					//	glBegin(GL_POINTS);
					//	glVertex2f(0.0, -0.2);
					//	glVertex2f(0.2, -0.2);
					//	glVertex2f(0.4, -0.2);
					//	glEnd();
					//	glFlush();
					//}
					//
					//void DrawTriangles() {
					//
					//	glBegin(GL_TRIANGLES);
					//	glColor3f(0, 0, 1);
					//	glVertex2f(0.5f, 0.0f);
					//	glColor3f(0, 1, 0);
					//	glVertex2f(0.0f, 0.5f);
					//	glColor3f(1, 0, 0);
					//	glVertex2f(-0.5f, 0.0f);
					//	glEnd();
					//	glFlush();
					//}
					//
					//void RenderScene() {
					//	
					//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
					//	glClear(GL_COLOR_BUFFER_BIT);
					//	glColor3f(0.0f, 1.0f, 0.0f);
					//
					//	//if (model == 1) DrawSquares();    /* simple way to interact with keyboard*/
					//	//if (model == 2) DrawPolygons();
					//	//if (model == 3) DrawPoints();
					//	//if (model == 4) DrawTriangles();
					//
					// // Keyboard interaction               /* professional way to interact with keyboard*/
					//	switch (model)
					//	{
					//	case 1:
					//		DrawSquares();
					//		break;
					//	case 2:
					//		DrawPolygons();
					//		break;
					//	case 3:
					//		DrawPoints();
					//		break;
					//	case 4:
					//		DrawTriangles();
					//		break;
					//
					//	}
					//	glFlush();                   // passes draw order for execution
					//}
					//
					//
					//
					//void keys(unsigned char key, int x, int y)
					//{
					//	if (key == 'z') model = 1;
					//	if (key == 'x') model = 2;
					//	if (key == 'c') model = 3;
					//	if (key == 'p') model = 4;
					//
					//	RenderScene();                //re-draw the scene.
					//}



					/*Task2*/
#include <windows.h> 
#include <gl/gl.h> 
#include "glut.h"

void RenderScene(void);
void ChangeSize(GLsizei width, GLsizei height);

void DrawSquares();
void DrawPolygons();
void DrawPoints();

void keys(unsigned char key, int x, int y);
void KeysSpecial(int key, int x, int y);


float pos_x = 0.0f;
float pos_y = 0.0f;
static float angle = 0.0f;


int model = 2;

void main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // display mode settings   
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Lab 4"); //creates window with a certain title
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(keys);
	glutSpecialFunc(KeysSpecial);
	glutMainLoop();

}

void RenderScene(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	switch (model)
	{
	case 1:
		DrawSquares();
		break;
	case 2:
		DrawPolygons();
		break;
	case 3:
		DrawPoints();
		break;
	}
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

void DrawSquares()
{

	glPushMatrix();                      /* Start: glPushMatrix Without this command it it difficult to control transformation*/
	glTranslatef(pos_x, pos_y, 0.0f);    /*This line is to make translation dependent on the variables*/
	glRotatef(angle, 0.0f, 0.0f, 1.0f);   /* rotation*/

	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.5f, 1.0f);
	glVertex2f(-0.2f, 0.2f);
	glVertex2f(0.2f, 0.2f);
	glVertex2f(0.2f, -0.2f);
	glVertex2f(-0.2f, -0.2f);
	glEnd();



	glPopMatrix();                    /* End: glPushMatrix Without this command it it difficult to control transformation*/
}

void DrawPolygons()
{
	glPushMatrix();                      /* Start: glPushMatrix Without this command it it difficult to control transformation*/
	glTranslatef(pos_x, pos_y, 0.0);    /*This line is to make translation dependent on the variables*/
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.5f, 1.0f);
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

	glPopMatrix();                    /* End: glPushMatrix Without this command it it difficult to control transformation*/
}

void DrawPoints()
{
	glPushMatrix();                      /* Start: glPushMatrix Without this command it it difficult to control transformation*/
	glTranslatef(pos_x, pos_y, 0.0);    /*This line is to make translation dependent on the variables*/
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	glColor3f(1.0f, 0.5f, 0.5f);
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glVertex2f(-0.1, -0.2);
	glVertex2f(0.1, -0.2);
	glVertex2f(0.3, -0.2);
	glEnd();

	glColor3f(1.0f, 0.5f, 0.5f);
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glVertex2f(0.0, -0.2);
	glVertex2f(0.2, -0.2);
	glVertex2f(0.4, -0.2);
	glEnd();

	glPopMatrix();                    /* End: glPushMatrix Without this command it it difficult to control transformation*/
}


void keys(unsigned char key, int x, int y)
{
	if (key == 'z') model = 1;
	if (key == 'x') model = 2;
	if (key == 'c') model = 3;

	RenderScene();   //re-draw the scene
}

void KeysSpecial(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)    pos_y += 0.05f;     /*GLUT_KEY_UP: Keyboard callbacks in openGL*/
	if (key == GLUT_KEY_DOWN)  pos_y -= 0.05f;
	if (key == GLUT_KEY_LEFT)  pos_x -= 0.05f;
	if (key == GLUT_KEY_RIGHT) pos_x += 0.05f;

	if (key == GLUT_KEY_F1)    angle -= 10.0f;
	if (key == GLUT_KEY_F2)    angle += 10.0f;

	RenderScene();
}
