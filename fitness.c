#include "a4.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double comp_distance (const PIXEL *A , const PIXEL *B , int image_size){
    long int f = 0;
    for (int i = 0; i < image_size; i++ ){
        f += (A[i].r - B[i].r)*(A[i].r - B[i].r) + (A[i].g - B[i].g)*(A[i].g - B[i].g) + (A[i].b - B[i].b)*(A[i].b - B[i].b);
    }
    return sqrt((double)f);
}
void comp_fitness_population(const PIXEL *image, Individual *individual, int population_size){
    int size = (individual[0].image.width * individual[0].image.height);
    for (int i = 0; i < population_size; i++) {
        individual[i].fitness=comp_distance(image, individual[i].image.data, size);
    }
}
