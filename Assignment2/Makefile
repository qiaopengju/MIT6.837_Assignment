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
		  ../plane.C

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


# ===============================================================

-include Makefile.depend

