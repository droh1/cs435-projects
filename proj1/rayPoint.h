/*****************************************************************
* File:		rayPoint.h
* Project:	CMSC 435 Project 1, Spring 2019
* Author:	Daniel Roh
* Date:		02/09/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	Functions: Header for rayPoint.cpp
*****************************************************************/
#ifndef _RAYPOINT_H_
#define _RAYPOINT_H_

#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

class rayPoint {
public:
	rayPoint(Vector3d from, Vector3d direction);

	Vector3d from;
	Vector3d direction;
private:
	//No private vars;
};
#endif
