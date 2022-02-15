#include "../model/hero/hero.h"
#include "../model/enemy/enemy.h"
#include "../model/map/map.h"

#define DOT -1
#define VERTICAL 8
#define HORIZONTAL 6
#define CROSSING 5

typedef struct hero_position {
    int X;
    int Y;
} hero_position;

hero_position* get_hero_starter_position(map *m) {
    int i, j;
    hero_position *pos = (hero_position*) malloc(sizeof(hero_position));
    for (i = 0; i < m->X; i++) {
        for (j = 0; j < m->Y; j++) {
            if (m->Matrix[i][j] == '@') {
                pos->X = i;
                pos->Y = j;
                return pos;
            }
        }
    }
    free(pos);
    return NULL;
}

int move_on_map(hero* ness, enemy *enemy_list, map *m, int i, int j) {
    hero copy;

    copy.P = ness->P;
    copy.K = ness->K;

    if ((i >= 0 && j >= 0) && (i < m->X && j < m->Y)) {
        int enemy_index = check_enemy(m->Matrix[i][j], enemy_list);
        if (enemy_index != -1) {
            if (copy.P >= enemy_list[enemy_index].P) {
                copy.P += enemy_list[enemy_index].X;
                m->Matrix[i][j] = '+';
            } else {
                if (copy.K > 0) {
                    copy.P += enemy_list[enemy_index].X;
                    copy.K--;
                    m->Matrix[i][j] = '+';
                } else {
                    return 0;
                }
            }
        }

        if (enemy_list[enemy_index].type == 'G') return 999;

        int route = check_route(m->Matrix[i][j]);
        if (route == VERTICAL) {

        } else if (route == HORIZONTAL) {

        } else if (route == CROSSING) {

        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

int check_enemy(char pos, enemy *enemy_list) {
    int i;
    for (i = 0; i < ENEMY_TYPE_AMOUNT; i++) {
        if (enemy_list[i].type == pos) {
            return i;
        }
    }
    return -1;
}

int check_route(char pos) {
    if (pos == '|') {
        return VERTICAL;
    } else if (pos == '-') {
        return HORIZONTAL;
    } else if (pos == '+') {
        return CROSSING;
    } else {
        return DOT;
    }
}