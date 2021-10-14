# Simple Makefile for 6.837 raycasting assignment
# for g++ on linux platforms

# ===============================================================
OBJ_DIR = obj/
RAY_TRACER_DIR = ray_tracer/

SRCS 	 	= main.C \
		  ../matrix.C \
		  ../image.C \
		  scene_parser.C \
		  $(OBJ_DIR)/sphere.C \
		  $(OBJ_DIR)/group.C \
		  $(OBJ_DIR)/plane.C \
		  $(OBJ_DIR)/triangle.C \
		  $(OBJ_DIR)/transform.C \
		  $(RAY_TRACER_DIR)/camera.C

# ===============================================================

FLAG 	= -I../ -I$(RAY_TRACER_DIR) -I$(OBJ_DIR) -std=c++11
CC		= clang++
EXE	  	= raytracer
OBJS =  $(SRCS:.C=.o)

# ===============================================================
# targets

.PHONY: all depend clean clean_img

all: depend $(EXE)

depend:
	$(CC) -E -M $(SRCS) $(FLAG)> Makefile.depend

clean: 
	-rm -f *~ *bak *.o  ../*.o $(RAY_TRACER_DIR)/*.o $(OBJ_DIR)/*.o core.* Makefile.depend $(EXE)
clean_img:
	-rm -f *.tga *.ppm

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
scene5_no_back:
	./raytracer -input src/scene2_05_inside_sphere.txt -size 200 200 -output output2_05_no_back.tga
scene5_shade_back:
	./raytracer -input src/scene2_05_inside_sphere.txt -size 200 200 -output output2_05.tga -depth 9 11 depth2_05.tga -normals normals2_05.tga -shade_back
scene6:
	./raytracer -input src/scene2_06_plane.txt -size 200 200 -output output2_06.tga -depth 8 20 depth2_06.tga -normals normals2_06.tga
scene7_shade_back:
	./raytracer -input src/scene2_07_sphere_triangles.txt -size 200 200 -output output2_07.tga -depth 9 11 depth2_07.tga -normals normals2_07.tga -shade_back
scene7_no_back:
	./raytracer -input src/scene2_07_sphere_triangles.txt -size 200 200 -output output2_07_no_back.tga
cube:
	./raytracer -input src/scene2_08_cube.txt -size 200 200 -output output2_08.tga -depth 8 20 depth2_08.tga -normals normals2_08.tga
bunny200:
	./raytracer -input src/scene2_09_bunny_200.txt -size 200 200 -output output2_09.tga
bunny1k:
	./raytracer -input src/scene2_10_bunny_1k.txt -size 200 200 -output output2_10.tga
scene11:
	./raytracer -input src/scene2_11_squashed_sphere.txt -size 200 200 -output output2_11.tga -normals normals2_11.tga -depth 9 10 depth2_11.tga
scene12:
	./raytracer -input src/scene2_12_rotated_sphere.txt -size 200 200 -output output2_12.tga -normals normals2_12.tga
scene13:
	./raytracer -input src/scene2_13_rotated_squashed_sphere.txt -size 200 200 -output output2_13.tga -normals normals2_13.tga
scene14:
	./raytracer -input src/scene2_14_axes_cube.txt -size 200 200 -output output2_14.tga -normals normals2_14.tga
scene15:
	./raytracer -input src/scene2_15_crazy_transforms.txt -size 200 200 -output output2_15.tga
scene16:
	./raytracer -input src/scene2_16_t_scale.txt -size 200 200 -output output2_16.tga -depth 2 7 depth2_16.tga


# ===============================================================

-include Makefile.depend

