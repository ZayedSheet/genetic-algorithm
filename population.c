#include <stdio.h>
#include <stdlib.h>
#include "a4.h"
#include <time.h>

PIXEL * generate_random_image ( int width , int height , int max_color ){
    PIXEL *pixels = malloc ((width*height)* sizeof(PIXEL));
    for (int i = 0; i < width*height; i++){
        pixels[i].r = rand() % (max_color+1);
        pixels[i].g = rand() % (max_color+1);
        pixels[i].b = rand() % (max_color+1); 
    }
    return pixels;
}

Individual * generate_population ( int population_size , int width , int height , int max_color ){
    Individual *ind = malloc((population_size)* sizeof(Individual));
    for (int i = 0; i < population_size; i++){
        PPM_IMAGE img;
        img.width = width;
        img.height = height;
        img.max_color = max_color;
        img.data = generate_random_image(width, height, max_color);
        ind[i].image = img;
    }
    return ind;
}

