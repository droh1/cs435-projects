/*****************************************************************
* File:		Sphere.h
* Project:	CMSC 435 Project 1, Spring 2019
* Author:	Daniel Roh
* Date:		02/09/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	Functions: Header for Sphere.cpp
*****************************************************************/
#ifndef _SPHERE_H_
#define  _SPHERE_H_

#include "rayPoint.h"
#include "texture.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

class Sphere : public texture{
public:
	Sphere(Vector3d center, double radius, vector<double> color = vector<double>{0, 0, 0, 0, 0, 0, 0, 0});// = vector<double>);
	double intersect(rayPoint ray, double hither = -1) const; 

private:
	double radius;
	Vector3d center;
};
#endif
