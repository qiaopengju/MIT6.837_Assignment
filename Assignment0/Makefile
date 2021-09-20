# Simple Makefile for 6.837 assignment 0
# for g++ on linux platforms

# ===============================================================

SRCS 	 	= main.C \
		  ../matrix.C \
		  ../image.C \
		  ifs.C

# ===============================================================

LIBS            = -lm 
CC		= clang++
INCLUDE 	= -I../
EXE 	  	= ifs
OBJS =  $(SRCS:.C=.o)

# ===============================================================
# targets

.PHONY: all depend clean

all: depend $(EXE) 

depend:
	#$(CC) -E -M $(INCLUDE) $(SRCS) > Makefile.depend

clean: 
	rm -f *~ *bak *.o ../*.o $(EXE) Makefile.depend *.ppm *.tga

# ===============================================================
# run EXE
T0:
	./ifs -input src/sierpinski_triangle.txt -points 10000 -iters 0 -size 200 -output sierpinski_triangle_0.tga
T1:
	./ifs -input src/sierpinski_triangle.txt -points 10000 -iters 1 -size 200 -output sierpinski_triangle_1.tga
T2:
	./ifs -input src/sierpinski_triangle.txt -points 10000 -iters 2 -size 200 -output sierpinski_triangle_2.tga
T3:
	./ifs -input src/sierpinski_triangle.txt -points 10000 -iters 3 -size 200 -output sierpinski_triangle_3.tga
T4:
	./ifs -input src/sierpinski_triangle.txt -points 10000 -iters 4 -size 200 -output sierpinski_triangle_4.tga
T30:
	./ifs -input src/sierpinski_triangle.txt -points 10000 -iters 30 -size 200 -output sierpinski_triangle_30.tga
fern:
	./ifs -input src/fern.txt -points 50000 -iters 30 -size 400 -output fern.tga


# ===============================================================
# compilation rules

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

.C.o:
	$(CC) $< -c -o $@  $(INCLUDE)
# ===============================================================

-include Makefile.depend

# DO NOT DELETE
