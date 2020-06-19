READ ME FILE:

Project 1:
	Implment a ray tracer using the barycentric coordinate intersection method.
	Link to project page: https://www.csee.umbc.edu/~adamb/435/proj1.html

How to run:
    0. Pull the git repo
    1. Type "make" to allow the compiler to create the program.
    2. Type "make run" to run the program that was just compiled.
    3. Follow the on screen instructions to run the program.
    4. Once the program is completed, the program will wrtie a file called "output.ppm"
    5. Take "output.ppm" and convert the file to a image format that your device can read.
    	   -Can use command "convert output.ppm output.bmp" to change convert the file to
	    a bitmap file that should be able to be seen on most computers.
	    
Other commands
    "make clean" to remove .o files and exacutable (output files need to removed manually)

Issues Yet to be fixed:
    -The calculation of distince of Z in rayTrace.cpp does no seem to give the correct Z value.
    -Running gear.nff, gears do not appear to be rendered in the correct order.
    -Running balls.nff, Only shows the background element.

Helped Received:
    -"Fundamentals of Computer Graphics" (Equations and sudo code)
    -"https://www.fileformat.info/format/nff/egff.htm" (For NFF File formatting)
    -Class Piazza Page
    -"http://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html" (For eigen
     documentation and usage examples)
    -"Noah (not sure of lastname)" Helped with realising that my normalizing of U, V, W was being
     called wrong and telling me about the compiler optimsation of "-O3".
    -"www.cplusplus.com" For reminders on vector functions, string.h, math.h libaries.
