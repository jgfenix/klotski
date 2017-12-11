#include <stdio.h>
#include <stdlib.h>

#define MAPSIZE	7
#define FILHOS 6
#define LINHAS 5
#define COLUNAS 7 //se considerar a saida como o 7

//imprime uma matriz
void imprimeMatriz(int c[LINHAS][COLUNAS]){
	int i,j=0;
	for(i=0;i<LINHAS;i++){
		for(j=0;j<COLUNAS;j++){
			//printf("i:%d j:%d %d:%c\n",i,j,c[i][j],c[i][j]);
			printf("%c",c[i][j]);
		}
		printf("\n");
	}
}

//copia uma matriz pra outra
void copiaMatriz(int cola[LINHAS][COLUNAS],int copia[LINHAS][COLUNAS]){
	int i,j=0;
	for(i=0;i<LINHAS;i++){
		for(j=0;j<COLUNAS;j++){
			cola[i][j]=copia[i][j];
		}
	}
}

//compara duas matrizes e retorna 1 se são diferentes
int comparaMatiz(int cola[LINHAS][COLUNAS],int copia[LINHAS][COLUNAS]){
	int i,j,ret=0;
	for(i=0;i<LINHAS;i++){
		for(j=0;j<COLUNAS;j++){
			if(cola[i][j]!=copia[i][j]){
				ret++;
				break;
			}
		}
		if(ret>0){
			break;
		}
	}
	return ret;
}

struct No {
	int map[LINHAS][COLUNAS];
	int repetido;	//se é repetida então =1
	int sol;		//se é solução entao =1
	struct No *pai;
	struct No *filho[6];
};
typedef struct No No;

void criaArvore(No *pRaiz){
	pRaiz = NULL;
}

void setRepetido(No *Raiz){
	Raiz->repetido=1;
}

//insere em até 8 filhos/possibilidades de movimento para cada estado atual
void insereNo(No **Raiz, int input[LINHAS][COLUNAS]){
	if (*Raiz){
		*Raiz=(No *)malloc(sizeof (No));
		int i =0;
		for (i=0;i<FILHOS;i++){
			(*Raiz)->filho[i]=NULL;
		}		
		(*Raiz)->repetido=0;
		(*Raiz)->sol=0;
		(*Raiz)->pai=(*Raiz);
		// copiaMatriz((*Raiz)->map,input);
		int j=0;
		for(i=0;i<LINHAS;i++){
			for(j=0;j<COLUNAS;j++){
				// cola[i][j]=copia[i][j];
				(*Raiz)->map[i][j]=input[i][j];
				//A copia acontece
				// printf("%c",(*Raiz)->map[i][j]);
			}
			// printf("\n");
		}
		// imprimeMatriz((*Raiz)->map);
	}
	else {
		int i =0;
		for (i=0;i<FILHOS;i++){
			if((*Raiz)->filho[i]==NULL){
				insereNo(&(*Raiz)->filho[i],input);		
			}
		}
	}
}

//percorro toda a arvove comparando *comp com cada No
void checaRepetidos(No *pRaiz, No *comp){
    if((pRaiz != NULL)&&(comp->repetido!=1)){
		//se o conteudo de pRaiz é diferente de comp e comp não é repetido eu prossigo		
		if(comparaMatiz(pRaiz->map,comp->map)==1){	
			int i =0;
			for (i=0;i<FILHOS;i++){
				if(pRaiz->filho[i]==NULL){
					checaRepetidos(pRaiz->filho[i],comp);		
				}
			}
		}
		else{
			setRepetido(comp);//repetido=1
		}
    }
}

void mapPeca(int moveTo, int x, int y, No **p){
	// printf("mapPeca\n");
	int i,j,flag=0;
	int peca = (*p)->map[x][y];
	int backup[LINHAS][COLUNAS]={0};
	
	for(i=0;i<LINHAS;i++){
		for(j=0;j<COLUNAS;j++){
			backup[i][j]=(*p)->map[i][j];
			if((i>0)&&(moveTo=='<')){//moveLeft		
				if(((*p)->map[i][j]==peca)&&((*p)->map[i-1][j]==' ')){
					(*p)->map[i-1][j]=(*p)->map[i][j];
				}
				else{
					flag =1;
				}
			}
			if((j>0)&(moveTo=='^')){//moveUp
				if(((*p)->map[i][j]==peca)&&((*p)->map[i][j-1]==' ')){
					(*p)->map[i][j-1]=(*p)->map[i][j];
				}
				else{
					flag =1;
				}
			}
			if((i<LINHAS)&(moveTo=='>')){//moveRigth
				if(((*p)->map[i][j]==peca)&&((*p)->map[i+1][j]==' ')){
					(*p)->map[i+1][j]=(*p)->map[i][j];
				}
				else{
					flag =1;
				}
			}
			if((j<COLUNAS)&(moveTo=='|')){//moveBot
				if(((*p)->map[i][j]==peca)&&((*p)->map[i][j-1]==' ')){
					(*p)->map[i][j-1]=(*p)->map[i][j];
				}
				else{
					flag =1;
				}
			}		
		}
	}
	
	if(flag ==1){
		printf(" falha\n");
		for(i=0;i<MAPSIZE;i++){
			for(j=0;j<MAPSIZE;j++){
				(*p)->map[i][j]=backup[i][j];
			}
		}
	}
	else{
		printf(" sucesso\n");
		insereNo(&(*p),(*p)->map);
	}
}
	
void arredores (int i, int j, No **p){
	int movimento;
	if(i>0){
		movimento=i-1;
		if(movimento<MAPSIZE){
			printf("moveBot %c",(*p)->map[i-1][j]);
			mapPeca('|',movimento,j, &(*p));
		}
	}
	if(j>0){
		movimento=j-1;
		if(movimento<MAPSIZE){
			printf("moveRigth %c",(*p)->map[i][j-1]);
			mapPeca('>',i,movimento, &(*p));
		}
	}
	if(i<MAPSIZE){
		movimento=i+1;
		if(movimento<MAPSIZE){
			printf("moveUp %c",(*p)->map[i+1][j]);
			mapPeca('^',movimento,j, &(*p));
		}
	}
	if(j<MAPSIZE){
		movimento=j+1;
		if(movimento<MAPSIZE){
			printf("moveLeft %c",(*p)->map[i][j+1]);
			mapPeca('<',i,movimento, &(*p));
		}
	}
	
}

void buscaEspaco(No *pRaiz){
	printf("No \n");	
	int i,j=0;
	for(i=0;i<MAPSIZE;i++){
		for(j=0;j<MAPSIZE;j++){
			// printf("%c",pRaiz->map[i][j]);
			if(pRaiz->map[i][j]== ' '){
				printf("espaço em i:%d j:%d\n",i,j);
				arredores(i,j,&pRaiz);
			}
		}
		printf("\n");
	}
}

//Toda hora precisa gerar uma matriz zerada, entao melhor uma funcao pra isso logo
int** cria_matriz_zerada() {
	int i, j;
	int **input = (int**)malloc(LINHAS * sizeof(int*)); //Aloca um Vetor de Ponteiros

	for (i = 0; i < LINHAS; i++){ //Percorre as linhas do Vetor de Ponteiros
		input[i] = (int*) malloc(COLUNAS * sizeof(int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
		for (j = 0; j < COLUNAS; j++){ //Percorre o Vetor de Inteiros atual.
			input[i][j] = ' '; //Inicializa com ' '.
		}
	}
	return input; //Retorna o Ponteiro para a Matriz Alocada
};

int** pega_matriz_entrada() {
	printf("DIGITE A MATRIZ\n");
	int i=0,j=0;
	int c;

	int **input = cria_matriz_zerada();
	if(!input) {
		printf("\nfuncao 'pega_matriz_entrada' \nDEU RUIM AO ALOCAR A MATRIZ\n");
		exit(1);
	}

	while (/*(c=getchar())!=EOF ||*/ i < LINHAS){
		c=getchar();
		if(c =='\n'){
			i++;
			j=0;
		}
		else{
			input[i][j++]=c;					
		}
	}
	return input;
}

int main (int argc, char **argv){

	int** input;
	int i,j,c=0;
	No *raiz;
	
	input = pega_matriz_entrada();

	// imprimeMatriz(input);
	insereNo(&raiz,input);
	insereNo(&raiz,input);
	insereNo(&raiz,input);
	// imprimeMatriz(raiz->map);
	buscaEspaco(raiz);
	//movimento(raiz);

	return 1;
}
