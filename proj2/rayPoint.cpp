/*****************************************************************
* File:		rayPoint.cpp
* Project:	CMSC 435 Project 2, Spring 2019
* Author:	Daniel Roh
* Date:		02/25/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is rayPoint.cpp
*	Functions: Make ray and hit record objects
*****************************************************************/
#include "rayPoint.h"

/********************************************************
*	rayPoint Class Functions							*
*********************************************************/
//Constructor
rayPoint::rayPoint(Vector3d from, Vector3d direction){
	this->from = from;
	this->direction = direction;
}

/********************************************************
*	hitRecord Class Functions							*
*********************************************************/
//Constructor
hitRecord::hitRecord(textureType type, double intersection, double distince, Vector3d point, double beta, double gamma, double triangleIndex, double textureIndex){
	this->type = type;
	this->intersection = intersection;
	this->distince = distince;
	this->point = point;
	this->beta = beta;
	this->gamma = gamma;
	this->triangleIndex = triangleIndex;
	this->textureIndex = textureIndex;
}
