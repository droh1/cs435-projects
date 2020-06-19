README FILE (Updated 04/15/19):

Project 4:
	Implement a program that smooths .obj files using laplacian smoothing.
	Link to project page: https://www.csee.umbc.edu/~adamb/435/proj4.html

How to run:
    1. Pull the git repo
    2. Type "make" to allow the compiler to create the program.
    3. Methods to run the program.
		- "make run" 
			Will run the program using laplacian smoothing with "./proj4 bunny.obj output.obj 1 1 50" as input
			
		- "make run2"
			Will run the program using implicit integration with "./proj4 bunny.obj output.obj -i 0.00001 1 1 50" as input
			
		- "./proj4 user input here"
			Can be used to customize the output 
			(Note: the project expects 6 or 8 arguments, or it will kill the program.
					Arguments can be structured as './proj4 input_name output_name lambda dT iterations'
												    or
												   './proj4 input_name output_name mode eps lambda dT iterations'
			)
			
	4. Once run, a output file is generated and can be viewed on any .obj viewer.
	    
Other commands
    "make clean" to remove .o files and executables (output files that named "output.obj" will be removed. Other files will need to removed manually)

Extra Credit implemented:
	>Implicit Integration
	
Extra Credit not implemented:
	>Cotangent weights
	>Volume preservation
	>Biharmonic Operator
	>Loop subdivision

Helped Received:
	- "Implicit Fairing of Irregular Meshes using Diffusion and Curvature Flow" for equations 
		needed for smoothing a object.
    - Class Piazza Page
    - "http://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html" (For eigen
       documentation and usage examples)
    - "www.cplusplus.com" For reminders on vector functions, string.h, math.h libraries.
	- Dr.Bargteil, helped with the linking errors I was facing
	