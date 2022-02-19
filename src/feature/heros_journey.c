#include <string.h>
#include "heros_journey.h"

#define DOT -1
#define VERTICAL 8
#define HORIZONTAL 6
#define CROSSING 5
#define NO_INFO 7

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

int * get_moves_from_pos(map* m, int i, int j){
    int * result = (int*) malloc(sizeof(int)*4);
    memset(result,0,sizeof(result));
    // {esquerda,direita,sobe,desce}
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

int move_on_map(int lvl, hero* ness, enemy *enemy_list, stack *stack, map *m, int i, int j, int lasti, int lastj, int mat[m->X][m->Y]){
    hero copy;
    copy.P = ness->P;
    copy.K = ness->K;
    int matcopy[m->X][m->Y];
    memcpy(matcopy, mat, sizeof(int)*m->X*m->Y);
    item ncoord;
    ncoord.i = i;
    ncoord.j = j;
    if ((i >= 0 && j >= 0) && (i <= m->X && j <= m->Y)) {
        int enemy_index = check_enemy(m->Matrix[i][j], enemy_list);
        if (enemy_index != -1 && enemy_list[enemy_index].type != 'G') {
            if (copy.P >= enemy_list[enemy_index].P) {
                copy.P += enemy_list[enemy_index].X;
                printf("Ganhou contra %c\n",enemy_list[enemy_index].type);
            } else {
                if (copy.K > 0) {
                    copy.P += enemy_list[enemy_index].X;
                    copy.K--;
                    printf("Ganhou contra %c usando o poder K\n",enemy_list[enemy_index].type);
                } else {
                    printf("Perdeu contra %c\n",enemy_list[enemy_index].type);
                    return 0;
                }
            }
        }

        printf("poder do heroi: %d, K: %d\n", copy.P, copy.K);

        if (enemy_list[enemy_index].type == 'G') {
            ness->P = copy.P;
            ness->K = copy.K;
            if (copy.P > enemy_list[enemy_index].P){
                printf("Ganhou\n");
                push(&stack, ncoord);
                return 999;    
            } else {
                printf("Perdeu\n");
                return 0;
            }
            
        }

        int z;
        int * possible_moves = NULL;
        possible_moves = get_moves_from_pos(m,i,j);
        if(m->Matrix[i][j] != '+'){
            matcopy[i][j] = 1;
        }
        for(int x=0;x<4;x++){
            if(possible_moves[x]){
                printf("%d [%c] From [%d, %d]: %d %d %d %d\n",lvl,m->Matrix[i][j],i,j,possible_moves[0],possible_moves[1],possible_moves[2],possible_moves[3]);
                switch(x){
                    case 0:
                        printf("prox: %d\n",mat[i][j-1]);
                        if(!mat[i][j-1] && (i != lasti || j-1 != lastj)){
                            printf("foi pra esquerda\n");
                            z = move_on_map(lvl+1, &copy, enemy_list, stack, m, i, (j-1), i, j, matcopy);
                            if(z == 999){
                                push(&stack,ncoord);                   
                                return 999;
                            }
                        }
                        else{
                            printf("não vai pra esquerda\n");
                        }
                        break;
                    case 1:
                        printf("prox: %d\n",mat[i][j+1]);
                        if(!mat[i][j+1] && (i != lasti || j+1 != lastj)){
                            printf("foi pra direita\n");
                            z = move_on_map(lvl+1, &copy, enemy_list, stack, m, i, (j+1), i, j, matcopy);
                            if(z == 999){
                                push(&stack,ncoord);
                                return 999;
                            }
                        }
                        else{
                            printf("não vai pra direita\n");
                        }
                        break;
                    case 2:
                        printf("prox: %d\n",mat[i-1][j]);
                        if(!mat[i-1][j] && (i-1 != lasti || j != lastj)){
                            printf("foi pra cima\n");
                            z = move_on_map(lvl+1, &copy, enemy_list, stack, m, (i-1), j, i, j, matcopy);
                            if(z == 999){
                                push(&stack,ncoord);
                                return 999;
                            }
                        }
                        else{
                            printf("não vai pra cima\n");
                        }
                        break;
                    case 3:
                        printf("prox: %d\n",mat[i+1][j]);
                        if(!mat[i+1][j] && (i+1 != lasti || j != lastj)){
                            printf("foi pra baixo\n");
                            z = move_on_map(lvl+1, &copy, enemy_list, stack, m, (i+1), j, i, j, matcopy);
                            if(z == 999){
                                push(&stack,ncoord);
                                return 999;
                            }
                        }
                        else{
                            printf("não vai pra baixo\n");
                        }
                        break;            
                }
            }
        }
        printf("level %d Acabou\n", lvl);
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
    } else if (pos == '@') {
        return NO_INFO;
    } return DOT;
}