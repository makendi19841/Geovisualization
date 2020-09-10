
#include <windows.h>  
#include<iostream>
#include <gl/gl.h> 
#include "glut.h"
#include "Contour.h"
#include "Point.h"
#include"Poly.h"

void RenderScene();
void ChangeSize(GLsizei width, GLsizei height);

Poly arrow;
Poly CreateArrow();
void DrawArrow();

void CALLBACK beginCallback(GLenum which);
void CALLBACK endCallback();
void CALLBACK vertexCallback(void * vertex_data);
void CALLBACK TessEdgeFlagCallback(GLboolean flag);

void KeysSpecial(int key, int x, int y);
void keys(unsigned char key, int x, int y);

vector<Point>  tessellate(Poly* p);
vector<Point>tess_pts;

void DrawTesselated();

float pos_x = 0.0f;
float pos_y = 0.0f;
static float angle = 0.0f;

int model = 2;

//**************************************************************************************
void main()
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);


	glutInitWindowPosition(200, 100);
	glutInitWindowSize(720, 720);
	glutCreateWindow("Tesselation");

	arrow = CreateArrow();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	tess_pts = tessellate(&arrow);

	glutKeyboardFunc(keys);
	glutSpecialFunc(KeysSpecial);

	glutMainLoop(); //starts GLUT library
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RENDERING
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ChangeSize(GLsizei width, GLsizei height)
{
	if (height == 0)
		height = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat AspectRatio;
	AspectRatio = (GLfloat)width / (GLfloat)height;

	GLfloat multiple = 5;

	if (width <= height)
		gluOrtho2D(-1.0*multiple, 1.0*multiple, -1.0 / AspectRatio *multiple, 1.0 / AspectRatio*multiple);
	else
		gluOrtho2D(-1.0*AspectRatio*multiple, 1.0*AspectRatio*multiple, -1.0*multiple, 1.0*multiple);

	glViewport(0, 0, width, height);

}

void RenderScene()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);


	glPushMatrix();                        /* Start: glPushMatrix Without this command it it difficult to control transformation*/
	glTranslatef(pos_x, pos_y, 0.0f);      /* This line is to make translation dependent on the variables*/
	glRotatef(angle, 0.0f, 0.0f, 1.0f);    /* for rotation*/

	switch (model)
	{
	case 1:
		DrawArrow();
		break;
	case 2:
		DrawTesselated();
		break;

	}

	glPopMatrix();                           /* End: glPushMatrix Without this command it it difficult to control transformation*/
	glFlush();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DRAWING
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Poly CreateArrow()
{
	Poly p;

	Point p1(-1, 3);
	Point p2(0, 0);
	Point p3(1, 3);
	Point p4(0, 2);

	p.outer_contour.points.push_back(p1);
	p.outer_contour.points.push_back(p2);
	p.outer_contour.points.push_back(p3);
	p.outer_contour.points.push_back(p4);
	p.outer_contour.points.push_back(p1);

	return p;
}


void DrawArrow()
{

	//glPushMatrix();                        /* Start: glPushMatrix Without this command it it difficult to control transformation*/
	//glTranslatef(pos_x, pos_y, 0.0f);      /* This line is to make translation dependent on the variables*/
	//glRotatef(angle, 0.0f, 0.0f, 1.0f);    /* for rotation*/

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);

	for (int i = 0; i < arrow.outer_contour.points.size(); i++)
	{
		glVertex2f(arrow.outer_contour.points[i].x, arrow.outer_contour.points[i].y);
	}
	glEnd();
	glPopMatrix();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < arrow.outer_contour.points.size(); i++)
	{
		glVertex2f(arrow.outer_contour.points[i].x, arrow.outer_contour.points[i].y);
	}
	glEnd();

	//glPopMatrix();                           /* End: glPushMatrix Without this command it it difficult to control transformation*/
}

void DrawTesselated()
{
	glColor3f(0.8, 0, 0);
	glBegin(GL_TRIANGLES);

	//glPushMatrix();                        /* Start: glPushMatrix Without this command it it difficult to control transformation*/
	//glTranslatef(pos_x, pos_y, 0.0f);      /* This line is to make translation dependent on the variables*/
	//glRotatef(angle, 0.0f, 0.0f, 1.0f);    /* for rotation*/

	for (int i = 0; i < tess_pts.size(); i++)
	{
		glVertex2f(tess_pts[i].x, tess_pts[i].y);
	}
	glEnd();

	//glPopMatrix();                           /* End: glPushMatrix Without this command it it difficult to control transformation*/

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TESSELATION  FUNCTION : Function tessalate that takes a pointer to a polygon as an argument and returns a vector of points
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Point>  tessellate(Poly* p)
{

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// DATA CONVERSION:  convert polygon into a double array
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	tess_pts.clear();                                          // Clear tess_points container

															   // Start conversion:  convert polygon into double array format


	int pts_no = p->outer_contour.points.size();        	   // Define the numbers of a 2-D contour points: e.g 5points here
	double * pPts = new double[3 * pts_no];
	double * pPoints = pPts;

	for (int i = 0; i < pts_no; i++)
	{
		*pPoints++ = p->outer_contour.points[i].x;
		*pPoints++ = p->outer_contour.points[i].y;
		*pPoints++ = 0;
	}

	pPoints = pPts;                                              // End data conversion:  convert polygon into double array format


																 // Creates a new tessellation object and returns a pointer to it
	GLUtesselator* tess = gluNewTess();

	// Define tessellation callbacks
	gluTessCallback(tess, GLU_TESS_BEGIN, (void(CALLBACK *) ()) &beginCallback);
	gluTessCallback(tess, GLU_TESS_END, (void(CALLBACK *) ()) &endCallback);
	gluTessCallback(tess, GLU_TESS_VERTEX, (void(CALLBACK *) ()) &vertexCallback);
	gluTessCallback(tess, GLU_TESS_EDGE_FLAG, (void(CALLBACK *) ()) &TessEdgeFlagCallback);


	//Start tesselation
	gluTessBeginPolygon(tess, 0); //start tesselation for polygons
	cout << "Start tesselation: " << endl << endl;

	// Outer contour
	gluTessBeginContour(tess);   //start tesselation for contours 

	for (int i = 0; i < p->outer_contour.points.size(); i++, pPoints += 3)   // THis is the part where tess function creates: triangle, triangle strips or triangle fans from the outer_contour
	{
		cout << "input vertex: " << pPoints[0] << " " << pPoints[1] << endl;
		gluTessVertex(tess, pPoints, pPoints);
	}
	gluTessEndContour(tess);    //end tesselation for contours 

								/*For a polygon with hole */
								/*Include anoother for loop for inner contour*/                         // THis is the part where tess function creates: triangle, triangle strips or triangle fans from the inner_contour

	cout << endl;

	gluTessEndPolygon(tess);    //end tesselation for polygons

	cout << endl << "End tesselation. " << endl;

	// Delete tessellator after processing
	gluDeleteTess(tess);

	return tess_pts;
}


void CALLBACK beginCallback(GLenum which)
{
}

void CALLBACK endCallback(void)
{
}

void CALLBACK vertexCallback(void * vertex_data)
{
	double * xyz = (double *)vertex_data;
	tess_pts.push_back(Point(xyz[0], xyz[1]));
	cout << "output vertex: " << xyz[0] << " " << xyz[1] << endl;
}

void CALLBACK TessEdgeFlagCallback(GLboolean flag)
{
}


void keys(unsigned char key, int x, int y)
{
	if (key == 'z') model = 1;
	if (key == 'x') model = 2;

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
