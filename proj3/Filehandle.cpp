/*****************************************************************
* File:		Filehandle.cpp
* Project:	CMSC 435 Project 3, Spring 2019
* Author:	Daniel Roh
* Date:		03/11/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is Filehandle.cpp
*	Functions: Reads in data from nff files
*****************************************************************/
#include "Filehandle.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <iterator>
#include <assert.h>
using namespace std;
using namespace Eigen;

/********************************************************
*	colorInfo Class Functions							*
*********************************************************/
//Debugger Print Out
void ColorInfo::printMe() {
	for (int x = 0; x < 3; x++) {
		cout << color[x] << ", ";
	}
	cout << diffuse << ", " << specular << ", " << shine << ", " << T << ", " << refract << endl;
}

/********************************************************
*	Light Class Functions								*
*********************************************************/
//Constructor
Light::Light(Vector3d position, Vector3d color){
	this->color = color;
	this->position = position;
}

/********************************************************
*	Filehandle Class Functions							*
*********************************************************/
//Constructor
Filehandle::Filehandle() {
    back = Vector3d(0,0,0); //default background color is 0,0,0
    from = Vector3d(0,0,0);
    at = Vector3d(0,0,0);
    up = Vector3d(0,0,0);
    angle = 0;
    hither = 0;
}

//Destructor
Filehandle::~Filehandle() {
    for (unsigned int i = 0; i<textures.size(); i++) {
        delete textures[i];
    }
    for (unsigned int i = 0; i<info.size(); i++) {
        delete info[i];
    }
	textures.clear();
    info.clear();
}

//File input
void Filehandle::readFile(string file) {
	string x;
	//vector<double> color{ 0, 0, 0, 0, 0, 0, 0, 0 };
	//vector<double> light; //X Y Z R G B
	vector<Vector3d> currentEdges;
	vector<Vector3d> currentNormal;
	ifstream infile;
	infile.open(file);
	cout << "Opening " << file << " " << endl; //DEBUG

	if (!infile) { //If file dosent exist
		cout << "Unable to find " << file << endl;
		exit(1);
	}

	while (!infile.eof()) { //Until end of file is reached
		getline(infile, x);
		istringstream iss(x);
		vector<string> buffer((istream_iterator<string>(iss)), istream_iterator<string>());

		if (buffer.size() == 0) { //If the buffer iis 
			break;
		}
		string test = buffer.front(); //Grab the identfying letter
		buffer.erase(buffer.begin()); //Get rid of letter

		if (test == "b") {
			for (unsigned int t = 0; t < buffer.size(); t++) {
				back[t] = stod(buffer.at(t));
			}
		}
		else if (test == "f") {
			ColorInfo *tempColor = new ColorInfo;
			for (unsigned int t = 0; t < 3; t++) {
				//color[t] = stod(buffer.at(t));
				tempColor->color[t] = stod(buffer.at(t));
			}
			tempColor->diffuse = stod(buffer.at(3)); //Grab the other values
			tempColor->specular = stod(buffer.at(4));
			tempColor->shine = stod(buffer.at(5));
			tempColor->T = stod(buffer.at(6));
			tempColor->refract = stod(buffer.at(7));

			info.push_back(tempColor);
		}
		else if (test == "s") { //"s" center.x center.y center.z radius
			Vector3d center;

			//for (unsigned int t = 0; t < (buffer.size() - 1); t++) { //Spheres have 3 positions and radius
			for (int t = 0; t < 3; t++) {
				center[t] = stod(buffer.at(t));
			}

			double radius = stod(buffer.at(buffer.size() - 1));
			textures.push_back(new Sphere(center, radius, info.back()));
		}
		else if (test == "p") {
			int count = stoi(buffer.front());

			while (count != 0) { //For the amount of points in the image
				getline(infile, x);
				istringstream iss(x);
				vector<string> buffer2(istream_iterator<string>{iss}, istream_iterator<string>());
				Vector3d edge;

				for (unsigned int t = 0; t < buffer2.size(); t++) { //For X values (should be 3)
					edge[t] = stod(buffer2.at(t));
				}
				currentEdges.push_back(edge); //Store point
				count--;
			}

			Vector3d fake(0, 0, 0);
			currentNormal.push_back(fake); //Make a empty Vector3d

			Polygon *temps = new Polygon(currentEdges, currentNormal, info.back(), false);
			textures.push_back(temps);
			currentEdges.clear(); //Clear buffer for next
			currentNormal.clear();
		}
		else if (test == "pp") { //Polygon Patch
			int count = stoi(buffer.front()); //Get amount of items

			while (count != 0) {
				getline(infile, x);
				istringstream iss(x);
				vector<string> buffer2(istream_iterator<string>{iss}, istream_iterator<string>());
				Vector3d edge, normal;

				for (unsigned int t = 0; t < buffer2.size(); t++) {
					if (t < 3) { //For edges
						edge[t] = stod(buffer2.at(t));
					}
					else { //For normals
						normal[t - 3] = stod(buffer2.at(t));
					}
				}
				currentEdges.push_back(edge);
				currentNormal.push_back(normal);
				count--;
			}

			Polygon *temps = new Polygon(currentEdges, currentNormal, info.back(), true); //Set true for PP
			textures.push_back(temps);
			currentEdges.clear(); //Clear buffer for next
			currentNormal.clear();
		}
		else if (test == "l") { //If a light is found
			//vector<double> tempLight;
			Vector3d tempLight;
			Vector3d tempPosition;

			if (buffer.size() == 3) { //If only position is given
				for (unsigned t = 0; t < buffer.size(); t++) { //Position
					tempPosition[t] = (stod(buffer.at(t)));
				}
				for (unsigned t = 3; t < buffer.size(); t++) { //Color
					//tempLight.push_back(1.0); //Default RGB values of 1
					tempLight[t - 3] = 1.0;
				}
			}
			else { //If position and color is given
				for (unsigned int t = 0; t < (buffer.size() / 2); t++) { //Position 
					tempPosition[t] = (stod(buffer.at(t)));
				}
				for (unsigned int t = 3; t < buffer.size(); t++) { //Color
					//tempLight.push_back(stod(buffer.at(t)));
					tempLight[t - 3] = (stod(buffer.at(t)));
				}
			}
			//Light *temp = new Light(tempPosition, tempLight); //Does not work for project 2
			lights.push_back(Light(tempPosition, tempLight));
		}
		else if (test == "v") { //If view is detected
			int count = 6;

			while (count != 0) { //Process all view elements
				getline(infile, x); //Get the next string
				istringstream iss(x);
				vector<string> buffer2(istream_iterator<string>{iss}, istream_iterator<string>());

				test = buffer2.front(); //Grab the key in the beginning of the data
				buffer2.erase(buffer2.begin()); //Remove the key to allow proccessing 

				if (test == "from") {
					for (unsigned int t = 0; t < buffer2.size(); t++) {
						from[t] = stod(buffer2.at(t));
					}
				}
				if (test == "at") {
					for (unsigned int t = 0; t < buffer2.size(); t++) {
						at[t] = stod(buffer2.at(t));
					}
				}
				if (test == "up") {
					for (unsigned int t = 0; t < buffer2.size(); t++) {
						up[t] = stod(buffer2.at(t));
					}
				}
				if (test == "angle") {
					angle = stod(buffer2.at(0));
				}
				if (test == "hither") {
					hither = stod(buffer2.at(0));
				}
				if (test == "resolution") {
					for (unsigned int t = 0; t < buffer2.size(); t++) {
						resolution[t] = stoi(buffer2.at(t));
					}
				}
				count--;
			}
		}
	}

	cout << "File Read Sucessful" << endl; //DEBUG
	return;
}