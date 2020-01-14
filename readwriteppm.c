#include <stdio.h>
#include <stdlib.h>
#include "a4.h"

PPM_IMAGE * read_ppm ( const char * file_name ){

    FILE * fPointer;
    fPointer = fopen(file_name, "r");
    fseek(fPointer, 3, SEEK_SET);//seeks forward 4 characters (ignoring A3)

    PPM_IMAGE * img = malloc(sizeof(PPM_IMAGE));
    fscanf(fPointer, "%d%d%d", &img->width,&img->height,&img->max_color);//scans for width, height and max color

    PIXEL *pixels = malloc ((img->width*img->height)* sizeof(PIXEL));
    int i = 0;
    while(!feof(fPointer)){ //while file pointer has not reached the end of the file
            fscanf(fPointer, "%hhu%hhu%hhu", &(pixels[i].r), &(pixels[i].g), &(pixels[i].b) );//scans for sets of r g b
            i++;
    }
    img->data = pixels;
    fclose(fPointer);
    return img;
}


void write_ppm ( const char * file_name , const PPM_IMAGE * image ){
    FILE * fPointer;
    fPointer = fopen(file_name, "w");
    fprintf(fPointer, "P3\r\n%d %d\r\n%d", image->width,image->height,image->max_color);
    for (int i = 0; i < image->height; i++){
        fprintf(fPointer, "\r\n");
        for (int j = 0; j < image->width; j++){
            fprintf(fPointer, "%d %d %d ", (image->data)[(i*image->width)+j].r,(image->data)[(i*image->width)+j].g,(image->data)[(i*image->width)+j].b);
        }
    }
    fclose(fPointer);
}