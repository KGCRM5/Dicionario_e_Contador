/*Projeto 2 - Algoritmo e Programação II

Grupo:
- Klaus Gustavo Castelein Ricieri Moura
- Bruno Matheus Garutti Pinto
- Ana Julia Almeida
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO_PALAVRA 100
#define MAX_PALAVRAS 1000

// Chamada das funções
int lerProximaPalavra(FILE *arq, char *palavra);
int buscaBinariaRecursiva(char palavras[][TAMANHO_PALAVRA], const char *palavra, int inicio, int fim);
void inserirOrdenado(char palavras[][TAMANHO_PALAVRA], int frequencias[], int *totalPalavrasUnicas, const char *palavra);
void imprimirDicionario(char palavras[][TAMANHO_PALAVRA], int frequencias[], int totalPalavrasUnicas);

int main(){
    char palavras[MAX_PALAVRAS][TAMANHO_PALAVRA];
    int frequencias[MAX_PALAVRAS];

    int totalPalavrasUnicas = 0;
    char palavraLida[TAMANHO_PALAVRA];
    
    FILE *arquivoEntrada = fopen("arquivo.txt", "r");

    if (arquivoEntrada == NULL){
        printf("ERRO: Nao foi possivel abrir o arquivo.\n"); 
    }

    while(lerProximaPalavra(arquivoEntrada, palavraLida)){
        int indice = buscaBinariaRecursiva(palavras, palavraLida, 0, totalPalavrasUnicas - 1);

        if(indice != -1){
            frequencias[indice]++;
        } 
        else{
            inserirOrdenado(palavras, frequencias, &totalPalavrasUnicas, palavraLida);
        }
    }
    fclose(arquivoEntrada);
    imprimirDicionario(palavras, frequencias, totalPalavrasUnicas);

    return 0; 
}

int lerProximaPalavra(FILE *arq, char *palavra){
    int ch;
    int i = 0;

    // Pula caracteres não alfabéticos
    while ((ch = fgetc(arq)) != EOF && !isalpha(ch));

    if (ch == EOF){ // quando ch for igual ao fim do arquivo (EOF)
        return 0; 
    }

    // Lê os caracteres alfabéticos, convertendo para minúsculo
    while(isalpha(ch)){
        if (i < TAMANHO_PALAVRA - 1){ 
            palavra[i] = tolower(ch); 
            i++;
        }
        ch = fgetc(arq); 
    }
    // Finaliza a string
    palavra[i] = '\0';

    return (i > 0);
}


int buscaBinariaRecursiva(char palavras[][TAMANHO_PALAVRA], const char *palavra, int inicio, int fim){
    if (inicio > fim){
        return -1; // Não encontrado
    }

    // Algoritmo de busca binária
    int meio = inicio + (fim - inicio) / 2;
    int comparacao = strcmp(palavra, palavras[meio]);

    if (comparacao == 0){
        return meio; // Encontrado
    } 
    else if (comparacao < 0){
        return buscaBinariaRecursiva(palavras, palavra, inicio, meio - 1); // Busca na esquerda
    } 
    else {
        return buscaBinariaRecursiva(palavras, palavra, meio + 1, fim); // Busca na direita
    }
}

void inserirOrdenado(char palavras[][TAMANHO_PALAVRA], int frequencias[], int *totalPalavrasUnicas, const char *palavra){
    int i = 0;
    
    // Encontra a posição correta (i)
    while (i < *totalPalavrasUnicas && strcmp(palavra, palavras[i]) > 0) {
        i++;
    }

    // Desloca (shift) todos os elementos de 'i' em diante para a direita
    // Devemos deslocar AMBOS os vetores (palavras e frequências)
    for (int j = *totalPalavrasUnicas; j > i; j--) {
        // Desloca a palavra (string)
        strcpy(palavras[j], palavras[j - 1]);
        
        // Desloca a frequência (inteiro)
        frequencias[j] = frequencias[j - 1]; 
    }

    // Insere a nova palavra e frequência na posição 'i'
    strcpy(palavras[i], palavra);
    frequencias[i] = 1; 

    // Incrementa o contador
    (*totalPalavrasUnicas)++;
}

void imprimirDicionario(char palavras[][TAMANHO_PALAVRA], int frequencias[], int totalPalavrasUnicas) {
    // Imprime a lista de palavras e frequências
    for (int i = 0; i < totalPalavrasUnicas; i++) {
        // Formato: "palavra, ocorrencias"
        printf("%s, %d\n", palavras[i], frequencias[i]);
    }

    // Imprime o total de palavras diferentes
    printf("total de palavras diferentes no dicionario = %d\n", totalPalavrasUnicas);

}
