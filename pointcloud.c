#include <stdio.h>
#include "pointcloud.h"
#include <stdlib.h>
#include "util.h"
#include "bmp.h"
#include <float.h>
#include <math.h>
#include <unistd.h>

void stat1(List *list, double pair[2])
{
    double x, y;
    // double minh, maxh, totalh = 0;
    double minh = DBL_MAX, maxh = -DBL_MAX;
    double totalh = 0.0;
    int count = 0;

    // while (scanf("%lf %lf %lf", &x, &y, &height) == 3)
    // {
    //     if (height > maxh)
    //     {
    //         maxh = height;
    //     }
    //     else if (height < minh)
    //     {
    //         minh = height;
    //     }

    //     count++;
    //     totalh = totalh + height;
    // }

    for (int i = 0; i < list->size; i++)
    {
        pcd_t *pnt = (pcd_t *)listGet(list, i);
        if (pnt->height < minh)
        {
            minh = pnt->height;
        }
        if (pnt->height > maxh)
        {
            maxh = pnt->height;
        }
        totalh += pnt->height;
        count++;
    }

    double avg = totalh / count;
    pair[0] = minh;
    pair[1] = maxh;

    printf("avg heigh: %f\n", avg);
    printf("minimum heigh: %f\n", minh);
    printf("max heigh: %f\n", maxh);
}

void readPointCloudData(FILE *stream, List *list)
{
    pcd_t pnt;

    if (!stream)
    {
        fprintf(stderr, "Can not read");
        return;
    }
    // while (fscanf(stream, "%lf %lf %lf", &pnt.x, &pnt.y, &pnt.height) == 3)
    // {
    //     pnt.amtWater = 0;
    //     pnt.north = pnt.south = pnt.west = pnt.west = NULL;
    //     listAddEnd(list, &pnt);
    // }
    
    while (!feof(stream) && fscanf(stream, "%lf %lf %lf", &pnt.x, &pnt.y, &pnt.height) == 3)
    {
        printf("Read point: (%f, %f, %f)\n", pnt.x, pnt.y, pnt.height);
        listAddEnd(list, &pnt);
    }
}

void imagePointCloud(List *list, char *filename)
{
    // double min_h
    if (list == NULL)
    {
        printf("null list");
        return;
    }
    double pair[2];
    stat1(list, pair);
    int width = (int)sqrt(list->size);
    int height = (list->size + width - 1) / width;
    double range = pair[1] - pair[0];
    if (range == 0)
        range = 1;
    Bitmap *bitmap = bm_create(width, height);
    if (!bitmap)
    {
        printf("cant create bitmap");
        return;
    }

    int x = 0, y = 0;
    for (int i = 0; i < list->size; i++)
    {
        pcd_t *pnt = (pcd_t *)listGet(list, i);

        double rgb = ((pnt->height - pair[0]) / range) * 255.0;
        if (rgb < 0)
            rgb = 0;
        if (rgb > 255)
            rgb = 255;
        unsigned int color = (0xFF << 24) | ((int)rgb << 16) | ((int)rgb << 8) | (int)rgb;

        bm_set_color(bitmap, color);
        bm_putpixel(bitmap, y, x);

        if (++x >= width)
        {
            x = 0;
            y++;
        }
    }
    bm_save(bitmap, "./output.bmp");
    bm_free(bitmap);
    printf("Bitmap saved successfully as %s\n", filename);
}

// int main(int argc, char *argv[])
// {
//     if (argc < 2)
//     {
//         fprintf(stderr, "Usage: %s <datafile>\n", argv[0]);
//         return 1;
//     }

//     FILE *file = fopen(argv[1], "r");
//     if (!file)
//     {
//         fprintf(stderr, "Failed to open file: %s\n", argv[1]);
//         return 1;
//     }

//     List list;
//     listInit(&list, sizeof(pcd_t));

//     readPointCloudData(file, &list);
//     fclose(file);

//     double heightPair[2];
//     stat1(&list, heightPair);

//     free(list.data);
//     return 0;
//     // stat1();
//     // return;
// }


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <datafile>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Failed to open file: %s\n", argv[1]);
        return 1;
    }

    List list;
    listInit(&list, sizeof(pcd_t));

    printf("Reading point cloud data...\n");
    readPointCloudData(file, &list); 
    fclose(file);                    

    double heightPair[2];    
    stat1(&list, heightPair); 

    
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working directory: %s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
    }

   
    imagePointCloud(&list, "output.bmp");

    free(list.data); 

    printf("Program successful!\n");
    return 0;
}

