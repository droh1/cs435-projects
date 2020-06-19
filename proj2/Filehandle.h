/*****************************************************************
* File:		Filehandle.h
* Project:	CMSC 435 Project 2, Spring 2019
* Author:	Daniel Roh
* Date:		02/25/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is Filehandle.h
*	Functions: Header file
*****************************************************************/
#ifndef _FILEHANDLE_H_
#define _FILEHANDLE_H_

#include "Texture.h"
#include "Polygon.h"
#include "Sphere.h"
#include <stdlib.h>
#include <string>
#include <iterator>
#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

/*********************************
*	colorInfo Class	Headers		 *
**********************************/
class ColorInfo {
    friend class Filehandle;
    friend class RayTrace;
	public:
		void printMe(); //DEBUG

    private:
        Vector3d color;
        double diffuse;
        double specular;
        double shine;
        double T;
		double refract; 
};

/*********************************
*	Light Class	Headers			 *
**********************************/
class Light {
    friend class Filehandle;
    friend class RayTrace;
    public:
		Light(Vector3d position, Vector3d color = Vector3d(1, 1, 1));

    private:
        Vector3d color;
        Vector3d position;
};

/*********************************
*	Filehandle Class Headers	 *
**********************************/
class Filehandle {
    friend class RayTrace;
    public:
        Filehandle();
        ~Filehandle();
        void readFile(string file);

    private:
        double angle;
        double hither;

        Vector3d back;
        Vector3d from;
        Vector3d at;
        Vector3d up;

		vector<int> resolution{0, 0};
        vector<Texture*> textures; 
        vector<ColorInfo*> info;
        vector<Light> lights;
};
#endif
