/*****************************************************************
* File:		Texture.cpp
* Project:	CMSC 435 Project 2, Spring 2019
* Author:	Daniel Roh
* Date:		02/25/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is Texture.cpp
*	Functions: Virtual functions for polyogns/spheres
*****************************************************************/
#include "Texture.h"

/********************************************************
*	Texture Class Functions								*
*********************************************************/
//Constructor
Texture::Texture(ColorInfo *colors) {
	this->colors = colors;
}
