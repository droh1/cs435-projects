/*****************************************************************
* File:		Polygon.h
* Project:	CMSC 435 Project 1, Spring 2019
* Author:	Daniel Roh
* Date:		02/09/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	Functions: Header for Polygon.cpp
*****************************************************************/
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "rayPoint.h"
#include "Triangle.h"
#include "texture.h"
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

class Polygon : public texture{
public:
	Polygon(vector<Vector3d> edges, vector<double> color = vector<double>{0, 0, 0, 0, 0, 0, 0, 0});
	vector<Triangle> getTriangles() const;
	void setEdges(vector<Vector3d> vertices);
	double intersect(rayPoint ray, double hither = -1) const; //Virtual

private:
	vector<Triangle> triangles; // triangle fan for this polygon
	vector<Vector3d> vertices;  // vertices of triangle in 3D space
};
#endif
