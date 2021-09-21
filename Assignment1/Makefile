# Simple Makefile for 6.837 raycasting assignment
# for g++ on linux platforms

# ===============================================================

SRCS 	 	= main.C \
		  ../matrix.C \
		  ../image.C \
		  scene_parser.C \
		  sphere.C \
		  raytracer.C \
		  camera.C \
		  group.C

# ===============================================================

INCLUDE 	= -I../ -std=c++11
CC		= clang++
EXE	  	= raytracer
OBJS =  $(SRCS:.C=.o)

# ===============================================================
# targets

.PHONY: all depend clean

all: depend $(EXE)

depend:
	$(CC) -E -M $(SRCS) $(INCLUDE)> Makefile.depend

clean: 
	-rm -f *~ *bak *.o  ../*.o *.tga *.ppm core.* Makefile.depend $(EXE) 

# ===============================================================
# compilation rules

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS) 

.C.o:
	$(CC) $< -c -o $@ $(INCLUDE)

.cpp.o:
	$(CC) $< -c -o $@ $(INCLUDE)

# ===============================================================
# EXE
scene1:
	./raytracer -input src/scene1_01.txt -size 200 200 -output output1_01.tga -depth 9 10 depth1_01.tga

# ===============================================================

-include Makefile.depend

