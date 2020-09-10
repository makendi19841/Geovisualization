#include <windows.h> 
#include <gl/gl.h> 
#include "glut.h"
#include "Point.h"
#include "LineString.h"
#include "wktReader.h"
#include "Util.h"

static GLfloat  angle_X = 0.0f;
static GLfloat  angle_Y = 0.0f;
static GLfloat  angle_Z = 0.0f;

int last_x = 0;                     // last position of the cursor: Rotation
int last_y = 0;

int last_x1 = 0;                    // last position of the cursor: Rotation
int last_y1 = 0;

int last_y2 = 0;                    // last position of the cursor: scaling


bool left_button = false;           //if the button is pressed: rotation
bool right_button = false;          //if the button is pressed: translation
bool centre_button = false;         //if the button is pressed: scaling


GLfloat theta_x = 0.0f;              //rotation angle
GLfloat theta_y = 0.0f;

GLfloat trans_x = 0.0f;              //translation
GLfloat trans_y = 0.0f;

GLfloat scale = 1.0f;                 //scaling

GLfloat window_width;
GLfloat window_height;


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

void RenderScene();                             //Declaration of diffrerent functions
void DrawPointsFeatures();
void DrawLinesFeatures();
void DrawPolygonFeatures();
void ChangeSize(GLsizei width, GLsizei height);


void RenderScene()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix(); // Push the current matrix onto the matrix stack in other to save it for further use

	glRotatef(theta_x, 0, 1, 0);         // Model transformation steps
	glRotatef(theta_y, 1, 0, 0);         // Rotation

	glScalef(scale, scale, scale);       // Scaling

	glTranslatef(trans_x, trans_y, 0);   // Translation

	glTranslatef(-13.334, -52.511, 0);

	DrawPointsFeatures();                // Functions to draw point, lines, and Polygon features.  
	DrawLinesFeatures();
	DrawPolygonFeatures();

	glPopMatrix();
	glFlush();
}



void mouse_button(int button, int state, int x, int y)
{
	/* Function that checks if mouse button is pressed and gets the current position of the cursor*/
	last_x = x;   // save current cursor position: rotation
	last_y = y;


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)    // Rotation
		left_button = true;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		left_button = false;


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)    // Translation
		right_button = true;
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
		right_button = false;


	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)   //  Scaling
		centre_button = true;
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
		centre_button = false;

}



void mouse_motion(int x, int y)
{

	float dx = (float(x) - last_x) / window_width;
	float dy = (float(y) - last_y) / window_height;


	if (left_button)
	{

		theta_x += dx * 360.0 / 2;      //fast rotation
		theta_y -= dy * 360.0 / 2;

	}

	if (right_button)
	{

		trans_x += dx*0.1;             //fast translation
		trans_y -= dy*0.1;

	}

	if (centre_button)
	{
		scale += dy * 2;                //fast scaling		
	}


	last_x = x;       // Update current position: rotation
	last_y = y;

	RenderScene();
}

void ChangeSize(GLsizei width, GLsizei height) // ChangeSize Function
{
	if (height == 0)   // To avoid division by zero
		height = 1;

	window_width = (float)width;
	window_height = (float)height;

	glMatrixMode(GL_PROJECTION);  // Observed coordinate system
	glLoadIdentity();

	GLfloat AspectRatio;
	AspectRatio = (GLfloat)width / (GLfloat)height;  // Window's height/size ratio

	GLfloat multiple = 0.015;

	if (width <= height)
		gluOrtho2D(-1.0*multiple, 1.0*multiple, -1.0 / AspectRatio *multiple, 1.0 / AspectRatio*multiple);
	else
		gluOrtho2D(-1.0*AspectRatio*multiple, 1.0*AspectRatio*multiple, -1.0*multiple, 1.0*multiple);

	glViewport(0, 0, width, height);  // Size of device's window in pixels

}



void DrawPointsFeatures()
{

	/*************************************************Draw Points Features************************************************/
	glBegin(GL_POINTS); // Draw all points of interests after reading them all
	for (int i = 0; i < points_of_interest.size(); i++) {
		glVertex2f(points_of_interest[i]->x, points_of_interest[i]->y);
	} // Read all points of interests in a vector container
	glEnd();


	glPointSize(4.0f);                          //Define point size
	glColor3f(0.0f, 0.0f, 1.0f);                //Define point color
	glBegin(GL_POINTS); //Draw all stations
	for (int i = 0; i < stations.size(); i++) {
		glVertex2f(stations[i]->x, stations[i]->y);
	}// Read all stations defined in a vector container
	glEnd();


	glPointSize(4.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS); //Draw all traffic_points
	for (int i = 0; i < traffic_points.size(); i++) {
		glVertex2f(traffic_points[i]->x, traffic_points[i]->y); // Read all traffic_points defined in a vector container
	}glEnd();

	glFlush();
}

void DrawLinesFeatures()
{/*************************************************Draw Line Features************************************************/

	for (int i = 0; i < railways.size(); i++) {
		for (int n = 0; n < railways[i].size(); n++) {
			//Define the width of the visualized line
			glLineWidth(1.0f);
			//Define the color of the visualized line
			glColor3f(1.0f, 0.411765f, 0.705882f);    // define color parameter for better visualization
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
			glColor3f(1.0f, 0.4f, 0.7f);   // define color parameter for better visualization
			glBegin(GL_LINE_STRIP);
			glVertex2f(roads[j][k][0], roads[j][k][1]);
		}
		glEnd();
	}

	glFlush();
}

void DrawPolygonFeatures()
{


	/*****************************************Draw Polygon Features**********************************/

	for (int i = 0; i < water.size(); i++) {   /*draw water features: change indexe in this code and check other ways of implementing pointers*/
		if (water[i]->inner_contour.size() > 0)
			for (int j = 0; j < water[i]->inner_contour.size(); j++) {
				for (int k = 0; k < water[i]->inner_contour[j].points.size(); k++) {

					glLineWidth(1.0f);
					glColor3f(0.0f, 0.0f, 0.803922f);  // define color parameter for better visualization
					glBegin(GL_LINE_STRIP);
					glVertex2f(water[i]->inner_contour[j].points[k].x, water[i]->inner_contour[j].points[k].y);
				}
				glEnd();
			}

	}

	for (int i = 0; i < water.size(); i++) {
		for (int j = 0; j < water[i]->outer_contour.points.size(); j++) {

			glLineWidth(1.0f);
			glColor3f(0.0f, 0.0f, 0.803622f);  // define color parameter for better visualization
			glBegin(GL_LINE_STRIP);
			glVertex2f(water[i]->outer_contour.points[j].x, water[i]->outer_contour.points[j].y);
		}
		glEnd();
	}


	/*draw buildings features: change indexe in this code and check other ways of implementing pointers*/

	for (int i = 0; i < buildings.size(); i++) {
		if (buildings[i]->inner_contour.size() > 0)
			for (int j = 0; j < buildings[i]->inner_contour.size(); j++) {
				for (int k = 0; k < buildings[i]->inner_contour[j].points.size(); k++) {

					glLineWidth(1.0f);
					glColor3f(0.556863f, 0.219608f, 0.556863f); // define color parameter for better visualization
					glBegin(GL_LINE_STRIP);
					glVertex2f(buildings[i]->inner_contour[j].points[k].x, buildings[i]->inner_contour[j].points[k].y);
				}
				glEnd();
			}

	}

	for (int i = 0; i < buildings.size(); i++) {
		for (int j = 0; j < buildings[i]->outer_contour.points.size(); j++) {

			glLineWidth(1.0f);
			glColor3f(0.866667f, 0.627451f, 0.866667f); // define color parameter for better visualization
			glBegin(GL_LINE_STRIP);
			glVertex2f(buildings[i]->outer_contour.points[j].x, buildings[i]->outer_contour.points[j].y);
		}
		glEnd();
	}

	/*****************draw land_use features: change indexe in this code and check other ways of implementing pointers**************************/

	for (int i = 0; i < land_use.size(); i++) {
		if (land_use[i]->inner_contour.size() > 0)
			for (int j = 0; j < land_use[i]->inner_contour.size(); j++) {
				for (int k = 0; k < land_use[i]->inner_contour[j].points.size(); k++) {

					glLineWidth(1.0f);
					glColor3f(0.44f, 0.77f, 0.44f);// define color parameter for better visualization
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
			glColor3f(0.0f, 1.0f, 0.498039f); // define color parameter for better visualization
			glBegin(GL_LINE_STRIP);
			glVertex2f(land_use[i]->outer_contour.points[j].x, land_use[i]->outer_contour.points[j].y);
		}
		glEnd();
	}
	glFlush();
}

void main(void)
{

	wktReader wkt;                                                   //Read the files
	railways = wkt.ReadLinesFile("../data/railways.txt");
	roads = wkt.ReadLinesFile("../data/roads.txt");

	points_of_interest = wkt.ReadPointsFile("../data/points_of_interest.txt");
	stations = wkt.ReadPointsFile("../data/stations.txt");
	traffic_points = wkt.ReadPointsFile("../data/traffic_points.txt");

	water = wkt.ReadPolygonFile("../data/water.txt");
	land_use = wkt.ReadPolygonFile("../data/land_use.txt");
	buildings = wkt.ReadPolygonFile("../data/buildings.txt");


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);                   // display mode settings   
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(720, 720);
	glutCreateWindow("Mouse interraction: Rotation_TRanslation_Scaling"); //creates window with a tittle
	glutMouseFunc(mouse_button);
	glutMotionFunc(mouse_motion);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();

}