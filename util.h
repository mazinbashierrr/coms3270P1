#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

#define macroAcc (rown,column, num_cols) ((row)*(num_cols) + (column)) 

void *allocateArray(int rows, int columns);

typedef struct{
    int max_size;
    int max_element_size;
    void* data;
    int size;
}List;

int listInit(List* l, int max_elmt_size);
void listAddEnd(List* l, void* elmt);
void *listGet(List* l, int index);

#endif