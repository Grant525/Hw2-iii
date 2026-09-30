
#ifndef BIT2_INCLUDED
#define BIT2_INCLUDED

#define T Bit2_T   
typedef struct T *T;

T Bit2_new(int width, int height);

int Bit2_width(T bit2);

int Bit2_height(T bit2);

int Bit2_put(T bit2, int col, int row, int marker);

int Bit2_get(T bit2, int col, int row);

void Bit2_map_row_major(T bit2, 
        void apply(int col, int row, T uarray2, int b, void *p1), void *cl);

void Bit2_map_col_major(T bit2, 
        void apply(int col, int row, T uarray2, int b, void *p1), void *cl);

void Bit2_free(T *bit2);

#undef T
#endif