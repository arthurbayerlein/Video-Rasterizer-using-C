#include "Movie.h"
#include "ImageList.h"
#include "Image.h"

/* allocate the memory space for the movie */
/* and the memory space for the frame list. */
/* return the pointer to the movie */
MOVIE *CreateMovie(unsigned int nFrames, unsigned int W, unsigned int H)
{
    MOVIE * myMovie = (MOVIE*)malloc(sizeof(MOVIE));
    myMovie->Width = W;
    myMovie->Height = H;
    myMovie->NumFrames = nFrames;
    myMovie->Frames = NewImageList();
    
    
    return myMovie;
}

/*release the memory space for the frames and the frame list. */
/*release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
    assert(movie);
    DeleteImageList(movie->Frames);
    free(movie);
}

int clip(int x)
{
    if( x >= 0 && x <= 255) return x;
    else if(x < 0) return 0;
    else return 255;
}

/* convert a YUV image into a RGB image */
void YUV2RGBImage(IMAGE *Image)
{
    assert(Image);
    int x, y;
    for(x = 0; x < Image->Width; x++)
    {
        for(y = 0; y < Image->Height; y++)
        {
            int C = GetPixelY(Image, x, y) -16;
            int D = GetPixelU(Image, x, y) -128;
            int E = GetPixelV(Image, x, y) -128;
            unsigned char R = clip((298 *C +409 *E +128) >> 8);
            unsigned char G = clip((298 *C -100 *D-208 *E +128) >> 8);
            unsigned char B = clip((298 *C +516 *D+128) >> 8);
            
            SetPixelR(Image, x, y, R);
            SetPixelG(Image, x, y, G);
            SetPixelB(Image, x, y, B);
        }
    }
}

/* convert a RGB image into a YUV image */
void RGB2YUVImage(IMAGE *Image)
{
    assert(Image);
    
    int x, y;
    for(x = 0; x < Image->Width; x++)
    {
        for(y = 0; y < Image->Height; y++)
        {
            unsigned char R = GetPixelR(Image, x, y);
            unsigned char G = GetPixelG(Image, x, y);
            unsigned char B = GetPixelB(Image, x, y);
            
            unsigned char Y = clip(((66 *R+129 *G+25 *B+128) >> 8) +16);
            unsigned char U = clip(((-38 *R-74 *G+112 *B+128) >> 8) +128);
            unsigned char V = clip(((112 *R-94 *G-18 *B+128) >> 8) +128);
            
            SetPixelY(Image, x, y, Y);
            SetPixelU(Image, x, y, U);
            SetPixelV(Image, x, y, V);
        }
    }
}

