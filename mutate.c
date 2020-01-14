#include "a4.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void mutate(Individual *individual, double rate){
    int n = individual->image.width * individual->image.height;
    int max_color = individual->image.max_color;
    int num = (int)(rate/100*n);
    for (int i = 0; i < num; i++) {
        int x = rand()% n;
        individual->image.data[x].r = (rand()%(max_color+1));
        individual->image.data[x].g = (rand()%(max_color+1));
        individual->image.data[x].b = (rand()%(max_color+1));
    }
}
void mutate_population(Individual *individual, int population_size, double rate){
    int n = population_size/4;
    for (int i = n; i < population_size; i++){
        mutate(&(individual[i]),rate);
    }
}

