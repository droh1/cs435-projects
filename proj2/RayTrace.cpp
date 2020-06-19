/*****************************************************************
* File:		RayTrace.cpp
* Project:	CMSC 435 Project 2, Spring 2019
* Author:	Daniel Roh
* Date:		02/25/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is RayTrace.cpp
*	Functions: Renders the image
*****************************************************************/
#include "RayTrace.h"

/********************************************************
*	RayTrace Class Functions							*
*********************************************************/
//Constructor
RayTrace::RayTrace(string filename) {
	input.readFile(filename);
}

//Renderer
void RayTrace::render(int bounces) {
	cout << endl << "Starting Render" << endl; //DEBUG

    Vector3d w = (input.from - input.at).normalized(); //Make world camera location
    Vector3d u = input.up.cross(w).normalized();
    Vector3d v = w.cross(u).normalized(); //Normalized for sanity

    double tempD = (input.at - input.from).norm();
    double offset = 2 * (tempD * tan(input.angle/2 * M_PI/180)) / input.resolution[0]; //FOR GL (change to radians)
	//double offset = 2 * (tempD * tan(input.angle / 2 * VI_PI / 180)) / input.resolution[0]; //For VS17 (change to radians)

    double initX = -(offset * ((input.resolution[0] / 2.0) - (1.0 / 2.0))); //Get camera location
    double initY = (offset * ((input.resolution[1] / 2.0) - (1.0 / 2.0)));

    const int yHeight = input.resolution[1]; //Size of image in y
    const int xWidth = input.resolution[0]; //Size of image in x
    unsigned char* pixels = new unsigned char[yHeight * xWidth * 3]; //Make array for all pixels

    /*Render pixels (starting at top left)*/
    for (int j = 0; j < yHeight; j++) { //X coordinates
		cout << "Rendering: (" << j+1 << "/" << input.resolution[0] << ")" << endl; //DEBUG

        for (int i = 0; i < xWidth; i++) { //Y coordinates
            double u_s = (initX + (offset * i));
            double v_s = (initY - (offset * j));
			double w_s = -(offset * input.resolution[0]); //This may not be correct?

            Vector3d position = (u_s * u) + (v_s * v) + (w_s * w) + input.from; //Calculate pixel location in world
            rayPoint ray = rayPoint(input.from, position-input.from);
            Vector3d color = trace(ray, input.hither, -1, bounces); //Get reflections

            for (int k = 0; k < 3; k++) {
				int temp = ((j * (xWidth * 3)) + (i * 3) + k); 
				color[k] = max(color[k], 0.0); //Clamp output range
				color[k] = min(color[k], 1.0);
				
                pixels[temp] = (color[k] * 255); //255 = 8-bit color
            }
        }
    }
	cout << ":::::::::RENDER COMPLETE:::::::::" << endl << endl; //DEBUG

    /*Code for saving file taken from project site*/
    FILE *f = fopen(output.c_str(), "wb");
    fprintf(f, "P6\n%d %d\n%d\n", xWidth, yHeight, 255);
    fwrite(pixels, 1, (yHeight * xWidth * 3), f);
    fclose(f);
    delete[] pixels;

    cout << "image written to " << output << endl; //DEBUG
}

//Reflections
Vector3d RayTrace::trace(rayPoint ray, double d, double d2, int bounces) {
    bool interpolate = false;
    hitRecord hit = getHitRecord(ray, d, d2);
    if (hit.textureIndex == -1) // no intersection
        return input.back;

    ColorInfo *colors = input.textures[hit.textureIndex]->colors; //Grab color info
    Vector3d localColor = Vector3d(0,0,0); 
    Vector3d V, N, H, L, R;
    V = (hit.point - ray.from).normalized();
    double intensity = 1.0 / sqrt(input.lights.size());

    for (unsigned int t = 0; t < input.lights.size(); t++) {
        Light light = input.lights[t];
        L = (light.position - hit.point).normalized(); //Light location from intersection

		if (getHitRecord(rayPoint(hit.point, L), SHADOW_BIAS, -1).distince != -1) { //If no shadows are cast
			continue; //Go to next
		}

        N = input.textures[hit.textureIndex]->getNormal(hit, interpolate); //Normal
        H = (L + V) / (L + V).norm(); //Bisecting angle between L and V
        R = (-V + (2 * (V.dot(N)) * N));  // reflection direction

        double diffuse = max(0.0, N.dot(L));
        double specular = pow(max(0.0, N.dot(H)), colors->shine); //One time that prof says to use POW

        for (int y = 0; y < 3; y++) {
			double temp = ((colors->diffuse * colors->color[y]) * diffuse);
			temp = temp + (colors->specular * specular);
			localColor[y] = localColor[y] + (temp * intensity);
        }
    }
    if ((bounces - 1) > 0) { //If theres a reflection
		Vector3d temp = trace(rayPoint(hit.point, R*-1), SHADOW_BIAS, d2, bounces - 1);
		temp = temp * colors->specular;
		localColor = temp + localColor;
    }
    return localColor;
}

//Get the hit
hitRecord RayTrace::getHitRecord(rayPoint ray, double d0, double d1) {
    hitRecord current(textureType::polygon, -1); //Set base hit

    for (unsigned int t = 0; t < input.textures.size(); t++) {
        hitRecord temp = input.textures[t]->intersect(ray, d0, d1); 

        if (temp.distince != -1 && (current.distince == -1 || temp.distince < current.distince)) { //If a closer hit or first hit is found
            current = temp; //Update hit
            current.textureIndex = t; //Location of hit
		}
		/* 
		if (temp.distince != -1) {//Does not work as intended
			if (current.distince == -1 || temp.distince < current.distince)) {
				current = temp; //Update hit
				current.textureIndex = t; //Location of hit
			}
		}*/
		//input.textures[i]->colors->printMe(); //DEBUG
    }
    return current;
}
