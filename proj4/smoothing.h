#ifndef SMOOTHING_H
#define SMOOTHING_H

#include "io.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <Eigen/Dense>
#include "LinearSolver/cghs.h"
using namespace Eigen;
using namespace std;

struct Operator { //Struct taken from implicit.cpp
		int n;
		double lambda, dt;
		std::vector<Tri> tris;
	};

class Smoothing {
	public:
		Smoothing(char *input, char *output); //Constructor
		~Smoothing() {}; //Distructor
		void smooth(double lambda, double dT, int iter);

	private:
		char *input;
		char *output;
};

#endif