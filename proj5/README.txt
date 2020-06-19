README FILE (Updated 05/01/19):

Project 5:
	Implement a program that runs a boid simulation based on symbolics paper
	Link to project page: https://www.csee.umbc.edu/~adamb/435/proj5.html

How to run:
    1. Pull the git repo
    2. Type "make" to allow the compiler to create the program.
    3. Methods to run the program.
		- "make run" 
			Will run the program using "sample.in" as input.

		- "./proj4 input"
			Can be used to customize the output 
			(Note: the project expects 2 arguments, or it will kill the program.
					Arguments can be structured as './proj4 input.in'
			)
			
	4. Once run, the program will produce a "sample.out" file and open the viewer to run the animation.
	    
Other commands
    "make clean" to remove .o files, executables, and output files. 

Extra Credit implemented:
	>Food particles 
	>phenomena (Note: Added some code to make the boid get bigger when the boid eats, but unsure how to let
					  the viewer show these changes)
	
Extra Credit not implemented:
	>KDtree

Helped Received:
	- "Flocks, Herds, and Schools: A Distributed Behavioral Model" (Project Info)
    - Class Piazza Page
    - "http://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html" (For eigen
       documentation and usage examples)
    - "www.cplusplus.com" For reminders on c++ libraries.
	- "Noah" Helped with fixing bounding box issues 
	