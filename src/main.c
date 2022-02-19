#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "feature/heros_journey.h"

int main() {
    int i;
    int X, Y;
    
    FILE *f;
    map stage; hero ness;
    enemy* enemy_list = NULL;
    stack* pilha = NULL;
    
    f = fopen("MAP.txt", "r");

    if (!f)
        return 3;

    ness = *generate_hero(f);
    enemy_list = generate_enemies(f);

    fscanf(f, "%d %d", &X, &Y);

    stage = *generate_map(f, X, Y);

    int mat[X][Y];
    memset(mat, 0, stage.X * stage.Y * sizeof(int));

    show_hero_data(&ness);
    for (i = 0; i < ENEMY_TYPE_AMOUNT; i++)
        show_enemy_data(&enemy_list[i]);

    show_map(&stage);
    hero_position initial_pos = *get_initial_position(&stage);
    move_on_map(1, &ness, enemy_list, &pilha, &stage, initial_pos.X, initial_pos.Y, -1, -1, mat);
    puts("");
    
    if (!is_stack_empty(pilha)) {
        while (!is_stack_empty(pilha)) {
            pop(&pilha);
        }
    }

    fclose(f);
    return 0;
}