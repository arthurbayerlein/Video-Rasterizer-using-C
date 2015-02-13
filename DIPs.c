#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "DIPs.h"
#include "Constants.h"
#include "Image.h"

void BlackNWhite(IMAGE *image)
{
    int avg;
    int x,y;
    
    for (y = 0; y < image->Height; y++)
        for (x = 0; x < image->Width; x++)
        {
            avg = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y))/ 3;
            SetPixelR(image, x, y, avg);
            SetPixelG(image, x, y, avg);
            SetPixelB(image, x, y, avg);
        }
}

void VFlip(IMAGE *image)
{
    int             x, y;
    unsigned char   r, g, b;
    unsigned int WIDTH;
    unsigned int HEIGHT;
    
    assert(image);
    WIDTH 	= image->Width;
    HEIGHT = image->Height;
    
    for (y = 0; y < HEIGHT/2; y++) {
        for (x = 0; x < WIDTH; x++) {
            r = GetPixelR(image, x, HEIGHT - 1 - y);
            g = GetPixelG(image, x, HEIGHT - 1 - y);
            b = GetPixelB(image, x, HEIGHT - 1 - y);
            
            SetPixelR(image, x, HEIGHT - 1 - y, GetPixelR(image, x, y));
            SetPixelG(image, x, HEIGHT - 1 - y, GetPixelG(image, x, y));
            SetPixelB(image, x, HEIGHT - 1 - y, GetPixelB(image, x, y));
            
            SetPixelR(image, x, y, r);
            SetPixelG(image, x, y, g);
            SetPixelB(image, x, y, b);
        }
    }
}

void HMirror(IMAGE *image)
{
    int x, y;
    
    for (y = 0; y < image->Height; y++)
        for (x = 0; x < (image->Width); x++)
        {
            SetPixelR(image, x, y, GetPixelR(image, image->Width-x, y));
            SetPixelG(image, x, y, GetPixelG(image, image->Width-x, y));
            SetPixelB(image, x, y, GetPixelB(image, image->Width-x, y));
        }

}

void ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b)
{
    int x = 0, y = 0;
    
    for (y = 0; y < image->Height; y++)
        for (x = 0; x < image->Width; x++)
        {
            if (GetPixelR(image, x, y) > (target_r - threshold) && GetPixelR(image, x, y) < (target_r + threshold) &&
                GetPixelG(image, x, y) > (target_g - threshold) && GetPixelG(image, x, y) < (target_g + threshold) &&
                GetPixelB(image, x, y) > (target_b - threshold) && GetPixelB(image, x, y) < (target_b + threshold) )
            {
                SetPixelR(image, x, y, replace_r);
                SetPixelG(image, x, y, replace_g);
                SetPixelB(image, x, y, replace_b);
            }
        }
}




void Edge(IMAGE *image)
{
    int             x, y, m, n, a, b;
    int             tmpR = 0;
    int             tmpG = 0;
    int             tmpB = 0;
    
    unsigned char   R_tmp[image->Width][image->Height];
    unsigned char   G_tmp[image->Width][image->Height];
    unsigned char   B_tmp[image->Width][image->Height];
    
    for (y = 0; y < image->Height; y++)
    {
        for (x = 0; x < image->Width; x++)
        {
            R_tmp[x][y] = GetPixelR(image, x, y);
            G_tmp[x][y] = GetPixelG(image, x, y);
            B_tmp[x][y] = GetPixelB(image, x, y);
        }
    }
    
    for (y = 0; y < image->Height; y++)
    {
        for (x = 0; x < image->Width; x++)
        {
            for (n = -1; n <= 1; n++)
            {
                for (m = -1; m <= 1; m++)
                {
                    a = x + m;
                    b = y + n;
                    if (a > image->Width - 1)
                        a = image->Width - 1;
                    if (a < 0)
                        a = 0;
                    if (b > image->Height - 1)
                        b = image->Height - 1;
                    if (b < 0)
                        b = 0;
                    
                    if ((n==0)&&(m==0))
                    {
                        tmpR += 8*R_tmp[a][b] ;
                        tmpG += 8*G_tmp[a][b] ;
                        tmpB += 8*B_tmp[a][b] ;
                    }
                    else
                    {
                        tmpR -= R_tmp[a][b] ;
                        tmpG -= G_tmp[a][b] ;
                        tmpB -= B_tmp[a][b] ;
                    }
                }
            }
            SetPixelR(image, x, y, (tmpR>255)? 255: (tmpR<0)? 0: tmpR );
            SetPixelG(image, x, y, (tmpG>255)? 255: (tmpG<0)? 0: tmpG );
            SetPixelB(image, x, y, (tmpB>255)? 255: (tmpB<0)? 0: tmpB );
            tmpR = tmpG = tmpB = 0;
        }
    }
}

void AddBorder(IMAGE *image, char color[SLEN], int border_width)
{
    int x, y ;
    int border_r = 255;
    int border_g = 255;
    int border_b = 255;
    if (!strcmp(color, "black")) {
        border_r = 0;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "white")) {
        border_r = 255;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "red")) {
        border_r = 255;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "green")) {
        border_r = 0;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "blue")) {
        border_r = 0;
        border_g = 0;
        border_b = 255;
    } else if (!strcmp(color, "yellow")) {
        border_r = 255;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "cyan")) {
        border_r = 0;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "pink")) {
        border_r = 255;
        border_g = 192;
        border_b = 203  ;
    } else if (!strcmp(color, "orange")) {
        border_r = 255;
        border_g = 165;
        border_b = 0;
    }
    
    for (y = 0; y < image->Height; y++)
    {
        for (x = 0; x < image->Width; x++)
        {
            if ((y < border_width)||
                (y > image->Height - border_width)||
                (x < border_width)||
                (x > image->Width - border_width))
            {
                SetPixelR(image, x, y, border_r);
                SetPixelG(image, x, y, border_g);
                SetPixelB(image, x, y, border_b);
            }
        }
    }
}

IMAGE *Rotate(IMAGE *image)
{
    int x,y, x_r, y_r;
    
    IMAGE *rotImg = CreateImage(image->Height, image->Width);
    
    
    for (y = 0, x_r = rotImg->Width; x_r >= 0; y++, x_r--)
        for (x = 0, y_r = rotImg->Height; y_r >= 0; x++, y_r--)
        {
            SetPixelR(rotImg, x_r, y_r, GetPixelR(image, x, y));
            SetPixelG(rotImg, x_r, y_r, GetPixelG(image, x, y));
            SetPixelB(rotImg, x_r, y_r, GetPixelB(image, x, y));
        }
    
    return rotImg;
    
}

/* Resize */
IMAGE *Resize(	unsigned int percentage, IMAGE *image)
{
    unsigned int    x, y, x1, y1, x2, y2, i, j, tmpR, tmpG, tmpB;
    unsigned int 	NEW_WIDTH, NEW_HEIGHT;
    unsigned int WIDTH;
    unsigned int HEIGHT;
    IMAGE *image_tmp;
    
    assert(image);
    WIDTH 	= image->Width;
    HEIGHT = image->Height;
    
    if(percentage <= 0 || percentage > 500){
        printf("Resizing percentage %d%% is out of the range, Sorry! \n", percentage);
        return image;
    }
    
    NEW_WIDTH = WIDTH * percentage / 100;
    NEW_HEIGHT = HEIGHT * percentage / 100;
    image_tmp = CreateImage(NEW_WIDTH, NEW_HEIGHT);
    
    for(x = 0; x < NEW_WIDTH; x ++){
        for(y = 0; y < NEW_HEIGHT; y++){
            x1 = (unsigned int)(x / (percentage / 100.00));
            y1 = (unsigned int)(y / (percentage / 100.00));
            x2 = (unsigned int)((x + 1) / (percentage / 100.00));
            y2 = (unsigned int)((y + 1) / (percentage / 100.00));
            tmpR = tmpB = tmpG = 0;
            
            if(percentage < 100){
                for(i = x1; i < x2; i ++){
                    for(j = y1; j < y2; j ++){
                        tmpR += GetPixelR(image, i, j);
                        tmpG += GetPixelG(image, i, j);
                        tmpB += GetPixelB(image, i, j);
                    }
                }
                SetPixelR(image_tmp, x, y, tmpR / ((x2 - x1) * (y2 - y1)));
                SetPixelG(image_tmp, x, y, tmpG / ((x2 - x1) * (y2 - y1)));
                SetPixelB(image_tmp, x, y, tmpB / ((x2 - x1) * (y2 - y1)));
                
            }
            else{
                SetPixelR(image_tmp, x, y, GetPixelR(image, x1, y1));
                SetPixelG(image_tmp, x, y, GetPixelG(image, x1, y1));
                SetPixelB(image_tmp, x, y, GetPixelB(image, x1, y1));
            }
        }
    }
    
    DeleteImage(image);
    image = NULL;
    return image_tmp;
}

















