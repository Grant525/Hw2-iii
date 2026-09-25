#ifndef UARRAY2_H_  
#define UARRAY2_H_

#define T UArray2_T     //does this go here?

/* uarray2_new
* Summary: 
* Allocates space for and creates a new 2D array, using the given width, height,
* and size of each element
* Parameters:
*         const int WIDTH: width of the 2D array
*	        const int HEIGHT: height of the 2D array
* 	      const int ELEMENT_SIZE: byte size of each element in the array
* Return: A pointer to the 2D array
* 
* Expects: WIDTH, HEIGHT, and ELEMENT_SIZE should be greater than 0 than 0
*/                                                                                
T urray2_new(unsigned int width, unsigned int height, unsigned int ELEMENT_SIZE)

/* NAME: uarray2_width(T array)
* Summary: Goes through the 2Darray and returns the number of columns (or length of each row)
* 
* Parameters: T array: pointer to the 2D array
*
* Return: Returns an integer representing the length of each row in the array 
*
* Expects: The 2D array is not empty. All columns are the same length as each
*          other. All rows are the same length as each other. 
*/
int uarray2_width(T array)

/* NAME
* Summary: Goes through the 2Darray and returns the number of rows (or length of each column)
* 
* Parameters: T array: pointer to the 2D array
*
* Return: Returns an integer representing the number of rows in the array 
*
* Expects: The 2D array is not empty.  All columns are the same length as each other. All
*          rows are the same length as each other. 
*/
int uarray2_height(T array)

/* uarray2_size
* Summary: Check for the size each element is taking up in the array
* 
* Parameters: T array: pointer to the 2D array
*
* Return: Returns an integer representing the size of each element in the array
*
* Expects: The 2D array is not empty (array is not null)
*
*/
int uarray2_size(T array)

/* uarray2_at
* Summary: Go through the array and return the element associated with the given width and 
height coordinate
* 
* Parameters: T array: pointer to the 2D array
*         unsigned int width: width position of the desired element
*         unsigned int height:  height position of the desired element
*
* Return: pointer value of the element in the 2D array at the given width and height (x,y)
* 
* Expects: The 2D array is not empty (array is not null)
*
*/
void *uarray2_at (T array, unsigned int width, unsigned int height)

/* uarray2_map_col_major
* Summary: Maps an apply function to each element in the array row by row 
* 
* Parameters: T array: pointer to the 2D array
*                      Apply () function 
*	           *closure
* Return: Returns the result of apply() for each element of the array row by row
*
* Expects:  The 2D array is not empty.  All columns are the same length as each other.
* All rows * are the same length as each other. Apply() takes in an array and returns
* some value. 
*/
uarray2_map_col_major (array, apply(), *cl)

/* NAME
* Summary: Maps an apply function to each element in the array column by column 
* 
* Parameters: T array: pointer to the 2D array
*                      Apply () function 
*	           *closure
*
* Return:  Returns the result of apply() for each element of the array col by col*
*
* Expects:  The 2D array is not empty.  All columns are the same length as each other.
* All rows * are the same length as each other. Apply() takes in an array and returns
* some value. 
*/
urray2_map_row_major (array, apply(), *cl)

/* uarray2_free
* Summary: Deallocates all of the allocated memory for the 2D array.
* 
* Parameters: T array: Pointer to the 2D array
*
* Return: nothing
*
* Expects: The 2D array is not empty (array is not null) and has allocated memory. 
*	
*/
void urray2_free(T array)

#endif
