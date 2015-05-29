#include <stdio.h>
#include <stdlib.h>

typedef struct tipoNo{
    int dado;
    char cor;
    struct tipoNo *noEsquerdo;
    struct tipoNo *noDireito;
}tipoNo;

typedef struct tipoArvore{
    tipoNo *topo;
}tipoArvore;

void criarArvore(tipoArvore *arvore){
    arvore->topo = NULL;
}

void inserirElemento(int numero, tipoNo *raiz){
}

void inserirArvore(int numero, tipoArvore* arvore){
    arvore->topo = inserirElemento(numero, arvore->topo);
}

tipoNo* buscarElemento(int numero, tipoNo *raiz){
}

tipoNo* buscarNaArvore(int numero, tipoArvore arvore){
    return buscarElemento(numero, arvore.topo);
}

tipoNo* removerElemento(int numero, tipoNo *raiz){
}

void removerDaArvore(int numero, tipoArvore *arvore){
    arvore->topo = removerElemento(numero, arvore->topo);
}

void lerArquivo(tipoArvore *arvore, char *nomeArquivo){
    FILE *arquivo;
    int valor;
    arquivo = fopen(nomeArquivo, "r");
    if(arquivo == 0){
        printf("\nNao existe o arquivo na pasta do programa.\n\n");
    } else {
        while((fscanf(arquivo,"%d",&valor) != EOF)){
            inserirArvore(valor, arvore);
        }
        printf("\nOs elementos do arquivo foram inseridos na arvore com sucesso.\n\n");
    }
    fclose(arquivo);
}

int main(){

}
