README FILE (Updated 03/11/19):

Project 3:
	Implement a rasterization based renderer using the pipeline rending.
	Link to project page: https://www.csee.umbc.edu/~adamb/435/proj3.html

How to run:
    1. Pull the git repo
    2. Type "make" to allow the compiler to create the program.
    3. Type "make run" to run the program that was just compiled.
    4. Follow the on screen instructions to run the program. (Note: To run the program with no
	   transparency, use the value of 1.00 when asked)
    5. Once the program is completed, the program will write a file called "output.ppm"
    6. Take "output.ppm" and convert the file to a image format that your device can read.
    	   -Can use command "convert output.ppm output.bmp" to change convert the file to
			a bitmap file that should be able to be seen on most computers.
	    
Other commands
    "make clean" to remove .o files and executable (output files that are converted to anything other then
	'output.ppm' will need to removed manually)

Extra Credit implemented:
	>Transparency
	
Extra Credit not implemented:
	>Clipping
	>Fragment Shading
	>Shadow maps

Helped Received:
    -"Fundamentals of Computer Graphics" (Equations and sudo code)
    -"https://www.fileformat.info/format/nff/egff.htm" (For NFF File formatting)
    -Class Piazza Page
    -"http://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html" (For eigen
     documentation and usage examples)
    -"www.cplusplus.com" For reminders on vector functions, string.h, math.h libraries.
	-"Noah (not sure of lastname)" Helped with giving advice on the transparency.
	