README FILE (Updated 05/14/19):

Project 6:
	Implement a program that allow content aware image resizing via seam carving
	Link to project page: https://www.csee.umbc.edu/~adamb/435/proj6.html

How to run:
    1. Pull the git repo
    2. Type "make" to allow the compiler to create the program.
    3. Methods to run the program.
		- "make run" 
			Will run the program using dog.jpg, house.jpg, and up.jpg. Each image will be resized to various sizes. 

		- "./proj4 input.jpg output.jpg X Y"
			Can be used to customize the output (Note: will only downscale images, upscaling will crash the program)
			
			
	4. Once run, the program will output a resized image and the image of the energy calculated.
	    
Other commands
    "make clean" to remove .o files, executables, and output files from the make run command. 

Extra Credit implemented:
	>N/A
Extra Credit not implemented:
	> Scharr Gradient Operator
	> Compute the energy once
	> Create a webpage 
	> Adding seams

Helped Received:
	- "Seam Carving for Content-Aware Image Resizing" (Project Info)
    - Class Piazza Page
    - "http://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html" (For eigen
       documentation and usage examples)
    - "www.cplusplus.com" For reminders on c++ libraries.
	- "https://stackoverflow.com/questions/33327727/cimg-library-linking-error" For fixing a
		linking issue when compiling.
	