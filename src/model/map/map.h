#include <stdio.h>
#include <stdlib.h>

#ifndef MAP
#define MAP

typedef struct map {
    unsigned int X;
    unsigned int Y;
    char **Matrix;
} map;

void show_map(map*);
map *generate_map(FILE*, int, int);

#endif // MAP