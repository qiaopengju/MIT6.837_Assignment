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
		$(RAY_TRACER_DIR)/raytracer.C \
		$(RAY_TRACER_DIR)/material.C \
		$(RAY_TRACER_DIR)/light.C \
		$(RAY_TRACER_DIR)/camera.C \
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
scene1:
	./raytracer -input src/scene4_01_sphere_shadow.txt -size 200 200 -output output4_01.tga -shadows #-gui -tessellation 50 25 -gouraud
scene2:
	./raytracer -input src/scene4_02_colored_shadows.txt -size 200 200 -output output4_02.tga -shadows -gui -tessellation 50 25 -gouraud
scene3:
	./raytracer -input src/scene4_03_mirrored_floor.txt -size 200 200 -output output4_03.tga -shadows -bounces 1 -weight 0.01 -gui
scene40:
	./raytracer -input src/scene4_04_reflective_sphere.txt -size 200 200 -output output4_04a.tga -shadows -bounces 0 -weight 0.01 
scene41:
	./raytracer -input src/scene4_04_reflective_sphere.txt -size 200 200 -output output4_04b.tga -shadows -bounces 1 -weight 0.01 -gui
scene42:
	./raytracer -input src/scene4_04_reflective_sphere.txt -size 200 200 -output output4_04c.tga -shadows -bounces 2 -weight 0.01 -gui
scene43:
	./raytracer -input src/scene4_04_reflective_sphere.txt -size 200 200 -output output4_04d.tga -shadows -bounces 3 -weight 0.01 -gui
scene5:
	./raytracer -input src/scene4_05_transparent_bar.txt -size 200 200 -output output4_05.tga -shadows -bounces 10 -weight 0.01 -shade_back -gui
scene60:
	./raytracer -input src/scene4_06_transparent_bars.txt -size 200 200 -output output4_06a.tga -shadows -bounces 0 -weight 0.01 -shade_back -gui
scene61:
	./raytracer -input src/scene4_06_transparent_bars.txt -size 200 200 -output output4_06b.tga -shadows -bounces 1 -weight 0.01 -shade_back -gui
scene62:
	./raytracer -input src/scene4_06_transparent_bars.txt -size 200 200 -output output4_06c.tga -shadows -bounces 2 -weight 0.01 -shade_back -gui
scene63:
	./raytracer -input src/scene4_06_transparent_bars.txt -size 200 200 -output output4_06d.tga -shadows -bounces 3 -weight 0.01 -shade_back -gui
scene64:
	./raytracer -input src/scene4_06_transparent_bars.txt -size 200 200 -output output4_06e.tga -shadows -bounces 4 -weight 0.01 -shade_back -gui
scene65:
	./raytracer -input src/scene4_06_transparent_bars.txt -size 200 200 -output output4_06f.tga -shadows -bounces 5 -weight 0.01 -shade_back -gui
scene7:
	./raytracer -input src/scene4_07_transparent_sphere_1.0.txt -size 200 200 -output output4_07.tga -shadows -bounces 5 -weight 0.01 -shade_back -gui -tessellation 30 15
scene8:
	./raytracer -input src/scene4_08_transparent_sphere_1.1.txt -size 200 200 -output output4_08.tga -shadows -bounces 5 -weight 0.01 -shade_back -gui -tessellation 30 15
scene9:
	./raytracer -input src/scene4_09_transparent_sphere_2.0.txt -size 200 200 -output output4_09.tga -shadows -bounces 5 -weight 0.01 -shade_back -gui -tessellation 30 15
scene10:
	./raytracer -input src/scene4_10_point_light_distance.txt -size 200 200 -output output4_10.tga -shadows -gui
scene11:
	./raytracer -input src/scene4_11_point_light_circle.txt -size 200 200 -output output4_11.tga -shadows 
scene12:
	./raytracer -input src/scene4_12_point_light_circle_d_attenuation.txt -size 200 200 -output output4_12.tga -shadows 
scene13:
	./raytracer -input src/scene4_13_point_light_circle_d2_attenuation.txt -size 200 200 -output output4_13.tga -shadows 
scene140:
	./raytracer -input src/scene4_14_faceted_gem.txt -size 200 200 -output output4_14a.tga -shadows -shade_back -bounces 0 -weight 0.01 
scene141:
	./raytracer -input src/scene4_14_faceted_gem.txt -size 200 200 -output output4_14b.tga -shadows -shade_back -bounces 1 -weight 0.01 -gui
scene142:
	./raytracer -input src/scene4_14_faceted_gem.txt -size 200 200 -output output4_14c.tga -shadows -shade_back -bounces 2 -weight 0.01 -gui
scene143:
	./raytracer -input src/scene4_14_faceted_gem.txt -size 200 200 -output output4_14d.tga -shadows -shade_back -bounces 3 -weight 0.01 
scene144:
	./raytracer -input src/scene4_14_faceted_gem.txt -size 200 200 -output output4_14e.tga -shadows -shade_back -bounces 4 -weight 0.01 
scene145:
	./raytracer -input src/scene4_14_faceted_gem.txt -size 200 200 -output output4_14f.tga -shadows -shade_back -bounces 5 -weight 0.01