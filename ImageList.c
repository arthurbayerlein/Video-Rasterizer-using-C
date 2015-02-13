#include "ImageList.h"
#include "Image.h"
#include "Advanced.h"
#include "DIPs.h"

/* allocate a new image list */
ILIST *NewImageList(void)
{
    ILIST * myList = (ILIST*)malloc(sizeof(ILIST));
    myList->First = NULL;
    myList->Last = NULL;
    myList->Length = 0;
    return myList;
}
/* delete an image list (and all entries) */
void DeleteImageList(ILIST *l)
{
    IENTRY *currentEntry, *nextEntry;
    
    assert(l);
    currentEntry = l->First;
    while(currentEntry){
        nextEntry = currentEntry->Next;
        assert(currentEntry->List == l);
        DeleteImage(currentEntry->Image);
        currentEntry->Image = NULL;
        free(currentEntry);
        currentEntry = nextEntry;
    }
    
    free(l);
}
/* insert a frame into a list at the end*/
void AppendImage(ILIST *l, IMAGE *image)
{
    assert(image);
    assert(l);
    
    IENTRY * myEntry = (IENTRY*)malloc(sizeof(IENTRY));
    myEntry->List = l;
    myEntry->Next = NULL;
    myEntry->Prev = l->Last;
    myEntry->Image = image;
    
    if (l->Length == 0)
    {
        l->Last = myEntry;
        l->First = myEntry;
    }
    else
    {
        l->Last->Next = myEntry;
        l->Last = myEntry;
    }
        
    l->Length++;
    
}
/* reverse an image list */
void ReverseImageList(ILIST *l)
{
    assert(l);
    
    int i;
    IENTRY * currentEntry = l->First;
    IENTRY * nextEntry = NULL;
    IENTRY * prevEntry = NULL;
    for(i = 0; i < l->Length; i++)
    {
        nextEntry = currentEntry->Next;
        prevEntry = currentEntry->Prev;
        
        currentEntry->Next = prevEntry;
        currentEntry->Prev = nextEntry;
        
        currentEntry = nextEntry;
    }
    
    IENTRY * temp = l->First;
    l->First = l->Last;
    l->Last = temp;
}
/*Crop frames from the list starting from SFrame to EFrame*/
void CropImageList(ILIST *l, unsigned int SFrame, unsigned int EFrame)
{
    int i = 1;
    IENTRY *currentEntry, *nextEntry ;
    
    assert(l) ;
    
    currentEntry = l->First ;
    while (currentEntry != NULL)
    {
        nextEntry = currentEntry->Next ;
        if (i < SFrame || i > EFrame)
        {
            DeleteImage(currentEntry->Image);
            currentEntry->Image = NULL ;
            free (currentEntry) ;
        }
        else
        {
            if (i == EFrame)
            {
                l->Last = currentEntry ;
                currentEntry->Next = NULL;
            }
            else if (i == SFrame)
            {
                l->First = currentEntry ;
                currentEntry->Prev = NULL ;
            }
        }
        
        currentEntry = nextEntry ;
        
        i++ ;
    }
}

/*Resize the images in the list*/
void ResizeImageList(ILIST *l, unsigned int percentage)
{
    int i;
    
    IENTRY * currentEntry = l->First;
    for(i = 0; i < l->Length; i++)
    {
        currentEntry->Image = Resize(percentage, currentEntry->Image);
        currentEntry = currentEntry->Next;
    }
}

unsigned int FastImageList(ILIST *l, unsigned int ff_factor)
{
    int i, j;
    IENTRY *previousEntry, *currentEntry, *nextEntry ;
    
    assert(l) ;
    
    i = 0 ;
    j = 0 ;
    currentEntry = l->First ;
    previousEntry = l->First ;
    
    while (currentEntry != NULL)
    {
        nextEntry = currentEntry->Next ;
        if (i%ff_factor == 0)
        {
            if (i > 0)
            {
                previousEntry->Next = currentEntry ;
                currentEntry->Prev = previousEntry ;
            }
            previousEntry = currentEntry ;
            j ++ ;
        }
        else
        {
            DeleteImage(currentEntry->Image);
            currentEntry->Image = NULL ; 
            free (currentEntry) ; 			
        }
        
        currentEntry = nextEntry ; 
        i++ ; 
    }
    previousEntry->Next = NULL ; 
    return j ; 
}
