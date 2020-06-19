/*****************************************************************
* File:		texture.cpp
* Project:	CMSC 435 Project 1, Spring 2019
* Author:	Daniel Roh
* Date:		02/09/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	Functions: Contains constructor for storing color of the 
*			   pixel
*****************************************************************/
#include "texture.h"

texture::texture(vector<double> color) {
	this->color = color;
	//color = vector<double>(0, 0, 0, 0, 0, 0, 0, 0); //Default color is black
}