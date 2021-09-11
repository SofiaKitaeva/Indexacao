// Ayla Rodrigues e Sofia Kitaeva
// Trabalho Indexação pt.2 - Programacao com arquivos

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>

int arquivo=0;
int linha=0;

typedef struct ocorrencias{
    int arquivo;
    int qtdOcorrencias;
    int linhas[50];
    struct Ocorrencia *prox;
    
}Ocorrencia;

typedef struct Palavra{
    char letras[50];
    int qntOcorencias;
    Ocorrencia *ocorrencias;
    struct Palavra *prox;
    
}Palavra;

typedef struct arquivos{
  char nomeArq[50];
  struct Arquivo *prox;

}Arquivo;

typedef struct indices{
  int qtdArquivos;
  struct Arquivo *arquivos;
  int qtdPalavras;
  struct Palavra *iniciais[26];
  struct Palavra *Palavras;
}Indice;

Palavra *CriarElemento(char letras[]){
    struct Palavra *resp = (struct Palavra*) malloc(sizeof(struct Palavra));
    resp->qntOcorencias=1;
    strcpy(resp->letras,letras);
    int tam = strlen(resp->letras);
    resp->letras[tam]='\0';
    Ocorrencia* nova = (Ocorrencia*) malloc(sizeof(Ocorrencia));
    nova->arquivo=arquivo;
	nova->qtdOcorrencias=1;
    nova->linhas[0] = ;//resolver
    nova->prox=NULL;
    resp->ocorrencias=nova;
    resp->prox=NULL;

    return resp;

}

Palavra *Buscar(Indice* ind, char plv[]){
   /* int pos;
    if(plv[0]>90)
    	pos=plv[0]-97;
    else
    	pos=plv[0]-65;*/
    
	Palavra* aux = ind->Palavras;
    
    while(aux!=NULL && strcmp(aux->letras, plv)!=0)
        aux = aux->prox;
    
	return aux;
}

Ocorrencia* CriaOcorrencia(){
	Ocorrencia* novo = (Ocorrencia*) malloc(sizeof(Ocorrencia*));
	novo->arquivo=arquivo;
	novo->linhas[0] = linha;
	novo->qtdOcorrencias=1;
	novo->prox=NULL;
	
	return novo;
}

void InserirElemento(Indice* ind, char letras[]){
    Palavra* aux = Buscar(ind, letras);
     
	int pos;
    if(letras[0]>90)
    	pos=letras[0]-97;
    else
    	pos=letras[0]-65;
    
	if(aux!=NULL){ //se a palavra já existir
		Palavra* auxI=ind->iniciais[pos];
		while(strcmp(auxI->letras, letras)!=0)
        	auxI = auxI->prox;
        	
    	int flag = 0;
		Ocorrencia* auxO = aux->ocorrencias; //atualizar ocorrências na lista 'Palavras'	
		while(auxO!=NULL && flag!=1){
			if(auxO->arquivo==arquivo){
				flag=1;
				break;	
			}
			auxO=auxO->prox;
		}
		if(flag==1){
			auxO->linhas[auxO->qtdOcorrencias]=linha;
			auxO->qtdOcorrencias++;
			//incluir número da nova linha
		}
		else{
			auxO = aux->ocorrencias;
			while(auxO->prox!=NULL)
				auxO=auxO->prox;
			Ocorrencia* novo = CriaOcorrencia();
			auxO->prox=novo;	
		}
		
		flag = 0;
		auxO = auxI->ocorrencias; //atualizar ocorrências na lista 'iniciais'	
		while(auxO!=NULL && flag!=1){
			if(auxO->arquivo==arquivo){
				flag=1;
				break;	
			}
			auxO=auxO->prox;
		}
		if(flag==1){
			auxO->linhas[auxO->qtdOcorrencias]=linha;
			auxO->qtdOcorrencias++;
			//incluir número da nova linha
		}
		else{
			auxO = aux->ocorrencias;
			while(auxO->prox!=NULL)
				auxO=auxO->prox;
			Ocorrencia* novo = CriaOcorrencia();
			auxO->prox=novo;	
		}
    }
    else{//se a palavra não existir
    	ind->qtdPalavras++;
        struct Palavra *novo = CriarElemento(letras);
		if(ind->iniciais[pos]==NULL){//se lista de palavras estiver vazia
            ind->iniciais[pos]=novo;
            ind->Palavras=novo;
        }
        else{
        	aux=ind->iniciais[pos];
        	Palavra* aux2=aux;
			while(aux!=NULL){
                if(strcmp(novo->letras,aux->letras)<0 && aux==ind->iniciais[pos]){
                    novo->prox=aux;
                    ind->iniciais[pos]=novo;
                }
                else if(strcmp(novo->letras,aux->letras)<0){
                	novo->prox=aux;
                	aux2->prox=novo;
				}
                aux2=aux;
                aux=aux->prox;
            }
            
            aux=ind->Palavras;
        	Palavra* aux2=aux;
			while(aux!=NULL){
                if(strcmp(novo->letras,aux->letras)<0 && aux==ind->Palavras){
                    novo->prox=aux;
                    ind->Palavras=novo;
                }
                else if(strcmp(novo->letras,aux->letras)<0){
                	novo->prox=aux;
                	aux2->prox=novo;
				}
                aux2=aux;
                aux=aux->prox;
            }
        }
    }
}

Arquivo* BuscarArq(Indice* ind, char arq[]){
	if(ind->arquivos==NULL)
		return NULL;
	else{
		Arquivo* aux = ind->arquivos;
		while(aux!=NULL && strcmp(aux->nomeArq, arq)!=0)
        	aux = aux->prox;
        	
		return aux;
	}
}

void InserirArq(Indice* ind, char arv[]){
	arquivo++;
	if(ind->arquivos==NULL){
		Arquivo* novo = (Arquivo*) malloc(sizeof(Arquivo));
		strcpy(novo->nomeArq,arv);
		novo->prox=NULL;
		ind->arquivos=novo;
		ind->qtdArquivos++;
	}
	else{
		ind->qtdArquivos++;
		Arquivo* aux=ind->arquivos;
		while(aux->prox!=NULL)
			aux=aux->prox;
		Arquivo* novo = (Arquivo*) malloc(sizeof(Arquivo));
		novo->prox=NULL;
		strcpy(novo->nomeArq,arv);
		aux->prox=novo;
	}
}

void LerReceberArquivo(Indice* ind){
    char arv[50];
    char letras[1000];
    char *x;
    char *y;
    
    FILE *arq;
    printf("Qual o nome do arquivo?\n");
    scanf("%s", arv);

	Arquivo* aux = BuscarArq(ind,arv); //buscar nome do arquivo
	if (aux==NULL)//se o arquivo fornecido nao tiver sido lido ainda
    {
        arq=fopen(arv,"r");
        if (arq==NULL)
            printf("Problemas na leitura do arquivo\n");
        else{
            //inserir o nome do arquivo.txt no final da lista de arquivo
            InserirArq(ind,arv);
            linha=1;
			while(!feof(arq)){
                int resultado = fgets(letras,1000,arq);

                if (resultado){
                	x=strtok(letras, "\n"); //perguntar
					linha++; 
                	while(x!=NULL)
                	{
                		y=strtok(x, " ");
                		InserirElemento(ind, x);//colocar na lista a posicao do arquivo, linha
                		x=strtok(NULL,"\n");
                	}
                }  
			}
        }
		fclose(arq); 
    }
    else
        printf("O arquivo já foi lido\n");

}

void Listar(Indice* ind){
    Arquivo* auxA = ind->arquivos;
    
    printf("\tARQUIVOS:\n");
    int i=1;
    do{
        printf("%d: %s\n", i, auxA->nomeArq);
        auxA=auxA->prox;
        i++;
    }while(auxA!=NULL);
    
    Palavra* auxP = ind->Palavras;
    printf("\n\tPALAVRAS:\n-----------------------\n");
	do{
        printf("\t%s \n", auxP->letras);
        Ocorrencia* auxO=auxP->ocorrencias;
		while(auxO!=NULL){
        	printf("Arquivo: %d\n", auxO->arquivo);
        	printf("Ocorrências no arquivo: %d\n", auxO->qtdOcorrencias);
        	printf("Linhas em que aparece: ");
        	for(int i=0; i<auxO->qtdOcorrencias;i++)
        		printf(" %d", auxO->linhas[i]);
        	printf("\n");
        	auxO=auxO->prox;
		}
		auxP=auxP->prox;
		printf("-----------------------\n");
    }while(auxP!=NULL);
}

void EscreverDat(Indice *ind){
    FILE *dat;
    dat = fopen("indice.dat", "wb");
    fwrite(&ind->qtdArquivos, sizeof(int),1,dat);
	Arquivo* auxA= ind->arquivos;
	while(auxA!=NULL){
        int arqNomeT=strlen(auxA->nomeArq)+1;
        fwrite(&arqNomeT, sizeof(int),1,dat);
        fwrite(&auxA->nomeArq,sizeof(char)*arqNomeT-1,1,dat);
        fwrite("\0",sizeof(char),1,dat);
        auxA=auxA->prox;
    }
    
	fwrite(&ind->qtdPalavras, sizeof(int),1,dat);
	Palavra* auxP = ind->Palavras;
	while(auxP!=NULL){
    	int tamPlv=strlen(auxP->letras)+1;
    	fwrite(&tamPlv, sizeof(int),1,dat);
		fwrite(&auxP->letras,sizeof(char)*tamPlv-1,1,dat);
		fwrite("\0",sizeof(char),1,dat);
		Ocorrencia* auxO = auxP->ocorrencias;
		int i;
		int j;
		for(i=0;i<auxP->qntOcorencias;i++){
    		fwrite(&auxO->arquivo,sizeof(int),1,dat);
    		fwrite(&auxO->qtdOcorrencias,sizeof(int),1,dat);
			for(j=0;j<auxO->qtdOcorrencias;j++)
				fwrite(&auxO->linhas[i],sizeof(int),1,dat);
			auxO=auxO->prox;
		}
		auxP=auxP->prox;
	}
	
	fclose(dat);
}

Indice* CriaIndice(){
	Indice* ind = (Indice*) malloc(sizeof(Indice*));
	ind->arquivos=NULL;
	ind->Palavras=NULL;
	ind->qtdArquivos=0;
	ind->qtdPalavras=0;
	
	return ind;
}

void LiberaMem(Indice* ind){
	Arquivo* auxA=ind->arquivos;
	Arquivo* auxA2;
	while(auxA!=NULL){
		auxA2 = auxA->prox;
		free(auxA);
		auxA=auxA2;
	}
	
	Palavra* auxP=ind->Palavras;
	Palavra* auxP2;
	Ocorrencia* auxO;
	Ocorrencia* auxO2;
	while(auxP!=NULL){
		auxP2=auxP->prox;
		auxO=auxP->ocorrencias;
		while(auxO!=NULL){
			auxO2=auxO->prox;
			free(auxO);
			auxO=auxO2;
		}
		free(auxP);
		auxP=auxP2;
	}
	free(ind);
}

void LerDat(Indice* ind){
	FILE* arq;
	arq=fopen("indice.dat","rb");
	
	fread(&ind->qtdArquivos, sizeof(int),1,arq);
	int tam;
	
	for(int i=0; i<ind->qtdArquivos; i++){
		fread(&tam, sizeof(int),1,arq);
		char nomeArq[tam];
		fread(nomeArq, sizeof(char),tam,arq);
		InserirArq(ind, nomeArq);
	}
	
	fread(&ind->qtdPalavras, sizeof(int),1,arq);
	
	for(int i=0; i<ind->qtdPalavras; i++){
		fread(&tam, sizeof(int),1,arq);
		char Pal[tam];
		fread(Pal, sizeof(char),tam,arq);
		struct Palavra *novo = (struct Palavra*) malloc(sizeof(struct Palavra));
		strcpy(novo->letras,Pal);
		fread(&novo->qntOcorencias, sizeof(int),1,arq);
		for(int j=0; j<novo->qntOcorencias;j++){
			Ocorrencia *nova = (Ocorrencia*) malloc(sizeof(Ocorrencia));
			fread(&nova->arquivo, sizeof(int),1,arq);
			fread(&nova->qtdOcorrencias, sizeof(int),1,arq);
			for(int k=0;k<nova->qtdOcorrencias;k++){
				fread(&nova->linhas[k], sizeof(int),1,arq);
			}
			if(novo->ocorrencias==NULL)
				novo->ocorrencias=nova;
			else{
				Ocorrencia* auxO=novo->ocorrencias;
				while(auxO->prox!=NULL)
					auxO=auxO->prox;
				auxO->prox=nova;
			}	
		}
		
		int pos;
  		if(novo->letras[0]>90)
  	  		pos=novo->letras[0]-97;
    	else
    		pos=novo->letras[0]-65;
		
		if(ind->Palavras==NULL)
			ind->Palavras=novo;
		else{
			Palavra* aux = ind->Palavras;
			while(aux->prox!=NULL)
				aux=aux->prox;
			aux->prox=novo;
		}
		
		if(ind->iniciais[pos]==NULL)
			ind->iniciais[pos]=novo;
		else{
			Palavra* aux = ind->iniciais[pos];
			while(aux->prox!=NULL)
				aux=aux->prox;
			aux->prox=novo;
		}	
	}
	fclose(arq);
}

void BuscaSimples(Indice* ind, char plv[]){
		int pos;
  		if(novo->letras[0]>90)
  	  		pos=plv[0]-97;
    	else
    		pos=plv[0]-65;
    	
    	Palavra* aux= ind->iniciais[pos];
    	
		while(aux!=NULL && strcmp(aux->letras, plv)!=0)
    	    aux = aux->prox;
    	    
    	if(aux==NULL)
    		printf("Essa palavra não existe no índice\n");
    	else{
    		printf("\t%s\n", aux->letras);
    		printf("Ocorrências:");
    		
		}
    
}

int main(){

    setlocale(LC_ALL, "");

    int opcao =0;
    Indice* ind = CriaIndice();

    while (opcao!=5){
        printf("O que deseja fazer?\n1.Processar novo arquivo.\n2.Salvar o indice atual.\n3.Ler um arquvivo de indice\n4.Fazer busca de palavra\n5.Encerrar programa.\n>>");
        scanf("%d", &opcao);
        printf("\n");

        if (opcao==1){
            //processar arquivo
            LerReceberArquivo(ind);
        }
        else if(opcao==2){
            //salvar o indice atual
            EscreverDat(ind);
        }
        else if(opcao==3)
        {
            LiberaMem(ind);
            Indice* ind = CriaIndice();
            LerDat(ind); //ler o arquivo indice.dat e reconstruir a lista de palavras encontradas e suas ocorrencias
        }
        else if(opcao==4)
        	int busca;
			printf("Digite 1 para busca simples ou 2 para busca composta>>\n");
			scanf("%d", &busca);
			if(busca==1){
				char palavra[];
				printf("Digite a palavra que deseja buscar\n>>");
				scanf("%s", palavra);
				BuscaSimples(ind, palavra);
			}
			else{
				
			}

        system("pause");
        system("cls");
    }
    
	LiberaMem(ind);
    //nao remover o arquivo indice.dat
    printf("O usuário saiu!\n");

    return 0;
}
