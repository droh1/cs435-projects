/*****************************************************************
* File:		texture.h
* Project:	CMSC 435 Project 1, Spring 2019
* Author:	Daniel Roh
* Date:		02/09/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	Functions: Header for texture.cpp
*****************************************************************/
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "rayPoint.h"
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

class texture {
public:
	texture() {}; //Constructor
	~texture() {}; //Destructor
	texture(vector<double> color);
	virtual double intersect(rayPoint ray, double hither = -1) const = 0;

private:
	friend class rayTrace;

protected: //To allow other classes to see this variable
	vector<double> color{0, 0, 0, 0, 0, 0, 0, 0}; //Defualt is black
};
#endif



