README FILE (Updated 02/26/19):

Project 2:
	Implement a ray tracer using the barycentric coordinate intersection method with reflections and shading.
	Link to project page: https://www.csee.umbc.edu/~adamb/435/proj2.html

How to run:
    1. Pull the git repo
    2. Type "make" to allow the compiler to create the program.
    3. Type "make run" to run the program that was just compiled.
    4. Follow the on screen instructions to run the program.
    5. Once the program is completed, the program will write a file called "output.ppm"
    6. Take "output.ppm" and convert the file to a image format that your device can read.
    	   -Can use command "convert output.ppm output.bmp" to change convert the file to
			a bitmap file that should be able to be seen on most computers.
	    
Other commands
    "make clean" to remove .o files and executable (output files that are not 'output.ppm' need to removed manually)

Not implemented:
	-Extra Credit 
		>Stratified sampling
		>Depth of field
		>Refraction
		>Phong/Smoothing Shading

Helped Received:
    -"Fundamentals of Computer Graphics" (Equations and sudo code)
    -"https://www.fileformat.info/format/nff/egff.htm" (For NFF File formatting)
    -Class Piazza Page
    -"http://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html" (For eigen
     documentation and usage examples)
    -"www.cplusplus.com" For reminders on vector functions, string.h, math.h libraries.
	-"Noah (not sure of lastname)" Helped with giving advice on potential sources of output errors 
	 ("When only getting blue output")
	