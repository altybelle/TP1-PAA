#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "feature/heros_journey.h"

int main() {
    int i, j;
    int X, Y;
    
    FILE *f;
    map stage;
    hero ness;
    enemy* enemy_list = NULL;
    stack* pilha = NULL;
    item k;
    k.i = -1;
    k.j = -1;
    push(&pilha, k);
    f = fopen("MAP.txt", "r");

    if (!f)
        return 3;

    ness = *generate_hero(f);
    enemy_list = generate_enemies(f);

    fscanf(f, "%d %d", &X, &Y);

    stage = *generate_map(f, X, Y);
    int mat[stage.X][stage.Y];
    for(i=0;i<stage.X;i++){
        for(j=0;j<stage.Y;j++){
            mat[i][j] = 0;
        }
    }
    //int **mat = (int **)malloc(sizeof(int*)*stage.X);
    //for(int x=0;x<stage.X;x++){
        //mat[x] = (int *)malloc(sizeof(int)*stage.Y);
    //}
    //memset(mat, 0, stage.X*stage.Y*sizeof(int));
    show_hero_data(&ness);
    for (i = 0; i < ENEMY_TYPE_AMOUNT; i++)
        show_enemy_data(&enemy_list[i]);

    show_map(&stage);
    hero_position initial_pos = *get_initial_position(&stage);
    move_on_map(1, &ness,enemy_list,pilha,&stage,initial_pos.X,initial_pos.Y, -1, -1, mat);
    printf("\n\n\n\n");
    if(!is_stack_empty(pilha)){
       while(!is_stack_empty(pilha)){
           item i = *pop(&pilha);
           printf("X: %d Y: %d\n", i.i, i.j);
       }
    }
    else{
        printf("pilha nula\n");
    }
    
    fclose(f);
    return 0;
}