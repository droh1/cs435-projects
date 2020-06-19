/*****************************************************************
* File:		Triangle.h
* Project:	CMSC 435 Project 2, Spring 2019
* Author:	Daniel Roh
* Date:		02/25/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is Triangle.h
*	Functions: Header file for Triangle's
*****************************************************************/
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "rayPoint.h"
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

//Class Prototype
class hitRecord;
class ColorInfo;

/*********************************
*	colorInfo Class	Headers		 *
**********************************/
class Triangle {
    public:
		Triangle(Vector3d point1, Vector3d point2, Vector3d point3, bool polyPatch = false, Vector3d normal1 = Vector3d(0, 0, 0), Vector3d normal2 = Vector3d(0, 0, 0), Vector3d normal3 = Vector3d(0, 0, 0));
		hitRecord intersect(rayPoint ray, double d = 0, double d2 = -1) const;
        Vector3d getNormal(hitRecord hit, bool interpolate = false) const;

   private:
        bool polyPatch; //If its a polygon patch (false = p, true = pp)
		Vector3d point1, point2, point3;
        Vector3d normal1, normal2, normal3;
};
#endif