#include <stdlib.h>
#include <string.h>
#include "util.h"

void *allocateArray(int rows, int columns){

    double *array = (double *)calloc(rows * columns, sizeof(double));
    //for memory alc
    if(!array){
        return NULL;
    }
    return (void *) array;
};

int listInit(List *l, int max_elmt_size){
    l->max_size = 10;
    l->max_element_size = max_elmt_size;
    l->data = malloc(l->max_size * max_elmt_size);
    l->size = 0;
    return (l->data!=NULL) ? 0 : -1;
}

void listAddEnd(List *l, void *elmt){
    if(l->size == l->max_size){
        l->max_size *=2;
        l->data = realloc(l->data,l->max_size * l->max_element_size);
    }
    memcpy((char *)l->data + (l->size * l->max_element_size), elmt, l->max_element_size);
    l->size++;
}
void *listGet(List *l, int index){
    if(index < 0 || index >= l->size){
        return NULL;
    }
    return (char *)l->data + (index * l->max_element_size);

}