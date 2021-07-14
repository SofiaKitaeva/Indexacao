// Ayla Rodrigues e Sofia Kitaeva
// Trabalho Indexacao - Programacao com arquivos

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct Palavra
{
	char letras[50];
	int qntOcorencias;
	int *linhas;
	struct palavra *prox, *ant;
}Palavra;

Palavra *CriarLista()
{
	struct Palavra *sentinela = (struct Palavra*) malloc(sizeof(struct Palavra));
	sentinela->prox=sentinela;
	sentinela->ant=sentinela;
	return sentinela;
};

Palavra *CriarElemento(char letras[])
{
	struct Palavra *resp = (struct Palavra*) malloc(sizeof(struct Palavra));
	resp->ct=1;

	strcpy(resp->p,Palavra);
	resp->prox=NULL;
	resp->ant=NULL;

	return resp;
};

Palavra *Buscar
{
	struct Palavra *aux1=lista->prox;
    struct Palavra *aux2 = lista->prox->prox;
    
    while(aux1!=lista)
    {
        while(aux2!=lista)
        {
            if(strcmp(aux1->p, aux2->p)==0)
            {
                aux1->ct++;
                aux2->prox->ant=aux2->ant;
                aux2->ant->prox=aux2->prox;
                free(aux2);
            }
        }
    }
};

void InserirElemento(struct Palavra *Lista, char letras[])
{
	struct Palavra *novo = CriarElemento(letras);
    struct Palavra *aux=lista->prox;

    if(aux==lista){
        novo->prox=lista;
        novo->ant=lista->ant;
        lista->ant->prox=novo;
        lista->ant = novo;
    }
    else
    {
        while(aux!=lista){
            if(strcmp(novo->p,aux->p)<0){
                novo->prox=aux;
                novo->ant=aux->ant;
                aux->ant->prox=novo;
                aux->ant=novo;
                aux=lista;
            }
            else
            {
                aux=aux->prox;
            }
        }
    
        if(novo->prox==NULL){
            novo->prox=lista;
            novo->ant=lista->ant;
            lista->ant->prox=novo;
            lista->ant = novo;
        }
    }
}

void LerReceberArquivo(struct Palavra *Lista)
{
	FILE *arq;
	char arv[100];
	char letras[100];


	printf("Qual o nome do arquivo?");
	scanf("%s", arv);
	arq=fopen(arv,"rt");

	if (arq!=NULL)
	{
		while(feof(arq)==0)
		{
			fscanf(arq, "%s", letras)
			InserirElemento(lista, letras);
		}
	}fclose(arq);
}

int main(){

	setlocale(LC_ALL, "");

	int opcao =0;
	struct Palavra *lista=NULL;

	while (opcao!=3)
	{
		printf("O que deseja fazer?\n 1.Criar um indice para um arquivo de texto;\n2.Utilizar um indice existente para realizar busca por palavras;\n3.Encerrar programa;");
		scanf("%d", &opcao);
		printf("\n");

		if (opcao==1)
		{
			LerReceberArquivo(lista);
		}

		else if(opcao==2)
		{

		}

		Sleep(5000);
		system("cls");
	}
	printf("O usuário saiu!\n");

	return 0;
}