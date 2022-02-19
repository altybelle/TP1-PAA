#include <stdio.h>
#include <stdlib.h>

#ifndef ENEMY
#define ENEMY

#define ENEMY_TYPE_AMOUNT 5

typedef struct enemy {
    unsigned char type;          // Tipo de inimigo
    unsigned int P;              // Pontos de força
    unsigned int X;              // Pontos de experiência
} enemy;

void show_enemy_data(enemy*);
enemy *generate_enemies(FILE*);

#endif //ENEMY