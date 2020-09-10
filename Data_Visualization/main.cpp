#include <windows.h>
#include "glut.h"
#include "Point.h"
#include "LineString.h"
#include "wktReader.h"
#include "Util.h"


vector<Point*> stations;                 //Declaration of vectors
vector<Point*> traffic_points;
vector<Point*> points_of_interest;
vector<vector<vector<double>>> roads;
vector<vector<vector<double>>> railways;  

void RenderScene(void)
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   	//Define the color of render scene
	glClear(GL_COLOR_BUFFER_BIT);               //Constant to clear buffers currently enabled for color writing

	glPointSize(4.0f);                          //size of the visualized point

	glColor3f(1.0f, 0.0f, 0.0f);                //color of the visualized point    

	glPushMatrix();                             // Stacking matrix for storing purpose 

	glTranslatef(-13.334, -52.511, 0); 	        //To set the following coordinates as the center of the 2D scene

	glBegin(GL_POINTS); // Draw all points of interests after reading them all

	for (int i = 0; i < points_of_interest.size(); i++)
		glVertex2f(points_of_interest[i]->x, points_of_interest[i]->y); // Read all points of interests in a vector container
	glEnd();
	
	glPointSize(4.0f);                          //Define point size
	glColor3f(0.0f, 0.0f, 1.0f);                //Define point color


	glBegin(GL_POINTS); //Draw all stations
	for (int i = 0; i < stations.size(); i++)
		glVertex2f(stations[i]->x, stations[i]->y); // Read all stations defined in a vector container
	glEnd();
	
	glPointSize(4.0f);
	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_POINTS); //Draw all traffic_points
	for (int i = 0; i < traffic_points.size(); i++)
		glVertex2f(traffic_points[i]->x, traffic_points[i]->y); // Read all traffic_points defined in a vector container
	glEnd();

	cout << railways.size() << endl;

	for (int i = 0; i < railways.size(); i++) {
		for (int n = 0; n < railways[i].size(); n++) {
			//Define the width of the visualized line
			glLineWidth(1.0f);
			//Define the color of the visualized line
			glColor3f(1.0f, 0.411765f, 0.705882f);
			glBegin(GL_LINE_STRIP);
			//Railways[i][n][0] is the x coordinate of point n of linestring i
			glVertex2f(railways[i][n][0], railways[i][n][1]);
   }
		glEnd();
	}

	//We draw railways by using 2 iterations and a vector of vector of vector of double
	for (int j = 0; j < roads.size(); j++) {
		for (int k = 0; k < roads[j].size(); k++) {
			glLineWidth(1.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glBegin(GL_LINE_STRIP);
			glVertex2f(roads[j][k][0], roads[j][k][1]);
		}
		glEnd();
	}

	glFlush();
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


void main(void)
{
	wktReader wkt;        //Read the files
	railways = wkt.ReadLinesFile("../data/railways.txt");
	roads = wkt.ReadLinesFile("../data/roads.txt");


	points_of_interest = wkt.ReadPointsFile("../data/points_of_interest.txt");
	stations = wkt.ReadPointsFile("../data/stations.txt");
	traffic_points = wkt.ReadPointsFile("../data/traffic_points.txt");


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("2D City");
	glutDisplayFunc(RenderScene);

	glutReshapeFunc(ChangeSize);
	glutMainLoop();

	char c;
	cin >> c;
}