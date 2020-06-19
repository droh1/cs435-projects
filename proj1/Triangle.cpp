/*****************************************************************
* File:		Triangle.cpp
* Project:	CMSC 435 Project 1, Spring 2019
* Author:	Daniel Roh
* Date:		02/09/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	Functions: Class for holding triangle data
*****************************************************************/
#include "Triangle.h"

//Constructor 
Triangle::Triangle(Vector3d point1, Vector3d point2, Vector3d point3) {
	this->point1 = point1;
	this->point2 = point2;
	this->point3 = point3;
}

//
double Triangle::intersect(rayPoint ray) const {
	double vals[4];

	intersectValues(ray, vals); // [B, g, t, dist]
	return vals[3];
}

//Virtual Texture Function
void Triangle::intersectValues(rayPoint ray, double v[]) const {
	Matrix3d A;
	A << (point1 - point2), (point1 - point3), ray.direction;

	Matrix3d matx1;
	matx1 << (point1 - ray.from), (point1 - point3), (ray.direction);

	Matrix3d matx2;
	matx2 << (point1 - point2), (point1 - ray.from), ray.direction;

	Matrix3d matx3;
	matx3 << (point1 - point2), (point1 - point3), (point1 - ray.from);

	double determ = A.determinant(); //Get determinant of A
	v[0] = (matx1.determinant() / determ); //Beta
	v[1] = (matx2.determinant() / determ); //Gamma
	v[2] = (matx3.determinant() / determ); //t

	if ((0 <= v[0]) && (0 <= v[1]) && (v[2] > 0) && ((v[0] + v[1]) <= 1)) { //If valid beta, gamma, and t are valid
		Vector3d point = ray.from + (v[2] * ray.direction); //ray = e + (t*d);
		v[3] = (point - ray.from).norm(); //Distince to intersection
		return;
	}
	
	v[3] = -1; //If invalid set to -1
	return;
}	
/*
	//Wrong if statments, does not account for or
	if (t > 0) { 
		if (beta >= 0) {
			if (gamma >= 0) {
				if ((beta + gamma) <= 1) { //If all the points are valid
					Vector3d point = ray.from + (t * ray.direction); //Intersection Location
					v[3] = (point - ray.from).norm(); //Distence to intersection
					return;
				}
			}
		}
	}*/