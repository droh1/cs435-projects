/*****************************************************************
* File:		Filehandle.h
* Project:	CMSC 435 Project 1, Spring 2019
* Author:	Daniel Roh
* Date:		02/09/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	Functions: Header for Filehandle.cpp
*****************************************************************/
#ifndef _FILEHANDLE_H_
#define _FILEHANDLE_H_

#include "texture.h"
#include "Polygon.h"
#include "Sphere.h"
#include <stdlib.h>
#include <string>
#include <iterator>
#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

class Filehandle {
public:
	Filehandle();
	void readFile(string file);

private:
	friend class rayTrace;
	double angle;
	double hither;	

	Vector3d from;
	Vector3d at;
	Vector3d up;

	vector<int> res{0, 0};
	vector<double> back{0, 0, 0};
	vector<texture*> textures;
};
#endif
