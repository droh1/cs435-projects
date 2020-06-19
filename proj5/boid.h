/*****************************************************************
* File:		boid.h
* Project:	CMSC 435 Project 5, Spring 2019
* Author:	Daniel Roh
* Date:		05/01/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is boid.h
*	Functions: Header file for boid
*****************************************************************/
#ifndef _BOID_H_
#define _BOID_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

//Globals
const double MAX_FORCE = 10;
const double MAX_VELOCITY = 0.1 * MAX_FORCE;
const Vector3d boxMin(-0.5, -0.30, -0.125); //Bounding box
const Vector3d boxMax(0.5, 0.30, 0.125);

//Prototypes
class Fish;

//Struct for food 
struct Food {
	double time; //Starting time for food

	Vector3d position;
	Vector3d velocity;
};

/**************************
*  Boid Class
***************************/
class Boid {
	friend class Fish;
public:
	Boid(Vector3d position = Vector3d(0, 0, 0), Vector3d velocity = Vector3d(0, 0, 0));

private:
	double sizeF; //Size of boid (not supported by viewer)

	Vector3d position;     
	Vector3d velocity; 
	vector<int> near; //The birds that are near the current bird
	Vector3d force;
};

/**************************
*  Fish Class
***************************/
class Fish {
public:
	Fish(string filename);
	void readFile(string filename);
	void writeOutput(ofstream& output, double timeStep);
	void simulate();
	void computeForces(double time);
	void computeFood(double time);
	void readLines(ifstream &f, string &line);

private:
	double sizeB; 
	double sight;	
	double maxNear;	
	double wight; 
	double wCollision;
	double wCentering; 
	double wVelocity;  
	double hunger;		
	double damping;     
	double timeStep;    //Timestep size (should be 1/30 of a sec)
	double duration;    //Length of animation (seconds)

	vector<Boid> boids; //all boids in simulation
	vector<Food> meal;  //all food in simulation
};
#endif