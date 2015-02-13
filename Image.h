#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
#include <assert.h>

typedef struct
{
    unsigned int Width;             /* image width */
    unsigned int Height;    /* image height */
    union {
        struct s_rgb
        {
            unsigned char *R ;
            unsigned char *G ;
            unsigned char *B ;
        } RGB ;
        struct s_yuv
        {
            unsigned char *Y ;
            unsigned char *U ;
            unsigned char *V ;
        } YUV  ;
    } Color;
    /*unsigned char *R_Y;            pointer to the memory storing all the R or Y intensity values */
    /*unsigned char *G_U;            pointer to the memory storing all the G or U intensity values */
    /*unsigned char *B_V;            pointer to the memory storing all the B or V intensity values */
}IMAGE;

/*Get the color intensity of the Red channel of pixel (x, y) in image */
unsigned char GetPixelR(IMAGE *image, unsigned int x,  unsigned int y);

/*Get the color intensity of the Green channel of pixel (x, y) in image */
unsigned char GetPixelG(IMAGE *image, unsigned int x,  unsigned int y);

/*Get the color intensity of the Blue channel of pixel (x, y) in image */
unsigned char GetPixelB(IMAGE *image, unsigned int x,  unsigned int y);

/*Set the color intensity of the Red channel of pixel (x, y) in image with value r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r);

/*Set the color intensity of the Green channel of pixel (x, y) in image with value g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g);

/*Set the color intensity of the Blue channel of pixel (x, y) in image with value b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b);

/* allocate the memory spaces for the image              */
/* and the memory spaces for the color intensity values. */
/* return the pointer to the image                       */
IMAGE *CreateImage(unsigned int Width, unsigned int Height);

/*release the memory spaces for the pixel color intensity values */
/*release the memory spaces for the image                        */
void DeleteImage(IMAGE *image);


/*Get the color intensity of the Y channel of pixel (x, y) in image */
unsigned char GetPixelY(IMAGE *image, unsigned int x,  unsigned int y);

/*Get the color intensity of the U channel of pixel (x, y) in image */
unsigned char GetPixelU(IMAGE *image, unsigned int x,  unsigned int y);

/*Get the color intensity of the V channel of pixel (x, y) in image */
unsigned char GetPixelV(IMAGE *image, unsigned int x,  unsigned int y);

/*Set the color intensity of the Y channel of pixel (x, y) in image with value y */
void SetPixelY(IMAGE *image, unsigned int x,  unsigned int y, unsigned char yuv_y);

/*Set the color intensity of the U channel of pixel (x, y) in image with value u */
void SetPixelU(IMAGE *image, unsigned int x,  unsigned int y, unsigned char yuv_u);

/*Set the color intensity of the V channel of pixel (x, y) in image with value v */
void SetPixelV(IMAGE *image, unsigned int x,  unsigned int y, unsigned char yuv_v);

/* allocate a new image list */
ILIST *NewImageList(void);

/* delete a image list (and all entries) */
void DeleteImageList(ILIST *l);

/* insert a frame into a list at the end*/
void AppendImage(ILIST *l, IMAGE *image);

/* reverse an image list */
void ReverseImageList(ILIST *l);

/*Crop frames from the list starting from SFrame to EFrame*/
void CropImageList(ILIST *l, unsigned int SFrame, unsigned int EFrame) ;

/*Resize the images in the list*/
void ResizeImageList(ILIST *l, unsigned int percentage) ;

/*Fast forward the video*/
unsigned int FastImageList(ILIST *l, unsigned int ff_factor) ;




#endif