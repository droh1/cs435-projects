/*****************************************************************
* File:		Polygon.cpp
* Project:	CMSC 435 Project 1, Spring 2019
* Author:	Daniel Roh
* Date:		02/09/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	Functions: Handles polygoal objects
*****************************************************************/
#include "Polygon.h"
#include "texture.h"

//Constructor
Polygon::Polygon(vector<Vector3d> edges, vector<double> color) {
	this->color = color;
	setEdges(edges);
}

//Setter for Triangle Polygons
void Polygon::setEdges(vector<Vector3d> edges) {
	this->vertices = edges;

	for (unsigned int t = 1; t < (edges.size() - 1); t++) {
		triangles.push_back(Triangle(edges[0], edges[t], edges[t + 1])); //Store Triangles in groups of 3 (edge 0, 1, 2)
	}
	return;
}

//Getter for Triangle Polygons
vector<Triangle> Polygon::getTriangles() const {
	return triangles;
}

//Virtual Texture Function
double Polygon::intersect(rayPoint ray, double hither) const {
	double distince = -1; //Set to -1 if no intersection is made

	for (unsigned int i = 0; i < triangles.size(); i++) {
		double temp = triangles[i].intersect(ray);

		if (temp != -1 && (distince == -1 || temp < distince)) {//If a tringle is hit 
			if (hither != -1 && temp  < hither) { //If the intersection is closer then hither value
				//To close to camera, do nothing
			}
			else {
				distince = temp; //Set distince
			}
		}
	}
	return distince;
}