#include "hero.h"

void show_hero_data(hero* h) {
    printf("Hero[P=%d, K=%d]\n", h->P, h->K);
}

hero *generate_hero(FILE *f) {
    hero *h = (hero*) malloc(sizeof(hero));
    fscanf(f, "%d %d", &h->P, &h->K);
    return h;
}