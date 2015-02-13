#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Movie.h"
#include "Image.h"
#include "ImageList.h"
#include "Advanced.h"
#include "DIPs.h"


/*save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/*read one frame from the movie */
IMAGE* ReadOneFrame(const char* fname, int nFrame, unsigned int W, unsigned H);

/*read the movie frames from the input file */
int ReadMovie(const char *fname, int nFrame, unsigned int W, unsigned H, MOVIE *movie);

/* Print the command line parameter usage of the program*/
void PrintUsage();

/* type define the function pointer to the DIP function */
typedef void MOP_F(IMAGE *image);

/* the function for perform DIP operations on the movie*/
void Movie_DIP_Operation(MOVIE *movie, MOP_F *MovieOP);


int main(int argc, char *argv[])
{
    int x = 0;
    char *fin = NULL, *fout = NULL;
    MOVIE * myMovie = CreateMovie(0, 0, 0);
    int numOfFrames = 0;
    int imageHeight = 0;
    int imageWidth = 0;
    
    /*entering while loop to check options entered*/
    while(x < argc)
    {
        /*specify input video*/
        if(0 == strcmp(&argv[x][0], "-i"))
        {
            if(x < argc - 1)
            {
                fin = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
                strcpy(fin, argv[x + 1]);
                strcat( fin, ".yuv");
            }/*fi*/
            else
            {
                printf("Missing argument for input name!");
                free(fin);
                free(fout);
                return 5;
            }/*esle*/
            x += 2;
            continue;
        }/*fi*/
        
        /*specify output video*/
        if(0 == strcmp(&argv[x][0], "-o"))
        {
            if(x < argc - 1)
            {
                fout = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
                strcpy(fout, argv[x + 1]);
                strcat( fout, ".yuv");
            }/*fi*/
            else
            {
                printf("Missing argument for output name!");
                free(fin);
                free(fout);
                return 5;
            }/*esle*/
            x += 2;
            continue;
        }/*fi*/
        
        /*specify number of frames*/
        if(0 == strcmp(&argv[x][0], "-f"))
        {
            if(x < argc - 1)
            {
                numOfFrames = atoi(argv[x + 1]);
                myMovie->NumFrames = numOfFrames;
                if(numOfFrames && imageHeight && imageWidth) ReadMovie(fin, numOfFrames, imageWidth, imageHeight, myMovie);

            }
            else
            {
                printf("Missing argument for frame number");
                return 5;
            }
            x += 2;
            continue;
        }/*frames*/
        
        /*specify height and width*/
        if(0 == strcmp(&argv[x][0], "-s"))
        {
            if(sscanf(argv[x+1], "%dx%d", &imageWidth, &imageHeight) == 2)
            {
                myMovie->Width = imageWidth;
                myMovie->Height = imageHeight;
                if(numOfFrames && imageHeight && imageWidth) ReadMovie(fin, numOfFrames, imageWidth, imageHeight, myMovie);

            }
            else
            {
                printf("Missing argument for height and width!");
                return 5;
            }
            x += 2;
            continue;
        }/*frames*/
        
        /*activate the conversion to black and white*/
        if(0 == strcmp(&argv[x][0], "-bw"))
        {
            if(x < argc)
            {
                Movie_DIP_Operation(myMovie, BlackNWhite);
                printf("Operation Black and White is complete!\n");
            }
            else
            {
                printf("Went past the number of arguments");
                return 5;
            }
            x += 1;
            continue;
        }
        
        /*activate the conversion to flip*/
        if(0 == strcmp(&argv[x][0], "-vflip"))
        {
            if(x < argc)
            {
                Movie_DIP_Operation(myMovie, VFlip);
                printf("Operation VFlip is complete!\n");
            }
            else
            {
                printf("Went past the number of arguments");
                return 5;
            }
            x += 1;
            continue;
        }
        
        /*activate the conversion to mirror*/
        if(0 == strcmp(&argv[x][0], "-hmirror"))
        {
            if(x < argc)
            {
                Movie_DIP_Operation(myMovie, HMirror);
                printf("Operation HMirror is complete!\n");
            }
            else
            {
                printf("Went past the number of arguments");
                return 5;
            }
            x += 1;
            continue;
        }
        
        /*activate edge filter*/
        if(0 == strcmp(&argv[x][0], "-edge"))
        {
            if(x < argc)
            {
                Movie_DIP_Operation(myMovie, Edge);
                printf("Operation Edge is complete!\n");
            }
            else
            {
                printf("Went past the number of arguments");
                return 5;
            }
            x += 1;
            continue;
        }
        
        /*activate posterize filter*/
        if(0 == strcmp(&argv[x][0], "-poster"))
        {
            if(x < argc)
            {
                Movie_DIP_Operation(myMovie, Posterize);
                printf("Operation Posterize is complete!\n");
            }
            else
            {
                printf("Went past the number of arguments");
                return 5;
            }
            x += 1;
            continue;
        }
        
        /*cut the movie*/
        if(0 == strcmp(&argv[x][0], "-cut"))
        {
            int start, end;
            if(sscanf(argv[x+1], "%d-%d", &start, &end) == 2)
            {
                CropImageList(myMovie->Frames, start, end);
                printf("Cropping operation is complete!\n");
            }
            else
            {
                printf("Missing argument for number of frames to cut!");
                return 5;
            }
            x += 2;
            continue;
        }
        
        /*resize movie*/
        if(0 == strcmp(&argv[x][0], "-resize"))
        {
            if(x < argc - 1)
            {
                int factor = atoi(argv[x + 1]);
                ResizeImageList(myMovie->Frames, factor);
                printf("Operation Resize is complete!\n");
                imageWidth = myMovie->Width * (factor / 100.00);
                imageHeight = myMovie->Height * (factor / 100.00);
                
                myMovie->Width = imageWidth;
                myMovie->Height = imageHeight;
            }
            else
            {
                printf("Missing factor argument for resize");
                return 5;
            }
            x += 2;
            continue;
        }
        
        /*fast forward movie*/
        if(0 == strcmp(&argv[x][0], "-fast"))
        {
            if(x < argc - 1)
            {
                int factor = atoi(argv[x + 1]);
                myMovie->NumFrames = FastImageList(myMovie->Frames, factor);
                printf("Fast Forward operation is complete!\n");
            }
            else
            {
                printf("Missing factor argument for fast");
                return 5;
            }
            x += 2;
            continue;
        }
        
        /*reverse movie*/
        if(0 == strcmp(&argv[x][0], "-rvs"))
        {
            if(x < argc)
            {
                ReverseImageList(myMovie->Frames);
                printf("Reverse operation is complete!\n");
            }
            else
            {
                printf("Missing argument for frame number");
                return 5;
            }
            x += 2;
            continue;
        }
        
        /*help option*/
        if(0 == strcmp(&argv[x][0], "-h"))
        {
            PrintUsage();
            free(fin);
            free(fout);
            return 0;
        }/*fi*/
        x++;
        
        
        
    }/*elihw*/
    
    if(!fin){
        printf("Missing argument for input name!\n");
        PrintUsage();
        free(fin);
        free(fout);
        return 5;
    }
    
    if(!fout){
        printf("Missing argument for output name!\n");
        PrintUsage();
        free(fin);
        free(fout);
        return 5;
    }
    
    SaveMovie(fout, myMovie);
    DeleteMovie(myMovie);
    free(fin);
    free(fout);
    fin = NULL;
    fout = NULL;
    
    return 0;
}

void PrintUsage()
{
    printf("\nFormat on command line is:\n"
           "MovieLab [option]\n"
           "-i [file_name]    to provide the input file name\n"
           "-o [file_name]    to provide the       output file name\n"
           "-f [no_frames]    to determine how many frames desired in the input stream\n"
           "-s [WidthxHeight] to set resolution of the input stream (widthxheight)\n"
           "-j                to generate the movie with JuliaSet sequences\n"
           "-bw               to activate the conversion to black and white\n"
           "-vflip            to activate vertical flip\n"
           "-hmirror          to activate horizontal flip\n"
           "-edge             to activate edge filter\n"
           "-poster           to activate posterize filter\n"
           "-cut [Start-End]  to crop the frame from the video from frame Start to frame End\n"
           "-resize [factor]  to resize the video with the provided factor [1-100]\n"
           "-fast   [factor]  to fast forward the video with the provided factor [1+]\n"
           "-rvs              to reverse the frame order of the input stream\n"
           "-h                to show this usage information\n"
           );
}

IMAGE* ReadOneFrame(const char *fname, int nFrame, unsigned int W, unsigned H)
{
    /*defining local variables*/
    FILE *file;
    
    unsigned int x, y;
    unsigned char ch;
    IMAGE* image ;
    
    /*checking error*/
    assert(fname);
    assert(nFrame >= 0);
    
    image = CreateImage(W, H) ;
    assert(image) ;
    
    /*opening file stream*/
    file = fopen(fname, "r");
    assert(file) ;
    
    /*find desired frame*/
    fseek(file, 1.5 * nFrame * W * H, SEEK_SET);
    
    for(y = 0; y < H; y ++){
        for(x = 0; x < W; x ++){
            ch = fgetc(file);
            SetPixelY(image, x, y, ch);
        }/*rof*/
    }
    
    for(y = 0; y < H ; y += 2){
        for(x = 0; x < W ; x += 2){
            ch = fgetc(file);
            SetPixelU(image, x, y, ch);
            SetPixelU(image, x + 1, y, ch);
            SetPixelU(image, x, y + 1, ch);
            SetPixelU(image, x + 1, y + 1, ch);
        }
    }
    
    for(y = 0; y < H ; y += 2){
        for(x = 0; x < W ; x += 2){
            ch = fgetc(file);
            SetPixelV(image, x, y, ch);
            SetPixelV(image, x + 1, y, ch);
            SetPixelV(image, x, y + 1, ch);
            SetPixelV(image, x + 1, y + 1, ch);
        }
    }
    
    /*checking for error*/
    
    
    assert(ferror(file) == 0) ;
    
    /*closing stream and terminating*/
    fclose(file);
    file = NULL;
    return image;
}


/*save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
    int i ;
    int x, y;
    FILE *file;
    IENTRY *currFrame;
    
    /*opening file stream*/
    if(!(file = fopen(fname, "w"))){
        return 1;
    }
    
    i = 0 ;
    printf("start savemovie, total frame %d\n", movie->NumFrames) ;
    currFrame = movie->Frames->First;
    while(currFrame){
        for(y = 0; y < movie->Height; y ++){
            for(x = 0; x < movie->Width; x ++){
                fputc(GetPixelY(currFrame->Image, x, y), file);
            }
        }
        for(y = 0; y < movie->Height; y += 2){
            for(x = 0; x < movie->Width; x += 2){
                fputc(GetPixelU(currFrame->Image, x, y), file);
            }
        }
        for(y = 0; y < movie->Height; y += 2){
            for(x = 0; x < movie->Width; x += 2){
                fputc(GetPixelV(currFrame->Image, x, y), file);
            }
        }
        currFrame = currFrame->Next;
        i++;
    }
    
    fclose(file);
    file = NULL;
    printf("The movie file %s has been written successfully! \n", fname);
    printf("%d frames are written to the file %s in total \n", i, fname);
    return 0;
}

/*read the movie frames from the input file */
int ReadMovie(const char *fname, int nFrame, unsigned int W, unsigned H, MOVIE *movie)
{
    if(!movie) return 0;
    
    int i;
    IMAGE * tempImage;
    for(i = 0; i < nFrame; i++)
    {
        tempImage = ReadOneFrame(fname, i, W, H);
        AppendImage(movie->Frames, tempImage);
    }
    return 1;
}

void Movie_DIP_Operation(MOVIE *movie, MOP_F *MovieOP)
{
    assert(movie);
    
    IENTRY * currentFrame = movie->Frames->First;
    while(currentFrame != NULL)
    {
        YUV2RGBImage(currentFrame->Image);
        MovieOP(currentFrame->Image);
        RGB2YUVImage(currentFrame->Image);
        
        currentFrame = currentFrame->Next;
    }
}