CC          = c++ 

#-----------------------------------------
#Optimization ----------------------------
OPT   = -O3 -Wno-deprecated

#GL_LIB = -framework OpenGL -framework GLUT -framework foundation
GL_LIB = -lGL -lglut -lGLU

#-----------------------------------------

TARGETS = proj5 viewer

OBJECTS = 

#-----------------------------------------

LIBS = 
INCS = -I/usr/include/eigen3

CCOPTS = $(OPT) $(INCS) 
LDOPTS = $(OPT) $(INCS) $(LIBS) 

#-----------------------------------------
#-----------------------------------------

default: $(TARGETS)


clean:
	/bin/rm -f *.o $(TARGETS)
	/bin/rm -r sample.out

#-----------------------------------------
#-----------------------------------------

viewer: $(OBJECTS) viewer.o
	$(CC) $(OBJECTS) viewer.o $(LDOPTS) $(GL_LIB) -o viewer

proj5: $(OBJECTS) boid.o
	$(CC) $(OBJECTS) boid.o $(LDOPTS) -o proj5

boid.o: boid.cpp boid.h
	$(CC) $(CFLAGS) $(LDOPTS) -c boid.cpp
#-----------------------------------------
#-----------------------------------------

.cpp.o: 
	$(CC) $(CCOPTS) -c $< 

#-----------------------------------------
#-----------------------------------------

run:
	./proj5 sample.in
	./viewer sample.out













