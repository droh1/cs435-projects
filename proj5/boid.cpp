
/*****************************************************************
* File:		boid.cpp
* Project:	CMSC 435 Project 5, Spring 2019
* Author:	Daniel Roh
* Date:		05/01/19
* Section:
* E-mail:	droh1@umbc.edu
*
*	This file is boid.cpp
*	Functions: Contains the functions declared in boid.h.
*			   Main is also contained in this file
*****************************************************************/
#include "boid.h"

/*****************************************
*	Boid Constructor
******************************************/
Boid::Boid(Vector3d position, Vector3d velocity) {
	this->position = position;
	this->velocity = velocity;
}

/*****************************************
*	Fish Constructor
******************************************/
Fish::Fish(string filename){
	readFile(filename);
	simulate();
}

/*****************************************
*	Reads the file
******************************************/
void Fish::readFile(string filename) {
	int numB; 
	int food;
	string temp;
	ifstream input(filename);

	readLines(input, temp);
	sscanf(temp.c_str(), "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &sizeB, &sight, &maxNear, &wight, &wCollision, &wCentering, &wVelocity, &hunger, &damping, &timeStep, &duration);

	readLines(input, temp);
	sscanf(temp.c_str(), "%d", &numB);

	for (int i = 0; i < numB; i++) { //Read in the boids
		readLines(input, temp);
		Boid tempB;
		sscanf(temp.c_str(), "[%lf,%lf,%lf] [%lf,%lf,%lf]", &tempB.position[0], &tempB.position[1], &tempB.position[2], &tempB.velocity[0], &tempB.velocity[1], &tempB.velocity[2]);
		boids.push_back(tempB);
	}

	readLines(input, temp);
	sscanf(temp.c_str(), "%d", &food);

	for (int i = 0; i < food; i++) { //Read in the food
		readLines(input, temp);
		Food food;
		sscanf(temp.c_str(), "[%lf,%lf,%lf] [%lf,%lf,%lf] %lf", &food.position[0], &food.position[1], &food.position[2], &food.velocity[0], &food.velocity[1], &food.velocity[2], &food.time);
		meal.push_back(food);
	}
}


/*****************************************
*	Writes the simulation to a file
******************************************/
void Fish::writeOutput(ofstream& output, double timeStep) {
	output << boids.size() << endl;

	for (unsigned int i = 0; i < boids.size(); i++) { //Output the boids posistion
		output << "[" << boids[i].position[0] << "," << boids[i].position[1] << "," << boids[i].position[2] << "] ";
		output << "[" << boids[i].velocity[0] << "," << boids[i].velocity[1] << "," << boids[i].velocity[2] << "]" << endl;
	}

	int temp = 0;

	for (unsigned int i = 0; i < meal.size(); i++) { //Find only the food that is in the time step
		if (meal[i].time < timeStep) {
			temp++;
		}
	}
	output << temp << endl;

	for (unsigned int i = 0; i < temp; i++) {
		output << "[" << meal[i].position[0] << "," << meal[i].position[1] << "," << meal[i].position[2] << "]" << endl;
	}
	
}

/*****************************************
*	Simulates the boids
******************************************/
void Fish::simulate() {
	int frames = 0;
	ofstream output;

	output.open("sample.out"); //Output file name
	cout << "Starting Simulation for " << duration << " seconds with a time step of " << timeStep << endl; //DEBUG
	
	for (double t = 0; t < duration; t += timeStep) { //Calculate the amount of frames to make
		frames++;
	}
	
	output << frames << endl; //Output frame count to file

	for (double t = 0; t < duration; t += timeStep) {
		cout << "Simulating time: " << t << endl; //DEBUG
		computeForces(t); //update forces for all boids

		for (unsigned int i = 0; i < boids.size(); i++) {
			for (unsigned int j = 0; j < meal.size(); j++) { //Calculate food
				if (meal[j].time < t) { //If the food is shown in the simualtion
					double hungerT = (meal[j].position.norm() - boids[i].position.norm()); //Find the distence between the boid and food

					if (abs(hungerT) >= sight) { //If the boid can see food
						boids[i].force = boids[i].force + wVelocity * (meal[j].position - boids[i].velocity); //Head to the food
					}
				}
			}

			if (boids[i].force.norm() > MAX_FORCE) { //If the force is too high
				boids[i].force = MAX_FORCE * boids[i].force.normalized();
			}

			Vector3d boidMin(boxMin - boids[i].position);
			Vector3d boidMax(boxMax - boids[i].position);

			for (int j = 0; j < 3; j++) { //Check if the boid is leaving the bounding box
				if (boidMin[j] > 0) {
					boids[i].velocity[j] = boids[i].velocity[j] * -1;
				}
				if (boidMax[j] < 0) {
					boids[i].velocity[j] = boids[i].velocity[j] * -1;
				}
			}

			if (boids[i].velocity.norm() > MAX_VELOCITY) { //Check if the velocity is too high
				boids[i].velocity = MAX_VELOCITY * boids[i].velocity.normalized();
			}

			boids[i].position = boids[i].position + boids[i].velocity * timeStep; //Update boid posistion
		}

		computeFood(t); //Update the posistion for all the food
		writeOutput(output, t); 
	}
}

/*****************************************
*	Calculates the position of boids
******************************************/
void Fish::computeForces(double time) {
	for (unsigned int i = 0; i < boids.size(); i++) {
		double neighbors = 0;
		boids[i].force = Vector3d(0, 0, 0);
		Vector3d center = Vector3d(0, 0, 0);

		for(unsigned int j = 0; j < boids.size(); j++) { //Find neighbords
			if (j == i) { //If the current boid is the same boid being checked
				continue; //Skip to next
			}
			
			double distence = (boids[j].position - boids[i].position).norm(); //Find the distence between the two

			if (distence < sight) { //If the boid is in the sight range
				center = center + boids[j].position;
				boids[i].force = boids[i].force + wVelocity * (boids[j].velocity - boids[i].velocity);
				boids[i].force = boids[i].force + wCollision * ((boids[j].position - boids[i].position) / (distence * distence * distence));
				neighbors++;
			}
		}

		if (neighbors != 0) { //If a neighbor is found
			center = (center / neighbors); //Find the center from the averages
		}
		else { //If a neighbor is not found
			center = boids[i].position; //Use the position as the center
		}

		boids[i].force = boids[i].force + wCentering * (center - boids[i].position); //Updae boids force with center
	}
}

/*****************************************
*	Calculates the position of the food
******************************************/
void Fish::computeFood(double time) {
	int temp = 0;

	for (unsigned int i = 0; i < meal.size(); i++) { //Find the food that is in the time
		if (meal[i].time < time) {
			temp++;
		}
	}

	for (unsigned int i = 0; i < meal.size(); i++) { //Check if the food outside of the bounding box
		Vector3d foodMin(boxMin - meal[i].position);
		Vector3d foodMax(boxMax - meal[i].position);

		for (int j = 0; j < 3; j++) { 
			if (foodMin[j] > 0) {
				meal[i].position[j] = boxMin[j]; //Move food into the box
			}
			if (foodMax[j] < 0) {
				meal[i].position[j] = boxMax[j]; //Move food into the box
			}
		}
	}

	for (unsigned int i = 0; i < temp; i++) {
		if (boids[i].position == meal[i].position) { //If a boid is eating the food
			meal.erase(meal.begin() + i); //Remove the food
			temp--; //Update end condistion
			boids[i].sizeF = boids[i].sizeF + 0.25; //If the boid eats the food, increase size (not supported in viewer)
		}
		else {
			meal[i].position = meal[i].position + meal[i].velocity * timeStep; //Update position
		}
	}
}

/*****************************************
*	Read in Helper (Spaced delimited)
******************************************/
void Fish::readLines(ifstream &input, string &temp) {
	if (!getline(input, temp)) { //Catch the first space
		cout << "Problem reading file" << endl; //DEBUG
		exit(1);
	}
	while (temp == "") { //Get input, skip spaces
		if (!getline(input, temp)) {
			cout << "Problem reading file" << endl; //DEBUG
			exit(1);
		}
	}
}


/*****************************************
*	Main
******************************************/
int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Invalid amount of arguments" << endl;
		cout << "Please look at README.txt for input arguments" << endl;
		exit(1);
	}

	string filename = argv[1];
	Fish temp(filename);

	cout << "Done" << endl << "Running Simulation" << endl; //DEBUG
	return 0;
}