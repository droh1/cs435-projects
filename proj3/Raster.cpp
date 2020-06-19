/*****************************************************************
* File:		Raster.cpp
* Project:	CMSC 435 Project 3, Spring 2019
* Author:	Daniel Roh
* Date:		03/11/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is Raster.cpp
*	Functions: Contains the code for Raster functions
*****************************************************************/
#include "Raster.h"

/********************************************************
*	Raster Constructor									*
*********************************************************/
Raster::Raster(string in, double trans) {
	input.readFile(in); //Go to filehandle.cpp to read file

	/*Flipped values up, right to make image the correct orintation*/
	input.up = -input.up; //Flip image
	scene.from = input.from;
	scene.w = (input.from - input.at).normalized();
	scene.u = input.up.cross(scene.w).normalized();
	scene.v = scene.w.cross(scene.u).normalized();
	scene.fov = tan((input.angle / 2.0) * (M_PI / 180.0)); //For GL (Convert to radians)
	//scenefov = tan((input.angle / 2.0) * (VI_PI / 180.0)); //For VS17 (Convert to radians)
	scene.right = -scene.fov;
	scene.left = scene.fov;
	scene.top = scene.fov / ((input.resolution[0] / input.resolution[1]));
	scene.bottom = -scene.fov / ((input.resolution[0] / input.resolution[1]));
	scene.close = -input.hither;
	scene.far = -1000 * input.hither;
	alpha = trans;

	if (trans == 1) { //Set if transparency is used
		this->trans = false;
	}
	else {
		this->trans = true;
	}

	render(); //Start render
}

/********************************************************
*	render Class Function								*
*********************************************************/
void Raster::render() {
	cout << "Starting render" << endl; //DEBUG

	const int yHeight = input.resolution[1]; //Size of image in Y
	const int xWidth = input.resolution[0]; //Size of image in X
	unsigned char* pixels = new unsigned char[yHeight * xWidth * 3]; //Make array for all pixels

	Fragments ***frag = new Fragments**[yHeight];
	for (int y = 0; y < yHeight; y++) {
		frag[y] = new Fragments*[xWidth];

		for (int x = 0; x < xWidth; x++) {
			frag[y][x] = NULL; //Set all fragments to null 
		}
	}

	Matrix4d temp = makeMatrix();
	vertexProcess(temp); //Pipeline pt1
	rastering(frag); //Pipeline pt2
	fragmentsProcess(frag); //Pipeline pt3
	blend(pixels, frag); //Pipeline pt4
	
	cout << "Render Completed" << endl << endl; //DEBUG

	/*Code for saving input taken from project site*/
	FILE *f = fopen(output.c_str(), "wb");
	fprintf(f, "P6\n%d %d\n%d\n", xWidth, yHeight, 255);
	fwrite(pixels, 1, (yHeight * xWidth * 3), f);
	fclose(f);
	delete[] pixels;

	cout << "image written to " << output << endl << endl; //DEBUG

	/*Delete Linked List*/
	Fragments *cur, *next; 
	for (int y = 0; y<yHeight; y++) {
		for (int x = 0; x<xWidth; x++) {
			cur = frag[y][x];

			if (cur == NULL) { //If the list is 
				continue;
			}

			while (cur != NULL) {
				next = cur->next;
				delete cur;
				cur = next;
			}
		}
	}
}

/********************************************************
*	makeMatrix Class Function							*
*********************************************************/
Matrix4d Raster::makeMatrix() {
	int resX = input.resolution[0];
	int resY = input.resolution[1];

	Matrix4d viewPort; //View port matrix
	viewPort << (resX / 2.0),			 0, 0, ((resX - 1) / 2.0),
						   0, (resY / 2.0), 0, ((resY - 1) / 2.0),
						   0,			 0, 1,					0,
						   0,			 0, 0,					1;

	Matrix4d perspective; //Prespective matrix
	perspective << ((2.0 * scene.close) / (scene.right - scene.left)), 0, ((scene.left + scene.right) / (scene.left - scene.right)), 0,
					0, ((2.0 * scene.close) / (scene.top - scene.bottom)), ((scene.bottom + scene.top) / (scene.bottom - scene.top)), 0,
					0, 0, ((scene.far + scene.close) / (scene.close - scene.far)), ((2.0 * scene.far * scene.close) / (scene.far - scene.close)),
					0, 0, 1, 0;

	MatrixXd camera;
	camera.resize(3, 4);
	camera << scene.u, scene.v, scene.w, scene.from;
	camera.conservativeResize(4, 4);
	camera.row(3) = Vector4d(0, 0, 0, 1);
	camera = camera.inverse();

	Matrix4d tempM = viewPort * perspective * camera;

	return tempM;
}

/********************************************************
*	shade Class Function								*
*********************************************************/
Vector3d Raster::shade(Triangle &tempT, int points) {
	Vector3d localColor = Vector3d(0, 0, 0);
	Vector3d point = tempT.points[points];
	Vector3d V, N, H, L, R;

	V = (point - scene.from).normalized();
	double intensity = 1.0 / sqrt(input.lights.size());

	for (unsigned int t = 0; t < input.lights.size(); t++) { //For all lights
		Light light = input.lights[t];
		
		L = (light.position - point).normalized(); //Get the direction of the light

		if (tempT.polyPatch) { //If this is a polypatch
			N = tempT.normal[points];
		}
		else { //If its a normal polygon
			N = tempT.getNormal(hitRecord(textureType::polygon, -1));
		}
		H = (L + V) / (L + V).norm(); //Bisecting angle
		R = -V + 2 * (V.dot(N)) * N;  //Get the direction of reflection

		double diffuse = max(0.0, N.dot(L));
		double specular = pow(max(0.0, N.dot(H)), tempT.colors->shine); //One time prof says to use POW

		for (int y = 0; y < 3; y++) {
			double temp = ((tempT.colors->diffuse * tempT.colors->color[y]) * diffuse);
			temp = temp + (tempT.colors->specular * specular);
			localColor[y] = localColor[y] + (temp * intensity);
		}
	}

	for (int k = 0; k < 3; k++) {
		localColor[k] = max(localColor[k], 0.0); //Clamp color range
		localColor[k] = min(localColor[k], 1.0);
	}

	return localColor;
}

/********************************************************
*	getFragments Class Function							*
*********************************************************/
Fragments *Raster::getFragments(int x, int y, Triangle &tempT) {
	/*Points that make up line A-B */
	double point1A = tempT.pointsI[0][0];
	double point1B = tempT.pointsI[0][1];
	double point2A = tempT.pointsI[1][0];
	double point2B = tempT.pointsI[1][1];
	double point3A = tempT.pointsI[2][0];
	double point3B = tempT.pointsI[2][1];

	/*Make equations easier to read*/
	double beta = ((point1B - point3B) * x + (point3A - point1A) * y + point1A * point3B - point3A * point1B) / ((point1B - point3B) * point2A + (point3A - point1A) * point2B + point1A * point3B - point3A * point1B);
	double gamma = ((point1B - point2B) * x + (point2A - point1A) * y + point1A * point2B - point2A * point1B) / ((point1B - point2B) * point3A + (point2A - point1A) * point3B + point1A * point2B - point2A * point1B);
	double alpha = 1.0 - beta - gamma;
	
	Fragments *frag = NULL;

	if (alpha >= 0 && beta >= 0 && gamma >= 0) { //If alpha, beta, gamma exist, create fragment
		frag = new Fragments;

		frag->world = (alpha * tempT.pointsI[0]) + (beta * tempT.pointsI[1]) + (gamma * tempT.pointsI[2]);
		frag->normals = (alpha * tempT.normal[0]) + (beta * tempT.normal[1]) + (gamma * tempT.normal[2]);
		frag->color = (alpha * tempT.color[0]) + (beta * tempT.color[1]) + (gamma * tempT.color[2]);
		frag->depth = (alpha * tempT.pointsI[0][2]) + (beta * tempT.pointsI[1][2]) + (gamma * tempT.pointsI[2][2]);
		frag->next = NULL;
	}
	return frag;
}

/********************************************************
*	Vertex Process Class Function						*
*********************************************************/
void Raster::vertexProcess(Matrix4d tempM) {
	triangles.clear(); //Clear triangles

	for (unsigned int t = 0; t < input.textures.size(); t++) {
		Polygon *tempP = dynamic_cast<Polygon*>(input.textures[t]);
		
		if (tempP != NULL) {
			for (unsigned int y = 0; y < tempP->triangles.size(); y++) { 
				triangles.push_back(tempP->triangles[y]);
			}
		}
	}

	for (unsigned int t = 0; t < triangles.size(); t++) {
		Triangle &tempT = triangles[t]; //Get current triangle
		
		for (int k = 0; k < 3; k++) {
			tempT.color[k] = shade(tempT, k); //Get shading on point while in world

			Vector4d tempV;
			tempV << tempT.points[k], 1;
			tempV = tempM * tempV;
			tempV = tempV / tempV[3];
			tempT.pointsI[k] = Vector3d(tempV[0], tempV[1], tempV[2]);
		}
	}
	
	cout << "Vertexes Proccessed" << endl; //DEBUG
}

/********************************************************
*	Rastering Class Function							*
*********************************************************/
void Raster::rastering(Fragments ***tempF){
	for (unsigned int t = 0; t < triangles.size(); t++) {
		Triangle &tempT = triangles[t];
		
		double minX = tempT.pointsI[0][0];
		double maxX = minX;
		double minY = tempT.pointsI[0][1];
		double maxY = minY;

		/*Find Bounding box*/
		for (int k = 1; k < 3; k++) { //For each point in the triangle
			if (tempT.pointsI[k][0] < minX) { //If the point is inside the box
				minX = tempT.pointsI[k][0]; //Set smallest X value
			}
			if (tempT.pointsI[k][0] > maxX) {
				maxX = tempT.pointsI[k][0]; //Set largest X value
			}

			if (tempT.pointsI[k][1] < minY) {
				minY = tempT.pointsI[k][1]; //Set smallest Y value
			}
			if (tempT.pointsI[k][1] > maxY) {
				maxY = tempT.pointsI[k][1]; //Set largest Y value
			}
		}
		minX = floor(minX); //Round bounding box to the lower whole value
		minY = floor(minY);
		maxX = ceil(maxX); //Round bounding box to the upper whole value
		maxY = ceil(maxY);

		/*Go though all the pixels that are in the bounding box*/
		for (int y = minY; y <= maxY; y++) {
			for (int x = minX; x <= maxX; x++) {
				if (!((0 <= x) && (x < input.resolution[0]) && (0 <= y) && (y < input.resolution[1]))) { //If the pixel is outside the box
					continue; //Skip
				}

				Fragments *frag = getFragments(x, y, tempT);
				if (frag == NULL) { //If there is no fragment at the pixel
					continue; //Skip
				}

				if (tempF[y][x] == NULL) { //If there is no fragment
					tempF[y][x] = frag; //Store the empty fragment
				}
				else { //If a fragment exits
					frag->next = tempF[y][x]; //Store the fragment 
					tempF[y][x] = frag;
				}
			}
		}
	}
}

/********************************************************
*	Fragment Process Class Function					*
*********************************************************/
void Raster::fragmentsProcess(Fragments ***frag){
	cout << "FRAGMENTS PROCESS NOT IMPLMENTED" << endl;
}

/********************************************************
*	Blend Class Function								*
*********************************************************/
void Raster::blend(unsigned char* pixels, Fragments ***frag) {
	const int yHeight = input.resolution[1];
	const int xWidth = input.resolution[0];

	/*Blend pixels (Starting from top left)*/
	for (int y = 0; y < yHeight; y++) { 
		for (int x = 0; x < xWidth; x++) { 
			Vector3d localColor = input.back; //Get default color

			if (frag[y][x] != NULL) { //If a fragment exists
				Fragments *far = frag[y][x];
				Fragments *cur = far;

				while (cur != NULL) { //Until a fragment is not found
					if (cur->depth > far->depth) { //If the depth of the current fragment is further away
						far = cur; //Set the new further depth
					}
					localColor = alpha * cur->color + (1.0 - alpha) * localColor;
					cur = cur->next; 
				}

				if (trans == true) { //If transparency is chosen
					localColor = (alpha * far->color) + ((1.0 - alpha) * localColor); //Get last color and add it
				}
				else { //If transparency is not chosen
					localColor = far->color; //Get the color of the furthest only
				}
			}

			for (int k = 0; k < 3; k++) {
				localColor[k] = max(localColor[k], 0.0); //Clamp color range
				localColor[k] = min(localColor[k], 1.0); 

				int temp = ((y * (xWidth * 3)) + (x * 3) + k);
				pixels[temp] = (localColor[k] * 255); //255 = 8-bit color
			}
		}
	}
	cout << "Fragments Colored" << endl; //DEBUG
}
