/*****************************************************************
* File:		Filehandle.cpp
* Project:	CMSC 435 Project 1, Spring 2019
* Author:	Daniel Roh
* Date:		02/09/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is Filehandle.cpp
*	Functions: The main backbone of the program. Deals with
*			   reading in inputs and creating texture objects
*****************************************************************/
#include "Filehandle.h"

//Constructor
Filehandle::Filehandle() {
	from = Vector3d(0, 0, 0);
	at = Vector3d(0, 0, 0);
	up = Vector3d(0, 0, 0);
	angle = 0;
	hither = 0;
}

//File proccessing
void Filehandle::readFile(string file) {
	string x;
	vector<double> color{0, 0, 0, 0, 0, 0, 0, 0};
	vector<Vector3d> currentEdges;
	ifstream infile;
	infile.open(file);
	cout << "Opening " << file << " " << endl; //DEBUG
	
	if (!infile) {
		cout << "Unable to find " << file << endl;
		exit(1);
	}

	while (!infile.eof()) { //Untill end of file is reached
		getline(infile, x);
		istringstream iss(x);
		vector<string> buffer((std::istream_iterator<string>(iss)), std::istream_iterator<string>());
		
		if (buffer.size() == 0) {
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
			for (unsigned int t = 0; t < buffer.size(); t++) {
				color[t] = stod(buffer.at(t));
			}
		}
		else if (test == "s") { //"s" center.x center.y center.z radius
			Vector3d center; 

			//for (unsigned int t = 0; t < (buffer.size() - 1); t++) {
			for (int t = 0; t < 3; t++) {
				center[t] = stod(buffer.at(t)); 
			}

			double radius = stod(buffer.at(buffer.size() -1 ));
			textures.push_back(new Sphere(center, radius, color));
		}
		else if (test == "p" || test == "pp") { 
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
			Polygon *temps = new Polygon(currentEdges, color);
			textures.push_back(temps);
			currentEdges.clear();
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
						res[t] = stoi(buffer2.at(t));
					}
				}
				count--;
			}
		}
	}

	return;
}