#include <stdio.h>
#include "pointcloud.h"

void stat1()
{
    double x, y, height;
    double minh, maxh, totalh = 0;
    int count = 0;

    if (scanf("%lf %lf %lf", &x, &y, &height) == 3)
    {
        minh = maxh = height;
        totalh = height;
        count++;
    }

    
    while (scanf("%lf %lf %lf", &x, &y, &height) == 3)
    {
        if (height > maxh)
        {
            maxh = height;
        }
        else if (height < minh)
        {
            minh = height;
        }

        count++;
        totalh = totalh + height;
    }

    double avg = totalh / count;

    printf("avg heigh: %f\n", avg);
    printf("minimum heigh: %f\n", minh);
    printf("max heigh: %f\n", maxh);
}

void main()
{
    stat1();
    return;
}
