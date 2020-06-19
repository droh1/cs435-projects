CXX = g++
CXXFLAGS = -g -O3 -Wall -w -lblas -I/usr/include/eigen3/ -I/afs/umbc.edu/users/a/d/adamb/pub/ -L/usr/X11R6/lib -lm -lpthread -lX11

proj6: stub.cpp 
	$(CXX) $(CXXFLAGS) stub.cpp -o proj6

clean:
	rm *proj6
	rm energy.jpg
	rm output.jpg
	rm output2.jpg
	rm output3.jpg
	
run:
	./proj6 dog.jpg output.jpg 400 400
	./proj6 house.jpg output2.jpg 300 350
	./proj6 up.jpg output3.jpg 640 400
