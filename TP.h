#include<stdio.h>
#include<stdlib.h>

typedef struct Registro {
	int prioridade, chave;
} Registro;

typedef struct No * Apontador;

typedef struct No {
	Registro registro;
	Apontador esq, dir;
} No;

void inicializar(Apontador *p);

void inserir(Registro x, Apontador *p, Apontador *ant, Apontador *cab, int sent, int aux);

void corte(Apontador *p, Apontador *menor, Apontador *maior, Registro x);

void limpar(Apontador *p, Apontador *cab);

void fusao(Apontador *p, Apontador *menor, Apontador *cabme, Apontador *maior, Apontador *cabma, int aux);

int cp(Apontador p,Registro t,int *po);

void pesquisa(Apontador p, Registro t);


