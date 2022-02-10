#include <stdio.h>
#include <stdlib.h>

#include "model/hero/hero.h"
#include "model/enemy/enemy.h"

#define ENEMY_TYPE_AMOUNT 5

hero *generate_hero(FILE *f);
enemy *generate_enemies(FILE *f);
char **generate_map(FILE *f, int X, int Y);

int main() {
    int i, j;
    int X, Y;
    FILE *f;
    char **M;
    f = fopen("MAP.txt", "r");

    if (!f)
        return 3;

    hero ness = *generate_hero(f);
    enemy* enemy_list = generate_enemies(f);

    fscanf(f, "%d %d", &X, &Y);

    M = generate_map(f, X, Y);

    show_hero_data(&ness);
    for (i = 0; i < ENEMY_TYPE_AMOUNT; i++)
        show_enemy_data(&enemy_list[i]);

    for (i = 0; i < X; i++) {
        for (j = 0; j < Y; j++) {
            printf("%c", M[i][j]);
        }
    }

    puts("");
    fclose(f);
    return 0;
}

hero *generate_hero(FILE *f) {
    hero *h = (hero*) malloc(sizeof(hero));
    fscanf(f, "%d %d", &h->P, &h->K);
    return h;
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

char **generate_map(FILE *f, int X, int Y) {
    int i, j;
    char waste;
    char **M;

    M = (char**) calloc(sizeof(char*), X);
    for (i = 0; i < X; i++) {
        M[i] = (char*) calloc(sizeof(char), Y);
    }

    for (i = 0; i < X; i++)
        for (j = 0; j < Y; j++)
            fscanf(f, "%c", &M[i][j]);

    return M;
}

