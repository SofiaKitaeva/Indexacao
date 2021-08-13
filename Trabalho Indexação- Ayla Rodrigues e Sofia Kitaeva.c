// Ayla Rodrigues e Sofia Kitaeva
// Trabalho Indexacao - Programacao com arquivos

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>

int total=0;
int linha=1;


typedef struct ocorrencias{
    int arquivo;
    int qtdOcorrencias;
    int *linhas;
    struct Ocorrencia *prox;
    
}Ocorrencia;


typedef struct Palavra{
    char letras[50];
    int qntOcorencias;
    struct Ocorrencia *ocorrencias;
    struct Palavra *prox,*ant;
    
}Palavra;

typedef struct arquivos{
  char nomeArq[50];
  struct Arquivo *prox;

}Arquivo;

typedef struct indices{
  int qtdArquivos;
  struct Arquivo *arquivos;
  int qtdPalavras;
  struct Palavra *Palavras;

}Indice;


Palavra *CriarLista(){
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
    resp->linhas = (int*) malloc(sizeof(int*));
    resp->linhas = &linha;
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
    if(aux!=NULL){
        aux->qntOcorencias++;
        int vzs=aux->qntOcorencias;
        
        /* Professor, tentamos de todas as formas possíveis realocar o vetor dinâmico para caber
        as linhas diferentes, porém o programa INSISTE em crashar ao fazer o realloc, desculpa :(
        sabemos os passos necessários para realizar essa função, mas não conseguimos encontrar o erro
        
        aux->linhas = (int*) realloc(aux->linhas, vzs*sizeof(int*));
        aux->linhas[aux->qntOcorencias] = linha;*/
    }
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

    if (arv!=arquivos.nomeArq)//se o arquivo fornecido nao tiver sido lido ainda
    {
        arq=fopen(arv,"r");
        //inserir o nome do arquivo.txt no final da lista de arquivos
        InserirElemento(,arv);//terminar
        if (arq==NULL)
        {
            printf("Problemas na leitura do arquivo\n");
        }
        else
        {
            while(!feof(arq))
            {
                fscanf(arq, "%s", letras);
                if (strcmp(letras,Palavras.letras)!=0)
                {
                    InserirElemento(Lista, letras);//colocar na lista a posicao do arquivo, linha.
                    indices.qtdPalavras++;
                }
                else
                {
                    ocorrencias.arquivo = ;//tem que receber a posicao do arquivo na lista
                    //inserir na lista de ocorrencias, a posicao do arq, aumentar a qtd de ocorrencias, e em qual linha
                }
                
            } 
        } 
    }
    else
        printf("O arquivo já foi lido\n");

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
    dat = fopen("indice.dat", "ab");
    fwrite(&total, sizeof(int),1,dat);
    while(aux!=Lista){
        int stringT=strlen(aux->letras)+1;
        fwrite(&stringT, sizeof(int),1,dat);
        fwrite(&aux,sizeof(Palavra),1,dat);
        aux=aux->prox;
    }
}

Palavra *BuscaIndex(Palavra *Lista){
    int totalplv, tam;
    char plv[50];
    Palavra* info;
    
    Lista=Destruir(Lista);
    FILE* arq;
    arq=fopen("indice.dat", "rb");
    fread(&totalplv, sizeof(int),1,arq);
    printf("%d\n", totalplv);

    printf("Qual palavra deseja procurar?\n");
    scanf("%s", plv);
    
    while(feof(arq)==0){
        fread(&tam, sizeof(int),1,arq);
        fread(&info, sizeof(Palavra),1,arq);
        printf("Total de caracteres: %d\n", tam);
        printf("Palavra: %s\n", info);
        printf("Quantidade de ocorrências: %d\n", info->qntOcorencias);
        printf("Linhas em que aparece: ");
        for(int i=info->qntOcorencias; i=0; i++)
            printf("%d ", info->linhas[i]);
    }
   
    
    fclose(arq);
}

int main(){

    setlocale(LC_ALL, "");

    int opcao =0;
    struct Palavra *Lista = CriarLista();

    while (opcao!=5)
    {
        printf("O que deseja fazer?\n1.Processar novo arquivo.\n2.Salvar o indice atual.\n3.Ler um arquvivo de indice\n4.Mostrar informações do indice\n5.Encerrar programa.\n>");
        scanf("%d", &opcao);
        printf("\n");

        if (opcao==1){
            //processar arquivo
            LerReceberArquivo(Lista);
            EscreverDat(Lista);
        }

        else if(opcao==2){
            //salvar o indice atual
            BuscaIndex(Lista);
        }
        else if(opcao==3)
        {
            //ler um arquivo de indice
            //liberar a memoria do indice atual
            //ler o arquivo indice.dat e reconstruir a lista de palavras encontradas e suas ocorrencias

        }
        else if(opcao==4)
        {
            //mostrar informacoes do indice
            //mostrar os nomes de arquivo que compoem esse indice
            //as palavras em odrem alfabetica, cada palavras, quantidadde de vezes que apareceu nesse arquivo e os numeros das linhas
        }

        system("pause");
        system("cls");
    }
    
    //liberar a memori dinamicamente alocada
    //nao remover o arquivo indice.dat
    Lista=Destruir(Lista);
    printf("O usuário saiu!\n");

    return 0;
}
