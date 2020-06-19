/*****************************************************************
* File:		Raster.h
* Project:	CMSC 435 Project 3, Spring 2019
* Author:	Daniel Roh
* Date:		03/11/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is Raster.h
*	Functions: Header file for Raster functions
*****************************************************************/
#ifndef _RASTER_H_
#define _RASTER_H_

#include "Filehandle.h"
#include "Texture.h"
#include <iostream>
#include <math.h>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

class Info {
	public:
		double right, left, top, bottom, close, far, fov;
		
		Vector3d from;
		Vector3d w;
		Vector3d u;
		Vector3d v;
};

class Fragments {
	public:
		double depth;

		Vector3d color;
		Vector3d normals;
		Vector3d world;

		Fragments *next; //Linked list;
};

class Raster {
	public:
		Raster(string in, double trans);
		void render();
		
	private:
		Matrix4d makeMatrix();
		Vector3d shade(Triangle &tempT, int points);
		Fragments *getFragments(int x, int y, Triangle &tri);

		void vertexProcess(Matrix4d tempM); //Pipeline pt1
		void rastering(Fragments ***frag); //Pipeline pt2
		void fragmentsProcess(Fragments ***frag); //Pipeline pt3
		void blend(unsigned char *pexel, Fragments ***frag); //Pipeline pt4

		Filehandle input;
		vector<Triangle> triangles;
		Info scene;

		bool trans;
		double alpha; 
		const double SHADOW_BIAS = 0.000001; //Shadow Bias variable
		const double VI_PI = 3.14159265359; //For VS17
		string output = "output.ppm"; //Output input name
};
#endif