/*****************************************************************
* File:		RayTrace.h
* Project:	CMSC 435 Project 2, Spring 2019
* Author:	Daniel Roh
* Date:		02/25/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is RayTrace.h
*	Functions: Header file
*****************************************************************/
#ifndef _RAYTRACE_H_
#define _RAYTRACE_H_

/* 
//Defines for VS17 compiler to stop yelling about fopen

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
*/

#include "Filehandle.h"
#include "rayPoint.h"
#include "Texture.h"
#include "Polygon.h"
#include "Triangle.h"
#include <iostream>
#include <fstream>
#include <vector>
#include<math.h>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

//Class Prototype
class Filehandle; 

/*********************************
*	RayTrace Class	Headers		 *
**********************************/
class RayTrace {
    public:
        RayTrace(string filename);
        void render(int bounces);

    private:
        Filehandle input;
        Vector3d trace(rayPoint ray, double d, double d2, int bounces = 0);
        hitRecord getHitRecord(rayPoint ray, double d, double d2);

		const double SHADOW_BIAS = 0.000001; //Shadow Bias variable
		const double VI_PI = 3.14159265359; //For VS17
		string output = "output.ppm"; //Output file name
};
#endif
