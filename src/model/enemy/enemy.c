#include "enemy.h"

#include <stdio.h>

void show_enemy_data(enemy *e) {
    printf("Enemy[Type=%c, P=%d, K=%d]\n", e->type, e->P, e->X);
}