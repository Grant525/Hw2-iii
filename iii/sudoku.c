#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <iso646.h>
#include <assert.h>
#include "pnmrdr.h"
#include "table.h"

#include "except.h"
#include "uarray2.h"

typedef long number;
const int ELEMENT_SIZE = sizeof(number);

Except_T Too_Many_Args = { "Too many arguments" };
Except_T File_Error = { "Unable to open input file" };
Except_T Bound_Failure = { "Out of bounds" };

struct Closure {
        Table_T table;
        bool *valid;
};


// void check_sudoku(int i, int j, UArray2_T a, void *p1, void *p2) 
// {
//         number *entry_p = p1;

//         *((bool *)p2) &= UArray2_at(a, i, j) == entry_p;

//         if ( (i == (DIM1 - 1) ) && (j == (DIM2 - 1) ) ) {
//                 /* we got the corner */
//                 *((bool *)p2) &= (*entry_p == MARKER);
//         }
// }

//table holding whether we have checked each row, col, or box

bool box_check(int box_num, UArray2_T uarray2, Table_T checklist)
{
        int box_to_point[] = {1,1,4,1,7,1,1,4,4,4,7,4,1,7,4,7,7,7};
        int col = box_to_point[(box_num * 2) - 2];
        int row = box_to_point[(box_num * 2) - 1];
        
        int rows[] = {row, row + 1, row - 1};
        int cols[] = {col, col + 1, col - 1};

       
        for (int i = 0; i < 3; i++){
                for (int n = 0; n < 3; n++){
                        int *elem = UArray2_at(uarray2, cols[i], rows[n]);
                        void *ret = Table_put(checklist, &elem, (void *)1);   
                        if (ret != NULL){  
                                 return false;                 
                        }
                }
        }
        return true;
}       

void make_table(Table_T checked)
{
        enum key {
        ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8, ROW_9,
        COL_1, COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8, COL_9,
        BOX_1, BOX_2, BOX_3, BOX_4, BOX_5, BOX_6, BOX_7, BOX_8, BOX_9
        };
        //fill table 
        for (int i = 0; i < 9; i++){
                int row_key = ROW_1 + i;
                int col_key = COL_1 + i;
                int box_key = BOX_1 + i;

                Table_put(checked, &row_key, (void *)false);
                Table_put(checked, &col_key, (void *)false);
                Table_put(checked, &box_key, (void *)false);
        }
}

//whether the row/col/or box is on the checklist 
bool on_checklist(int key, int type, UArray2_T uarray2)
{
        if (type != 1 and type != 2 and type != 3){
              RAISE(Bound_Failure);  
        }  
        Table_T checklist = Table_new(0, NULL, NULL);
        //checks what type of thing we are chekcing col/row/box
        if (type == 1) {    
                for (int i = 0; i < 10; i++){
                        //find the value of the current element 
                        void *elem = UArray2_at(uarray2, (key - 1), i);
                        //put it on table, if we get non NUll value then number is repeated
                        void *ret = Table_put(checklist, elem, (void *)1);
                        if (ret != NULL){
                                return false;
                        }
                }
        }
        if (type == 2){
                for (int i = 0; i < 10; i++){
                        void *elem = UArray2_at(uarray2, i, (key - 1));
                        void *ret = Table_put(checklist, elem, (void *)1);
                        if (ret != NULL){
                                return false;
                        }
                }
        }
        if (type == 3){      
                if (not box_check (key, uarray2, checklist)){
                        return false;
                }
        }
        return true;
}



//what box is that element in 
int box_num(int col, int row)
{
        if (col <= 0 or col > 10 or row <= 0 or row > 10){
               RAISE(Bound_Failure); 
        }

        if (col < 4 and row < 4){
                return 1;
        }
        if ((3 < col and col < 7) and row < 4){
                return 2;
        }
        if ((6 < col and col < 10) and row < 4){
                return 3;
        }
        if (col < 4 and (3 < row  and row < 7)){
                return 4;
        }
        if ((3 < col and col < 7) and (3 < row and row < 7)){
                return 5;
        }
        if ((6 < col and col < 10) and (3 < row and row < 7)){
                return 6;
        }
        if (col < 4 and (6 < row and row < 10)){
                return 7;
        }
        if ((3 < col and col < 7) and (6 < row and row < 10)){
                return 8;
        }
        if ((6 < col and col < 10) and (6 < row and row < 10)){
                return 9;
        }
        return EXIT_FAILURE;

}
//apply function 
void sudoku_correctness(int col, int row, UArray2_T uarray2, void *p1 , void *p2)
{
        enum key {
        ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8, ROW_9,
        COL_1, COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8, COL_9,
        BOX_1, BOX_2, BOX_3, BOX_4, BOX_5, BOX_6, BOX_7, BOX_8, BOX_9
        };

        (void)p2;
        char row_key = ROW_1 + row;
        char col_key = COL_1 + col;
        int box = box_num(col, row);
        char box_key = BOX_1 + (box - 1);
        int type;
        
        //have we checked this row/col/box
        if (Table_get(*((Closure *)p2).table, &row_key) == false){
                //set that we have now checked it 
                Table_put(*((Closure *)p2)->table, &row_key,(void *)true);
                type = 1;
                //is it 1-9 or are their repeats?
                if (not on_checklist(row, type, uarray2)){
                        *((Closure *)p2)->valid = false;
                }
        }
        if (Table_get(*((Table_T *)p2)->table, &col_key) == false){
                Table_put(*((Closure *)p2)->table, &col_key,(void *)true);
                type = 2;
                if (not on_checklist(col_key, type, uarray2)){
                        *((Closure *)p2)->valid = false; 
                }
        }
        if (Table_get(*((Closure *)p2)->table, &box_key) == false){
                Table_put(*((Closure *)p2)->table, &box_key,(void *)true);
                type = 3;
                if (not on_checklist(box_key, type, uarray2)){
                        *((Closure *)p2)->valid = false;
                }
        }
        *((bool *)p2)->valid = true;
}

/* read_and_initialize
* Summary: read the input using Pnmrdr and creates a new 2D Uarray
*
* Parameters: FILE *inputfd: pointer to the input file
*        int *width: pointer to the width of the pgm file
*        int *height: pointer to the height of the pgm file
*
* Returns: UArray2_T struct representing the 2D uarray
*
* Expects: inputfd, width, and height are not NULL. 
*        inputfd should point to a valid pgm format, raise an exception if not.
*/
UArray2_T read_and_initialize(FILE *inputfd, int *width, int *height)
{
        Pnmrdr_T sudoku = Pnmrdr_new(inputfd);

        Pnmrdr_mapdata sudoku_data = Pnmrdr_data(sudoku);
        *width = sudoku_data.width;
        *height = sudoku_data.height;

        if (sudoku_data.type != 2 or *width != 9 or 
            *height != 9 or sudoku_data.denominator != 9){
            RAISE(Pnmrdr_Badformat);
        }

        UArray2_T sudoku_array = UArray2_new(*width, *height, ELEMENT_SIZE);

        for (int row_num = 0; row_num < *height; row_num++){
                for (int col_num = 0; col_num < *width; col_num++){
                        void *elem = UArray2_at(sudoku_array, col_num, row_num);
                        unsigned int *temp = elem;
                        *temp = Pnmrdr_get(sudoku);
                }
        }

        Pnmrdr_free(&sudoku);
        return sudoku_array; 
}



int main(int argc, char *argv[])
{
        FILE *inputfd;
        int width;
        int height;

        // Confirm that 0 or 1 command-line arguments will work
        if (argc > 2) {
                RAISE(Too_Many_Args);
        }

        // Use standard input if no filename was provided
        if (argc == 1) {
                inputfd = stdin;
        } else {
                // Open from specified file
                inputfd = fopen(argv[1], "r");

                // Check whether file successfully opened
                if (inputfd == NULL) {
                        RAISE(File_Error);
                }
        }

        UArray2_T sudoku_array = read_and_initialize(inputfd, &width, &height);

        Table_T checked = Table_new(0, NULL, NULL);
        make_table(checked);
        
        Closure check;
        check->table = checked;
        check->valid = true;

        
        UArray2_map_row_major(sudoku_array, sudoku_correctness, &check);
        
        if (not valid){
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}

