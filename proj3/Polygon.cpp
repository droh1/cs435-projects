/*****************************************************************
* File:		Polygon.cpp
* Project:	CMSC 435 Project 3, Spring 2019
* Author:	Daniel Roh
* Date:		03/11/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is Polygon.cpp
*	Functions: Functions for Polygons
*****************************************************************/
#include "Polygon.h"
#include "Texture.h"

/********************************************************
*	Polygon Class Functions								*
*********************************************************/
//Constructor
Polygon::Polygon(vector<Vector3d> edges, vector<Vector3d> normals, ColorInfo * colors, bool polyPatch){
	this->colors = colors;
	this->polyPatch = polyPatch;

    for (unsigned int i = 2; i < edges.size(); i++) {
		if (polyPatch == true) { //If a polygon patch is found
			triangles.push_back(Triangle(colors, edges[0], edges[i - 1], edges[i], polyPatch, normals[0], normals[i - 1], normals[i]));
		}
		else { //If a polygon is found
			triangles.push_back(Triangle(colors, edges[0], edges[i - 1], edges[i], polyPatch));
		}
    }
}


hitRecord Polygon::intersect(rayPoint ray, double d, double d2) const {
    hitRecord bestHit = hitRecord(textureType::polygon, -1);

    for (unsigned int i=0; i < triangles.size(); i++) {
        hitRecord hit = triangles[i].intersect(ray, d, d2); //Get the intersect of this triangle
		
		//cout << "TEST: " << hit.intersection << " == -1 , " << bestHit.intersection << endl; //DEBUG
        if (hit.intersection != -1 && (bestHit.intersection == -1 || hit.intersection < bestHit.intersection)) { //If a new hit or closer hit is found
            hit.type = textureType::polygon; //Set the type that got hit
            hit.triangleIndex = i;
            bestHit = hit;
        }
    }
    return bestHit;
}

Vector3d Polygon::getNormal(hitRecord hit, bool interpolate) const {
    return triangles[hit.triangleIndex].getNormal(hit, interpolate);
}