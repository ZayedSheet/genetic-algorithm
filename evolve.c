#include "a4.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

Individual *evolve_image_wrapper(const PPM_IMAGE *image, int num_generations, int population_size, double rate);

static int compare(const void *s1, const void *s2) {
    Individual *c1 = (Individual *)s1;
    Individual *c2 = (Individual *)s2;
    double compared = c1->fitness - c2->fitness;

    if (fabs(compared) < 10e-9) return 0;
    else if (compared < 0) return -1;
    return 1;
}

PPM_IMAGE *evolve_image(const PPM_IMAGE *image, int num_generations, int population_size, double rate){
    Individual *ind = evolve_image_wrapper(image, num_generations, population_size, rate);

    PPM_IMAGE *img = malloc(sizeof(PPM_IMAGE));
    memcpy(img, &(ind->image), sizeof(PPM_IMAGE));
    img->data = malloc((ind->image.width * ind->image.height) * sizeof(PIXEL));
    memcpy(img->data, (ind->image).data, (ind->image.width * ind->image.height) * sizeof(PIXEL));

    for (int i = 0; i < population_size; i++){
        free(ind[i].image.data);
    }
    free(ind);
    return img;
}

Individual *evolve_image_wrapper(const PPM_IMAGE *image, int num_generations, int population_size, double rate){
    srand(time(NULL));

    Individual *individual = generate_population(population_size,image->width,image->height,image->max_color);
    comp_fitness_population(image->data,individual,population_size);
    qsort(individual,population_size,sizeof(Individual),compare);

    for (int i = 1; i <= num_generations; i++) {
        crossover(individual,population_size);
        mutate_population(individual,population_size,rate);
        comp_fitness_population(image->data,individual,population_size);
        qsort(individual,population_size,sizeof(Individual),compare);
        printf("Generation: %d Fitness: %.10e\n",i,individual[0].fitness);
    }
    return individual;
}

void free_image(PPM_IMAGE *p){
    free(p->data);
    free(p);
}