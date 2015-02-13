# Makefile:  MovieLab
# 12/7/2014 GI

# variable definitions
CC     = gcc
DEBUG  = -g -DDEBUG
#DEBUG = -02 -DNDEBUG
CFLAGS = -Wall -lm -ansi $(DEBUG) -c
LFLAGS = -Wall -lm $(DEBUG)

# convenience targets
all: MovieLab

clean:
rm -f *.o
rm -f MovieLab

#compliation rules

DIPs.o:  DIPs.c DIPs.h Constants.h Image.h
$(CC) $(CFLAGS) DIPs.c -o DIPs.o

Advanced.o:  Advanced.c Advanced.h Constants.h Image.h
$(CC) $(CFLAGS) Advanced.c -o Advanced.o

Movie.o:  Movie.c Movie.h Image.h ImageList.h
$(CC) $(CFLAGS) Movie.c -o Movie.o

ImageList.o:  ImageList.c ImageList.h Image.h Advanced.h
$(CC) $(CFLAGS) ImageList.c -o ImageList.o

Image.o:  Image.c Image.h
$(CC) $(CFLAGS) Image.c -o Image.o

MovieLab.o:  MovieLab.c Constants.h DIPs.h Advanced.h Image.h ImageList.h Movie.h DIPs.h
$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o

MovieLab:  DIPs.o Advanced.o MovieLab.o Image.o Movie.o ImageList.o
$(CC) $(LFLAGS) DIPs.o Advanced.o Image.o MovieLab.o Movie.o ImageList.o -o MovieLab
