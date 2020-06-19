CXX = g++
CXXFLAGS = -g -O3 -Wall -I/usr/include/eigen3/

proj1: Filehandle.o Polygon.o rayPoint.o RayTrace.o Sphere.o Triangle.o Texture.o starter.cpp 
	$(CXX) $(CXXFLAGS) Filehandle.o Polygon.o rayPoint.o RayTrace.o Sphere.o Triangle.o Texture.o starter.cpp -o proj2

Texture.o: Texture.cpp Texture.h
	$(CXX) $(CXXFLAGS) -c Texture.cpp

Triangle.o: Triangle.cpp Triangle.h
	$(CXX) $(CXXFLAGS) -c Triangle.cpp

Sphere.o: Sphere.cpp Sphere.h
	$(CXX) $(CXXFLAGS) -c Sphere.cpp

RayTrace.o: RayTrace.cpp RayTrace.h
	$(CXX) $(CXXFLAGS) -c RayTrace.cpp

rayPoint.o: rayPoint.cpp rayPoint.h
	$(CXX) $(CXXFLAGS) -c rayPoint.cpp

Polygon.o: Polygon.cpp Polygon.h
	$(CXX) $(CXXFLAGS) -c Polygon.cpp

Filehandle.o: Filehandle.cpp Filehandle.h
	$(CXX) $(CXXFLAGS) -c Filehandle.cpp

clean:
	rm *.o
	rm output.ppm
	rm *proj2
run:
	./proj2
