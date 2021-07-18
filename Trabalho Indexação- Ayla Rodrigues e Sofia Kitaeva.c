// Ayla Rodrigues e Sofia Kitaeva
// Trabalho Indexacao - Programacao com arquivos

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>

int total=0;
int linha=1;

typedef struct Palavra
{
	char letras[50];
	int qntOcorencias;
	int *linhas;
	struct Palavra *prox,*ant;
	
}Palavra;

Palavra *CriarLista()
{
	Palavra *sentinela = (Palavra*) malloc(sizeof(Palavra));
	sentinela->prox = sentinela;
	sentinela->ant = sentinela;
	return sentinela; 
};

Palavra *CriarElemento(char letras[])
{
	struct Palavra *resp = (struct Palavra*) malloc(sizeof(struct Palavra));
	resp->qntOcorencias=1;
	strcpy(resp->letras,letras);
	int tam = strlen(resp->letras)+1;
	resp->letras[tam]=0;
	resp->linhas= (int*) malloc(sizeof(int));
	resp->prox=NULL;
	resp->ant=NULL;

	return resp;
};

Palavra *Buscar(struct Palavra *Lista, char plv[])
{
	struct Palavra *aux = Lista->prox;
    
    while(aux!=Lista && strcmp(aux->letras, plv)!=0)
    	aux = aux->prox;
    if(aux!=Lista)
    	return  aux;
    else
    	return NULL;
}

void InserirElemento(struct Palavra *Lista, char letras[])
{
	struct Palavra *aux = Buscar(Lista, letras);
	if(aux!=NULL)
		aux->qntOcorencias++;
	else{
		struct Palavra *novo = CriarElemento(letras);
	    aux = Lista->prox;
	    if(aux==Lista){
	        novo->prox=Lista;
	        novo->ant=Lista->ant;
	        Lista->ant->prox=novo;
	        Lista->ant = novo;
	    }
		else{
	        while(aux!=Lista){
	            if(strcmp(novo->letras,aux->letras)<0){
	                novo->prox=aux;
	                novo->ant=aux->ant;
	                aux->ant->prox=novo;
	                aux->ant=novo;
	                aux=Lista;
	            }
	            else
	            {
	                aux=aux->prox;
	            }
	        }
	    
	        if(novo->prox==NULL){
	            novo->prox=Lista;
	            novo->ant=Lista->ant;
	            Lista->ant->prox=novo;
	            Lista->ant = novo;
	        }
	    }
	}
}

void LerReceberArquivo(struct Palavra *Lista)
{
	char arv[50];
	char letras[100];
	
	FILE *arq;
	printf("Qual o nome do arquivo?\n");
	scanf("%s", arv);
	arq=fopen(arv,"r");

	if (arq!=NULL)
	{

		while(feof(arq)==0)
		{
			fscanf(arq, "%s", letras);
			InserirElemento(Lista, letras);
			for(int i=0; i<strlen(letras)+2; i++)
				if(letras[i]==10)
					linha++;
			total++;
		}
	}
	
	fclose(arq);
}

void listar(struct Palavra *Lista)
{
	struct Palavra *aux = Lista->prox;
	if (Lista==NULL)
	{
		return;
	}
	do
	{
		printf("%s, %d\n", aux->letras, aux-> qntOcorencias);
		aux=aux->prox;
	}while(aux!=Lista);
};

Palavra *Destruir(Palavra *Lista){
	Palavra *aux = Lista;
	Lista->ant->prox=NULL;
	while(aux!=NULL){
		Lista=Lista->prox;
		free(aux);
		aux=Lista;
	}
	return NULL;
}

void EscreverDat(Palavra *Lista){
	FILE *dat;
	Palavra *aux = Lista->prox;
	dat = fopen("indice.dat", "wb");
	fwrite(&total, sizeof(int),1,dat);
	while(aux!=Lista){
		int stringT=strlen(aux->letras)+1;
		fwrite(&stringT, sizeof(int),1,dat);
		fwrite(&aux,sizeof(Palavra),1,dat);
		aux=aux->prox;
	}
}

Palavra *BuscaIndex(Palavra *Lista, char plv[]){
	int totalplv;
	
	Lista=Destruir(Lista);
	FILE* arq;
	arq=fopen("indice.dat", "rb");
	fread(&totalplv, sizeof(int),1,arq);
	
	
	fclose(arq);
	
}

int main(){

	setlocale(LC_ALL, "");

	int opcao =0;
	char plv[50];
	struct Palavra *Lista = CriarLista();

	while (opcao!=3)
	{
		printf("O que deseja fazer?\n1.Criar um indice para um arquivo de texto.\n2.Utilizar um indice existente para realizar busca por palavras.\n3.Encerrar programa.\n");
		scanf("%d", &opcao);
		printf("\n");

		if (opcao==1)
		{
			LerReceberArquivo(Lista);
			EscreverDat(Lista);
			listar(Lista);
		}

		else if(opcao==2)
		{
			printf("Qual palavra deseja procurar?\n");
			scanf("%s", plv);
			BuscaIndex(Lista,plv);
		}

		system("pause");
		system("cls");
	}
	
	
	printf("O usuário saiu!\n");

	return 0;
}
