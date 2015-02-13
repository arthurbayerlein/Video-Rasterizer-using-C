#ifndef Advanced__H
#define Advanced__H
#define MAX_COLOR 16

#include <stdio.h>
#include "Constants.h"
#include "Image.h"

/*Posterize Image*/
void Posterize( IMAGE *image);

/* Add noise to image */
void FillLight( int number, int lightWidth,  IMAGE *image);

/* Overlay with another image */
void Overlay(char fname[SLEN], IMAGE *image, int x_offset, int y_offset);

/* Perform Cut Paste operations on the image*/
void CutPaste( IMAGE *image, unsigned int startX, unsigned int startY, unsigned int x_width, unsigned int y_width, unsigned int pasteNumber);

/*Mandelbrot*/
IMAGE *Mandelbrot(unsigned int W, unsigned int H, unsigned int max_iteration);

#endif /* defined(__Assignment_3__Advanced__) */
