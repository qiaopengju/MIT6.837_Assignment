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