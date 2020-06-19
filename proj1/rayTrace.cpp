/*****************************************************************
* File:		rayTrace.cpp
* Project:	CMSC 435 Project 1, Spring 2019
* Author:	Daniel Roh
* Date:		02/09/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is rayTrace.cpp
*	Functions: Handles the ray tracing and image rendering 
*****************************************************************/
#include "rayTrace.h"

//Constuctor
rayTrace::rayTrace(Filehandle input) {
	this->input = input;
}

//Ray Handler
vector<double> rayTrace::fireRay(rayPoint ray) {
	int distence = -1; //Distince to intersect 
	int closest = -1; //Location of closests poly

	for (unsigned int t = 0; t < input.textures.size(); t++) {
		int res = input.textures[t]->intersect(ray, input.hither); //See if a intersection occured

		if (res != -1) { //If a close object is hit
			if (distence == -1 || res < distence) { //If a closer object is found
				closest = t; //Set var
				distence = res;
			}
		}
	}

	if (distence != -1) { //If a object is hit
		return input.textures[closest]->color; //Return color info
	}
	return input.back; //If missed, return backgruond color info
}

//Render
void rayTrace::render() {
	cout << endl << "Starting render" << endl; //DEBUG

	Vector3d w = (input.from - input.at).normalized(); //Make world camera location
	Vector3d u = input.up.cross(w).normalized();
	Vector3d v = w.cross(u).normalized(); //Normalize for sanity 
	/*Note to self: w.normalized is not the same as (input.from - input.at).normalized() */

	Vector3d tempD = (input.at - input.from); //Find the distince from image
	double distince = sqrt((tempD[0] * tempD[0]) + (tempD[1] * tempD[1]) + (tempD[2] * tempD[2])); //This should be right
	//double distince = (input.at - input.from).norm(); //This is wrong
	
	double offset = tan((input.angle / 2.0) * (M_PI / 180.0)); //Change to radians (FOR GL)
	//double offset = tan((input.angle / 2.0) * (PI / 180.0)); //Change to radians (FOR VS17)

	offset = distince * offset;
	offset = 2 * offset / input.res[0]; //Off set of each pixel (width)
	
	double locX = -(offset * ((input.res[0] / 2.0) - (1.0 / 2.0))); //Get locaton for camera
	double locY = (offset * ((input.res[1] / 2.0)- (1.0 / 2.0)));

	const int yHight = input.res[1]; //Size of image in y
	const int xWidth = input.res[0]; //Size of image in x
	unsigned char* pixels = new unsigned char[yHight * xWidth * 3]; //Make array for all pixels

	/*Render pixels (starts at top left corner)*/
	for (int j = 0; j < yHight; j++) {  //X coordinates
		cout << "Rendering Row (" << (j + 1) << "/" << yHight << ")" << endl; //DEBUG

		for (int i = 0; i < xWidth; i++) { //Y coordinates
			double u_s = (locX + (offset * i)); 
			double v_s = (locY - (offset * j));
			double w_s = -(offset * input.res[0]); //Problem with distince is here? Should w be just hither?

			Vector3d position = (u_s * u) + (v_s * v) + (w_s * w) + input.from; //Calculate pixel location in world
			rayPoint ray = rayPoint(input.from, (position - input.from)); //Make ray from camera
			vector<double> color = fireRay(ray); //Get color values from ray

			for (int k = 0; k < 3; k++) { //Set color of each RGB pixel 
				int temp = ((j * (xWidth * 3)) + (i * 3) + k);
					
				pixels[temp] = (color[k] * 255); //255 = 8-bit color
			}
		}
	}

	/*Code for saving file taken from project site*/
	FILE *f = fopen("output.ppm", "wb");
	fprintf(f, "P6\n%d %d\n%d\n", xWidth, yHight, 255);
	fwrite(pixels, 1, xWidth * yHight * 3, f);
	fclose(f);
	cout << "Image saved to: " << out << endl; //DEBUG
	
	delete[] pixels;
}