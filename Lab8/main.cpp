#include <windows.h> 
#include<iostream>
#include <gl/gl.h> 
#include "glut.h"
#include "Contour.h"
#include "Point.h"
#include"Poly.h"

void RenderScene();
void keys(unsigned char key, int x, int y);
void KeysSpecial(int key, int x, int y);
void ChangeSize(GLsizei width, GLsizei height);

Poly p;
Poly plane;
Poly CreatePlane();

void DrawPlane();
void DrawTesselated();

void CALLBACK beginCallback(GLenum which);
void CALLBACK endCallback();
void CALLBACK vertexCallback(void * vertex_data);
void CALLBACK TessEdgeFlagCallback(GLboolean flag);

vector<Point>  tessellate(Poly* p);
vector<Point>tess_pts;


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
	glutCreateWindow("Tesselation_Flying_Airplane");

	plane = CreatePlane();
	tess_pts = tessellate(&plane);

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);


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
		DrawPlane();
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

Poly CreatePlane()                       // Adressing by value
{
	Poly p;                              // Draw the outer_plane

	p.outer_contour.points.push_back(Point(-2.86, 1.16));
	p.outer_contour.points.push_back(Point(-2.57, 1.20));
	p.outer_contour.points.push_back(Point(-1.97, 0.34));
	p.outer_contour.points.push_back(Point(-0.15, 0.39));
	p.outer_contour.points.push_back(Point(-0.86, 2.63));
	p.outer_contour.points.push_back(Point(-0.40, 2.57));
	p.outer_contour.points.push_back(Point(0.79, 0.44));
	p.outer_contour.points.push_back(Point(2.18, 0.41));
	p.outer_contour.points.push_back(Point(3.02, -0.01));
	p.outer_contour.points.push_back(Point(2.19, -0.45));
	p.outer_contour.points.push_back(Point(0.78, -0.45));
	p.outer_contour.points.push_back(Point(-0.45, -2.59));
	p.outer_contour.points.push_back(Point(-0.88, -2.63));
	p.outer_contour.points.push_back(Point(-0.15, -0.4));
	p.outer_contour.points.push_back(Point(-1.97, -0.28));
	p.outer_contour.points.push_back(Point(-2.59, -1.20));
	p.outer_contour.points.push_back(Point(-2.87, -1.15));
	p.outer_contour.points.push_back(Point(-2.47, -0.06));
	p.outer_contour.points.push_back(Point(-2.94, 0));
	p.outer_contour.points.push_back(Point(-2.48, 0.09));
	p.outer_contour.points.push_back(Point(-2.86, 1.16));


	Contour inner1;
	inner1.points.push_back(Point(0, 0));         // Draw the first inner_plane 
	inner1.points.push_back(Point(0.7, 0.35));
	inner1.points.push_back(Point(1, -0.1));
	inner1.points.push_back(Point(0, -0.35));
	inner1.points.push_back(Point(0, 0));
	p.inner_contour.push_back(inner1);

	return p;
}

void DrawPlane()                                   // Adressing by value
{

	for (int i = 0; i < p.inner_contour.size(); i++) {
		for (int j = 0; j < p.inner_contour[i].points.size(); j++) {

			glLineWidth(1.0f);
			glColor3f(0.556863f, 0.219608f, 0.556863f);
			glBegin(GL_LINE_STRIP);
			glVertex2f(p.inner_contour[i].points[j].x, p.inner_contour[i].points[j].y);
		}
		glEnd();
	}


	for (int k = 0; k < p.outer_contour.points.size(); k++) {

		glLineWidth(1.0f);
		glColor3f(0.866667f, 0.627451f, 0.866667f); // define color parameter for better visualization
		glBegin(GL_LINE_STRIP);
		glVertex2f(p.outer_contour.points[k].x, p.outer_contour.points[k].y);
	}
	glEnd();
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TESSELATION : 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Point>  tessellate(Poly* p)
{

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// DATA CONVERSION:  convert outer and inner polygon into a large double array
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	tess_pts.clear();                                          // Clear tess_points container

															   // Start conversion:  convert polygon into double array format


	int pts_no = p->outer_contour.points.size() + p->inner_contour[0].points.size();    // Define total size of the double array vector: size outer1 + size inner1[0] 
	double * pPts = new double[3 * pts_no];  // prepare 3 cases vides pour stoquer Px, Py, Pz
	double * pPoints = pPts;

	// Convert all outer_polygon points into double array format                                     // Start conversion:  convert outer_polygon into double array format
	for (int i = 0; i < p->outer_contour.points.size(); i++)
	{
		*pPoints++ = p->outer_contour.points[i].x;  // x-cordinate                                // Define the numbers of a 2-D contour points: e.g 5points here
		*pPoints++ = p->outer_contour.points[i].y;  // y-cordinate
		*pPoints++ = 0;  // z-cordinate
	}

	// Convert all inner_polygon points into double array format
	for (int j = 0; j < p->inner_contour.size(); j++) {                                           // Start conversion:  convert inner_polygon into double array format

		for (int k = 0; k< p->inner_contour[j].points.size(); k++) {

			*pPoints++ = p->inner_contour[j].points[k].x;
			*pPoints++ = p->inner_contour[j].points[k].y;
			*pPoints++ = 0;
		}
	}

	pPoints = pPts;                                                                             // End data conversion:  convert both outer and inner_polygon into double array format  

																								// Creates a new tessellation object and returns a pointer to it
	GLUtesselator *tess = gluNewTess();

	// Define tessellation callbacks
	gluTessCallback(tess, GLU_TESS_BEGIN, (void(CALLBACK *) ()) &beginCallback);
	gluTessCallback(tess, GLU_TESS_END, (void(CALLBACK *) ()) &endCallback);
	gluTessCallback(tess, GLU_TESS_VERTEX, (void(CALLBACK *) ()) &vertexCallback);
	gluTessCallback(tess, GLU_TESS_EDGE_FLAG, (void(CALLBACK *) ()) &TessEdgeFlagCallback);

	//Start tesselation
	gluTessBeginPolygon(tess, 0); //start tesselation for both outer_polygons and inner_polygons
	cout << "Start tesselation: " << endl << endl;

	// Outer_contour
	gluTessBeginContour(tess);   //start tesselation for outer_contours 

	for (int i = 0; i < p->outer_contour.points.size(); i++, pPoints += 3)   // THis is the part where tess function creates: triangle, triangle strips or triangle fans from the outer_contour
	{
		cout << "input vertex: " << pPoints[0] << " " << pPoints[1] << endl;
		gluTessVertex(tess, pPoints, pPoints);
	}
	gluTessEndContour(tess);    //end tesselation for outer_contours 



								 // inner_contour
	gluTessBeginContour(tess);   //start tesselation for Plane_inner_contours 

	for (int j = 0; j < p->inner_contour.size(); j++) {

		for (int k = 0; k < p->inner_contour[j].points.size(); k++, pPoints += 3) {
			gluTessVertex(tess, pPoints, pPoints);
			cout << "input vertex: " << pPoints[0] << " " << pPoints[1] << endl;
		}
	}
	gluTessEndContour(tess);    //end tesselation for Plane_outer_contours 


	cout << endl;

	//Close contour_tessalation
	gluTessEndContour(tess);

	//Close polygon_tessellation
	gluTessEndPolygon(tess);

	cout << endl << "End tesselation. " << endl;

	// delete tessellator after processing
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


void DrawTesselated()
{
	glColor3f(0.8, 0, 0);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < tess_pts.size(); i++)
	{
		glVertex2f(tess_pts[i].x, tess_pts[i].y);
	}
	glEnd();

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
