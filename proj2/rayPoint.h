/*****************************************************************
* File:		rayPoint.h
* Project:	CMSC 435 Project 2, Spring 2019
* Author:	Daniel Roh
* Date:		02/25/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is rayPoint.h
*	Functions: Header for rayPoint.cpp
*****************************************************************/
#ifndef _RAYPOINT_H_
#define _RAYPOINT_H_

#include <iostream>
#include <Eigen/Dense>

enum class textureType {polygon, triangle, sphere, polypatch};
using namespace Eigen;
using namespace std;


/*********************************
*	rayPoint Class Headers		 *
**********************************/
class rayPoint {
    public:
		rayPoint(Vector3d from, Vector3d direction);

        Vector3d from;
        Vector3d direction;
};

/*********************************
*	hitRecord Class	Headers		 *
**********************************/
class hitRecord {
    public:
		hitRecord(textureType type, double intersection, double distince = -1, Vector3d point = Vector3d(0, 0, 0), double beta = 0, double gamma = 0, double triangleIndex = -1, double textureIndex = -1);

		int triangleIndex;
        int textureIndex;
        double intersection;
        double distince;
        double beta; 
        double gamma;

		Vector3d point;
        textureType type; //enum texture
};
#endif