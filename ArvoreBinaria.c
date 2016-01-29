#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int cod;
	char nome[40];
	char data_nasc[11];
	char email[40];
	char telcel[11];
}T_Pessoa;

typedef struct nd{
	T_Pessoa Elem;
	struct nd *esq, *dir;	
}Nodo;

typedef Nodo *Arvore_Binaria;

typedef struct Cx{
	Arvore_Binaria Item;
	struct Cx *Prox;
}Caixa;

typedef Caixa *Ponteiro;

typedef struct {
	Ponteiro Inicio;
	Ponteiro Fim;
	int Tam;
}Fila_nodo;

int Verifica_Arvore_Vazia(Arvore_Binaria T){
	return (T == NULL);
} 

int Verifica_Fila_Vazia(Fila_nodo F){ 
	return (F.Inicio == F.Fim);
}

void Criar_Fila_Vazia(Fila_nodo *F){
	Ponteiro A;
	A = (Caixa *) malloc(sizeof(Caixa));
	A->Item = NULL;
	A->Prox = NULL;
	F->Inicio = A;
	F->Fim = A;
	F->Tam = 0;
}	

void Enfileirar(Fila_nodo *F, Arvore_Binaria X){
	Ponteiro A;
	A = (Ponteiro) malloc(sizeof (Caixa));
	A->Item = X;
	A->Prox = F->Fim->Prox;
	F->Fim->Prox = A;
	F->Fim = A;
	F->Tam++; 
}

void Desenfileirar(Fila_nodo *F, Arvore_Binaria *X){
	Ponteiro A;
	if(Verifica_Fila_Vazia(*F))
		printf("A Fila esta vazia - Desenfileirar\n");
	else {
		A = F->Inicio;  //aponta para a cabeça da fila
		F->Inicio = A->Prox;   //Corrige o Inicio
		*X = F->Inicio->Item;  //copia o T_pessoa para levar para o meio ext
		F->Tam--;      //Atualiza o Tam da Fila
		free(A);       //elimina o espaço da cx removida
	}		
}

void Insere_Elemento_Arvore(Arvore_Binaria *T, T_Pessoa X){
	if ((*T)==NULL){
		(*T) = (Arvore_Binaria) malloc(sizeof (Nodo));
		(*T)->dir = NULL;
		(*T)->esq = NULL;
		(*T)->Elem = X;
	}else if ((*T)->Elem.cod > X.cod)
		Insere_Elemento_Arvore(&((*T)->esq), X); // Insere no lado direito da sub-arvore
	else if ((*T)->Elem.cod < X.cod) 
		Insere_Elemento_Arvore(&((*T)->dir), X); // Insere no lado esquerdo da sub-arvore
	else (*T)->Elem = X; // só substitui o valor
}

void Exibir_Elemento(T_Pessoa X){
	printf("  %5d - %s \n",X.cod, X.nome);
}

void pre_ordem(Arvore_Binaria T){
	if(T != NULL){
		Exibir_Elemento(T->Elem);
		pre_ordem(T->esq);
		pre_ordem(T->dir);
	}
}

void in_ordem(Arvore_Binaria T){
	if(T != NULL){
		in_ordem(T->esq);
		Exibir_Elemento(T->Elem);
		in_ordem(T->dir);
	}
}

void pos_ordem(Arvore_Binaria T){
	if(T != NULL){
		pos_ordem(T->esq);
		pos_ordem(T->dir);
		Exibir_Elemento(T->Elem);
	}
}

void por_nivel(Arvore_Binaria T, Fila_nodo *F){
	Arvore_Binaria A;
	if(T!=NULL){
		Exibir_Elemento(T->Elem);
		if(T->esq != NULL)
			Enfileirar(&(*F),T->esq);
		if(T->dir != NULL)
			Enfileirar(&(*F),T->dir);
		if (!Verifica_Fila_Vazia(*F)){
			Desenfileirar(&(*F),&A);
			por_nivel(A,&(*F));
		}
	}
}

void busca_elem_arvore(Arvore_Binaria T, T_Pessoa X){
	if(T == NULL)
		printf("\nElemento não encontrado.\n");
	else if(X.cod < T->Elem.cod)
		busca_elem_arvore(T->esq,X);
	else if(X.cod > T->Elem.cod)
		busca_elem_arvore(T->dir,X);
	else Exibir_Elemento(T->Elem);
}

T_Pessoa maiorMenores(Arvore_Binaria Q, T_Pessoa *R){
	while (Q->dir != NULL){
		Q = Q->dir;
	}
	*R = Q->Elem;
	return (Q->Elem);
}

void removeElemArvore(Arvore_Binaria *T, T_Pessoa *X){
	Arvore_Binaria A;

	if ((*T) == NULL){
		printf("\nElemento não existe\n");
	} else if (X->cod < (*T)->Elem.cod){
		removeElemArvore(&((*T)->esq), &(*X));
	} else if (X->cod > (*T)->Elem.cod) {
		removeElemArvore(&((*T)->dir), &(*X));
	} else if ((*T)->dir == NULL){
		*X = (*T)->Elem;
		A = (*T);
		(*T) = (*T)->esq;
		free(A);
	} else if ((*T)->esq == NULL){
		*X = (*T)->Elem;
		A = (*T);
		(*T) = (*T)->dir;
		free(A);
	} else {
		(*T)->Elem = maiorMenores((*T)->esq, &(*X));
		removeElemArvore(&((*T)->esq), X);
	}
		
		printf("\nElemento Removido\n");
}

void Ler(T_Pessoa *X){
	printf("\nEntre com o Código: ");
	scanf("%d",&(X->cod));
	printf("\nEntre com o Nome : ");
	scanf("%s",X->nome);
}

void salvar(Arvore_Binaria T){
	FILE *arq;
}

void Menu()
{
printf("M E N U - L I S T A   E S T A T I C A  E N C A D E A D A\n");
printf("1 - Inserir Novo Elemento na Lista\n");
printf("2 - Remover Elemento da Lista\n");
printf("3 - Percorrer Pre-Ordem\n");
printf("4 - Percorrer In-Ordem\n");
printf("5 - Percorrer Pos-Ordem\n");
printf("6 - Percorrer Por-Nivel\n");
printf("7 - Consultar um Elemento\n");
printf("8 - Sair\n");
printf("Opcao:  ");	   
}

int main(int argc, char **argv)
{ Arvore_Binaria T;
Fila_nodo F;
int op;
T_Pessoa X;
T = NULL;  // torna a árvore vazia inicialmente
Criar_Fila_Vazia(&F);
do { Menu();
scanf("%d",&op);
switch (op) {
case 1:Ler(&X);
Insere_Elemento_Arvore(&T,X);
break;
case 2:Ler(&X);
removeElemArvore(&T,&X);
printf("\n Elemento removido : \n");
Exibir_Elemento(X);
break;
case 3:pre_ordem(T);
break;
case 4: in_ordem(T);
break;
case 5: pos_ordem(T);
break;
case 6: por_nivel(T,&F);
break;
case 7: Ler(&X);
busca_elem_arvore(T,X);
break;
case 8: printf("\nObrigado por usar nosso Software\n");
break;
default : printf("Opção não existente\n");
break;
}   	  
}while(op!=8);
return 0;
}
