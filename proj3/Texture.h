/*****************************************************************
* File:		Texture.h
* Project:	CMSC 435 Project 3, Spring 2019
* Author:	Daniel Roh
* Date:		03/11/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is Texture.h
*	Functions: Header file for Texture's
*****************************************************************/
#ifndef _TEXTURES_H_
#define _TEXTURES_H_

#include "rayPoint.h"
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

//Class Prototype
class hitRecord;
class ColorInfo;

/*********************************
*	Texture Class	Headers		 *
**********************************/
class Texture {
    friend class RayTrace;
	friend class Raster;

    public:
		Texture() {};
		Texture(ColorInfo *colors);
        virtual ~Texture() {} 
        virtual hitRecord intersect(rayPoint ray, double d = 0, double d2 = -1) const = 0;
        virtual Vector3d getNormal(hitRecord hit, bool interpolate=false) const = 0;

     protected:
        ColorInfo *colors;	//Pointer to ColorInfo class for this texture info
};
#endif
