/*****************************************************************
* File:		rayTrace.h
* Project:	CMSC 435 Project 1, Spring 2019
* Author:	Daniel Roh
* Date:		02/09/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	Functions: Header for rayTrace.cpp
*****************************************************************/
#ifndef _RAYTRACE_H_
#define _RAYTRACE_H_

#include "Filehandle.h"
#include "rayPoint.h"
#include "texture.h"
#include "Polygon.h"
#include "Triangle.h"
#include <iostream>
#include <fstream>
#include <vector>
#include<math.h>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;


class rayTrace {
public:
	rayTrace(Filehandle input);
	void render();
	vector<double> fireRay(rayPoint ray);

private:
	Filehandle input;
	const double PI = 360.0; //For VS17
	string out = "output.ppm"; //Output file name
};
#endif

