# Simple Makefile for 6.837 raycasting assignment
# for g++ on linux platforms

# ===============================================================
OBJ_DIR = ../obj
RAY_TRACER_DIR = ../raytracer

SRCS 	 	= main.C \
		  ../matrix.C \
		  ../image.C \
		  scene_parser.C \
		  $(OBJ_DIR)/sphere.C \
		  $(RAY_TRACER_DIR)/camera.C \
		  $(OBJ_DIR)/group.C

# ===============================================================

FLAG 	= -I../ -I../obj/ -I../raytracer/ -std=c++11
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
	-rm -f *~ *bak *.o  ../*.o *.tga *.ppm core.* Makefile.depend $(EXE) $(RAY_TRACER_DIR)/*.o $(OBJ_DIR)/*.o

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
	./raytracer -input src/scene1_01.txt -size 200 200 -output output1_01.tga -depth 9 10 depth1_01.tga
scene2:
	./raytracer -input src/scene1_02.txt -size 200 200 -output output1_02.tga -depth 8 12 depth1_02.tga
scene3:
	./raytracer -input src/scene1_03.txt -size 200 200 -output output1_03.tga -depth 8 12 depth1_03.tga
scene4:
	./raytracer -input src/scene1_04.txt -size 200 200 -output output1_04.tga -depth 12 17 depth1_04.tga
scene5:
	./raytracer -input src/scene1_05.txt -size 200 200 -output output1_05.tga -depth 14.5 19.5 depth1_05.tga
scene6:
	./raytracer -input src/scene1_06.txt -size 200 200 -output output1_06.tga -depth 3 7 depth1_06.tga
scene7:
	./raytracer -input src/scene1_07.txt -size 200 200 -output output1_07.tga -depth -2 2 depth1_07.tga




# ===============================================================

-include Makefile.depend

