#ifndef HERO
#define HERO

typedef struct hero Ness;

typedef struct hero {
    unsigned int P;          // Força do heroi
    unsigned int K;          // Quantidade de habilidades PK Flash
} hero;

void show_hero_data(hero*);

#endif // HERO