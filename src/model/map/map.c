#include "map.h"

void show_map(map* m) {
    int i, j;
    for (i = 0; i < m->X; i++) {
        for (j = 0; j < m->Y; j++) {
            printf("%c", m->Matrix[i][j]);
        }
        puts("");
    }   
}

map *generate_map(FILE *f, int X, int Y) {
    int i, j;
    char read;
    map *m = (map*) malloc(sizeof(map));

    m->X = X;
    m->Y = Y;

    m->Matrix = (char**) calloc(sizeof(char*), X);
    for (i = 0; i < X; i++) {
        m->Matrix[i] = (char*) calloc(sizeof(char), Y);
    }

    i = 0;
    j = 0;

    while (i < X) {
        while (j < Y) {
            fscanf(f, "%c", &read);
            if (read != '\n') {
                m->Matrix[i][j] = read;
                j++;
            }
        }
        i++;
        j = 0;
    }

    return m;
}