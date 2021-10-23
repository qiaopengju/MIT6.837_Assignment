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
		$(OBJ_DIR)/object3d.C \
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
		$(RAY_TRACER_DIR)/raytracing_stats.C \
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
FLAG = -O2 -I../GL -I$(OBJ_DIR) -I$(RAY_TRACER_DIR) -I../ -std=c++11

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
	./raytracer -input src/scene6_01_sphere.txt -output output6_01a.tga -size 200 200
scene1_1:
	./raytracer -input src/scene6_01_sphere.txt -output output6_01b.tga -size 200 200 -grid 10 10 10 -gui -visualize_grid
scene2_0:
	./raytracer -input src/scene6_02_sphere_triangles.txt -output output6_02a.tga -size 200 200 -shadows
scene2_1:
	./raytracer -input src/scene6_02_sphere_triangles.txt -output output6_02b.tga -size 200 200 -grid 10 10 10 -shadows -gui -visualize_grid
scene3_0:
	./raytracer -input src/scene6_03_sphere_plane.txt -output output6_03c.tga -size 200 200 -shadows
scene3_1:
	./raytracer -input src/scene6_03_sphere_plane.txt -output output6_03d.tga -size 200 200 -grid 10 10 10 -shadows -visualize_grid -gui
scene4:
	./raytracer -input src/scene6_04_bunny_mesh_200.txt -output output6_04c.tga -size 200 200 -shadows
scene5:
	./raytracer -input src/scene6_05_bunny_mesh_1k.txt  -output output6_05.tga -size 200 200 -grid 15 15 12 -shadows
scene6:
	./raytracer -input src/scene6_06_bunny_mesh_5k.txt  -output output6_06.tga -size 200 200 -grid 20 20 15 -shadows
scene7:
	./raytracer -input src/scene6_07_bunny_mesh_40k.txt -output output6_07.tga -size 200 200 -grid 40 40 33 -shadows -gui -visualize_grid
scene8:
	./raytracer -input src/scene6_08_scale_translate.txt -size 200 200 -output output6_08c.tga -grid 15 15 15 -visualize_grid
scene9:
	./raytracer -input src/scene6_09_rotated_triangles.txt -size 200 200 -output output6_09c.tga -grid 15 15 9 -visualize_grid
scene10:
	./raytracer -input src/scene6_10_nested_transformations.txt -size 200 200 -output output6_10c.tga -grid 30 30 30 -visualize_grid
scene11:
	./raytracer -input src/scene6_11_mirrored_floor.txt -size 200 200 -output output6_11b.tga -shadows -bounces 1 -weight 0.01 -grid 40 10 40 -gui
scene12:
	./raytracer -input src/scene6_12_faceted_gem.txt -size 200 200 -output output6_12b.tga -shadows -shade_back -bounces 5 -weight 0.01 -grid 20 20 20
scene13:
	./raytracer -input src/scene6_13_checkerboard.txt -size 200 200 -output output6_13.tga -shadows 
scene14:
	./raytracer -input src/scene6_14_glass_sphere.txt -size 200 200 -output output6_14.tga -shadows -shade_back -bounces 5 -weight 0.01 -grid 20 20 20
scene15:
	./raytracer -input src/scene6_15_marble_cubes.txt -size 300 300 -output output6_15.tga 
scene16:
	./raytracer -input src/scene6_16_wood_cubes.txt -size 300 300 -output output6_16.tga
scene17:
	./raytracer -input src/scene6_17_marble_vase.txt -size 300 300 -output output6_17a.tga -grid 15 30 15 -bounces 1 -shadows -gui -visualize_grid
scene18:
	./raytracer -input src/scene6_18_6.837_logo.txt -size 400 200 -output output6_18a.tga -shadows -shade_back -bounces 5 -weight 0.01 -grid 80 30 3 -gui -visualize_grid