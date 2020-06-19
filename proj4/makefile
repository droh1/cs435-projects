CXX = g++
CXXFLAGS = -g -O3 -Wall -lblas -I/usr/include/eigen3/ -I/afs/umbc.edu/users/a/d/adamb/pub/LinearSolver

proj3: io.o smoothing.cpp 
	$(CXX) $(CXXFLAGS) io.o smoothing.cpp -o proj4

io.o: io.cpp io.h
	$(CXX) $(CXXFLAGS) -c io.cpp

clean:
	rm *.o
	rm *output.obj
	rm *proj4
run:
	./proj4 bunny.obj output.obj 1 1 50
run2:
	./proj4 bunny.obj output.obj -i 0.00001 1 1 50
