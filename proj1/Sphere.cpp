/*****************************************************************
* File:		Sphere.cpp
* Project:	CMSC 435 Project 1, Spring 2019
* Author:	Daniel Roh
* Date:		02/09/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	Functions: Class for holding data of Sphere opbjects
*****************************************************************/
#include "Sphere.h"

//Constructor
Sphere::Sphere(Vector3d center, double radius, vector<double> color) {
	this->color = color;
	this->center = center;
	this->radius = radius;
}

//Virutal Texture Function
double Sphere::intersect(rayPoint ray, double hither) const {
	Vector3d diff = ray.from;// -center;
	double hitCheck = ((ray.direction.dot(diff) * ray.direction.dot(diff)) - ray.direction.dot(ray.direction) * diff.dot(diff) - (radius * radius));

	if (hitCheck < 0) { //No intersection is made
		return -1; 
	}

	double numerator = (-1 * ray.direction).dot(diff); //Numerator
	double denominator = ray.direction.dot(ray.direction); //Denominator

	if (hitCheck == 0) { //Ray hits sphere at one point
		return (numerator / denominator);
	}
	else {//If the ray hit the sphere and exits the sphere
		double temp = (numerator - sqrt(hitCheck)) / denominator; //Small Solution
		//double t2 = (numerator + sqrt(hitCheck)) / denominator; //Large solution								  
		double realDist = (temp * ray.direction).norm(); //Calculate distince of intersection from eye

		if (hither != -1 && realDist < hither) { //Check if distence is in render range
			return -1; //Image is too far or too close
		}
		return temp;
	}
}