#include<stdio.h>
#include <stdlib.h>

struct no {
	int info;
	struct no *esq;
	struct no *dir;
};

struct no *add_arvore(struct no *p, int info) {
	if(!p) {
		p = calloc(1, sizeof(struct no *));
		p->info=info;
		return p;
	}
	
	//poe na ordem de acordo com o valor de info, mas nao fica balanceando
	if(p->info > info)
		p->esq = add_arvore(p->esq, info);
	else if(p->info < info)
		p->dir = add_arvore(p->dir, info);
	
	return p;
}

//percurso em ordem
void printa_arvore(struct no *raiz ) {
	if(raiz) {
		if (raiz->esq) {
			printa_arvore(raiz->esq);
		}
		
		if (raiz->dir) {
			printa_arvore(raiz->dir);
		}

		printf("%d->", raiz->info);
	}
}

//busca em pre ordem
int busca_na_arvore(struct no *raiz, int valor ) {
	int achou = 0;
	if(raiz) {
		if(raiz->info == valor) {
			achou = 1;
			return achou;
		}
		
		else if((raiz->info > valor) && (raiz->esq != NULL) )
			achou = busca_na_arvore(raiz->esq, valor);
		
		else if((raiz->info < valor) && (raiz->dir != NULL) )
			achou = busca_na_arvore(raiz->dir, valor);
	}
	return achou;
}

int main(int argc, char **argv)
{	//srand(2);
	
	struct no *raiz = NULL;
		
	raiz = add_arvore(raiz, 10);
	raiz = add_arvore(raiz, 2);
	raiz = add_arvore(raiz, 5);
	raiz = add_arvore(raiz, 3);
	raiz = add_arvore(raiz, 11);
	raiz = add_arvore(raiz, 1);
	printa_arvore(raiz);
	printf("\nACHOU? %d\n",busca_na_arvore(raiz,5) );
	
	return 0;
}
