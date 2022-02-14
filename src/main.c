#include <stdio.h>
#include <stdlib.h>

#include "model/hero/hero.h"
#include "model/enemy/enemy.h"
#include "model/map/map.h"

int main() {
    int i, j;
    int X, Y;

    FILE *f;
    map stage;
    hero ness;
    enemy* enemy_list;

    f = fopen("MAP.txt", "r");

    if (!f)
        return 3;

    ness = *generate_hero(f);
    enemy_list = generate_enemies(f);

    fscanf(f, "%d %d", &X, &Y);

    stage = *generate_map(f, X, Y);

    show_hero_data(&ness);
    for (i = 0; i < ENEMY_TYPE_AMOUNT; i++)
        show_enemy_data(&enemy_list[i]);

    show_map(&stage);

    fclose(f);
    return 0;
}

