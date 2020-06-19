/*****************************************************************
* File:		rayPoint.cpp
* Project:	CMSC 435 Project 1, Spring 2019
* Author:	Daniel Roh
* Date:		02/09/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is rayPoint.cpp
*	Functions: Simple class to create rayPoint objects
*****************************************************************/
#include "rayPoint.h"

//Constructor
rayPoint::rayPoint(Vector3d from, Vector3d direction) {
	this->from = from;
	this->direction = direction;
}
