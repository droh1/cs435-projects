/*****************************************************************
* File:		Sphere.h
* Project:	CMSC 435 Project 2, Spring 2019
* Author:	Daniel Roh
* Date:		02/25/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is Sphere.h
*	Functions: Header for Sphere's
*****************************************************************/
#ifndef _SPHERE_H_
#define  _SPHERE_H_

#include "rayPoint.h"
#include "Texture.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

/*********************************
*	Sphere Class Headers		 *
**********************************/
class Sphere : public Texture {
    public:
		Sphere(Vector3d center, double radius, ColorInfo *colors);
        hitRecord intersect(rayPoint ray, double d = 0, double d2 = -1) const;
        Vector3d getNormal(hitRecord hit, bool interpolate=false) const;

     private:
		double radius;
        Vector3d center;
};
#endif