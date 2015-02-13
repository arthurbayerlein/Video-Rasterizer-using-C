#include "Constants.h"
#include "Image.h"
#include <math.h>

#ifndef DIPs_H
#define DIPs_H

/* change color image to black & white */
void    BlackNWhite(IMAGE *image);

/* flip image vertically */
void    VFlip(IMAGE *image);

/* mirror image horizontally */
void    HMirror(IMAGE *image);

/* color filter */
void    ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) ;

/* sharpen the image */
void    Shuffle(IMAGE *image);

/* edge detection */
void    Edge(IMAGE *image);

/* add border */
void    AddBorder(IMAGE *image, char color[SLEN], int border_width);

/*Resize*/
IMAGE *Resize(unsigned int percentage, IMAGE *image);

/*Rotate 90 degrees clockwise*/
IMAGE *Rotate(IMAGE *image);


#endif
