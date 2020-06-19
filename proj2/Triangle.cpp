/*****************************************************************
* File:		Triangle.cpp
* Project:	CMSC 435 Project 2, Spring 2019
* Author:	Daniel Roh
* Date:		02/25/19
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
Triangle::Triangle(Vector3d point1, Vector3d point2, Vector3d point3, bool polyPatch, Vector3d normal1, Vector3d normal2, Vector3d normal3){
	this->polyPatch = polyPatch;
	this->point1 = point1;
	this->point2 = point2;
	this->point3 = point3;
	this->normal1 = normal1;
	this->normal2 = normal2;
	this->normal3 = normal3;
}

//Calculates intersection
hitRecord Triangle::intersect(rayPoint ray, double d, double d2) const {
	Matrix3d A;
	A << (point1 - point2), (point1 - point3), ray.direction;

	Matrix3d matx1;
	matx1 << (point1 - ray.from), (point1 - point3), (ray.direction);

	Matrix3d matx2;
	matx2 << (point1 - point2), (point1 - ray.from), ray.direction;

	Matrix3d matx3;
	matx3 << (point1 - point2), (point1 - point3), (point1 - ray.from);

	
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
		 return (1.0 * normal1) + (hit.beta * normal2) + (hit.gamma * normal3);
    }
    return (point2 - point1).cross(point3 - point2).normalized();
}