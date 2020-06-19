/*****************************************************************
* File:		Triangle.h
* Project:	CMSC 435 Project 1, Spring 2019
* Author:	Daniel Roh
* Date:		02/09/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	Functions: Header for Triangle.cpp
*****************************************************************/
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "rayPoint.h"
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

class Triangle {
public:
	Triangle(Vector3d point1, Vector3d point2, Vector3d point3);
	void intersectValues(rayPoint ray, double v[]) const;
	double intersect(rayPoint ray) const;

	//Points of the polygon
	Vector3d point1;
	Vector3d point2;
	Vector3d point3;
};
#endif
