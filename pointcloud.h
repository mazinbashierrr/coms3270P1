#ifndef POINTCLOUDH
#define POINTCLOUDH

void stat1();
void *allocateArray(int rows, int columns);

typedef struct pcd_t
{
    double height;
    double x;
    double y;
    double amtWater;

    struct pcd_t *north, *south, *east, *west;
} pcd_t;

#endif
