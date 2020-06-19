/*****************************************************************
* File:		Sphere.cpp
* Project:	CMSC 435 Project 2, Spring 2019
* Author:	Daniel Roh
* Date:		02/25/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is Sphere.cpp
*	Functions: Functions for sphere objects
*****************************************************************/

#include "Sphere.h"

/********************************************************
*	Sphere Class Functions								*
*********************************************************/
//Constructor
Sphere::Sphere(Vector3d center, double radius, ColorInfo *colors){
	this->colors = colors;
	this->center = center;
	this->radius = radius;
	}

//Calculates intersect
hitRecord Sphere::intersect(rayPoint ray, double d, double d2) const {
    hitRecord hit(textureType::sphere, -1);
    Vector3d diff = ray.from - center;
	double hitCheck = ((ray.direction.dot(diff) * ray.direction.dot(diff)) - ray.direction.dot(ray.direction) * diff.dot(diff) - (radius * radius));

    if (hitCheck < 0) { //If no intersection is made
        return hit;
    }

    double numerator = (-1 * ray.direction).dot(diff); //Numerator
    double denominator = ray.direction.dot(ray.direction); //Denominator

    if (hitCheck == 0) { //Ray hits sphere at one point
        hit.intersection = numerator / denominator;
    }
    else { //If ray hits the sphere at two points (enters and exits)
        double t1 = (numerator - sqrt(hitCheck)) / denominator; //Small Solution
        //double t2 = (numerator + sqrt(hitCheck)) / denominator; //Large Solution

        hit.intersection = t1;
    }

    hit.point = ray.from + hit.intersection * ray.direction; //Point of intersection
    hit.distince = (hit.point - ray.from).norm(); //Calculates distance of intersection from eye

    if (! (d <= hit.distince && (hit.distince <= d2 || d2 == -1))) { //Checks if distance is in render range
        hit.intersection = -1;
        hit.distince = -1;
    }
    return hit;
}

//Getter
Vector3d Sphere::getNormal(hitRecord hit, bool interpolate) const {
    return (hit.point - center);
}