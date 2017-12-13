#include <stdio.h>
#include <stdlib.h>
#define LINHAS 5
#define COLUNAS 6
#define FILHOS 8
#define LIMITE 28 //limite de recursoes
#define ALVO 'I'  //peça a ser retirada
int eureka = 0;

struct solucao {

    struct solucao *proximo;
    struct arvore *noapontado;

};

struct solucao *novasolucao(){

	return NULL;

}

int pilhavazia(struct solucao *p) {

	if (p==NULL) return 1;
	else return 0;

}


struct solucao *pop(struct solucao *p) {

	if (pilhavazia(p))
		printf("Pilha vazia.");
	else {

		struct solucao *aux = p -> proximo;
		free(p);
		p=aux;

	}

	return p;

}

struct solucao* push(struct arvore *no, struct solucao *p ) {

	struct solucao *nova = (struct solucao*)malloc(sizeof(struct solucao));

	nova -> proximo = p;

	p = nova;

	return p;

}

struct arvore {
    struct arvore *pai;
    int matriz_atual[5][6];
    //int **pmatriz_atual = matriz_atual;
    struct arvore *filho[8];
};

typedef struct node{
    struct node *pai;
    char matriz_atual[LINHAS][COLUNAS];
    struct node *filho[FILHOS];
}node;

void copiaMatriz(char cola[5][6],char copia[5][6]){
	int i,j=0;
	for(i=0;i<5;i++){
		for(j=0;j<6;j++){
			cola[i][j]=copia[i][j];
		}
	}
}

//compara duas matrizes e retorna 1 se são diferentes
int compara_matriz(char cola[][6], char copia[][6]){
	int i,j,ret=0;
	for(i=0;i<5;i++){
		for(j=0;j<6;j++){
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


int eh_igual(char arg1[LINHAS][COLUNAS], char arg2[LINHAS][COLUNAS]){
//retorna 1 se as matrizes forem iguais
	for(int i = 0; i < LINHAS; i++){
		for(int j = COLUNAS-1; j > -1; --j){
			if(arg1[i][j] != arg2[i][j]){
				return 0;
			}
		}
	}
	return 1;
}

void imprime_mat(char vet[5][6]){
	int i,j;
  for (i=0;i<5;++i){
	  for (j=0;j<6;++j){
		  printf("%c ",vet[i][j]);
  	}
	  printf ("\n");
	}
  printf("\n");
}



int cima(char c, char arg[5][6]){
//Tenta mover C na matriz para cima. Retorna 1 se conseguir
  int i,j;
  for (j = 0; j < 6; ++j){
  	for (i = 1; i < 5; ++i){
      if (arg[i][j] == c){
        if (arg[i-1][j] == ' '){
          for(int linha = 1; linha < 5; ++linha){
            if ((j < 5)&(arg[linha][j+1] == c)){
              if(arg[linha-1][j+1] == ' '){
                //move pra cima----------------------------------------------------
                arg[linha-1][j+1] = c;
                if (arg[linha+1][j+1] == c){
                  arg[linha+1][j+1] = ' ';
                }
                else{
                  arg[linha][j+1] = ' ';
                }
                arg[i-1][j] = c;
                if (arg[i+1][j] == c){
                  arg[i+1][j] = ' ';
                }
                else{
                  arg[i][j] = ' ';
                }
                //---------------------------------------------------------------------
                return 1;
              }
              return 0;
            }
          }
          //move pra cima----------------------------------------------------
          arg[i-1][j] = c;
          if (arg[i+1][j] == c){
            arg[i+1][j] = ' ';
          }
          else{
            arg[i][j] = ' ';
          }
          //---------------------------------------------------------------------
          return 1;
        }
        return 0;
      }
    }
  }
  return 0;
}

int baixo(char c, char arg[5][6]){
//Tenta mover C na matriz para baixo. Retorna 1 se conseguir
  int i,j;
  for (j = 0; j < 6; ++j){
  	for (i = 3; i > -1; --i){
      if (arg[i][j] == c){
        if (arg[i+1][j] == ' '){
          for(int linha = 3; linha > -1; --linha){
            if ((j < 5)&(arg[linha][j+1] == c)){
              if(arg[linha+1][j+1] == ' '){
                //move pra baixo----------------------------------------------------
                arg[linha+1][j+1] = c;
                if (arg[linha-1][j+1] == c){
                  arg[linha-1][j+1] = ' ';
                }
                else{
                  arg[linha][j+1] = ' ';
                }
                arg[i+1][j] = c;
                if (arg[i-1][j] == c){
                  arg[i-1][j] = ' ';
                }
                else{
                  arg[i][j] = ' ';
                }
                //---------------------------------------------------------------------
                return 1;
              }
              return 0;
            }
          }
          //move pra baixo----------------------------------------------------
          arg[i+1][j] = c;
          if (arg[i-1][j] == c){
            arg[i-1][j] = ' ';
          }
          else{
            arg[i][j] = ' ';
          }
          //---------------------------------------------------------------------
          return 1;
        }
        return 0;
      }
    }
  }
  return 0;
}


int direita(char c, char arg[5][6]){
//Tenta mover C na matriz para direita. Retorna 1 se conseguir
  int i,j;
  for (i = 0; i < 5; ++i){
  	for (j = 4; j > -1; --j){
      if (arg[i][j] == c){
        if (arg[i][j+1] == ' '){
          for(int coluna = 4; coluna > -1; --coluna){
            if ((i < 4)&(arg[i+1][coluna] == c)){
              if(arg[i+1][coluna+1] == ' '){
                //move pra direita----------------------------------------------------
                arg[i+1][coluna+1] = c;
                if (arg[i+1][coluna-1] == c){
                  arg[i+1][coluna-1] = ' ';
                }
                else{
                  arg[i+1][coluna] = ' ';
                }
                arg[i][j+1] = c;
                if (arg[i][j-1] == c){
                  arg[i][j-1] = ' ';
                }
                else{
                  arg[i][j] = ' ';
                }
                //--------------------------------------------------------------------
                return 1;
              }
              return 0;
            }
          }
          //move pra direita----------------------------------------------------
          arg[i][j+1] = c;
          if (arg[i][j-1] == c){
            arg[i][j-1] = ' ';
          }
          else{
            arg[i][j] = ' ';
          }
          //---------------------------------------------------------------------
          return 1;
        }
        return 0;
      }
    }
  }
  return 0;
}

int esquerda(char c, char arg[5][6]){
//Tenta mover C na matriz para esquerda. Retorna 1 se conseguir
  int i,j;
  for (i = 0; i < 5; ++i){
  	for (j = 1; j < 6; ++j){
      if (arg[i][j] == c){
        if (arg[i][j-1] == ' '){
          for(int coluna = 1; coluna < 6; ++coluna){
            if ((i < 4)&(arg[i+1][coluna] == c)){
              if(arg[i+1][coluna-1] == ' '){
                //move pra esquerda----------------------------------------------------
                arg[i+1][coluna-1] = c;
                if (arg[i+1][coluna+1] == c){
                  arg[i+1][coluna+1] = ' ';
                }
                else{
                  arg[i+1][coluna] = ' ';
                }
                arg[i][j-1] = c;
                if (arg[i][j+1] == c){
                  arg[i][j+1] = ' ';
                }
                else{
                  arg[i][j] = ' ';
                }
                //---------------------------------------------------------------------
                return 1;
              }
              return 0;
            }
          }
          //move pra esquerda----------------------------------------------------
          arg[i][j-1] = c;
          if (arg[i][j+1] == c){
            arg[i][j+1] = ' ';
          }
          else{
            arg[i][j] = ' ';
          }
          //---------------------------------------------------------------------
          return 1;
        }
        return 0;
      }
    }
  }
  return 0;
}


void gera_matriz(char vet[5][6]){

  // vet=[['D','D','0','P','P','G'],
  //	    ['D','D','0','P','H','M'],
  //	    ['R','R','I','J','M','M'],
  //	    ['T','T','O','K','C','N'],
  //	    ['T','O','O','L','C','N']];

  vet[0][0]=vet[0][1]=vet[1][0]=vet[1][1]='D';
  vet[0][2]=vet[1][2]=' ';
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

void imprime_ate_a_raiz(node *arg){
  node *raiz = arg;
  int i = 0;
  while (raiz->pai){
    i++;
    imprime_mat(raiz->matriz_atual);
    raiz = raiz->pai;
  }
  printf("Total de passos: %d\n", i);
}

int preordenada(node *pai, char matriz_gerada[][6]) {
    if (!pai){
      return 0; /* se encontrar um nó terminal retorna */
    }
    if (eh_igual(pai->matriz_atual, matriz_gerada)){
      return 1;
    }

    for(int i = 0; i < 8; ++i){
      if(preordenada(pai->filho[i], matriz_gerada)){
        return 1;
      }
    }
    return 0;
}

int jah_tem(node *arg, char matriz_gerada[5][6]){
  node *raiz = arg;
  while (raiz->pai){
    raiz = (raiz->pai);
  }
  return preordenada(raiz,matriz_gerada);
}


int cheguei(char arg_matriz[LINHAS][COLUNAS], char arg_char){

  for(int i = 0; i < 3; i++){
    if(arg_matriz[i][COLUNAS-1] == arg_char){
        return 0;
    }
  }
  if((arg_matriz[3][COLUNAS-1] == arg_char)||(arg_matriz[4][COLUNAS-1] == arg_char)){
    if(arg_matriz[3][COLUNAS-1] == arg_char){
      if(arg_matriz[4][COLUNAS-1] == arg_char){
        return 1;
      }
      if(arg_matriz[3][COLUNAS-2] == arg_char){
        if(arg_matriz[4][COLUNAS-2] == arg_char){
          if((arg_matriz[4][COLUNAS-1] != arg_char)||(arg_matriz[4][COLUNAS-1] != ' ')){
            return 0;
          }
          return 1;
        }
        return 1;
      }
      return 1;
    }
    if(arg_matriz[4][COLUNAS-2] == arg_char){
      if(arg_matriz[3][COLUNAS-2] == arg_char){
        if(arg_matriz[3][COLUNAS-1] == ' '){
          return 1;
        }
        return 0;
      }
      return 1;
    }
    return 1;
  }else{
    return 0;
  }
}

int D_chegou(char arg_matriz[LINHAS][COLUNAS]){
//versao otimizada q só funciona pro D
  if(arg_matriz[2][COLUNAS-1] == 'D'){
    if(arg_matriz[3][COLUNAS-1] == 'D'){
      return 1;
    }
  }
  return 0;
}



void encontra_possibilidades(node *arg){
//é chamada dentro do loop principal,
	//-------------------------------------------------------------------------------------
  char nova_matriz[5][6];//vai ser modificada e gravada na filha
	copiaMatriz(nova_matriz, arg->matriz_atual);
  int filho = 0;
  //printf("Iniciei o brute force de possibilidades de movimentos\n");
  for (char k = 'C'; k < 'U'; ++k){
    //Tenta mover todas as peças para todas as direções
    if(cima(k, nova_matriz)){
      //printf("Achei uma nova matriz possivel. Pra cima\n");
      if(jah_tem(arg,nova_matriz)){
        //printf("Ja existe na arvore. Dispensei.\n");
      }else{
        arg->filho[filho] = (node*)malloc(sizeof(node));
        copiaMatriz(arg->filho[filho]->matriz_atual, nova_matriz);
      //  printf("Gravei na filha\n");
        //imprime_mat(nova_matriz);
        ++filho;
      }
      copiaMatriz(nova_matriz, arg->matriz_atual);
    }

    if(baixo(k, nova_matriz)){
      //printf("Achei uma nova matriz possivel. Pra baixo.\n");
      if(jah_tem(arg,nova_matriz)){
        //printf("Ja existe na arvore. Dispensei.\n");
      }else{
        arg->filho[filho] = (node*)malloc(sizeof(node));
        copiaMatriz(arg->filho[filho]->matriz_atual, nova_matriz);
        //printf("Gravei na filha\n");
        //imprime_mat(nova_matriz);
        ++filho;
      }
      copiaMatriz(nova_matriz, arg->matriz_atual);
    }

    if(direita(k, nova_matriz)){
      //printf("Achei uma nova matriz possivel. Pra direita\n");
      if(jah_tem(arg,nova_matriz)){
        //printf("Ja existe na arvore. Dispensei.\n");
      }else{
        arg->filho[filho] = (node*)malloc(sizeof(node));
        copiaMatriz(arg->filho[filho]->matriz_atual, nova_matriz);
        //printf("Gravei na filha\n");
        //imprime_mat(nova_matriz);
        ++filho;
      }
      copiaMatriz(nova_matriz, arg->matriz_atual);
    }

    if(esquerda(k, nova_matriz)){
      //printf("Achei uma nova matriz possivel. Pra esquerda.\n");
      if(jah_tem(arg,nova_matriz)){
        //printf("Ja existe na arvore. Dispensei.\n");
      }else{
        arg->filho[filho] = (node*)malloc(sizeof(node));
        copiaMatriz(arg->filho[filho]->matriz_atual, nova_matriz);
        //printf("Gravei na filha\n");
        //imprime_mat(nova_matriz);
        ++filho;
      }
      copiaMatriz(nova_matriz, arg->matriz_atual);
    }
  }
  //printf("Terminei o brute force de possibilidades de movimentos\n");
}


void loop_magico(node *arg, int arg_limite){
  /* recebe a raiz da arvore. vai rodar um algoritmo
  pra descobrir e fazer as novas matrizes possiveis.
	Vai pegar essa nova matriz e coloca-la numa nova
  struct filha*/

  //printf("Iniciei uma iteração do loop-------------------------------------------\n\n");
  if (eureka){//Se alguma outra recursao mudou essa variavel global, essa tbm para
    return;
  }

  //Parte do controle de numero de loops---------------------------------------------
  int passa_limite;
  if (arg_limite > LIMITE){
    return;
  }
  ++arg_limite;
  //printf("Passo: %d\n", arg_limite);//Imprime o nivel da arvore
  //----------------------------------------------------------------------------

  //if(D_chegou(arg->matriz_atual)){
  //if((arg->matriz_atual[3][COLUNAS-1] == 'M')&(arg->matriz_atual[4][COLUNAS-1] == 'M')){
  if(cheguei(arg->matriz_atual, ALVO)){
  //Função que verifica se a peça alvo está adjacente à saída
    eureka = 1;//Marca a variavel global para avisar as outras recursoes em andamento
    printf("\nFim da solução----------------------------------------------\n\n\n");
    imprime_ate_a_raiz(arg);
    printf("\n^^^^^^^^^ Inicio da solução acima ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
    printf("EUREKAA EUREKAAA EUREKAA KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK\n\n");
    printf("Tirei a peça %c\n", ALVO);
		return;
	}else{
    //printf("Não cheguei\n");
    //imprime_mat(arg->matriz_atual);
  }
	//---------------------------------------------------------------------------------

	encontra_possibilidades(arg);/*vai pegar o membro
	matriz_atual da struct de entrada. A partir dele, vai verificar quais sao
	os movimentos possiveis e gravá-los nas filhas.*/
  //printf("Gravei possibilidades nos filhos\n");

	for(int i = 0; i < 8; ++i){/*Parte responsável pela recursao. Quando
		chegar aqui, as structs filhas já tem seu estado atual(matriz_atual),
		que foram preenchidos no código acima.*/

		if (arg->filho[i]){/*Se a struct filha
			nao for null, é pq ela é uma filha válida.*/
      passa_limite = arg_limite;
			(arg->filho[i])->pai = arg;//linkei as filhas no pai
			loop_magico(arg->filho[i], passa_limite);/*Fiz todo o processo
			novamente para todas as filhas que contém uma nova matriz_atual
			preenchida*/
		}
	}
  //printf("Terminei essa iteração do loop-------------------------------------------\n\n");
	//----------------------------------------------------------------------------------
}

int main(int argc, char *argv[]){
	char matriz[5][6];
	gera_matriz(matriz);
  node raiz = *((node*)malloc(sizeof(node)));
  copiaMatriz(raiz.matriz_atual, matriz);
  int limit = 0;
  loop_magico(&raiz, limit);
  printf("Acabei\n");
return 0;
}
