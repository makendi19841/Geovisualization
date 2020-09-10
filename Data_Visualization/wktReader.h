#pragma once


#pragma once
#include "LineString.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "Point.h"
#include <string>
#include "Util.h"
using namespace std;

class wktReader
{
public:

	wktReader();
	~wktReader();

	vector<vector<vector<double>>>ReadLinesFile(const string path);
	vector<Point*> ReadPointsFile(const string path);
};

wktReader::wktReader()
{}

wktReader:: ~wktReader()
{}

vector<vector<vector<double>>> wktReader::ReadLinesFile(const string path)
{ // Definition of the function ReadLinesFile

	string line;                     //Initialization line
	vector<string> railways;         //Initialization of a string vector named railways
						      
	ifstream myfile(path, ios::in);  //Read the file to myfile from the path

	if (myfile.is_open())            
	{
		while (getline(myfile, line))
		{
			railways.push_back(line.substr(12, (line.size() - 14))); //Read all lines as string from line.substr 12 upto line.size()-14
		}
		myfile.close();
	}
	else { 
		cout << "Unable to open the file"; 
	}

   /********************************************************************************************/	
    vector <string> coord;
	vector <vector <string> > coordList;
	
	for (int i = 0; i<(railways.size()); i++)
	{
		coord = util::Util::Split(railways[i], ", ", true); //Split the coordinates using the comma delimeter
		coordList.push_back(coord);
		coord.clear();
	}

	/********************************************************************************************/
    vector<string> coordPoint_s;                       // initialization of a string vector called coordPoint_s
	vector<vector<vector<double>>> colCoordPoint_s;
	vector<vector<double>>vec_d;

	for (int p = 0; p < coordList.size(); p++)
	{

		for (int n = 0; n < coordList[p].size(); n++)
		{   //We read each string value delimited with space
			coordPoint_s = util::Util::Split(coordList[p][n], " ", true);

			// To convert string vector to vector of double
			std::vector<double> doubleVector(coordPoint_s.size());
			std::transform(coordPoint_s.begin(), coordPoint_s.end(), doubleVector.begin(), [](const std::string& val)
			{
				return std::stod(val);
			});

			// vec_d: vector of vector of double 
			vec_d.push_back(doubleVector);
			doubleVector.clear();

		}

		//colCoordPoint_s : vector of vector of vector of double 
		colCoordPoint_s.push_back(vec_d);
		vec_d.clear();


	}

	system("pause");
	return colCoordPoint_s;
}


vector<Point*> wktReader::ReadPointsFile(string path)
{
	vector<Point*> result;                 // initialization of the container: here we deal with Point pointers
	double x, y;                           // initializatiion of point coordinates: for the file contains point coordinates

	ifstream file(path, ios::in);          //open file with the given path, to read-in only

	while (file && !file.eof())            //if such a file exists and till it's not the end-of-file
	{
		file.ignore(100, '(');             // ignore all until bracket
		file >> x >> y;                    //read in double x and double y

		result.push_back(new Point(x, y)); //create a point and put it into a container
	}
	result.pop_back();                     //the last line is readed twice, so you must delete the last point

	return result;
}
