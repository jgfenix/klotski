#include <stdio.h>
#include <stdlib.h>

#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"

#define MAPSIZE	7
#define FILHOS 6
#define ITERACOES 200

int global =0;	//sinaliza quando a solução foi encontrada

//TODO: deixar de sair bruscamente após imprimir a resposta para contar o tempo 

//OBS:
//considero minha matriz com i crescendo de cima pra baixo e j crescendo da direita pra esquerda
//onde a linha i:0 j:0 vai ser a quina superior esquerda

//Toda hora precisa gerar uma matriz zerada, entao melhor uma funcao pra isso logo
int** cria_matriz_zerada() {
	int i, j;
	int **input = (int**)malloc(MAPSIZE * sizeof(int*)); //Aloca um Vetor de Ponteiros

	for (i = 0; i < MAPSIZE; i++){ //Percorre as linhas do Vetor de Ponteiros
		input[i] = (int*) malloc(MAPSIZE * sizeof(int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
		for (j = 0; j < MAPSIZE; j++){ //Percorre o Vetor de Inteiros atual.
			input[i][j] = 0; //Inicializa com 0.
		}
	}
	return input; //Retorna o Ponteiro para a Matriz Alocada
};

//imprime uma matriz
void imprimeMatriz(int **c){
	int i,j=0;
	for(i=0;i<MAPSIZE;i++){
		for(j=0;j<MAPSIZE;j++){
			if(c[i][j] == 'D')
				printf(BLU "%c" RESET,c[i][j]);
			else
				printf("%c",c[i][j]);
		}
		printf("\n");
	}
}

//copia uma matriz pra outra
void copiaMatriz(int ***cola,int **copia){
	int i,j=0;
	for(i=0;i<MAPSIZE;i++){
		for(j=0;j<MAPSIZE;j++){
			*cola[i][j]=copia[i][j];
		}
	}
}

//compara duas matrizes e retorna 1 se são diferentes
int comparaMatiz(int **cola,int **copia){
	int i,j,ret=0;
	for(i=0;i<MAPSIZE;i++){
		for(j=0;j<MAPSIZE;j++){
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
	int **map;
	int repetido;	//se é repetida então =1
	int sol;		//se é solução entao =1
	struct No *pai;
	struct No *filho[FILHOS];
};
typedef struct No No;

void criaArvore(No *pRaiz){
	pRaiz = NULL;
}

void setRepetido(No *Raiz){
	Raiz->repetido=1;
}

//raiz principal
No *raiz=NULL;

int isSolucao(No **p){
	int i,j=0;
	for(i=0;i<(MAPSIZE-1);i++){
		for(j=0;j<(MAPSIZE-1);j++){	
			if (((*p)->map[i][j]=='D')&&((*p)->map[i][j+1]=='S')){
				return 1;
			}
			if (((*p)->map[i][j]=='D')&&((*p)->map[i+1][j]=='S')){
				return 1;
			}
		}
	}
	return 0;
}

void imprimeResposta(No **p){
	if(*p){
		printf(" === imprimindo solução === \n");
		imprimeMatriz((*p)->map);
		imprimeResposta(&(*p)->pai);
	}
}

//percorro toda a arvove comparando *comp com cada No
int checaRepetidos(No *pRaiz, int **comp){
	//0=repetido 1= nao repetido
	int ret = 1;
    if(pRaiz != NULL){
		//se o conteudo de pRaiz é diferente de comp e comp não é repetido eu prossigo
    	// printf("\nENTROOOU\n");
		if((comparaMatiz(pRaiz->map,comp)==1)){		// se são diferentes
			int i =0;
			for (i=0;i<FILHOS;i++){
				if((pRaiz->filho[i] != NULL)&&(ret==1)){
					ret=checaRepetidos(pRaiz->filho[i],comp);
				}
				else break;
			}
		}
		else{
			ret =0;
		}
    }
    return ret;
}


//** é usado pra modificar a referencia da struct
No* insereNo(No **Raiz, int** input, No *pai){		//inserção ok
	if (!*Raiz){
		*Raiz=(No *)malloc(sizeof (No));
		int i =0;
		for (i=0;i<FILHOS;i++){
			(*Raiz)->filho[i]=NULL;
		}		
		(*Raiz)->repetido=0;

		(*Raiz)->pai=pai;
		int j=0;
		//copia matriz input para (*Raiz)->map
		(*Raiz)->map = cria_matriz_zerada();
		for(i=0;i<MAPSIZE;i++){
			for(j=0;j<MAPSIZE;j++){
				(*Raiz)->map[i][j]=input[i][j];		//copia ok
			}
		}
		if(isSolucao(Raiz)) {
			// printf("\n\nachooooo\n");
			// imprimeMatriz((*Raiz)->map);
			imprimeResposta(Raiz);
			exit(1);
		}
		(*Raiz)->sol=isSolucao(Raiz);
		global=isSolucao(Raiz);

		//printf("sol:%d\n",(*Raiz)->sol );
		//if((*Raiz)->sol ==1)	printf("ENCONTREI!!!\n");
		//printf("GLOBAL:%d\n",global);
		//imprimeMatriz((*Raiz)->map);
		if((*Raiz)->sol==1) {
			printf(" \t\t==== ENCONRREI ====<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");;
			imprimeResposta(Raiz);
			exit(0);
		}
		return (*Raiz);
	}
	else {
		if (checaRepetidos(raiz, input) == 1) {
			int i=0;
			for (i=0;i<FILHOS;i++){			//procuro um filho vago pra inserir
				if((*Raiz)->filho[i]==NULL){
					//printf("inseriu filho %d\n",i);
					//imprimeMatriz(input);
					(*Raiz)->filho[i]=insereNo(&(*Raiz)->filho[i],input,*Raiz);
					break;		//se eu insiro em um filho vago, posso parar de procurar	
				}
				else{				
					//se eu tenho um irmão igula a mim eu nao sou criado
					if(comparaMatiz((*Raiz)->filho[i]->map,input)==0){
						break;
					}
				}
				//se eu sou meu pai, eu nao existo; é preciso verificar se meu pai existe
			}
		}
	}
	return 0;
}

int ** mapPeca(int moveTo, int x, int y, No **p){
	
	int i,j,flag=0;
	int peca = (*p)->map[x][y];		//esta e a peca q eu tenho q mover
	int** backup = cria_matriz_zerada();
	//espaço e vazio e nao me interessa
	if((peca != ' ')&&(peca != 0)&&(peca != 'S')&&(peca != '0')){		//condições de skip
		//printf("=== DEBUG mapPeca === \nMatriz Pai\n");
		//imprimeMatriz((*p)->map);
		//printf("Matriz filha === trying to move %c to %c\n",peca,moveTo);
		if(peca == 'I'){
			for(i=0;i<MAPSIZE;i++){
				for(j=0;j<MAPSIZE;j++){
					backup[i][j]=(*p)->map[i][j];	
				}
			}
			if(moveTo=='^'){
				backup[x-1][y]='I';
				backup[x][y]=' ';
			}
			if(moveTo=='<'){
				backup[x][y-1]='I';
				backup[x][y]=' ';				
			}
			if(moveTo=='|'){
				backup[x+1][y]='I';
				backup[x][y]=' ';				
			}
			if(moveTo=='>'){
				backup[x][y+1]='I';
				backup[x][y]=' ';					
			}
		}
		else{	
			//na hora de substituir a string eu preciso de 2 for, pq se num for progressivo eu substituir i+1 por i entao eu vou estar encolhendo a peça
			//for progressivo para mover as pessas no sentido retrogrado	
			
			//printf("PARTE 1\n");//ok
			for(i=0;i<MAPSIZE;i++){
				for(j=0;j<MAPSIZE&&((moveTo=='^')||(moveTo=='<'));j++){
					backup[i][j]=(*p)->map[i][j];	//faço backup usado pra nao alterar o valor da matriz do No de entrada
					if((*p)->map[i][j]==peca){		//procuro minha peça por todo o mapeamento
					//printf("peca encontrada em :i=%d j= %d\n",i,j );
						if((i>0)&&(moveTo=='^')){//se eu poso mover pra cima	
							if(((*p)->map[i-1][j]==' ')||(((*p)->map[i-1][j]==peca))) {
								backup[i-1][j]=(*p)->map[i][j];
								backup[i][j]=' ';
							}
							else{
								flag =1;
							}
						}
						if((j>0)&(moveTo=='<')){//se eu posso mover pra esquerda
							if(((*p)->map[i][j-1]==' ')||((*p)->map[i][j-1]==peca)) {
								backup[i][j-1]=(*p)->map[i][j];
								backup[i][j]=' ';
							}
							else{
								flag =1;
							}
						}
					}
					
					if (flag ==1){
						break;
					}		
				}

				if (flag ==1){
					break;
				}		
			}
			//printf("PARTE 2\n");//ok
			//for regressivo para mover as pessas no sentido nao retrogrado	
			//limite no regressivo tem que ser MAPSIZE-1
			for(i=MAPSIZE-1;i>=0&&((moveTo=='|')||(moveTo=='>'));i--){		//verifico se nao vou sobreescrever o backup
				for(j=MAPSIZE-1;j>=0;j--){
					backup[i][j]=(*p)->map[i][j];
					//nao preciso de outro backup pq o primeiro ja guardou ovalor da entrada
					if((*p)->map[i][j]==peca){		//procuro minha peça por todo o mapeamento
					//printf("peca encontrada em :i=%d j= %d\n",i,j );
						if((i<MAPSIZE)&&(moveTo=='|')){//se eu posso mover pra baixo
							if(((*p)->map[i+1][j]==' ')||((*p)->map[i+1][j]==peca)) {
								backup[i+1][j]=(*p)->map[i][j];
								backup[i][j]=' ';
							}
							else{
								flag =1;
							}
						}
						if((j<MAPSIZE)&&(moveTo=='>')){//se eu posso mover pra direita
							if(((*p)->map[i][j+1]==' ')||((*p)->map[i][j+1]==peca)) {
								backup[i][j+1]=(*p)->map[i][j];
								backup[i][j]=' ';
							}
							else{
								flag =1;
							}
						}
					}
					if (flag ==1) break;		
				}
				if (flag ==1) break;		
			}
		}
		if (flag ==1) backup = cria_matriz_zerada();
		//if (flag ==0) printf(" Moved\n");
		//imprimeMatriz(backup);
	}
	return backup;
}
	
//verifico os arredores do espaço e vejo se posso move-los
void arredores (int i, int j, No **p){	
	int **matriz0=cria_matriz_zerada();
	int **matriz1=cria_matriz_zerada();
	int **matriz2=cria_matriz_zerada();
	int **matriz3=cria_matriz_zerada();
	int max = MAPSIZE-1;

	if(i>0){
		matriz0=mapPeca('|',i-1,j, p);	
	}
	if(j>0){
		matriz1=mapPeca('>',i,j-1, p);	
	}
	if(i<max){
		matriz2=mapPeca('^',i+1,j, p);	
	}
	if(j<max){
		matriz3=mapPeca('<',i,j+1, p);
	}	

	if(comparaMatiz(matriz0,cria_matriz_zerada())==1)	insereNo(p,matriz0,0);
	if(comparaMatiz(matriz1,cria_matriz_zerada())==1)	insereNo(p,matriz1,0);
	if(comparaMatiz(matriz2,cria_matriz_zerada())==1)	insereNo(p,matriz2,0);
	if(comparaMatiz(matriz3,cria_matriz_zerada())==1)	insereNo(p,matriz3,0);
}

void buscaEspaco(No **pRaiz){
	int i,j=0;
	if((*pRaiz)->repetido==0){
		(*pRaiz)->repetido=1;
		for(i=0;i<MAPSIZE;i++){
			for(j=0;j<MAPSIZE;j++){
				// printf("%c",pRaiz->map[i][j]);
				if((*pRaiz)->map[i][j]== ' '){
					//printf(" === espaço em i:%d j:%d ===\n",i,j);
					arredores(i,j,pRaiz);
				}
			}
			//printf("\n");
		}		
	}
	else{
		for (i=0;i<FILHOS;i++){			//procuro um filho vago pra inserir
			if((*pRaiz)->filho[i]!=NULL){
				// printf(" === entrou no filho %d === \n",i);
				buscaEspaco(&(*pRaiz)->filho[i]);
			}
		}
	}
}

int** pega_matriz_entrada() {
	//printf("DIGITE A MATRIZ\n");
	int i=0,j=0;
	int c;

	int **input = cria_matriz_zerada();
	if(!input) {
		printf("\nfuncao 'pega_matriz_entrada' \nDEU RUIM AO ALOCAR A MATRIZ\n");
		exit(1);
	}

	while ((c=getchar())!=EOF){
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
	// No *raiz=NULL;
	
	input = pega_matriz_entrada();

	// printf("Matriz inicial:\n");
	//imprimeMatriz(input);//ok
	insereNo(&raiz,input,NULL);//ok
	int i=0;
	for (i=0;i<ITERACOES;i++){
		printf("##############################\nparei na %d	\n##############################\n", i );
		buscaEspaco(&raiz);//ok
	}
	//movimento(raiz);

	return 1;
}
