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
Poly rectangle;
Poly CreateRectangle();

void DrawRectangle();
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
	glutCreateWindow("Tesselation");

	rectangle = CreateRectangle();
	tess_pts = tessellate(&rectangle);

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
		DrawRectangle();
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

//
//Poly CreateRectangle()
//{
//	Poly* p;          // Draw the outer polygon
//
//
//	Point* p1 = new Point(0, 0);
//	Point* p2 = new Point(3, 0);
//	Point* p3 = new Point(0, 5);
//	Point* p4 = new Point(3, 5);
//	
//
//	p->outer_contour.points.push_back(Point(0, 0));
//	p->outer_contour.points.push_back(Point(3, 0));
//	p->outer_contour.points.push_back(Point(0, 5));
//	p->outer_contour.points.push_back(Point(3, 5));
//	p->outer_contour.points.push_back(Point(0, 0));
//
//	
//	Point p5(1, 1);              // Draw the first inner polygon             
//	Point p6(1, 2);
//	Point p7(2, 1);
//	Point p8(2, 2);
//	Contour *inner1;
//	inner1->points.push_back(p5);
//	inner1->points.push_back(p6);
//	inner1->points.push_back(p7);
//	inner1->points.push_back(p8);
//	inner1->points.push_back(p5);
//	
//	Point p9(1, 3);                 // Draw the second inner polygon
//	Point p10(2, 3);
//	Point p11(1, 4);
//	Point p12(2, 4);
//	Contour *inner2;
//	inner2->points.push_back(p9);
//	inner2->points.push_back(p10);
//	inner2->points.push_back(p11);
//	inner2->points.push_back(p12);
//	inner2->points.push_back(p9);
//
//	p->inner_contour.push_back(*inner1);
//	p->inner_contour.push_back(*inner2);
//	
//	
//	return p;
//}

//void DrawRectangle()
//{
//	
//	for (int i = 0; i < rectangle->inner_contour.size(); i++) {
//		for (int j = 0; j < rectangle->inner_contour[i].points.size(); j++) {
//
//			glLineWidth(1.0f);
//			glColor3f(0.556863f, 0.219608f, 0.556863f); 
//			glBegin(GL_LINE_STRIP);
//
//			glVertex2f(rectangle->inner_contour[i].points[j].x, rectangle->inner_contour[i].points[j].y);
//		}
//		glEnd();
//	}
//	
//
//   for (int k = 0; k < rectangle->outer_contour.points.size(); k++) {
//
//			glLineWidth(1.0f);
//			glColor3f(0.866667f, 0.627451f, 0.866667f); // define color parameter for better visualization
//			glBegin(GL_LINE_STRIP);
//			glVertex2f(rectangle->outer_contour.points[k].x, rectangle->outer_contour.points[k].y);
//		}
//		glEnd();
//	}   

Poly CreateRectangle()                    // Adressing by value
{
	Poly p;                              // Draw the outer_polygon

	Point p1(-3, -3);
	Point p2(-3, 3);
	Point p3(3, 3);
	Point p4(3, -3);
	p.outer_contour.points.push_back(p1);
	p.outer_contour.points.push_back(p2);
	p.outer_contour.points.push_back(p3);
	p.outer_contour.points.push_back(p4);
	p.outer_contour.points.push_back(p1);

	Point p5(-1, 1.5);                   // Draw the first inner_polygon             
	Point p6(1, 1.5);
	Point p7(1, 0.5);
	Point p8(-1, 0.5);
	Contour inner1;
	inner1.points.push_back(p5);
	inner1.points.push_back(p6);
	inner1.points.push_back(p7);
	inner1.points.push_back(p8);
	inner1.points.push_back(p5);

	Point p9(-1, -1.5);                 // Draw the second inner_polygon
	Point p10(1, -1.5);
	Point p11(1, -0.5);
	Point p12(-1, -0.5);
	Contour inner2;
	inner2.points.push_back(p9);
	inner2.points.push_back(p10);
	inner2.points.push_back(p11);
	inner2.points.push_back(p12);
	inner2.points.push_back(p9);

	p.inner_contour.push_back(inner1);
	p.inner_contour.push_back(inner2);


	return p;
}



void DrawRectangle()                   // Adressing by value
{

	for (int i = 0; i < rectangle.inner_contour.size(); i++) {
		for (int j = 0; j < rectangle.inner_contour[i].points.size(); j++) {

			glLineWidth(1.0f);
			glColor3f(0.556863f, 0.219608f, 0.556863f);
			glBegin(GL_LINE_STRIP);
			glVertex2f(rectangle.inner_contour[i].points[j].x, rectangle.inner_contour[i].points[j].y);
		}
		glEnd();
	}


	for (int k = 0; k < rectangle.outer_contour.points.size(); k++) {

		glLineWidth(1.0f);
		glColor3f(0.866667f, 0.627451f, 0.866667f); // define color parameter for better visualization
		glBegin(GL_LINE_STRIP);
		glVertex2f(rectangle.outer_contour.points[k].x, rectangle.outer_contour.points[k].y);
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


	int pts_no = p->outer_contour.points.size() + p->inner_contour[0].points.size() + p->inner_contour[1].points.size();    // Define total size of the double array vector: size outer + size inner[0] + size inner[1]
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
	gluTessBeginContour(tess);   //start tesselation for inner_contours 

	for (int j = 0; j < p->inner_contour.size(); j++) {

		for (int k = 0; k < p->inner_contour[j].points.size(); k++, pPoints += 3) {
			gluTessVertex(tess, pPoints, pPoints);
			cout << "input vertex: " << pPoints[0] << " " << pPoints[1] << endl;
		}
	}
	gluTessEndContour(tess);    //end tesselation for outer_contours 


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
