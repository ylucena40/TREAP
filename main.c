#include<stdio.h>
#include<stdlib.h>
#include "TP.h"


void inicializar(Apontador *p) {
	*p = (Apontador)calloc(sizeof(No),1); 
	(*p)->esq = NULL; 
	(*p)->dir = NULL;  
}

void inserir(Registro x, Apontador *p, Apontador *ant, Apontador *cab, int sent, int aux) {
	if(aux == 1){
		*p = (Apontador)calloc(sizeof(No),1); 
		(*p)->esq = NULL; 
		(*p)->dir = NULL;  
		(*p)->registro = x;
		return;
	}
	else{
		if(*p == NULL){
				*p = (Apontador)calloc(sizeof(No),1); 
				(*p)->esq = NULL; 
				(*p)->dir = NULL;  
				(*p)->registro = x;
				return;		
			}
		if(x.prioridade < (*p)->registro.prioridade){
			if( *p == *ant ){
				if(x.chave < (*p)->registro.chave){
					Apontador novo;
					inicializar(&novo);
					novo->registro = x;
					novo->dir = *ant;
					*p = novo;
					return;
				}
				else if(x.chave > (*p)->registro.chave){
					Apontador novo;
					inicializar(&novo);
					novo->registro = x;
					novo->esq = *ant;
					*p = novo;
					return;
				}
			}
			else{
				if( sent == 1 ){
					if(x.chave < (*p)->registro.chave){
						Apontador novo;
						inicializar(&novo);
						novo->registro = x;
						novo->dir = *p;
						(*ant)->dir = novo;
						return;
					}
					else if(x.chave > (*p)->registro.chave){
						Apontador novo;
						inicializar(&novo);
						novo->registro = x;
						novo->esq = *p;
						(*ant)->dir = novo;
						return;
					}
				}
				else{
					if(x.chave < (*p)->registro.chave){
						Apontador novo;
						inicializar(&novo);
						novo->registro = x;
						novo->dir = *p;
						(*ant)->esq = novo;
						return;
					}
					else if(x.chave > (*p)->registro.chave){
						Apontador novo;
						inicializar(&novo);
						novo->registro = x;
						novo->esq = *p;
						(*ant)->esq = novo;
						return;
					}
				}
			}
		}
		else{
			if(x.chave < (*p)->registro.chave)
				inserir(x,&(*p)->esq,&(*p),&(*cab),0,aux);
			else if(x.chave > (*p)->registro.chave)
				inserir(x,&(*p)->dir,&(*p),&(*cab),1,aux);
			else
				return;
		}
	}
}

void corte(Apontador *p, Apontador *menor, Apontador *maior, Registro x){
	if((*p) != NULL){
		if( (*p)->registro.chave < x.chave){
			Registro t;
			t.chave = (*p)->registro.chave;
			t.prioridade = (*p)->registro.prioridade;
			inserir(t,&(*menor),&(*menor),&(*menor),0,2);
		}
		else if( (*p)->registro.chave > x.chave){
			Registro t;
			t.chave = (*p)->registro.chave;
			t.prioridade = (*p)->registro.prioridade;
			inserir(t,&(*maior),&(*maior),&(*maior),0,2);
		}
		corte(&(*p)->esq,&(*menor),&(*maior),x);
		corte(&(*p)->dir,&(*menor),&(*maior),x);
	}
}

void limpar(Apontador *p, Apontador *cab){
	if((*p)!=NULL){
		limpar(&(*p)->esq,&(*cab));
		limpar(&(*p)->dir,&(*cab));
		if((*p) != (*cab)){
			free(*p);
			*p=NULL;
		}
	}
}

void fusao(Apontador *p, Apontador *menor, Apontador *cabme, Apontador *maior, Apontador *cabma, int aux){
	if( (*menor)->registro.prioridade < (*maior)->registro.prioridade || aux == 1){
		if((*menor)->dir == NULL){
			(*menor)->dir = (*maior);
			(*p) = (*cabme);
		}
		else{
			fusao(&(*p),&(*menor)->dir,&(*cabme),&(*maior),&(*cabma),1);
		}
	}
	else{
		if((*maior)->esq == NULL){
			(*maior)->esq= (*menor);
			(*p) = (*cabma);
		}
		else{
			fusao(&(*p),&(*menor),&(*cabme),&(*maior)->esq,&(*cabma),2);
		}
	}
}


int cp(Apontador p,Registro t,int *po) {
	if (p != NULL) {
		cp(p->esq,t,&(*po));
		if(t.chave == p->registro.chave)
			*po = 1;
		cp(p->dir,t,&(*po));
	}
}

void pesquisa(Apontador p, Registro t){
	if(p==NULL)
		return;
	if(t.chave < p->registro.chave){
		printf("L");
		pesquisa(p->esq,t);
	}
	else if(t.chave > p->registro.chave){
		printf("R");
		pesquisa(p->dir,t);
	}
	else{
		return;
	}
}

int main(){
	Apontador p;
	Registro t;
	int i=1, aux=1;
	while(i!=0){
		system("cls");
		printf("DIGITE A OPCAO:\n1 INSERIR.\n2 PESQUISAR.\n3 REMOVER.\n");
		scanf("%d",&i);
		if(i==1){
			printf("\nDIGITE A CHAVE: ");
			scanf("%d",&t.chave);
			printf("\nDIGITE A PRIORIDADE: ");
			scanf("%d",&t.prioridade);
			inserir(t,&p,&p,&p,0,aux);
			aux++;
		}
		if(i==2){
			if(aux != 0){
				printf("\nDIGITE A CHAVE: ");
				scanf("%d",&t.chave);
				int po=0;
				cp(p,t,&po);
				if(po == 1)
					pesquisa(p,t);
				else
					printf("-1");
			}
		}
		if(i==3){
			if(aux != 0){
				printf("\nDIGITE A CHAVE: ");
				scanf("%d",&t.chave);
				int po=0;
				cp(p,t,&po);
				if(po==1){
					Apontador menor, maior;
					inicializar(&menor);
					inicializar(&maior);
					corte(&p,&menor,&maior,t);
					menor=menor->dir;
					maior=maior->dir;
					limpar(&p,&p);
					fusao(&p,&menor,&menor,&maior,&maior,0);
				}
			}
		}
		getch();
	}
}
