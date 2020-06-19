/*****************************************************************
* File:		Triangle.cpp
* Project:	CMSC 435 Project 3, Spring 2019
* Author:	Daniel Roh
* Date:		03/11/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is Triangle.cpp
*	Functions: Functions for Triangles
*****************************************************************/
#include "Triangle.h"

/********************************************************
*	Triangle Class Functions							*
*********************************************************/
//Constructor
Triangle::Triangle(ColorInfo *colors, Vector3d point1, Vector3d point2, Vector3d point3, bool polyPatch, Vector3d normal1, Vector3d normal2, Vector3d normal3){
	this->colors = colors;
	this->polyPatch = polyPatch;
	this->points[0] = point1;
	this->points[1] = point2;
	this->points[2] = point3;
	this->normal[0] = normal1;
	this->normal[1] = normal2;
	this->normal[2] = normal3;
	
	for (int t = 0; t < 3; t++) {
		pointsI[t] = Vector3d(0, 0, 0);
	}
}

//Calculates intersection
hitRecord Triangle::intersect(rayPoint ray, double d, double d2) const {
	Matrix3d A;
	A << (points[0] - points[1]), (points[0] - points[2]), ray.direction;

	Matrix3d matx1;
	matx1 << (points[0] - ray.from), (points[0] - points[2]), (ray.direction);

	Matrix3d matx2;
	matx2 << (points[0] - points[1]), (points[0] - ray.from), ray.direction;

	Matrix3d matx3;
	matx3 << (points[0] - points[1]), (points[0] - points[2]), (points[0] - ray.from);

	
	double v[3];
	double determ = A.determinant(); //Get determinant of A
	v[0] = (matx1.determinant() / determ); //Beta
	v[1] = (matx2.determinant() / determ); //Gamma
	v[2] = (matx3.determinant() / determ); //t

	hitRecord hit(textureType::triangle, -1);

	if (v[2] > 0 && 0 <= v[0] && 0 <= v[1] && v[0] + v[1] <= 1) { //If valid beta, gamma, and t are valid
		double distince = (v[2] * ray.direction).norm();

		if (d <= distince && (distince <= d2 || d2 == -1)) {
			Vector3d point = ray.from + (v[2] * ray.direction);  //ray = e + (t*d)
			distince = (point - ray.from).norm(); //Distance to intersection
			hit = hitRecord(textureType::triangle, v[2], distince, point, v[0], v[1]);
		}
	}

	return hit;
}

//Getter
Vector3d Triangle::getNormal(hitRecord hit, bool interpolate) const {
    if (polyPatch && interpolate) {
	//if (polyPatch == false){ //Does not work
		 return (1.0 * points[0]) + (hit.beta * points[1]) + (hit.gamma * points[2]);
    }
    return (points[1] - points[0]).cross(points[2] - points[1]).normalized();
}