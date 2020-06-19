CXX = g++
CXXFLAGS = -g -O3 -Wall -I/usr/include/eigen3/

proj3: Filehandle.o Polygon.o rayPoint.o Raster.o Sphere.o Triangle.o Texture.o starter.cpp 
	$(CXX) $(CXXFLAGS) Filehandle.o Polygon.o rayPoint.o Raster.o Sphere.o Triangle.o Texture.o starter.cpp -o proj3

Texture.o: Texture.cpp Texture.h
	$(CXX) $(CXXFLAGS) -c Texture.cpp

Triangle.o: Triangle.cpp Triangle.h
	$(CXX) $(CXXFLAGS) -c Triangle.cpp

Sphere.o: Sphere.cpp Sphere.h
	$(CXX) $(CXXFLAGS) -c Sphere.cpp

Raster.o: Raster.cpp Raster.h
	$(CXX) $(CXXFLAGS) -c Raster.cpp

rayPoint.o: rayPoint.cpp rayPoint.h
	$(CXX) $(CXXFLAGS) -c rayPoint.cpp

Polygon.o: Polygon.cpp Polygon.h
	$(CXX) $(CXXFLAGS) -c Polygon.cpp

Filehandle.o: Filehandle.cpp Filehandle.h
	$(CXX) $(CXXFLAGS) -c Filehandle.cpp

clean:
	rm *.o
	rm output.ppm
	rm *proj3
run:
	./proj3
