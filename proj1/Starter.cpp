/*****************************************************************
* File:		Starter.cpp
* Project:	CMSC 435 Project 1, Spring 2019
* Author:	Daniel Roh
* Date:		02/09/19
* Section:	
* E-mail:	droh1@umbc.edu
*
*	This file is Starter.cpp
*	Functions: Act as the driver for the program
*****************************************************************/
#include "rayTrace.h"
#include "Filehandle.h"
#include <stdio.h>
#include <string>
using namespace std;

//Start point
int main(void) {
	int input = 0;
	string files;
	cout << "Welcome to ray tracer with RTX ON" << endl;

	while (((input == 0) || (input != 1)) && ((input != 2) && (input != 3))) { //Selecting test file
		cout << "1 - tetra-3.nff" << endl;
		cout << "2 - gears.nff" << endl;
		cout << "3 - balls.nff" << endl;
		cout << "Which test would you like to run? (Please enter 1, 2, or 3)" << endl;
		cin >> input;

		if (input != 1 && input != 2 && input != 3) { //Sorta repetitve but alerts input error
			cout << "Invalid input!!" << endl << endl;
			cin.clear(); //Protecton from Char input
			cin.ignore(1, '\n'); //Clear buffer
		}
	}

	switch (input) { //What did the user choose to run
	case 1:
		files = "tetra-3.nff";
		break;
	case 2:
		files = "gears.nff";
		break;
	case 3:
		files = "balls.nff";
		break;
	default: //Should not be able to get to this part of the code
		cout << "how did you get here?" << endl;
		exit(1); //Kill program
	}

	Filehandle process = Filehandle(); 
	process.readFile(files); //Start Phase 1
	cout << "Done reading" << endl; //DEBUG
	rayTrace run = rayTrace(process); //Run Phase 2
	run.render(); //Run Phase 3

	cout << endl << endl << "Render Completed" << endl; //Alert user that program has finised
	//system("pause"); //DEBUG for VS17
	return 0;
}