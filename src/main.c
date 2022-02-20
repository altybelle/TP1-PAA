#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NORMAL 1
#define ANALISE 2

#include "feature/heros_journey.h"

int menu();

int main() {
    int X, Y;
    int max_recursions, count_recursions; 

    int operation = 0;

    while (operation != NORMAL && operation != ANALISE) {
        operation = menu();
    }
    
    time_t begin, end;

    FILE *f;
    map stage; hero ness;
    enemy* enemy_list = NULL;
    stack* path = NULL;
    
    f = fopen("MAP.txt", "r");

    if (!f)
        return 3;

    begin = clock();

    ness = *generate_hero(f);
    enemy_list = generate_enemies(f);

    fscanf(f, "%d %d", &X, &Y);

    stage = *generate_map(f, X, Y);

    int mat[X][Y];
    memset(mat, 0, stage.X * stage.Y * sizeof(int));

    max_recursions = count_recursions = 0;

    hero_position initial_pos = *get_initial_position(&stage);
    move_on_map(1, &max_recursions, &count_recursions, &ness, enemy_list, &path, &stage, initial_pos.X, initial_pos.Y, -1, -1, mat);
    puts("========================================");
    if (!is_stack_empty(path)) {
        while (final_move(&ness, enemy_list, &path, &stage) != 999) {
            puts("========================================");
        }
    } else {
        puts("Apesar de todas as tentativas, Ness falha em derrotar Giygas!");
    }
    puts("========================================");

    fclose(f);

    end = clock();

    if (operation == ANALISE) {
        double time_spent = (double) (end - begin) * 1000.00 / CLOCKS_PER_SEC;
        printf("Recursao maxima: %d\n", max_recursions);
        printf("Total de recursoes: %d\n", count_recursions);
        printf("Tempo gasto: %.3lf ms\n", time_spent);
        puts("========================================");
    }
    

    return 0;
}

int menu() {
    int menu;
    puts("========================================");
    puts("| Modos de operacao disponiveis:       |");
    puts("| 1. Modo normal;                      |");
    puts("| 2. Modo de analise.                  |");
    puts("========================================");
    printf("Escolha: ");
    scanf("%d", &menu);
    return menu;
}