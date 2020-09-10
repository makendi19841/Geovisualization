#include <windows.h>
#include "glut.h"
#include "Point.h"
#include "LineString.h"
#include "wktReader.h"
#include "Util.h"



vector<Point*> stations;                            //Declaration of vectors
vector<Point*> traffic_points;
vector<Point*> points_of_interest;
vector<vector<vector<double>>> roads;
vector<vector<vector<double>>> railways;
vector<Poly*> water;
vector<Poly*> buildings;
vector<Poly*> land_use;
Contour outer_contour;
vector<Contour> inner_contour;

void RenderScene();                                   //Declaration of diffrerent functions
void ChangeSize(GLsizei width, GLsizei height);
void DrawPointsFeatures();
void DrawLinesFeatures();
void DrawPolygonFeatures();
int model = 2;                                        //Display the lines first

void keys(unsigned char key, int x, int y);

void main()
{
	wktReader wkt;                                  //Read the files
	railways = wkt.ReadLinesFile("../data/railways.txt");
	roads = wkt.ReadLinesFile("../data/roads.txt");


	points_of_interest = wkt.ReadPointsFile("../data/points_of_interest.txt");
	stations = wkt.ReadPointsFile("../data/stations.txt");
	traffic_points = wkt.ReadPointsFile("../data/traffic_points.txt");

	water = wkt.ReadPolygonFile("../data/water.txt");
	land_use = wkt.ReadPolygonFile("../data/land_use.txt");
	buildings = wkt.ReadPolygonFile("../data/buildings.txt");


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("2D City");
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(keys);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
}


void RenderScene()
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   	//Define the color of render scene
	glClear(GL_COLOR_BUFFER_BIT);               //Constant to clear buffers currently enabled for color writing							
												//color of the visualized point    
	glPushMatrix();                             // Stacking matrix for storing purpose 
	glTranslatef(-13.334, -52.511, 0); 	        //To set the following coordinates as the center of the 2D scene

												// Keyboard with interaction
	switch (model)
	{
	case 1:
		DrawPointsFeatures();
		break;
	case 2:
		DrawLinesFeatures();
		break;
	case 3:
		DrawPolygonFeatures();
		break;
	case 4:
		DrawPointsFeatures();
		DrawLinesFeatures();
		DrawPolygonFeatures();
		break;
	}

	glFlush();
	glPopMatrix();

}


void keys(unsigned char key, int x, int y) //Switching between layers
{
	if (key = 'p') model = 1;
	if (key = 'l') model = 2;
	if (key = 'o') model = 3;
	if (key = 'a') model = 4;

	RenderScene();                  
}

void ChangeSize(GLsizei width, GLsizei height) // ChangeSize Function
{
	if (height == 0)
		height = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat AspectRatio;
	AspectRatio = (GLfloat)width / (GLfloat)height;

	GLfloat multiple = 0.015;

	if (width <= height)
		gluOrtho2D(-1.0*multiple, 1.0*multiple, -1.0 / AspectRatio *multiple, 1.0 / AspectRatio*multiple);
	else
		gluOrtho2D(-1.0*AspectRatio*multiple, 1.0*AspectRatio*multiple, -1.0*multiple, 1.0*multiple);

	glViewport(0, 0, width, height);

}

void DrawPointsFeatures()
{

	/*******Draw Points Features*********/
	glBegin(GL_POINTS);
	for (int i = 0; i < points_of_interest.size(); i++) {
		glVertex2f(points_of_interest[i]->x, points_of_interest[i]->y);
	}
	glEnd();


	glPointSize(4.0f);                          //Define point size
	glColor3f(0.0f, 0.0f, 1.0f);                //Define point color
	glBegin(GL_POINTS);
	for (int i = 0; i < stations.size(); i++) {
		glVertex2f(stations[i]->x, stations[i]->y);
	}
	glEnd();


	glPointSize(4.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < traffic_points.size(); i++) {
		glVertex2f(traffic_points[i]->x, traffic_points[i]->y);
	}glEnd();

	glFlush();
}

void DrawLinesFeatures()
{/*******Draw Line Features*********/

	for (int i = 0; i < railways.size(); i++) {
		for (int n = 0; n < railways[i].size(); n++) {
			glLineWidth(1.0f);
			glColor3f(1.0f, 0.411765f, 0.705882f);
			glBegin(GL_LINE_STRIP);
			glVertex2f(railways[i][n][0], railways[i][n][1]);
		}
		glEnd();
	}


	for (int j = 0; j < roads.size(); j++) {
		for (int k = 0; k < roads[j].size(); k++) {
			glLineWidth(1.0f);
			glColor3f(1.0f, 0.4f, 0.7f);
			glBegin(GL_LINE_STRIP);
			glVertex2f(roads[j][k][0], roads[j][k][1]);
		}
		glEnd();
	}

	glFlush();
}

void DrawPolygonFeatures()
{
	/*******Draw water Features*********/

	for (int i = 0; i < water.size(); i++) {
		if (water[i]->inner_contour.size() > 0)
			for (int j = 0; j < water[i]->inner_contour.size(); j++) {
				for (int k = 0; k < water[i]->inner_contour[j].points.size(); k++) {

					glLineWidth(1.0f);
					glColor3f(0.0f, 0.0f, 0.803922f);
					glBegin(GL_LINE_STRIP);
					glVertex2f(water[i]->inner_contour[j].points[k].x, water[i]->inner_contour[j].points[k].y);
				}
				glEnd();
			}

	}

	for (int i = 0; i < water.size(); i++) {
		for (int j = 0; j < water[i]->outer_contour.points.size(); j++) {

			glLineWidth(1.0f);
			glColor3f(0.0f, 0.0f, 0.803622f);
			glBegin(GL_LINE_STRIP);
			glVertex2f(water[i]->outer_contour.points[j].x, water[i]->outer_contour.points[j].y);
		}
		glEnd();
	}


	/*draw buildings features*/

	for (int i = 0; i < buildings.size(); i++) {
		if (buildings[i]->inner_contour.size() > 0)
			for (int j = 0; j < buildings[i]->inner_contour.size(); j++) {
				for (int k = 0; k < buildings[i]->inner_contour[j].points.size(); k++) {

					glLineWidth(1.0f);
					glColor3f(0.556863f, 0.219608f, 0.556863f); 
					glBegin(GL_LINE_STRIP);
					glVertex2f(buildings[i]->inner_contour[j].points[k].x, buildings[i]->inner_contour[j].points[k].y);
				}
				glEnd();
			}

	}

	for (int i = 0; i < buildings.size(); i++) {
		for (int j = 0; j < buildings[i]->outer_contour.points.size(); j++) {

			glLineWidth(1.0f);
			glColor3f(0.866667f, 0.627451f, 0.866667f); 
			glBegin(GL_LINE_STRIP);
			glVertex2f(buildings[i]->outer_contour.points[j].x, buildings[i]->outer_contour.points[j].y);
		}
		glEnd();
	}

/********draw land_use features********/

	for (int i = 0; i < land_use.size(); i++) {
		if (land_use[i]->inner_contour.size() > 0)
			for (int j = 0; j < land_use[i]->inner_contour.size(); j++) {
				for (int k = 0; k < land_use[i]->inner_contour[j].points.size(); k++) {

					glLineWidth(1.0f);
					glColor3f(0.0f, 0.0f, 0.0f);
					glBegin(GL_LINE_STRIP);
					glVertex2f(land_use[i]->inner_contour[j].points[k].x, land_use[i]->inner_contour[j].points[k].y);
				}
				glEnd();
			}

	}

	for (int i = 0; i < land_use.size(); i++) {
		for (int j = 0; j < land_use[i]->outer_contour.points.size(); j++) {

			glLineWidth(1.0f);
			glColor3f(0.0f, 1.0f, 0.498039f); 
			glBegin(GL_LINE_STRIP);
			glVertex2f(land_use[i]->outer_contour.points[j].x, land_use[i]->outer_contour.points[j].y);
		}
		glEnd();
	}
	glFlush();
}



