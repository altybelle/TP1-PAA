#include "../model/hero/hero.h"
#include "../model/enemy/enemy.h"
#include "../model/map/map.h"
#include "../data_structures/stack.h"

#ifndef HEROS_JOURNEY
#define HEROS_JOURNEY

typedef struct hero_position {
    int X;
    int Y;
} hero_position;

hero_position* get_initial_position(map*);
int move_on_map(int, hero*, enemy*, stack**, map *m, int, int, int, int, int mat[m->X][m->Y]);
int check_enemy(char, enemy*);

#endif // HEROS_JOURNEY