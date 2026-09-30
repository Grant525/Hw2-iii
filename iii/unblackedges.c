#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <iso646.h>
#include <assert.h>
#include "pnmrdr.h"
#include "table.h"

#include "except.h"
#include "bit2.h"

int black_search(int col; int row; Bit2_T bit2){
        char prev = int current;
        int current = (col * 10) + row
        bit2_put(Bit2_T bit2, col, row, 0);
        if (bit2_get(Bit2_T bit2, col + 1, row) == 1){
                black_search(int col + 1; int row; Bit2_T bit2)
        }

        if (bit2_get(Bit2_T bit2, col - 1, row) == 1){
                black_search(int col - 1; int row; Bit2_T bit2)
        }

        if (bit2_get(Bit2_T bit2, col, row + 1) == 1){
                black_search(int col; int row + 1; Bit2_T bit2)
        }

        if (bit2_get(Bit2_T bit2, col, row - 1) == 1){
                black_search(int col; int row - 1; Bit2_T bit2)
        }
        else return 0

}

void edge_search(int col; int row; Bit2_T bit2){
        for (int i = 0; i < 9; i++){
                for (int n = 0; n < 9; n++){
                        
                }
        }
}