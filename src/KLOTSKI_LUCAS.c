#include <stdio.h>
#include <stdlib.h>
//#include "percorre_arvore.c"

struct arvore {
    struct arvore *pai;
    int matriz_atual[5][6];
    int *matriz_atual = matriz_atual;
    struct arvore *filho[8];
};

void gotoleft(int vet[5][6],char c){
int i,j,aux,vet1[5][6],k;klotski
k=1;
for (i=0;i<5;++i){
	for (j=0;j<6;++j)
		vet1[i][j]=vet[i][j];
	}
for (i=0;i<5;++i){

		for (j=0;j<6;++j){
		if (j==0)
		if (vet[i][j]==c)
			k=0;
		 if (vet[i][j]==c){
			 aux=vet[i][j-1];
			 vet[i][j-1]=vet[i][j];
			 vet[i][j]=aux;
			 if (aux!=0)
				k=0;
		 }}

}
if (k==0){
	for (i=0;i<5;++i){
	for (j=0;j<6;++j)
		vet[i][j]=vet1[i][j];
	}}
}

void gotoright(int vet[5][6],char c){
int i,j,aux,vet1[5][6],k;
k=1;
for (i=0;i<5;++i){
	for (j=0;j<6;++j)
		vet1[i][j]=vet[i][j];
	}
for (i=0;i<5;++i){

		for (j=5;j>=0;--j){
		if (j==5)
		if (vet[i][j]==c)
			k=0;
		 if (vet[i][j]==c){
			 aux=vet[i][j+1];
			 vet[i][j+1]=vet[i][j];
			 vet[i][j]=aux;
			 if (aux!=0)
				k=0;
		 }}

}
if (k==0){
	for (i=0;i<5;++i){
	for (j=0;j<6;++j)
		vet[i][j]=vet1[i][j];
	}}
}

void goup(int vet[5][6],char c){
int i,j,aux,vet1[5][6],k;
k=1;
for (i=0;i<5;++i){
	for (j=0;j<6;++j)
		vet1[i][j]=vet[i][j];
	}
for (j=0;j<6;++j){

		for (i=0;i<5;++i){
		if (i==0)
		if (vet[i][j]==c)
			k=0;
		 if (vet[i][j]==c){
			 aux=vet[i-1][j];
			 vet[i-1][j]=vet[i][j];
			 vet[i][j]=aux;
			 if (aux!=0)
				k=0;
		 }}

}
if (k==0){
	for (i=0;i<5;++i){
	for (j=0;j<6;++j)
		vet[i][j]=vet1[i][j];
	}}
}

void godown(int vet[5][6],char c){
int i,j,aux,vet1[5][6],k;
k=1;
for (i=0;i<5;++i){
	for (j=0;j<6;++j)
		vet1[i][j]=vet[i][j];
	}
for (j=0;j<6;++j){

		for (i=5;i>=0;--i){
		if (i==4)
		if (vet[i][j]==c)
			k=0;
		 if (vet[i][j]==c){
			 aux=vet[i+1][j];
			 vet[i+1][j]=vet[i][j];
			 vet[i][j]=aux;
			 if (aux!=0)
				k=0;
		 }}

}
if (k==0){
	for (i=0;i<5;++i){
	for (j=0;j<6;++j)
		vet[i][j]=vet1[i][j];
	}}
}

void gera_matriz(int vet[5][6]){

// vet=[['D','D','0','P','P','G'],
//	    ['D','D','0','P','H','M'],
//	    ['R','R','I','J','M','M'],
//	    ['T','T','O','K','C','N'],
//	    ['T','O','O','L','C','N']];

vet[0][0]=vet[0][1]=vet[1][0]=vet[1][1]='D';
vet[0][2]=vet[1][2]=0;
vet[0][3]=vet[0][4]=vet[1][3]='P';
vet[0][5]='G';
vet[1][4]='H';
vet[2][2]='I';
vet[2][3]='J';
vet[3][3]='K';
vet[4][3]='L';
vet[1][5]=vet[2][4]=vet[2][5]='M';
vet[2][0]=vet[2][1]='R';
vet[3][0]=vet[3][1]=vet[4][0]='T';
vet[3][2]=vet[4][1]=vet[4][2]='O';
vet[3][4]=vet[4][4]='C';
vet[3][5]=vet[4][5]='N';
}
void imprime_mat(int vet[5][6]){
	int i,j;
for (i=0;i<5;++i){
	for (j=0;j<6;++j){
		if(vet[i][j] == 0){
  		printf(" ");
	  }
		printf("%c ",vet[i][j]);
	}
	printf ("\n");
	}
printf("\n");
}


void copiaMatriz(int cola[5][6],int copia[5][6]){
	int i,j=0;
	for(i=0;i<5;i++){
		for(j=0;j<6;j++){
			cola[i][j]=copia[i][j];
		}
	}
}

void eh_movivel(int arg_matriz[5][6]){
	int i,j=0;
	for(i=0;i<5;i++){
		for(j=0;j<6;j++){
			if(arg_matriz[i][j] == 0){
			}
		}
	}
}

void espaco_adjacente_horizontal(){

}

void espaco_adjacente_vertical(int arg_matriz[5][6]){
	int nova_matriz[5][6];//vai ser modificada e gravada na filha
	//copiaMatriz(nova_matriz[5][6],arg_matriz[5][6]);

	/*vou encontrar um espaço e chamar a função eh_movivel,
	que vai verificar se as peças adjacentes ao espaço pode ser movida*/

}

void espaco_sozinho(){

}



void encontra_possibilidades(struct arvore *arg){//é chamada dentro do loop principal,
  //-------------------------------------------------------------------------------------
	for(int i = 0; i < 8; ++i){/*Como são 8 filhas, as que não forem preenchidas
		devem ser null*/
		(arg->filho[i])->matriz_atual = NULL;
	}
	//-------------------------------------------------------------------------------------
	/* Aqui eu começo a buscar um espaço vazio na matriz_atual. Se eu encontrar,
	eu tenho que verificar se eu tenho outro adjacente acima, abaixo ou de
	algum lado. Na primeira solução q pensei é que em cada caso desse,
	preciso de uma função diferente pra mover as peças. */
	int i,j=0;
	for(i=0;i<5;i++){
		for(j=0;j<6;j++){
			if(arg->matriz_atual[i][j] == 0){
				if((j + 1 <= 5)&(arg->matriz_atual[i][j+1] == 0)) || ((j - 1 >= 0)&(arg->matriz_atual[i][j-1] == 0)){
					/*Esse teste verifica se tem outro espaço acima ou abaixo do
					espaço q foi encontrado*/
					espaco_adjacente_vertical()/*função que cria novas matrizes dentro
					da filha, supondo que o espaço é adjacente e vertical*/
				}
				//Preciso de outros testas para os outros tipos de espaço
			}
		}
	}
}

void loop_magico(struct arvore *arg){/* recebe a raiz da arvore. vai rodar
	um algoritmo pra descobrir e fazer as novas matrizes possiveis.
	Vai pegar essa nova matriz e coloca-la numa nova struct
	filha*/

	encontra_possibilidades(struct arvore *arg);/*vai pegar o membro
	matriz_atual da struct de entrada. A partir dele, vai verificar quais sao
	os movimentos possiveis e gravá-los nas filhas.*/

	//------------------------------------------------------------------------------
	if(cheguei(int matriz_atual[][])){/* Função que verifica se a peça alvo
		está adjacente à saída*/
		encontra_solucao()/*Percorre o arvore->pai até chegar na raiz. Tal
		caminho é a soluçao final*/
		return;
	}

	//---------------------------------------------------------------------------------
	for(int i = 0; i < 8; ++i){/*Parte responsável pela recursao. Quando
		chegar aqui, as structs filhas já tem seu estado atual(matriz_atual),
		que foram preenchidos no código acima.*/

		(arg->filho[i])->pai = &arg;//linkei as filhas no pai

		if ((arg->filho[i])->matriz_atual != NULL){/*Se a matriz_atual da
			struct filha nao for null, é pq ela é uma filha válida.*/

			loop_magico(struct arvore arg->filho[i]);/*Fiz todo o processo
			novamente para todas as filhas que contém uma nova matriz_atual
			preenchida*/
		}
	}
	//----------------------------------------------------------------------------------
}

int main(int argc, char *argv[]){
	int matriz[5][6];
	gera_matriz(matriz);
	struct arvore raiz;//tatatatatatatatatataravo
	raiz.pai = NULL;
	raiz.matriz_atual = matriz;


imprime_mat(raiz.matriz_atual);
imprime_mat(matriz);
//gera_matriz(matriz);
imprime_mat(matriz);
gotoright(matriz, 'D');
imprime_mat(matriz);
gotoright(matriz, 'D');
imprime_mat(matriz);
//gera_estado(vet);
return 0;
}
