#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "bit.h"

#ifndef BIT2_INCLUDED
#define BIT2_INCLUDED

#define T Bit2_T   
typedef struct T *T;

T Bit2_new(unsigned int width, unsigned int height)

int Bit2_width(T bit2)

int Bit2_height(T bit2)

void Bit2_put(T bit2, int width, int height, int marker)

void Bit2_get(T bit2, int width, int height)

void Bit2_map_row_major(T bit2, 
        void apply((int col, int row, T uarray2, void *elem, void *cl)),
        *cl)

void Bit2_map_col_major(T bit2, 
        void apply((int col, int row, T uarray2, void *elem, void *cl)),
        *cl)

void Bit2_free(T *bit2)



#undef T
#endif