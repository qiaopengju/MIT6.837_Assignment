# Simple Makefile for 6.837 curve editing assignment
# for g++ on linux platforms

# ===============================================================

SRCS 	 	= main.cpp \
		  ../matrix.C \
		  glCanvas.cpp \
		  spline_parser.cpp \
		  triangle_mesh.cpp \


# ===============================================================
# NOTE:  On athena, the Mesa GL libraries are currently located in the
#        mesa_v501 locker.  Type "add mesa_v501" to access these files.

LIBS = -framework OpenGL -framework GLUT
FLAG 	= -I/mit/mesa_v501/Mesa-5.0.1/include/ -I../ -std=c++11
INCLUDE = spline.h surface.h curve.h
CC		= clang++
EXE	  	= curve_editor
OBJS =  $(SRCS:.C=.o)

# ===============================================================
# targets

.PHONY: all depend clean

all: depend $(EXE)

depend:
	$(CC) $(FLAG) -E -M $(SRCS) > Makefile.depend

clean: 
	-rm -f *~ *bak *.o  core.* Makefile.depend $(EXE) 

# ===============================================================
# compilation rules

$(EXE): $(OBJS) $(INCLUDE)
	$(CC) $(FLAG) -o $@ $(OBJS) $(LIBS)

.C.o:
	$(CC) $(FLAG) $< -c -o $@

# ===============================================================

-include Makefile.depend

# ===============================================================
# RUN
scene1:
	./curve_editor -input src/spline8_01_bezier.txt -gui -curve_tessellation 30
scene2:
	./curve_editor -input src/spline8_02_bspline.txt -gui -curve_tessellation 30
scene3:
	./curve_editor -input src/spline8_01_bezier.txt -output_bezier output8_01_bezier.txt
not_complete:
	./curve_editor -input src/spline8_01_bezier.txt -output_bspline output8_01_bspline.txt
	./curve_editor -input src/spline8_02_bspline.txt -output_bezier output8_02_bezier.txt
	./curve_editor -input src/spline8_02_bspline.txt -output_bspline output8_02_bspline.txt
	./curve_editor -input src/output8_01_bezier.txt -gui -curve_tessellation 30
	./curve_editor -input src/output8_01_bspline.txt -gui -curve_tessellation 30
	./curve_editor -input src/output8_02_bezier.txt -gui -curve_tessellation 30
	./curve_editor -input src/output8_02_bspline.txt -gui -curve_tessellation 30
test:
	./curve_editor -input src/spline8_03_bezier.txt -gui -curve_tessellation 30
	./curve_editor -input src/spline8_04_bspline.txt -gui -curve_tessellation 30
	./curve_editor -input src/spline8_05_bspline_dups.txt -gui -curve_tessellation 30
not_complete1:
	./curve_editor -input src/spline8_06_torus.txt -curve_tessellation 4 -gui
	./curve_editor -input src/spline8_06_torus.txt -curve_tessellation 4 -revolution_tessellation 10 -output torus_low.obj
	./curve_editor -input src/spline8_06_torus.txt -curve_tessellation 30 -revolution_tessellation 60 -output torus_high.obj
	./../Assignment7/raytracer -input src/scene8_06_torus_low.txt -gui -size 300 300
	./../Assignment7/raytracer -input src/scene8_06_torus_high.txt -gui -size 300 300
	./curve_editor -input src/spline8_07_vase.txt -curve_tessellation 4 -output_bspline output8_07_edit.txt -gui
	./curve_editor -input src/output8_07_edit.txt -curve_tessellation 4 -revolution_tessellation 10 -output vase_low.obj
	./curve_editor -input src/output8_07_edit.txt -curve_tessellation 10 -revolution_tessellation 60 -output vase_high.obj
	./../Assignment7/raytracer -input src/scene8_07_vase_low.txt -gui -size 300 300
	./../Assignment7/raytracer -input src/scene8_07_vase_high.txt -gui -size 300 300
	./curve_editor -input src/spline8_08_bezier_patch.txt -gui
	./curve_editor -input src/spline8_08_bezier_patch.txt -patch_tessellation 4 -output patch_low.obj
	./curve_editor -input src/spline8_08_bezier_patch.txt -patch_tessellation 10 -output patch_med.obj
	./curve_editor -input src/spline8_08_bezier_patch.txt -patch_tessellation 40 -output patch_high.obj
	./../Assignment7/raytracer -input src/scene8_08_bezier_patch_low.txt -gui -size 300 300
	./../Assignment7/raytracer -input src/scene8_08_bezier_patch_med.txt -gui -size 300 300
	./../Assignment7/raytracer -input src/scene8_08_bezier_patch_high.txt -gui -size 300 300
	./curve_editor -input src/spline8_09_teapot.txt -curve_tessellation 4 -gui
	./curve_editor -input src/spline8_09_teapot.txt -patch_tessellation 4 -curve_tessellation 4 -revolution_tessellation 10 -output teapot_low.obj
	./curve_editor -input src/spline8_09_teapot.txt -patch_tessellation 30 -curve_tessellation 30 -revolution_tessellation 100 -output teapot_high.obj
	./../Assignment7/raytracer -input src/scene8_09_teapot_low.txt -gui -size 300 300
	./../Assignment7/raytracer -input src/scene8_09_teapot_high.txt -gui -size 300 300
	./curve_editor -input src/output8_07_edit.txt -curve_tessellation 20 -revolution_tessellation 100 -output vase_very_high.obj
	./../Assignment7/raytracer -input src/scene8_10_transparent_vase.txt -output output8_10.tga -grid 30 30 30 -size 300 300 -bounces 4 -shade_back -jittered_samples 9 -tent_filter 1.0 -shadows
	./../Assignment7/raytracer -input src/scene8_11_reflective_teapot.txt -output output8_11.tga -grid 50 30 30 -size 300 300 -bounces 4 -shade_back -jittered_samples 9 -tent_filter 1.0 -shadows

