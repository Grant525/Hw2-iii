#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <iso646.h>
#include "assert.h"

#include "bit.h"
#include "bit2.h"

Except_T Memory_Error = { "Memory allocation failed" };
Except_T Bound_Error = { "Out of bounds reference" };

/* Bit2_T
 * Stores the 2D Uarray and its information
 * 
 * Members:
 *      int width: width of the 2D bit
 *      int height: height of the 2D bit
 *      UArray_T elems: Hanson's bit
 */
struct Bit2_T {
        int width; 
        int height;
        Bit_T elems;
};

/* uarray2_new
* Summary: 
* Allocates space for and creates a new 2D array, using the given width, 
* height, and size of each element
*
* Parameters:
*        int width: width of the 2D array
*        int height: height of the 2D array
* 	     int size: byte size of each element in the array
*
* Return: A pointer to the 2D array
* 
* Expects: width, height, and size are positive integers
*        caller is expected to free the allocated memory on the heap
*        after calling the function.
*/       
Bit2_T Bit2_new(int width, int height)
{
        // allocating space for bit2
        size_t length = width * height;
        Bit2_T bit2 = malloc(sizeof(*bit2));

        if (bit2 == NULL){
            RAISE(Memory_Error);
        }

        // Asssigning values to bit2 struct
        bit2->width = width;
        bit2->height = height;

        // Creating a Hanson Bit to represent the 2D array
        bit2->elems =  Bit_new(length);

        return bit2;
}

/* uarray2_width(T array)
* Summary: Goes through the 2Darray and returns the number of columns 
*        (or length of each row)
* 
* Parameters: T array: pointer to the 2D array
*
* Return: Returns an integer representing the length of each row in the array 
*
* Expects: The 2D array is not empty (array is not null). An exception is
*        raised if that is the case. 
*/
int Bit2_width(Bit2_T bit2)
{
        if (bit2 = NULL){
            RAISE(Memory_Error);
        }

        int width = bit2->width;
        assert(width > 0);
        return width;
}


/* UArray2_height
* Summary: Goes through the 2Darray and returns the number of rows 
*        (or length of each column)
* 
* Parameters: T uarray2: pointer to the 2D array
*
* Return: Returns an integer representing the number of rows in the array
*
* Expects: The 2D array is not empty (array is not null). An exception is
*        raised if that is the case. 
*/
int Bit2_height(Bit2_T bit2)
{
        if (bit2 = NULL){
            RAISE(Memory_Error);
        }

        int height = bit2->height;
        assert(height > 0);
        return height;
}

int Bit2_put(Bit2_T bit2, int col, int row, int marker)
{
        assert(bit2 != NULL);

        int width = Bit2_width(bit2);
        int height = Bit2_height(bit2);
        
        if ((col < 0 or col >= width) or (row < 0 or row >= height)){
            RAISE(Bound_Error);
        }   
        
        int i = ((row * width)) + col;
        return Bit_put(bit2->elems, i, marker);
}

int Bit2_get(Bit2_T bit2, int col, int row)
{
        assert(bit2 != NULL);

        int width = Bit2_width(bit2);
        int height = Bit2_height(bit2);

        if (col < 0 or col >= width or row < 0 or row >= height){
            RAISE(Bound_Error);
        }   
        
        int i = ((row * width)) + col;
        return Bit_get(bit2->elems, i);
}

/* uarray2_map_col_major
* Summary: Maps an apply function to each element in the array row by row 
* 
* Parameters: T array: pointer to the 2D array
*        void apply(): function being applied to each element in the 2D array
*                - col: width position of the starting element
*                - row: height position of the starting element
*                - uarray2: pointer to the 2D array
*                - p1: pointer to the element being appplied
*                - p2: closure pointer
*        *cl: closure pointer
*
* Return: Nothing
*
* Expects:  The 2D array is not empty.  All columns are the same length as each other.
* All rows * are the same length as each other. Apply() takes in an array and returns
* some value. 
*/
void Bit2_map_row_major(Bit2_T bit2, 
        void apply(int col, int row, Bit2_T bit2, int b, void *p1), void *cl)
{
        if (bit2 = NULL){
            RAISE(Memory_Error);
        }

        for (int row_num = 0; row_num < bit2->height; row_num++){
                for (int col_num = 0; col_num < bit2->width; col_num++){
                        int b = Bit2_get(bit2, col_num, row_num);
                        apply(col_num, row_num, bit2, b, cl);  
                }
        }

}

/* uarray2_map_row_major
* Summary: Maps an apply function to each element in the array column by column 
* 
* Parameters: T array: pointer to the 2D array
*        void apply(): function being applied to each element in the 2D array
*                - col: width position of the starting element
*                - row: height position of the starting element
*                - uarray2: pointer to the 2D array
*                - p1: pointer to the element being appplied
*                - p2: closure pointer
*        *cl: closure pointer
*
* Return: Nothing
*
* Expects:  The 2D array is not empty.  All columns are the same length as each other.
* All rows * are the same length as each other. Apply() takes in an array and returns
* some value. 
*/
void Bit2_map_col_major(Bit2_T bit2, 
        void apply(int col, int row, Bit2_T bit2, int b, void *p1), void *cl)
{
        if (bit2 = NULL){
            RAISE(Memory_Error);
        }

         for (int col_num = 0; col_num < bit2->width; col_num++){
                for (int row_num = 0; row_num < bit2->height; row_num++){
                        int b = Bit2_get(bit2, col_num, row_num);
                        apply(col_num, row_num, bit2, b, cl);  
                }
        }
}

/* uarray2_free
* Summary: Deallocates all of the allocated memory for the 2D array.
* 
* Parameters: T array: Pointer to the pointer 2D array
*
* Return: nothing
*
* Expects: The 2D array is not empty (array is not null) and has allocated memory. 
*/
void Bit2_free(Bit2_T *bit2)
{
        assert(bit2 != NULL && *bit2 != NULL);

        // Free the Hanson Bit in the struct
        Bit_free(&(*bit2)->elems);

        // Free the 2D bit array
        free(*bit2);
        *bit2 = NULL;
}