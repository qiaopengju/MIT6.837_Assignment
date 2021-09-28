# Simple Makefile for 6.837 raycasting assignment
# for g++ on linux platforms

# ===============================================================

SRCS 	 	= main.C \
		  ../matrix.C \
		  ../image.C \
		  scene_parser.C \
		  ../sphere.C \
		  ../camera.C \
		  ../group.C \
		  ../plane.C \
		  ../triangle.C \
		  ../transform.C

# ===============================================================

FLAG 	= -I../ -std=c++11
CC		= clang++
EXE	  	= raytracer
OBJS =  $(SRCS:.C=.o)

# ===============================================================
# targets

.PHONY: all depend clean

all: depend $(EXE)

depend:
	$(CC) -E -M $(SRCS) $(FLAG)> Makefile.depend

clean: 
	-rm -f *~ *bak *.o  ../*.o *.tga *.ppm core.* Makefile.depend $(EXE) 

# ===============================================================
# compilation rules

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS) 

.C.o:
	$(CC) $< -c -o $@ $(FLAG)

.cpp.o:
	$(CC) $< -c -o $@ $(FLAG)

# ===============================================================
# EXE
scene1:
	./raytracer -input src/scene2_01_diffuse.txt -size 200 200 -output output2_01.tga
scene2:
	./raytracer -input src/scene2_02_ambient.txt -size 200 200 -output output2_02.tga
scene3:
	./raytracer -input src/scene2_03_colored_lights.txt -size 200 200 -output output2_03.tga -normals normals2_03.tga
scene4:
	./raytracer -input src/scene2_04_perspective.txt -size 200 200 -output output2_04.tga -normals normals2_04.tga
scene5:
	./raytracer -input src/scene2_05_inside_sphere.txt -size 200 200 -output output2_05_no_back.tga
scene5_shade_back:
	./raytracer -input src/scene2_05_inside_sphere.txt -size 200 200 -output output2_05.tga -depth 9 11 depth2_05.tga -normals normals2_05.tga -shade_back

# ===============================================================

-include Makefile.depend

