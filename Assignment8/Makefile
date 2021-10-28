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
INCLUDE 	= -I/mit/mesa_v501/Mesa-5.0.1/include/ -I../
CC		= clang++
EXE	  	= curve_editor
OBJS =  $(SRCS:.C=.o)

# ===============================================================
# targets

.PHONY: all depend clean

all: depend $(EXE)

depend:
	$(CC) $(INCLUDE) -E -M $(SRCS) > Makefile.depend

clean: 
	-rm -f *~ *bak *.o  core.* Makefile.depend $(EXE) 

# ===============================================================
# compilation rules

$(EXE): $(OBJS)
	$(CC) $(INCLUDE) -o $@ $(OBJS) $(LIBS)

.C.o:
	$(CC) $(INCLUDE) $< -c -o $@

# ===============================================================

-include Makefile.depend

