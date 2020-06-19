/*****************************************************************
* File:		stub.cpp
* Project:	CMSC 435 Project 6, Spring 2019
* Author:	Daniel Roh
* Date:		05/14/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is stub.cpp
*	Functions: A modified stub.cpp that contains the
*		   functions needed to seam carve.
*****************************************************************/

#define cimg_display 0
#include "CImg.h"
#include<iostream>
#include <Eigen/Dense>
#include <limits> //Numeric limit function
#include<algorithm> //Max and min functions
using std::numeric_limits;
using namespace Eigen;
using namespace cimg_library;
using namespace std;

//Function Prototypes
int getIndex(int col, int row, int width, int height);
double getEnergy(Vector3d *img, int col, int row, int width, int height);
double getD(Vector3d *img, bool test, int col, int row, int width, int height);
void outputImg(Vector3d *img, int width, int height);
Vector3d *removeSeam(Vector3d *img, int width, int height);
Vector3d *transpose(Vector3d *img, int width, int height);

/******************************************************
*	Main Function
*******************************************************/
int main(int argc, char *argv[]) {
	CImg<double> input(argv[1]);
	CImg<double> lab = input.RGBtoLab();
	
	int finalWidth = atoi(argv[3]); //Get the requested width
	int finalHeight = atoi(argv[4]); //Get the requested height
	int currentWidth = input.width(); //Get the original size
	int currentHeight = input.height();
	char* outFile = argv[2]; //Name of output file

	Vector3d *image = new Vector3d[input.width() * input.height()];

	for (unsigned int i = 0; i < input.width(); i++) {
		for (unsigned int j = 0; j < input.height(); j++) {
			image[i*input.height() + j][0] = lab(i, j, 0);
			image[i*input.height() + j][1] = lab(i, j, 1);
			image[i*input.height() + j][2] = lab(i, j, 2);
		}
	}

	//Start of my code
	//==========================================================================================
	cout << "Starting caving of " << argv[1] << " from " << input.width() << "x" << input.height() << " -> " << finalWidth << "x" << finalHeight << endl; //DEBUG
	outputImg(image, input.width(), input.height());//Get the images energy

	for (currentWidth; currentWidth > finalWidth; currentWidth--) {
		image = removeSeam(image, currentWidth, currentHeight);
	}

	image = transpose(image, currentWidth, currentHeight); //rotate

	for (currentHeight; currentHeight > finalHeight; currentHeight--) {
		image = removeSeam(image, currentHeight, currentWidth); //Flip vars due to roation
	}

	image = transpose(image, currentHeight, currentWidth); //Rotate image back
	//==========================================================================================
	//End of my code

	CImg<double> output(atoi(argv[3]), atoi(argv[4]), input.depth(), input.spectrum(), 0);
	for (unsigned int i = 0; i < output.width(); i++) {
		for (unsigned int j = 0; j < output.height(); j++) {
			output(i, j, 0) = image[i*output.height() + j][0];
			output(i, j, 1) = image[i*output.height() + j][1];
			output(i, j, 2) = image[i*output.height() + j][2];
		}
	}

	CImg<double> rgb = output.LabtoRGB();
	if (strstr(argv[2], "png")) {
		rgb.save_png(argv[2]);
	}
	else if (strstr(argv[2], "jpg")) {
		rgb.save_jpeg(argv[2]);
	}
	cout << "Image carved, saved to: " << outFile << endl;

	delete[] image;
	return 0;
}



/******************************************************************************************
***********************************************************************************
*	Below here are the functions made for seam carving
***********************************************************************************
*******************************************************************************************/

/******************************************************
*	A getter to return the index 
*******************************************************/
int getIndex(int col, int row, int width, int height) {
	return col * height + row;
}

/******************************************************
*	Calculates the energy of a given pixel
*******************************************************/
double getEnergy(Vector3d *image, int col, int row, int width, int height) {
	double temp = getD(image, false, col, row, width, height);
	double temp2 = getD(image, true, col, row, width, height);
	return (temp + temp2);
}

/******************************************************
*	Find the derivative of a pixel 
*******************************************************/
double getD(Vector3d *image, bool test,int col, int row, int width, int height) {
	int index1, index2;
	
	if (test == false) { //If the X derivative is needed
		if (0 == col) { //If the end of the col is reached
			index1 = getIndex(col, row, width, height);
			index2 = getIndex(col + 1, row, width, height);
			return abs(image[index2][0] - image[index1][0]) / 1.0;
		}
		else if (width - 1 == col) { //If the top of the column is reached
			index1 = getIndex(col - 1, row, width, height);
			index2 = getIndex(col, row, width, height);
			return abs(image[index2][0] - image[index1][0]) / 1.0;
		}
		else { //If inside the column
			index1 = getIndex(col - 1, row, width, height);
			index2 = getIndex(col + 1, row, width, height);
			return abs(image[index2][0] - image[index1][0]) / 2.0;
		}
	}
	else { //If the Y derivative is needed
		if (0 == row) { //If the end of the row is reached
			index1 = getIndex(col, row, width, height);
			index2 = getIndex(col, row + 1, width, height);
			return abs(image[index2][0] - image[index1][0]) / 1.0;
		}
		else if ((height - 1) == row) { //If the top of the row is reached
			index1 = getIndex(col, row - 1, width, height);
			index2 = getIndex(col, row, width, height);
			return abs(image[index2][0] - image[index1][0]) / 1.0;
		}
		else { //If inside the row
			index1 = getIndex(col, row - 1, width, height);
			index2 = getIndex(col, row + 1, width, height);
			return abs(image[index2][0] - image[index1][0]) / 2.0;
		}
	}
}

/******************************************************
*	Outputs the energy to a image file
*******************************************************/
void outputImg(Vector3d *image, int width, int height){
	double mEnergy = 0.0;
	double *energy = new double[width * height];
	string fname("energy.jpg");

	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++) {
			int index = getIndex(i, j, width, height); //Get pixel 

			energy[index] = getEnergy(image, i, j, width, height); //Store pixel
			mEnergy = max<double>(mEnergy, energy[index]);
		}
	}

	CImg<float> output(width, height, 1, 3);

	for (unsigned int i = 0; i < output.width(); i++) {
		for (unsigned int j = 0; j < output.height(); j++) {
			int index = getIndex(i, j, output.width(), output.height());

			output(i, j, 0) = 255.0 * pow((energy[index] / mEnergy), (1 / 3.0));
			output(i, j, 1) = 255.0 * pow((energy[index] / mEnergy), (1 / 3.0));
			output(i, j, 2) = 255.0 * pow((energy[index] / mEnergy), (1 / 3.0));
		}
	}

	output.save_png(fname.c_str());
	cout << "Energy of image saved to: " << fname << endl; //DEBUG
	delete[] energy;
}

/******************************************************
*	Removes a seam from the image
*******************************************************/
Vector3d *removeSeam(Vector3d *image, int width, int height) {
	double mEnergy = 0.0;
	double *energy = new double[width * height];

	for (unsigned int row = 0; row < height; row++) {
		for (unsigned int col = 0; col < width; col++) {
			int index = getIndex(col, row, width, height); //Get the pixel

			energy[index] = getEnergy(image, col, row, width, height); //Find the energy for the pixel
			mEnergy = max<double>(mEnergy, energy[index]); 
		}
	}

	double *minEnergy = new double[width * height];

	for (unsigned int col = 0; col < width; col++) { //Get the min energy for the first column
		int index = getIndex(col, 0, width, height);
		minEnergy[index] = energy[index];
	}

	for (unsigned int row = 1; row < height; row++) { //Find the minEnergy for the rest 
		for (unsigned int col = 0; col < width; col++) {
			int index = getIndex(col, row, width, height);
			double C[3] = {numeric_limits<double>::max(), numeric_limits<double>::max(), numeric_limits<double>::max()};

			if (0 != col) { //If the end of the column is not reached
				C[0] = minEnergy[getIndex(col - 1, row - 1, width, height)]; //Look over one row and column
			}

			C[1] = minEnergy[getIndex(col, row - 1, width, height)]; //Look one row over

			if (width - 1 != col) { //If the end of the column is not reached
				C[2] = minEnergy[getIndex(col + 1, row - 1, width, height)]; //Look over one row and column
			}

			minEnergy[index] = energy[index] + min<double>(min<double>(C[0], C[1]), C[2]); //Find the min energy of the 3
		}
	}

	int *seam = new int[height];
	int lCol = 0;
	int rCol = (width - 1); 

	for (int row = (height - 1); row >= 0; row--) {
		seam[row] = lCol; //Set initial min energy
		for (unsigned int col = lCol; col <= rCol; col++) {
			int index = getIndex(col, row, width, height); //Get pixel

			if (minEnergy[index] < minEnergy[getIndex(seam[row], row, width, height)]) { //Check if current energy is smaller
				seam[row] = col; //Set new energy if smaller
			}
		}

		lCol = max(0, (seam[row] - 1)); //Move over
		rCol = min((width - 1), (seam[row] + 1)); //Move over
	}

	Vector3d *outFile = new Vector3d[(width - 1) * height]; //Create new image with the seam removed

	for (unsigned int row = 0; row < height; row++) {
		double minCost = numeric_limits<double>::max();
		int skip = 0;

		for (unsigned int col = 0; col < width - 1; col++) {
			if (col == seam[row]) { //If the seam is reached
				skip++; //Skip the seam
			}

			for (unsigned int k = 0; k < 3; k++) {
				outFile[getIndex(col, row, width, height)][k] = image[getIndex((col + skip), row, width, height)][k];
			}
		}
	}

	delete[] energy;
	delete[] minEnergy;
	delete[] seam;
	delete[] image;
	
	return outFile;
}

/******************************************************
*	Transposes the image
*******************************************************/
Vector3d *transpose(Vector3d *image, int width, int height) {
	int origIndex, newIndex;
	Vector3d *newImage = new Vector3d[width * height]; //Create a new image for the transpose

	for (unsigned int row = 0; row < height; row++) {
		for (unsigned int col = 0; col < width; col++) {
			origIndex = getIndex(col, row, width, height); //Get the current pixel
			newIndex = getIndex(row, col, height, width); //Get the pixel at the transposed locatiom
			newImage[newIndex] = image[origIndex]; //Replace the pixel 
		}
	}

	delete[] image;
	return newImage;
}
