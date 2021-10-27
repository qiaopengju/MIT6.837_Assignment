# Simple Makefile for 6.837 raycasting assignment
# for g++ on linux platforms

# ===============================================================
# update this list as you add new C++ source files
OBJ_DIR = ../obj
RAY_TRACER_DIR = ../ray_tracer
SAMPLE_DIR = $(RAY_TRACER_DIR)/sample
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
		$(RAY_TRACER_DIR)/grid.C \
		$(RAY_TRACER_DIR)/raytracer.C \
		$(RAY_TRACER_DIR)/material.C \
		$(RAY_TRACER_DIR)/light.C \
		$(RAY_TRACER_DIR)/camera.C \
		$(RAY_TRACER_DIR)/boundingbox.C \
		$(RAY_TRACER_DIR)/raytracing_stats.C \
		$(RAY_TRACER_DIR)/texture/perlin_noise.C \
		$(RAY_TRACER_DIR)/sample/film.C \
		$(RAY_TRACER_DIR)/sample/filter.C \
		$(RAY_TRACER_DIR)/sample/sampler.C \
		../GL/rayTree.C \
		../GL/glCanvas.C \
		#$(SAMPLE_DIR)/film.C \

# ===============================================================
# NOTE:  On athena, the Mesa GL libraries are currently located in the
#        mesa_v501 locker.  Type "add mesa_v501" to access these files.

LIBS = -framework OpenGL -framework GLUT
INCLUDE = -I/mit/mesa_v501/Mesa-5.0.1/include/ 
CC = clang++
EXE = raytracer
OBJS =  $(SRCS:.C=.o)
FLAG = -O2 -I../GL -I$(OBJ_DIR) -I$(RAY_TRACER_DIR) -I../ -I$(SAMPLE_DIR) -std=c++11

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
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 180 180 -output output7_01.tga 
# ===============sampler
scene1_1:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_samples samples7_01a.tga 20 -random_samples 4
scene1_2:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_samples samples7_01b.tga 20 -uniform_samples 4
scene1_3:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_samples samples7_01c.tga 20 -jittered_samples 4
scene1_4:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_samples samples7_01d.tga 20 -random_samples 9
scene1_5:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_samples samples7_01e.tga 20 -uniform_samples 9
scene1_6:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_samples samples7_01f.tga 20 -jittered_samples 9
scene1_7:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_samples samples7_01g.tga 20 -random_samples 36
scene1_8:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_samples samples7_01h.tga 20 -uniform_samples 36
scene1_9:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_samples samples7_01i.tga 20 -jittered_samples 36
# ===============filter
scene2_1:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_filter filter7_01a.tga 20 -box_filter 0.5
scene2_2:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_filter filter7_01b.tga 20 -tent_filter 0.5
scene2_3:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_filter filter7_01c.tga 20 -gaussian_filter 0.5
scene2_4:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_filter filter7_01d.tga 20 -box_filter 1.7
scene2_5:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_filter filter7_01e.tga 20 -tent_filter 1.7
scene2_6:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_filter filter7_01f.tga 20 -gaussian_filter 1.7
scene2_7:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_filter filter7_01g.tga 20 -box_filter 2.3
scene2_8:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_filter filter7_01h.tga 20 -tent_filter 2.3
scene2_9:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 9 9 -render_filter filter7_01i.tga 20 -gaussian_filter 2.3
# ===============filter result
scene3:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -output output7_01_low_res.tga
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -render_samples low_res_random_samples7_01a.tga 15 -random_samples 9 
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -render_samples low_res_uniform_samples7_01b.tga 15 -uniform_samples 9
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -render_samples low_res_jittered_samples7_01c.tga 15 -jittered_samples 9
scene3_1:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -render_filter box_filter7_01a_low_res.tga 15 -box_filter 0.5
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -output box_rand_output7_01a_low_res.tga -random_samples 9 -box_filter 0.5
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -output box_unif_output7_01d_low_res.tga -uniform_samples 9 -box_filter 0.5
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -output box_jitt_output7_01g_low_res.tga -jittered_samples 9 -box_filter 0.5
scene3_2:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -render_filter tent_filter7_01b_low_res.tga 15 -tent_filter 1.5
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -output tent_rand_output7_01b_low_res.tga -random_samples 9 -tent_filter 1.5
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -output tent_unif_output7_01e_low_res.tga -uniform_samples 9 -tent_filter 1.5
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -output tent_jitt_output7_01h_low_res.tga -jittered_samples 9 -tent_filter 1.5
scene3_3:
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -render_filter gaussian_filter7_01c_low_res.tga 15 -gaussian_filter 1.0
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -output gaussian_rand_output7_01c_low_res.tga -random_samples 9 -gaussian_filter 1.0
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -output gaussian_unif_output7_01f_low_res.tga -uniform_samples 9 -gaussian_filter 1.0
	./raytracer -input src/scene7_01_sphere_triangle.txt -size 12 12 -output gaussian_jitt_output7_01i_low_res.tga -jittered_samples 9 -gaussian_filter 1.0
test:
	./raytracer -input ../Assignment4/src/scene4_04_reflective_sphere.txt -size 200 200 -output test.tga -shadows -bounces 3 -weight 0.01 -jittered_samples 9 -tent_filter 2
# ===============
texture:
	./raytracer -input src/scene7_02_checkerboard.txt -size 180 180 -output output7_02.tga 
	./raytracer -input src/scene7_02_checkerboard.txt -size 9 9 -render_samples samples7_02a.tga 20 -random_samples 16
	./raytracer -input src/scene7_02_checkerboard.txt -size 9 9 -render_samples samples7_02b.tga 20 -uniform_samples 16
	./raytracer -input src/scene7_02_checkerboard.txt -size 9 9 -render_samples samples7_02c.tga 20 -jittered_samples 16
	./raytracer -input src/scene7_02_checkerboard.txt -size 9 9 -render_filter filter7_02a.tga 20 -box_filter 0.5
	./raytracer -input src/scene7_02_checkerboard.txt -size 9 9 -render_filter filter7_02b.tga 20 -tent_filter 1.5
	./raytracer -input src/scene7_02_checkerboard.txt -size 9 9 -render_filter filter7_02c.tga 20 -gaussian_filter 0.6
	./raytracer -input src/scene7_02_checkerboard.txt -size 180 180 -output output7_02a.tga -random_samples 16 -box_filter 0.5
	./raytracer -input src/scene7_02_checkerboard.txt -size 180 180 -output output7_02b.tga -random_samples 16 -tent_filter 1.5
	./raytracer -input src/scene7_02_checkerboard.txt -size 180 180 -output output7_02c.tga -random_samples 16 -gaussian_filter 0.6
	./raytracer -input src/scene7_02_checkerboard.txt -size 180 180 -output output7_02d.tga -uniform_samples 16 -box_filter 0.5
	./raytracer -input src/scene7_02_checkerboard.txt -size 180 180 -output output7_02e.tga -uniform_samples 16 -tent_filter 1.5
	./raytracer -input src/scene7_02_checkerboard.txt -size 180 180 -output output7_02f.tga -uniform_samples 16 -gaussian_filter 0.6
	./raytracer -input src/scene7_02_checkerboard.txt -size 180 180 -output output7_02g.tga -jittered_samples 16 -box_filter 0.5
	./raytracer -input src/scene7_02_checkerboard.txt -size 180 180 -output output7_02h.tga -jittered_samples 16 -tent_filter 1.5
	./raytracer -input src/scene7_02_checkerboard.txt -size 180 180 -output output7_02i.tga -jittered_samples 16 -gaussian_filter 0.6
texture2:
	./raytracer -input src/scene7_03_marble_vase.txt  -size 200 200 -output output7_03a.tga -grid 15 30 15 -shadows
	./raytracer -input src/scene7_03_marble_vase.txt  -size 200 200 -output output7_03b.tga -grid 15 30 15 -shadows -jittered_samples 4 -gaussian_filter 0.4
	./raytracer -input src/scene7_03_marble_vase.txt  -size 200 200 -output output7_03c.tga -grid 15 30 15 -shadows -jittered_samples 9 -gaussian_filter 0.4
	./raytracer -input src/scene7_03_marble_vase.txt  -size 200 200 -output output7_03d.tga -grid 15 30 15 -shadows -jittered_samples 36 -gaussian_filter 0.4
texture3:
	./raytracer -input src/scene7_04_6.837_logo.txt -size 400 200 -output output7_04a.tga -shadows -shade_back -bounces 5 -weight 0.01 -grid 80 30 3
	./raytracer -input src/scene7_04_6.837_logo.txt -size 400 200 -output output7_04b.tga -shadows -shade_back -bounces 5 -weight 0.01 -grid 80 30 3 -jittered_samples 9 -gaussian_filter 0.4
mirror:
	./raytracer -input src/scene7_05_glass_sphere.txt -size 300 300 -output output7_05a.tga -shadows -shade_back -bounces 5 -weight 0.01 -grid 20 20 20
	./raytracer -input src/scene7_05_glass_sphere.txt -size 300 300 -output output7_05b.tga -shadows -shade_back -bounces 5 -weight 0.01 -grid 20 20 20 -jittered_samples 4 -gaussian_filter 0.4
	./raytracer -input src/scene7_05_glass_sphere.txt -size 300 300 -output output7_05c.tga -shadows -shade_back -bounces 5 -weight 0.01 -grid 20 20 20 -jittered_samples 16 -gaussian_filter 0.4
diamond:
	./raytracer -input src/scene7_06_faceted_gem.txt -size 200 200 -output output7_06a.tga -shadows -shade_back -bounces 5 -weight 0.01 -grid 20 20 20 
	./raytracer -input src/scene7_06_faceted_gem.txt -size 200 200 -output output7_06b.tga -shadows -shade_back -bounces 5 -weight 0.01 -grid 20 20 20 -jittered_samples 9 -gaussian_filter 0.4
