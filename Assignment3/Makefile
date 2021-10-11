# Simple Makefile for 6.837 raycasting assignment
# for g++ on linux platforms

# ===============================================================
# update this list as you add new C++ source files
OBJ_DIR = ../GL/obj
RAY_TRACER_DIR = ../GL/ray_tracer
SRCS 	 	= main.C \
		../matrix.C \
		../image.C \
		../scene_parser.C \
		$(OBJ_DIR)/group.C \
		$(OBJ_DIR)/sphere.C \
		$(OBJ_DIR)/triangle.C \
		$(OBJ_DIR)/plane.C \
		$(OBJ_DIR)/transform.C \
		$(RAY_TRACER_DIR)/raytracer.C \
		$(RAY_TRACER_DIR)/material.C \
		$(RAY_TRACER_DIR)/light.C \
		$(RAY_TRACER_DIR)/camera.C \
		../GL/glCanvas.C \

# ===============================================================
# NOTE:  On athena, the Mesa GL libraries are currently located in the
#        mesa_v501 locker.  Type "add mesa_v501" to access these files.

LIBS = -framework OpenGL -framework GLUT
INCLUDE = -I/mit/mesa_v501/Mesa-5.0.1/include/
CC = clang++
EXE = raytracer
OBJS =  $(SRCS:.C=.o)
FLAG = -I../GL -I$(OBJ_DIR) -I$(RAY_TRACER_DIR) -I../ -std=c++11

# ===============================================================
# targets

.PHONY: all depend clean

all: depend $(EXE)

depend:
	$(CC) $(INCLUDE) $(FLAG) -E -M $(SRCS) > Makefile.depend

clean: 
	-rm -f *~ *bak *.o ../*.o ../GL/*.o $(OBJ_DIR)/*.o $(RAY_TRACER_DIR)/*.o core.* Makefile.depend $(EXE) 

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
scene2:
	./raytracer -input src/scene3_02_cube_perspective.txt -size 200 200 -output output3_02.tga -gui
scene3:
	./raytracer -input src/scene3_03_bunny_mesh_200.txt -size 200 200 -output output3_03.tga -gui
scene4:
	./raytracer -input src/scene3_04_bunny_mesh_1k.txt -size 200 200 -output output3_04.tga -gui
scene5:
	./raytracer -input src/scene3_05_axes_cube.txt -size 200 200 -output output3_05.tga -normals normals_3_05.tga -gui
scene6:
	./raytracer -input src/scene3_06_crazy_transforms.txt -size 200 200 -output output3_06.tga -gui
scene7:
	./raytracer -input src/scene3_07_plane.txt -size 200 200 -output output3_07.tga -gui -tessellation 10 5
scene9:
	./raytracer -input src/scene3_09_exponent_variations.txt -size 300 300 -output output3_09.tga -gui -tessellation 100 50 -gouraud
scene10:
	./raytracer -input src/scene3_10_exponent_variations_back.txt -size 300 300 -output output3_10.tga -gui -tessellation 100 50 -gouraud 
scene11:
	./raytracer -input src/scene3_11_weird_lighting_diffuse.txt -size 200 200 -output output3_11.tga -gui -tessellation 100 50 -gouraud
scene12:
	./raytracer -input src/scene3_12_weird_lighting_specular.txt -size 200 200 -output output3_12.tga -gui -tessellation 100 50 -gouraud
