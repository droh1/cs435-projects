/*****************************************************************
* File:		Starter.cpp
* Project:	CMSC 435 Project 3, Spring 2019
* Author:	Daniel Roh
* Date:		03/11/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This input is Starter.cpp
*	Functions: Act as the driver for the program
*****************************************************************/
#include <stdlib.h>
#include <iostream>
#include "Raster.h"
#include <stdio.h>
#include <string>
using namespace std;

//Start point
int main(void) {
	int input = 0;
	double trans = -1;
	string files;
	cout << "Welcome to rasteriser with GTX ON (Now with legacy rasters)" << endl;

	while (((input == 0) || (input != 1)) && ((input != 2))) { //Selecting test input
		cout << "1 - teapot-3.input" << endl;
		cout << "2 - refract.input" << endl;
		cout << "Which test would you like to run? (Please enter 1 or 2)" << endl;
		cin >> input;

		if (input != 1 && input != 2 && input != 3) { //Sorta repetitve but alerts input error
			cout << "Invalid input!!" << endl << endl;
			cin.clear(); //Protecton from Char input
			cin.ignore(1, '\n'); //Clear buffer
		}
	}

	while (((trans <= 1) && (trans >= 0)) == false) { //Selecting transparency
		cout << endl << "What transparency would you like to use? (Please enter a number from 0 - 1.00)" << endl;
		cin >> trans;

		if (((trans <= 1) && (trans >= 0)) == false) { //Sorta repetitve but alerts input error
			cout << "Invalid transparency!!" << endl << endl;
			cin.clear(); //Protecton from Char input
			cin.ignore(1, '\n'); //Clear buffer
		}
	}
	cout << endl; //Formatting
	cout << "----------------------" << endl; //Formatting

	switch (input) { //What did the user choose to run
	case 1:
		files = "teapot-3.nff";
		break;
	case 2:
		files = "refract.nff";
		break;
	default: //Should not be able to get to this part of the code
		cout << "how did you get here?" << endl;
		exit(1); //Kill program
	}

	/* //Project 1 starter
	Filehandle process = Filehandle();
	process.readFile(files); //Start Phase 1
	rayTrace run = rayTrace(process); //Run Phase 2
	run.render(); //Run Phase 3
	//ADD rayTace.h to run
	*/
	
	/*//Project 2 starter
	int bounces = 5; //Set bounce limit for reflections
	RayTrace run = RayTrace(files); //Start Phase 1
	cout << "Done reading" << endl; //DEBUG
	
	run.render(bounces); //Start Phase 2
	//Add rayTrace.h to run
	*/

	//Project 3 starter
	Raster rast = Raster(files, trans);

	//system("pause"); //DEBUG for VS17

	return 0;
}