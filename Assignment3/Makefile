# Simple Makefile for 6.837 raycasting assignment
# for g++ on linux platforms

# ===============================================================
# update this list as you add new C++ source files

SRCS 	 	= main.C \
		../matrix.C \
		../image.C \
		../scene_parser.C \
		../GL/obj/group.C \
		../GL/obj/sphere.C \
		../GL/obj/triangle.C \
		../GL/obj/plane.C \
		../GL/obj/transform.C \
		../GL/raytracer/material.C \
		../GL/raytracer/light.C \
		../GL/raytracer/camera.C \
		../GL/glCanvas.C

# ===============================================================
# NOTE:  On athena, the Mesa GL libraries are currently located in the
#        mesa_v501 locker.  Type "add mesa_v501" to access these files.

LIBS = -framework OpenGL -framework GLUT
INCLUDE = -I/mit/mesa_v501/Mesa-5.0.1/include/
CC = clang++
EXE = raytracer
OBJS =  $(SRCS:.C=.o)
FLAG = -I../GL -I../GL/obj/ -I../GL/raytracer/ -I../ -std=c++11

# ===============================================================
# targets

.PHONY: all depend clean

all: depend $(EXE)

depend:
	$(CC) $(INCLUDE) $(FLAG) -E -M $(SRCS) > Makefile.depend

clean: 
	-rm -f *~ *bak *.o ../*.o ../GL/*.o ../GL/obj/*.o ../GL/raytracer/*.o core.* Makefile.depend $(EXE) 

# ===============================================================
# compilation rules

$(EXE): $(OBJS)
	$(CC) $(INCLUDE) $(FLAG) -o $@ $(OBJS) $(LIBS)

.C.o:
	$(CC) $(INCLUDE) $(FLAG) $< -c -o $@

# ===============================================================

-include Makefile.depend

# ===============================================================
# run
scene1:
	./raytracer -input src/scene3_01_cube_orthographic.txt -size 200 200 -output output3_01.tga -gui

