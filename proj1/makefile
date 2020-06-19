CXX = g++
CXXFLAGS = -g -O3 -Wall -I/usr/include/eigen3/

proj1: Filehandle.o Polygon.o rayPoint.o rayTrace.o Sphere.o Triangle.o texture.o Starter.cpp 
	$(CXX) $(CXXFLAGS) Filehandle.o Polygon.o rayPoint.o rayTrace.o Sphere.o Triangle.o Starter.cpp -o proj1

texture.o: texture.cpp texture.h
	$(CXX) $(CXXFLAGS) -c texture.cpp

Triangle.o: Triangle.cpp Triangle.h
	$(CXX) $(CXXFLAGS) -c Triangle.cpp

Sphere.o: Sphere.cpp Sphere.h
	$(CXX) $(CXXFLAGS) -c Sphere.cpp

rayTrace.o: rayTrace.cpp rayTrace.h
	$(CXX) $(CXXFLAGS) -c rayTrace.cpp

rayPoint.o: rayPoint.cpp rayPoint.h
	$(CXX) $(CXXFLAGS) -c rayPoint.cpp

Polygon.o: Polygon.cpp Polygon.h
	$(CXX) $(CXXFLAGS) -c Polygon.cpp

Filehandle.o: Filehandle.cpp Filehandle.h
	$(CXX) $(CXXFLAGS) -c Filehandle.cpp

clean:
	rm *.o
	rm *~
run:
	./proj1
