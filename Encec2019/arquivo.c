#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arquivo.h"



void exibe_arquivo(char *arquivo){
    FILE *c;
    char ch;
    c = fopen(arquivo,"r");
    if(c==NULL)
        printf("erro");

    while (!feof(c))        		/* Enquanto n�o se chegar no final do arquivo */
    {
     printf("%c",ch); 		/*   Imprime o caracter na tela */
     ch = getc(c);    		/* Le um novo caracter no arquivo */
     if(ch == '\n')
        putchar('\t');
    }
    fclose(c);
}

void exibe_arquivo2(char *arquivo){
        FILE *c;
        char texto_str[30];
        c = fopen(arquivo,"r");
        while(fgets(texto_str, 30, c) != NULL)
            printf("%s", texto_str);
        fclose(c);
}


int conta_linhas(char *arquivo){
    FILE *arqv;
    arqv = fopen(arquivo,"r");
    if(arqv == NULL)
        return 0;
    char caracter;
    int linhas=0;
    while (caracter!=EOF) {
      caracter = fgetc(arqv);
      if (caracter=='\n') {
             linhas++;
             }
    }
    fclose(arqv);
    return linhas;
}

int pesquisa_no_arquivo(char *arquivo,char *str){
    FILE *arqv;
    arqv = fopen(arquivo,"r");
    if(arqv == NULL)
        return 0;
    char caracter;
    int iguais=0,i=0,aux=0;

    while (caracter!=EOF) {
      caracter = fgetc(arqv);
      if (caracter==str[i]) {
             if(iguais == 0 && i == 0){
             iguais++;
             i++;
             }
             else{
                if(aux){
                    iguais = 0;
                    i = 0;
                    continue;
                }
                else{
                    iguais++;
                    i++;
                    if(iguais==strlen(str))
                        break;
                }
             }
             aux = 0;
            }
      else {
        aux++;
      }
    }

      fclose(arqv);
      if(iguais==strlen(str))
        return 1;
    return 0;

}

int linha_selecionada(char *arquivo, char *str){
    int linha = 1;
    FILE *arqv;
    arqv = fopen(arquivo,"r");
    if(arqv == NULL)
        return 0;
    char caracter;
    int iguais=0,i=0;
    while (caracter!=EOF) {
      caracter = fgetc(arqv);
      if (caracter==str[i]) {
             iguais++;
             i++;
             }
      if(caracter == '\n')
        linha++;
      if(iguais==strlen(str)){
        break;
      }
    }
   fclose(arqv);
   return linha;


}

void exibir_dados_pessoas(char *arquivo,char *str){
    FILE *arqv;
    arqv = fopen(arquivo,"r");
    if(arqv==NULL){
        //printf("erro");
    }
    int linha_atual = 0;
    int linha = linha_selecionada(arquivo,str);
    if(arqv != NULL){

    char caracter;
    while(caracter!=EOF){
        caracter = fgetc(arqv);
        if(linha_atual >= linha && linha_atual<=linha+LINHAS_PESSOA-1){
            printf("%c",caracter);
        }
        if(caracter=='\n')
            linha_atual++;
    }
    }

}


void exibir_dados_evento(char *str){
    FILE *arqv;
    char *arquivo = ARQ_EVENTOS;
    arqv = fopen(arquivo,"r");
    if(arqv==NULL){
        //printf("erro");
    }
    int linha_atual = 0;
    int linha = linha_selecionada(arquivo,str);
    if(arqv != NULL){

    char caracter;
    while(caracter!=EOF){
        caracter = fgetc(arqv);
        if(linha_atual >= linha && linha_atual<=linha+LINHAS_EVENTO){
            printf("%c",caracter);
        }
        if(caracter=='\n')
            linha_atual++;
    }
    }

}

//STACK OVERFLOW
void editar_dados_pessoas(char *arquivo,int linha,char *novo_dado){
    FILE *input = fopen(arquivo, "r"); //Arquivo de entrada.
    FILE *output = fopen(ARQ_TRANSFERIR, "w"); //Arquivo de sa�da.
    if(input==NULL || output ==NULL){
        //printf("erro");
    }
    int linha_atual = 1;
    char caracter;
    int cont = 0;
    while(caracter!=EOF){
        caracter = fgetc(input);
        if(linha_atual != linha){
            fputc(caracter,output);
        }else{
            if(!cont)
             fprintf(output,"%s",novo_dado);
            cont++;
        }
        if(caracter == '\n')
            linha_atual++;
    }
    fclose(input);
    fclose(output);
    remove(arquivo);
    rename(ARQ_TRANSFERIR, arquivo);

}

int remover_dados(char *arquivo,int linha,int seguintes){
    FILE *input = fopen(arquivo, "r"); //Arquivo de entrada.
    FILE *output = fopen(ARQ_TRANSFERIR, "w"); //Arquivo de sa�da.
    if(input==NULL || output ==NULL){
        printf("erro");
        return 0;
    }
    int linha_atual = 1;
    char caracter;
    while(caracter!=EOF){
        caracter = fgetc(input);
        if(linha_atual<linha || linha_atual>linha+seguintes)
            fputc(caracter,output);
        if(caracter == '\n')
            linha_atual++;
    }
    fclose(input);
    fclose(output);
    remove(arquivo);
    rename(ARQ_TRANSFERIR, arquivo);

return 1;
}

int checa_existencia_evento(char *cod){
    char texto[20] = "CODIGO DO EVENTO: ";
    strcat(texto,cod);
    return pesquisa_no_arquivo(ARQ_EVENTOS,texto);
}

int limpar_caracteres(char *arquivo){
    FILE *input = fopen(arquivo, "r"); //Arquivo de entrada.
    FILE *output = fopen(ARQ_TRANSFERIR, "w"); //Arquivo de sa�da.
    if(input==NULL || output ==NULL){
        printf("erro");
        return 0;
    }
    int linha_atual = 1;
    char caracter;
    while(caracter!=EOF){
        caracter = fgetc(input);
        if(caracter=='�')
            fputc('-',output);
        else
            fputc(caracter,output);
        if(caracter == '\n')
            linha_atual++;
    }
    fclose(input);
    fclose(output);
    remove(arquivo);
    rename(ARQ_TRANSFERIR, arquivo);

return 1;
}

int busca_cpf(char *arquivo,char *cpf){
    char testa_cpf[25];
    strcpy(testa_cpf,"\nCPF: ");
    strcat(testa_cpf,cpf);
    return(pesquisa_no_arquivo(arquivo,testa_cpf));
}

int busca_cpf_palest(char *arquivo,char *cpf){
    char testa_cpf[25];
    strcpy(testa_cpf,"(");
    strcat(testa_cpf,cpf);
    strcat(testa_cpf,")");
    return(pesquisa_no_arquivo(arquivo,testa_cpf));
}


void borda(){
    for(int i = 0;i<90;i++){
        printf("%c",242);
    }
    putchar('\n');
    printf("\n\t\t\t#EncontroCampinenseDosEstudantesdeComputacao\n");
    for(int i = 0;i<90;i++){
        printf("%c",242);
    }
    putchar('\n');

}
