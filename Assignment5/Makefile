# Simple Makefile for 6.837 raycasting assignment
# for g++ on linux platforms

# ===============================================================
# update this list as you add new C++ source files
OBJ_DIR = ../obj
RAY_TRACER_DIR = ../ray_tracer
SRCS 	 	= main.C \
		../matrix.C \
		../image.C \
		../scene_parser.C \
		$(OBJ_DIR)/group.C \
		$(OBJ_DIR)/sphere.C \
		$(OBJ_DIR)/triangle.C \
		$(OBJ_DIR)/plane.C \
		$(OBJ_DIR)/transform.C \
		$(OBJ_DIR)/grid.C \
		$(RAY_TRACER_DIR)/raytracer.C \
		$(RAY_TRACER_DIR)/material.C \
		$(RAY_TRACER_DIR)/light.C \
		$(RAY_TRACER_DIR)/camera.C \
		$(RAY_TRACER_DIR)/boundingbox.C \
		../GL/rayTree.C \
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
scene1_0:
	./raytracer -input src/scene5_01_sphere.txt -size 200 200 -output output5_01a.tga -gui -grid 1 1 1 -visualize_grid
scene1_1:
	./raytracer -input src/scene5_01_sphere.txt -size 200 200 -output output5_01b.tga -gui -grid 5 5 5 -visualize_grid
scene1_2:
	./raytracer -input src/scene5_01_sphere.txt -size 200 200 -output output5_01c.tga -gui -grid 15 15 15 -visualize_grid
scene2_0:
	./raytracer -input src/scene5_02_spheres.txt -size 200 200 -output output5_02a.tga -gui -grid 15 15 15 -visualize_grid
scene2_1:
	./raytracer -input src/scene5_02_spheres.txt -size 200 200 -output output5_02b.tga -gui -grid 15 15 3 -visualize_grid
scene2_2:
	./raytracer -input src/scene5_02_spheres.txt -size 200 200 -gui -grid 8 8 8 -visualize_grid
scene3:
	./raytracer -input src/scene5_03_offcenter_spheres.txt -size 200 200 -output output5_03.tga -gui -grid 20 20 20 -visualize_grid
scene4:
	./raytracer -input src/scene5_04_plane_test.txt -size 200 200 -output output5_04.tga -gui -grid 15 15 15 -visualize_grid
scene5:
	./raytracer -input src/scene5_05_sphere_triangles.txt -size 200 200 -gui -tessellation 30 15 -gouraud
scene5_0:
	./raytracer -input src/scene5_05_sphere_triangles.txt -size 200 200 -output output5_05.tga -gui -grid 20 20 10 -visualize_grid
scene6:
	./raytracer -input src/scene5_06_bunny_mesh_200.txt -size 200 200 -output output5_06.tga -gui -grid 10 10 7 -visualize_grid
scene7:
	./raytracer -input src/scene5_07_bunny_mesh_1k.txt -size 200 200 -output output5_07.tga -gui -grid 15 15 12 -visualize_grid
scene8:
	./raytracer -input src/scene5_08_bunny_mesh_5k.txt -size 200 200 -output output5_08.tga -gui -grid 20 20 15 -visualize_grid
scene9:
	./raytracer -input src/scene5_09_bunny_mesh_40k.txt -size 200 200 -output output5_09.tga -gui -grid 40 40 33 -visualize_grid
scene10:
	./raytracer -input src/scene5_10_scale_translate.txt -size 200 200 -gui -tessellation 30 15 -gouraud
scene10_0:
	./raytracer -input src/scene5_10_scale_translate.txt -size 200 200 -output output5_10.tga -gui -grid 15 15 15 -visualize_grid
scene11:
	./raytracer -input src/scene5_11_rotated_triangles.txt -size 200 200 -gui
scene11_0:
	./raytracer -input src/scene5_11_rotated_triangles.txt -size 200 200 -output output5_11.tga -gui -grid 15 15 9 -visualize_grid
scene12:
	./raytracer -input src/scene5_12_nested_transformations.txt -size 200 200 -gui
scene12_0:
	./raytracer -input src/scene5_12_nested_transformations.txt -size 200 200 -output output5_12.tga -gui -grid 30 30 30 -visualize_grid

