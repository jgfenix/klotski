//20.11.2017 
#include <stdio.h> //printf
#include <stdlib.h> //exit

#define LIMITE_SUPERIOR 5
#define LIMITE_DIREITA 6

struct ponto {
	int x, y;
};

struct ponto *cria_ponto(int x, int y) {
	if(x ==-1 && y ==-1) { //caso o ponto nao exista na peca, por exemplo um T
		// tmp.x = -1;
		// tmp.y = -1;
		// free(tmp);
		return NULL;
	}
	struct ponto *tmp = (struct ponto *) malloc(sizeof(struct ponto));
	tmp->x = x;
	tmp->y = y;
	return tmp;
}

struct obj_generico {
	char *nome ; //deveria ter um tamanho aqui ou pode ser assim?
	struct ponto *Pes ; //Ponto esquerda superior
	struct ponto *Pei ; //Ponto esquerda inferior
	struct ponto *Pds ; //Ponto direita superior
	struct ponto *Pdi ; //Ponto direita inferior
};

//libera os pontos alocados pela funcao cria_ponto e o objeto em si
void jfree(struct obj_generico *obj) {
	free(obj->Pes); 
	free(obj->Pei); 
	free(obj->Pds); 
	free(obj->Pdi);
	free(obj);
}

// struct obj_generico monta_obj(struct ponto Pes, struct Pei, struct Pds, struct Pdi) {
// }
void print_obj(struct obj_generico *obj) {
	if(obj) {
		printf("\t%s\n",obj->nome);
		if(obj->Pes) {
			printf("Pes (%d, %d)\n",obj->Pes->x, obj->Pes->y );
		}
		if(obj->Pei) {
			printf("Pei (%d, %d)\n",obj->Pei->x, obj->Pei->y );
		}
		if(obj->Pds) {
			printf("Pds (%d, %d)\n",obj->Pds->x, obj->Pds->y );
		}
		if(obj->Pdi) {
			printf("Pdi (%d, %d)\n",obj->Pdi->x, obj->Pdi->y );
		}
	}
	printf("------------------------------------------\n");
};

//DEPRECATED?
// verifica se pode mover pra nova posicao, se sim, retorna 1, se nao, retorna 0
int verifica_posicao_objetos(struct obj_generico *vetor_obj, int tamanho_vetor, int x, int y) {
	while(tamanho_vetor) {
		// print_obj(vetor_obj);

		if(	(vetor_obj->Pes->x == x && vetor_obj->Pes->y == y) ||
			(vetor_obj->Pei->x == x && vetor_obj->Pei->y == y) ||
			(vetor_obj->Pds->x == x && vetor_obj->Pds->y == y) ||
			(vetor_obj->Pdi->x == x && vetor_obj->Pdi->y == y)) {
			printf("NAO PODE MOVER, %s ESTA LA\n", vetor_obj->nome );
			return 0;
		}
		tamanho_vetor--;
		vetor_obj++;
	}
	return 1;
}

int limite_sup(int pos int limite) {
	if(pos + 1 >= limite)
		return 0;
	else
		return 1;
}
// considero que o programa/usuario nao vai tentar mover diagonalmente o objeto.
// Ex: move_objeto(dama, 1,0,1,0) -> eh possivel mas nao aconselhavel
// TODO: impedir movimentos diagonais
// TODO: TESTAR ANTES DE MOVER
// OBS: essa funcao so permitira 0 ou 1
int move_objeto(struct obj_generico *obj, int cima, int baixo, int esquerda, int direita) {

	if (cima > 1 || cima < 0 || baixo > 1 || baixo < 0 || esquerda > 1 || esquerda < 0 || direita > 1 || direita < 0 ) {
		printf("TENTATIVA INVALIDA DE MOVER O OBJETO\n");
		return 0; //erro
		//exit(0);
	}

	if (	(cima && baixo) || (cima && direita) || (cima && esquerda) 
		||	(baixo && esquerda) || (baixo && direita)
		||	(esquerda && direita)	) {

		//TODO: colocar log pra saber em qual tentativa de mover deu erro
		printf("TENTATIVA INVALIDA DE MOVER O OBJETO\n");
		return 0; //erro
		// exit(0);
	}

	if(cima) {
		if(obj->Pes)
			if(limite_sup(obj->Pes->y, LIMITE_SUPERIOR) //verifica se estourou o limite superior
				obj->Pes->y += 1;
		if(obj->Pds)
			if(limite_sup(obj->Pds->y, LIMITE_SUPERIOR)
				obj->Pds->y += 1;
		if(obj->Pei)
			if(limite_sup(obj->Pei->y, LIMITE_SUPERIOR)
				obj->Pei->y += 1;
		if(obj->Pdi)
			if(limite_sup(obj->Pdi->y, LIMITE_SUPERIOR)
				obj->Pdi->y += 1;
		return 1; //ok
	}

	else if(baixo) {
		if(obj->Pes)
			obj->Pes->y -= 1;
		if(obj->Pds)
			obj->Pds->y -= 1;
		if(obj->Pei)
			obj->Pei->y -= 1;
		if(obj->Pdi)
			obj->Pdi->y -= 1;
		return 1; //ok
	}

	else if(esquerda) {
		if(obj->Pes)
			obj->Pes->x -= 1;
		if(obj->Pds)
			obj->Pds->x -= 1;
		if(obj->Pei)
			obj->Pei->x -= 1;
		if(obj->Pdi)
			obj->Pdi->x -= 1;
		return 1; //ok
	}

	else if(direita) {
		if(obj->Pes)
			obj->Pes->x += 1;
		if(obj->Pds)
			obj->Pds->x += 1;
		if(obj->Pei)
			obj->Pei->x += 1;
		if(obj->Pdi)
			obj->Pdi->x += 1;
		return 1; //ok
	}
	return 1; //ok
}

int main(int argc, char const *argv[]) {
	
	struct obj_generico *dama = (struct obj_generico *) malloc(sizeof(struct obj_generico));
	dama->nome = "dama";
	dama->Pes = cria_ponto(0,4);
	dama->Pei = cria_ponto(0,3);
	dama->Pds = cria_ponto(1,4);
	dama->Pdi = cria_ponto(1,3);

	struct obj_generico *tio = (struct obj_generico *) malloc(sizeof(struct obj_generico));
	tio->nome = "tio";
	tio->Pes = cria_ponto(0,1);
	tio->Pei = cria_ponto(0,0);
	tio->Pds = cria_ponto(1,1);
	tio->Pdi = cria_ponto(-1,-1);

	struct obj_generico *R = (struct obj_generico *) malloc(sizeof(struct obj_generico));
	R->nome = "R";
	R->Pes = cria_ponto(0,2);
	R->Pei = cria_ponto(-1,-1);
	R->Pds = cria_ponto(1,2);
	R->Pdi = cria_ponto(-1,-1);

	// struct obj_generico *vetor_obj[3] = ;
	// vetor_obj[0] = &dama;
	// vetor_obj[1] = &tio;
	// vetor_obj[2] = &R;
	
	//printf("D\n");

	//print_obj(dama);
	//print_obj(tio);
	//print_obj(R);


	// printf("D\n");
	// print_obj(vetor_obj[0]);
	// printf("T\n");
	// print_obj(vetor_obj[1]);
	// printf("R\n");
	// print_obj(vetor_obj[2]);

	//BUG: preciso mandar a quantidade de elementos presentes na matriz pra poder iterar sem invadir outros programas no loop
	// printf("\nPODE MOVER?%d\n", verifica_posicao_objetos((vetor_obj[0]), 3, 0, 2));
	//print_obj(dama);
	//move_objeto(dama, 1,0,0,0); //move pra cima
	//print_obj(dama);
	//////////////////////////////////////////
	//move_objeto(dama, 0,0,0,0);
	print_obj(dama);
	move_objeto(dama, 1,0,0,0);//pra cima
	print_obj(dama);
	//move_objeto(dama, 0,0,1,0);
	//print_obj(dama);
	//move_objeto(dama, 0,0,1,1);
	//print_obj(dama);

	//move_objeto(tio, 0,1,0,0);
	//move_objeto(tio, 0,1,0,1);
	//move_objeto(tio, 0,1,1,0);
	//move_objeto(tio, 0,1,1,1);

	//move_objeto(tio, 1,0,0,0);
	//move_objeto(tio, 1,0,0,1);
	//move_objeto(tio, 1,0,1,0);
	//move_objeto(tio, 1,0,1,1);

	//move_objeto(dama, 1,1,0,0);
	//move_objeto(dama, 1,1,0,1);
	//move_objeto(dama, 1,1,1,0);
	//move_objeto(dama, 1,1,1,1);
	//////////////////////////////////////////

	// move_objeto(&dama, 1,0,0,0); //move pra cima
	// printf("D\n");
	// print_obj(vetor_obj[0]);

	// move_objeto(&dama, 0,1,0,0); //move pra baixo
	// printf("D\n");
	// print_obj(vetor_obj[0]);

	// move_objeto(&dama, 0,0,1,0); //move pra esquerda
	// printf("D\n");
	// print_obj(vetor_obj[0]);

	// move_objeto(&dama, 0,0,0,1); //move pra direita
	// printf("D\n");
	// print_obj(vetor_obj[0]);

	jfree(dama);
	jfree(tio);
	jfree(R);
	return 0;
}
