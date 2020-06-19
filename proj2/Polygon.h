/*****************************************************************
* File:		Polygon.h
* Project:	CMSC 435 Project 2, Spring 2019
* Author:	Daniel Roh
* Date:		02/25/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is Polygon.h
*	Functions: Header file for polygons
*****************************************************************/
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "rayPoint.h"
#include "Triangle.h"
#include "Texture.h"
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

//Class Prototype
class hitRecord;
class ColorInfo;

/*********************************
*	Polygon Class Headers		 *
**********************************/
class Polygon : public Texture {
    public:
        Polygon(vector<Vector3d> edges, vector<Vector3d> normals, ColorInfo *colors, bool polyPatch = false);
        hitRecord intersect(rayPoint ray, double d = 0, double d2 = -1) const;
        Vector3d getNormal(hitRecord hit, bool interpolate=false) const;

    protected:
		bool polyPatch;
		vector<Vector3d> edges; 
        vector<Triangle> triangles;
        vector<Vector3d> normals;   //Normals for Polygon patch
};
#endif
