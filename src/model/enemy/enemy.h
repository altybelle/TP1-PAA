#ifndef ENEMY
#define ENEMY

typedef struct enemy {
    unsigned char type;          // Tipo de inimigo
    unsigned int P;              // Pontos de força
    unsigned int X;              // Pontos de experiência
} enemy;

void show_enemy_data(enemy*);

#endif //ENEMY