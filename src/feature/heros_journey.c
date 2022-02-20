#include <string.h>
#include "heros_journey.h"

#define MOVE_POSSIBILITIES 4

hero_position* get_initial_position(map *m) {
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

int *get_moves_from_pos(map* m, int i, int j){
    int *result = (int*) malloc(sizeof(int) * MOVE_POSSIBILITIES);
    memset(result, 0, MOVE_POSSIBILITIES);

    if (i>0){
        if (m->Matrix[i-1][j] != '.'){
                result[2] = 1;
            }
        }
    if (i<(m->X)-1){
        if (m->Matrix[i+1][j] != '.'){
                result[3] = 1;
            }
        }
    if (j>0){
        if (m->Matrix[i][j-1] != '.'){
                result[0] = 1;
            }
        }
    if (j<(m->Y)-1){
        if (m->Matrix[i][j+1] != '.'){
                result[1] = 1;
            }
        }
    return result;
}

int move_on_map(int lvl, int *max_recursions, int *count_recursions, hero* ness, enemy *enemy_list, stack **st, map *m, 
                int i, int j, int lasti, int lastj, int mat[m->X][m->Y]){
    int it;
    int matcopy[m->X][m->Y];
    hero copy;
    item ncoord;

    copy.P = ness->P;
    copy.K = ness->K;

    if (lvl > (*max_recursions))
        (*max_recursions) = lvl;
    
    (*count_recursions)++;
    
    memcpy(matcopy, mat, sizeof(int) * m->X * m->Y);

    ncoord.i = i;
    ncoord.j = j;

    if ((i >= 0 && j >= 0) && (i <= m->X && j <= m->Y)) {
        int enemy_index = check_enemy(m->Matrix[i][j], enemy_list);
        if (enemy_index != -1 && enemy_list[enemy_index].type != 'G') {
            if (copy.P >= enemy_list[enemy_index].P) {
                copy.P += enemy_list[enemy_index].X;
            } else {
                if (copy.K > 0) {
                    copy.P += enemy_list[enemy_index].X;
                    copy.K--;
                } else {
                    return 0;
                }
            }
        }

        if (enemy_list[enemy_index].type == 'G') {
            if (copy.P > enemy_list[enemy_index].P){
                push(st, ncoord);
                return 999;    
            } else {
                return 0;
            }
            
        }

        int z;

        int *possible_moves = NULL;

        possible_moves = get_moves_from_pos(m,i,j);
        if(m->Matrix[i][j] != '+'){
            matcopy[i][j] = 1;
        }

        for(it = 0; it < 4; it++){
            if(possible_moves[it]){
                switch(it){
                    case 0:
                        if(!mat[i][j - 1] && (i != lasti || j - 1 != lastj)){
                            z = move_on_map(lvl + 1, max_recursions, count_recursions, &copy, enemy_list, st, m, i, (j - 1), i, j, matcopy);
                            if(z == 999){
                                push(st, ncoord);                   
                                return 999;
                            }
                        }
                        break;
                    case 1:
                        if(!mat[i][j + 1] && (i != lasti || j + 1 != lastj)){
                            z = move_on_map(lvl + 1, max_recursions, count_recursions, &copy, enemy_list, st, m, i, (j + 1), i, j, matcopy);
                            if(z == 999){
                                push(st, ncoord);
                                return 999;
                            }
                        }
                        break;
                    case 2:
                        if(!mat[i - 1][j] && (i - 1 != lasti || j != lastj)){
                            z = move_on_map(lvl + 1, max_recursions, count_recursions, &copy, enemy_list, st, m, (i - 1), j, i, j, matcopy);
                            if(z == 999){
                                push(st, ncoord);
                                return 999;
                            }
                        }
                        break;
                    case 3:
                        if(!mat[i + 1][j] && (i + 1 != lasti || j != lastj)){
                            z = move_on_map(lvl + 1, max_recursions, count_recursions, &copy, enemy_list, st, m, (i + 1), j, i, j, matcopy);
                            if(z == 999){
                                push(st, ncoord);
                                return 999;
                            }
                        }
                }
            }
        }
    }
    return 0;
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

int final_move(hero* ness, enemy *enemy_list, stack **st, map *m){
    item pos = *pop(st);

    printf("Linha: %d, Coluna: %d; ", pos.i, pos.j);

    int enemy_index = check_enemy(m->Matrix[pos.i][pos.j], enemy_list);
    if (enemy_index != -1 && enemy_list[enemy_index].type != 'G') {
        if (ness->P >= enemy_list[enemy_index].P) {
            ness->P += enemy_list[enemy_index].X;
            printf("P: %d, K: %d", ness->P, ness->K);
        } else {
            if (ness->K > 0) {
                ness->P += enemy_list[enemy_index].X;
                ness->K--;
                printf("P: %d, K: %d", ness->P, ness->K);
            }
        }
    }

    if (enemy_list[enemy_index].type == 'G') {
        if (ness->P > enemy_list[enemy_index].P){
            printf(" P: %d, K: %d\n", ness->P, ness->K);
            printf("Ness teve sucesso ao derrotar Giygas!\n");
            return 999;    
        }
    }
    printf("\n");
    return 0;
}
