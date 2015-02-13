#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "Advanced.h"
#include "Image.h"

/*Posterize Image*/
void Posterize( IMAGE *image)
{
    unsigned char pbits = 6;
    
    unsigned char maskzero[8] = {0xff-0x1, 0xff-0x2, 0xff-0x4, 0xff-0x8, 0xff-0x10, 0xff-0x20, 0xff-0x40, 0xff-0x80};
    unsigned char maskone[8]  = {0x0     , 0x1     , 0x3     , 0x7     , 0xf      , 0x1f     , 0x3f     , 0x7f     };
    
    int x, y;
    
    unsigned char R[image->Width][image->Height];
    unsigned char G[image->Width][image->Height];
    unsigned char B[image->Width][image->Height];
    
    for(x = 0; x < image->Width; x ++)
    {
        for(y = 0; y < image->Height; y ++)
        {
            R[x][y] = GetPixelR(image, x, y);
            G[x][y] = GetPixelG(image, x, y);
            B[x][y] = GetPixelB(image, x, y);
            
            R[x][y] &= maskzero[pbits - 1];
            R[x][y] |= maskone[pbits - 1];
            
            G[x][y] &= maskzero[pbits - 1];
            G[x][y] |= maskone[pbits - 1];
            
            B[x][y] &= maskzero[pbits - 1];
            B[x][y] |= maskone[pbits - 1];
            
            SetPixelR(image, x, y, R[x][y]);
            SetPixelG(image, x, y, G[x][y]);
            SetPixelB(image, x, y, B[x][y]);
        }
    }
}

/* Add christmas lights */
void FillLight( int number, int lightWidth,  IMAGE *image)
{
    srand((unsigned)time(NULL));
    
    int x, y, z;
    
    int topHeight =  image->Height - (lightWidth);
    int bottomHeight = lightWidth/2;
    int topWidth = image->Width - (lightWidth);
    int bottomWidth = (lightWidth/2);
    
    for (z =0; z < number; z++)
    {
        
        int color = (rand()%3); /*0 - RED, 1 - GREEN, 2 - BLUE*/
        int lightCenterY = bottomHeight + (rand()%topHeight);
        int lightCenterX = bottomWidth + (rand()%topWidth);
        
        
        /*Center to top-right*/
        for( x = lightCenterX, y = lightCenterY; x <= lightCenterX + lightWidth/2; x++, y--)
        {
            if(color == 0)
            {
                SetPixelR(image, x, y, 255);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 1)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 255);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 2)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 255);
            }
        }
        
        /*Center to right*/
        for( x = lightCenterX,  y = lightCenterY; x <= lightCenterX + lightWidth/2; x++)
        {
            if(color == 0)
            {
                SetPixelR(image, x, y, 255);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 1)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 255);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 2)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 255);
            }
        }
        
        /*Center too bottom-right*/
        for( x = lightCenterX,  y = lightCenterY; x <= lightCenterX + lightWidth/2; x++, y++)
        {
            if(color == 0)
            {
                SetPixelR(image, x, y, 255);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 1)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 255);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 2)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 255);
            }
        }
        
        /*Center to bottom*/
        for( x = lightCenterX,  y = lightCenterY; y <= lightCenterY + lightWidth/2; y++)
        {
            if(color == 0)
            {
                SetPixelR(image, x, y, 255);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 1)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 255);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 2)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 255);
            }
        }
        
        /*Center to bottom-left*/
        for( x = lightCenterX,  y = lightCenterY; x >= lightCenterX - lightWidth/2; x--, y++)
        {
            if(color == 0)
            {
                SetPixelR(image, x, y, 255);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 1)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 255);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 2)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 255);
            }
        }
        
        /*Center to left*/
        for( x = lightCenterX,  y = lightCenterY; x >= lightCenterX - lightWidth/2; x--)
        {
            if(color == 0)
            {
                SetPixelR(image, x, y, 255);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 1)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 255);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 2)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 255);
            }
        }
        
        /*Center to top-left*/
        for( x = lightCenterX,  y = lightCenterY; x >= lightCenterX - lightWidth/2; x--, y--)
        {
            if(color == 0)
            {
                SetPixelR(image, x, y, 255);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 1)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 255);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 2)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 255);
            }
        }
        
        /*Center to top*/
        for( x = lightCenterX,  y = lightCenterY; y >= lightCenterY - lightWidth/2; y--)
        {
            if(color == 0)
            {
                SetPixelR(image, x, y, 255);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 1)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 255);
                SetPixelB(image, x, y, 0);
            }
            else if(color == 2)
            {
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 255);
            }
        }
    }
}


/*Mandelbrot*/

const unsigned char palette[MAX_COLOR][3] =
{
    /* r g b*/
    { 0, 0, 0 }, /* 0, black */
    { 127, 0, 0 }, /* 1, brown */
    { 255, 0, 0 }, /* 2, red */
    { 255, 127, 0 }, /* 3, orange */
    { 255, 255, 0 }, /* 4, yellow */
    { 127, 255, 0 }, /* 5, light green */
    { 0, 255, 0 }, /* 6, green */
    { 0, 255, 127 }, /* 7, blue green */
    { 0, 255, 255 }, /* 8, turquoise */
    { 127, 255, 255 }, /* 9, light blue */
    { 255, 255, 255 }, /* 10, white */
    { 255, 127, 255 }, /* 11, pink */
    { 255, 0, 255 }, /* 12, light pink */
    { 127, 0, 255 }, /* 13, purple */
    { 0, 0, 255 }, /* 14, blue */
    { 0, 0, 127 } /* 15, dark blue */
};

double scale(int valueIn, double baseMin, double baseMax, double limitMin, double limitMax)
{
    return ((limitMax - limitMin) * (valueIn - baseMin) / (baseMax - baseMin)) + limitMin;
}

IMAGE *Mandelbrot(unsigned int W, unsigned int H, unsigned int max_iteration)
{
    assert(W);
    assert(H);
    assert(max_iteration);
    
    IMAGE * mandelImage;
    mandelImage = malloc(sizeof(IMAGE));
    mandelImage = CreateImage(W, H);
    
    int i, j, iteration, color;
    double x, y, x0, y0, xtemp;
    for(i = 0; i < mandelImage->Width; i++)
    {
        for(j = 0; j < mandelImage->Height; j++)
        {
            x0 = scale(i, 0, mandelImage->Width, -2.5, 1);
            y0 = scale(j, 0, mandelImage->Height, -1, 1);
            
            x = 0;
            y = 0;
            iteration = 0;
            
            while ( x*x + y*y < 2*2 && iteration < max_iteration )
            {
                xtemp = x*x - y*y + x0;
                y = 2*x*y + y0;
                x = xtemp;
                iteration = iteration + 1;
            }
            
            color = iteration % 16;
            SetPixelR(mandelImage,i ,j, palette[color][0]);
            SetPixelG(mandelImage,i ,j, palette[color][1]);
            SetPixelB(mandelImage,i ,j, palette[color][2]);
        }
    }
    printf("Mandelbot image has been created!\n");
    return mandelImage;
}
