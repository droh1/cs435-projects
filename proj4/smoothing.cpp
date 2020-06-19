/*****************************************************************
* File:		Filehandle.cpp
* Project:	CMSC 435 Project 4, Spring 2019
* Author:	Daniel Roh
* Date:		04/15/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is smoothing.cpp
*	For project 4 regarding smoothing a obj model
*****************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <Eigen/Dense>
#include "io.h"
#include "cghs.h"
using namespace Eigen;
using namespace std;

struct Operator { //Struct taken from implicit.cpp
	int n;
	double lambda, dt;
	std::vector<Tri> tris;
};

/*************************
*	Function Prototypes	 *
**************************/
void smooth(double lambda, double dT, int iter);
void implicitSmooth(double lambda, double dT, double eps);
void mult(const Operator &op, double *v, double *w);
vector<Vector3d> laplacian(const vector<Vector3d> &points, const vector<Tri> &triangle);

/*************************
*	Globals Variables	 *
**************************/
char *input, *output;

 /********************************************************
 *	Smoothing function using Laplacing smoothing		 *
 *********************************************************/
void smooth(double lambda, double dT, int iter){
	vector<double> temp;
	vector<Vector3d> points;
	vector<Vector3d> smooth;
	vector<Tri> triangle;

	bool test = readObjFile(input, points, triangle); //Read in file
	if (test == false) { //If the file was not read properlly 
		cout << "Error reading obj file " << input << endl;
		cout << "Termiating Program" << endl;
		exit(1); //Kill program
	}

	for (int i = 0; i < iter; i++) { //Run smoothing I times
		//cout << "Smoothing " << i + 1 << endl; //DEBUG

		for (unsigned int u = 0; u < points.size(); u++) { //Initialize smoothing Vector
			smooth.push_back(Vector3d(0.0, 0.0, 0.0));
			temp.push_back(0);
		}

		for (unsigned int y = 0; y < triangle.size(); y++) { 
			Tri &tTemp = triangle[y];

			for (int t = 0; t < 3; t++) { //Get the things needed for lapacian
				int j = (t + 1) % 3;
				int k = (t + 2) % 3;
				smooth[tTemp.indices[t]] = smooth[tTemp.indices[t]] + points[tTemp.indices[j]] + points[tTemp.indices[k]] - (2 * points[tTemp.indices[t]]);
				temp[tTemp.indices[t]] = temp[tTemp.indices[t]] + 2;
			}
		}

		for (unsigned int t = 0; t < points.size(); t++) { //Find the lapacian 
			points[t] = points[t] + lambda * dT * (smooth[t] / temp[t]);
		}
	}
	cout << "Smoothing complete" << endl; //DEBUG

	writeObjFile(output, points, triangle);
	cout << "File written too " << output << endl; //DEBUG
}

/********************************************************
*	Laplacian function used by implicit smoothing		*
*********************************************************/
vector<Vector3d> laplacian(const vector<Vector3d>& points, const vector<Tri>& triangle){
	vector<Vector3d> laplacian;

	for (unsigned int i = 0; i < points.size(); i++) { //Initilize vector
		laplacian.push_back(Vector3d(0.0, 0.0, 0.0));
	}

	for (unsigned int i = 0; i < triangle.size(); i++) { //Go over triangles
		const Tri &tTemp = triangle[i];

		for (int t = 0; t < 3; t++) { //Get the things needed for lapacian except M
			int j = (t + 1) % 3;
			int k = (t + 2) % 3;
			laplacian[tTemp.indices[t]] = laplacian[tTemp.indices[t]] + points[tTemp.indices[j]] + points[tTemp.indices[k]] - (2 * points[tTemp.indices[t]]);
		}
	}

	return laplacian;
}

/********************************************************
*	Funtions below are for Implicit Smoothing.			*
*	Funtions taken from implicit.cpp on project website *
*	and modified for use								*
*********************************************************/

/********************************************************
*	Implicit smoothing method taken from implicit.cpp	*
*********************************************************/
void implicitSmooth(double lambda, double dT, double eps) {
	Operator op;
	vector<Vector3d> points; //Vector for mesh points

	bool test = readObjFile(input, points, op.tris); //Read in the file
	if (test == false) { //If the file was not read properlly 
		cout << "Error reading obj file " << input << endl;
		cout << "Termiating Program" << endl;
		exit(1); //Kill program
	}

	op.n = points.size();
	op.lambda = lambda;
	op.dt = dT;

	double *b = new double[3 * points.size()];
	double *x = new double[3 * points.size()];
	//double b[3 * points.size()]; //Compiler does not like variable size
	//double x[3 * points.size()];

	for (unsigned int i = 0; i < points.size(); i++) {
		b[3 * i + 0] = points[i][0];
		b[3 * i + 1] = points[i][1];
		b[3 * i + 2] = points[i][2];

		x[3 * i + 0] = points[i][0];
		x[3 * i + 1] = points[i][1];
		x[3 * i + 2] = points[i][2];
	}

	cghs<Operator>(3 * points.size(), op, b, x, eps, true); 

	for (unsigned int i = 0; i < points.size(); i++) {
		points[i] = Vector3d(x[3 * i + 0], x[3 * i + 1], x[3 * i + 2]);
	}
	cout << "Smoothing complete" << endl; //DEBUG

	writeObjFile(output, points, op.tris);
	cout << "File written to " << output << endl; //DEBUG

	delete[] b;
	delete[] x;
}

/********************************************************
*	Mult function used in Implicit smoothing,			*
*	taken from implicit.cpp								*
*********************************************************/
void mult(const Operator &op, double *v, double *w){
	std::vector<Vector3d> points;
	points.resize(op.n);
	
	for (unsigned int i = 0; i < points.size(); i++) {
		points[i] = Vector3d(v[3 * i + 0], v[3 * i + 1], v[3 * i + 2]);
	}

	std::vector<Vector3d> l = laplacian(points, op.tris);
	
	for (unsigned int i = 0; i < points.size(); i++) {
		l[i] *= op.lambda*op.dt;
		w[3 * i + 0] = v[3 * i + 0] - l[i][0];
		w[3 * i + 1] = v[3 * i + 1] - l[i][1];
		w[3 * i + 2] = v[3 * i + 2] - l[i][2];
	}
}

/********************************************************
*	Starting point of the program						*
*********************************************************/
int main(int argc, char *argv[]) {
	int iter;
	double lambda, dT;
	double eps = 0;
	string mode;
	//Note: input and output are globals

	if (argc == 6) { //If lapacian smoothing is requested
		input = argv[1];
		output = argv[2];
		sscanf(argv[3], "%lf", &lambda);
		sscanf(argv[4], "%lf", &dT);
		sscanf(argv[5], "%d", &iter);

		cout << "Starting lapacian smoothing" << endl; //DEBUG
		smooth(lambda, dT, iter);
	}
	else if (argc == 8) { //If smoothing using a mode is requested
		input = argv[1];
		output = argv[2];
		mode = argv[3];
		sscanf(argv[4], "%lf", &eps);
		sscanf(argv[5], "%lf", &lambda);
		sscanf(argv[6], "%lf", &dT);
		sscanf(argv[7], "%d", &iter);

		if(mode == "-i") {
			cout << "Starting implcit smoothing" << endl; //DEBUG
			implicitSmooth(lambda, dT, eps);
		}
		else if (mode == "-c") {
			cout << "Starting smoothing with cotangent weights" << endl; //DEBUG
			//To Do
		}
		else if (mode == "-v") {
			cout << "Starting smoothing with gloabl volume" << endl; // DEBUG
			//To Do
		}
		else if (mode == "-b") {
			cout << "Starting smoothing with biharmonic operatior" << endl; //DEBUG
			//To Do
		}
		else if (mode == "-s") {
			cout << "Starting smoothing with loop subdivision" << endl; //DEBUG
			//To Do
		}
		else {
			cout << "Unexpected running mode" << endl;
			exit(1);
		}
	}
	else { //If input was wrong
		cout << "Expected 6 or 8 arguments\n"; //DEBUG
		exit(1); //Kill program
	}

	return 0;
}
