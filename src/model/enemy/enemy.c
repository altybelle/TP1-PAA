#include "enemy.h"

#include <stdio.h>

void show_enemy_data(enemy *e) {
    printf("Enemy[Type=%c, P=%d, K=%d]\n", e->type, e->P, e->X);
}

enemy *generate_enemies(FILE *f) {
    int i;
    char enemy_types[ENEMY_TYPE_AMOUNT] = {'U', 'T', 'S', 'B', 'G'};
    enemy *e = (enemy*) calloc(sizeof(enemy), ENEMY_TYPE_AMOUNT);
    
    for (i = 0; i < ENEMY_TYPE_AMOUNT; i++) {
        e[i].type = enemy_types[i];
        fscanf(f, "%d %d", &e[i].P, &e[i].X);
    }

    return e;
}