#include "hero.h"

#include <stdio.h>

void show_hero_data(hero* h) {
    printf("Hero[P=%d, K=%d]\n", h->P, h->K);
}