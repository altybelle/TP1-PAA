#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NORMAL 1
#define ANALISE 2

#include "feature/heros_journey.h"

int menu();
int start(FILE*);

int main() {
    FILE *f;
    char stay_running;
    char file_path[250];
    
    do {
        printf("Insira o caminho do arquivo: ");
        scanf("%s", file_path);

        f = fopen(file_path, "r");
        if (!f) {
            puts("Arquivo não encontrado.");
        }
        else {
            start(f);
            puts("Deseja continuar rodando o programa (S/N)?");
            getchar(); stay_running = getchar();
        }
    } while (file_path[0] != '0' && (stay_running == 'S' || stay_running == 's'));
}

int start(FILE *f) {
    int X, Y;
    int max_recursions, count_recursions; 

    int operation = 0;

    while (operation != NORMAL && operation != ANALISE) {
        operation = menu();
    }
    
    time_t begin, end;

    map stage; hero ness;
    enemy* enemy_list = NULL;
    stack* path = NULL;

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

    free(enemy_list);
    free(path);
    
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