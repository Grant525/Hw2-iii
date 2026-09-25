#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "uarray.h"

#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED

#define T UArray2_T   
typedef struct T *T;

/* uarray2_new
* Summary: 
* Allocates space for and creates a new 2D array, using the given width, 
* height, and size of each element
*
* Parameters:
*        const int width: width of the 2D array
*        const int height: height of the 2D array
* 	     const int size: byte size of each element in the array
*
* Return: A pointer to the 2D array
* 
* Expects: The newly allocated memory is not NULL
*/                                                                                
T Urray2_new(unsigned int width, unsigned int height, unsigned int size)

/* uarray2_width(T array)
* Summary: Goes through the 2Darray and returns the number of columns 
*        (or length of each row)
* 
* Parameters: T array: pointer to the 2D array
*
* Return: Returns an integer representing the length of each row in the array 
*
* Expects: The 2D array is not empty. All columns are the same length as each
*          other. All rows are the same length as each other. 
*/
int Uarray2_width(T uarray2)

/* NAME
* Summary: Goes through the 2Darray and returns the number of rows 
*        (or length of each column)
* 
* Parameters: T uarray2: pointer to the 2D array
*
* Return: Returns an integer representing the number of rows in the array
*
* Expects: The 2D array is not empty.  All columns are the same length as each
*         other. All rows are the same length as each other. 
*/
int Uarray2_height(T uarray2)

/* uarray2_size
* Summary: Check for the size each element is taking up in the array
* 
* Parameters: T uarray2: pointer to the 2D array
*
* Return: Returns an integer representing the size of each element in the array
*
* Expects: The 2D array is not empty (array is not null)
*
*/
int Uarray2_size(T uarray2)

/* uarray2_at
* Summary: Go through the array and return the element associated with the
*        given width and height coordinate
* 
* Parameters: T uarray2: pointer to the 2D array
*         unsigned int width: width position of the desired element
*         unsigned int height:  height position of the desired element
*
* Return: pointer value of the element in the 2D array at the given width
*        and height (x,y)
* 
* Expects: The 2D array is not empty (array is not null)
*
*/
void *Uarray2_at (T uarray2, unsigned int width, unsigned int height)

/* uarray2_map_col_major
* Summary: Maps an apply function to each element in the array row by row 
* 
* Parameters: T array: pointer to the 2D array
*       Apply () function 
*	    *cl: pointer to bool that checks invariants
* Return: Nothing
*
* Expects:  The 2D array is not empty.  All columns are the same length as each other.
* All rows * are the same length as each other. Apply() takes in an array and returns
* some value. 
*/
void Uarray2_map_col_major (T uarray2, 
        void apply((int col, int row, T uarray2, void *elem, void *cl)),
        *cl)

/* urray2_map_row_major
* Summary: Maps an apply function to each element in the array column by column 
* 
* Parameters: T array: pointer to the 2D array
*       Apply () function 
*	    *cl: pointer to bool that checks invariants
*
* Return: Nothing
*
* Expects:  The 2D array is not empty.  All columns are the same length as each other.
* All rows * are the same length as each other. Apply() takes in an array and returns
* some value. 
*/
void Urray2_map_row_major (T uarray2, 
        void apply((int col, int row, T uarray2, void *elem, void *cl)),
        *cl)

/* uarray2_free
* Summary: Deallocates all of the allocated memory for the 2D array.
* 
* Parameters: T array: Pointer to the 2D array
*
* Return: nothing
*
* Expects: The 2D array is not empty (array is not null) and has allocated memory. 
*/
void Urray2_free(T uarray2)

#undef T
#endif
