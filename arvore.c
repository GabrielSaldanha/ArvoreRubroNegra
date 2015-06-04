#include <stdio.h>
#include <stdlib.h>
#define N_MAX 1027

typedef struct tipoNo{
    int dado;
    char cor;
    struct tipoNo *noEsquerdo;
    struct tipoNo *noDireito;
}tipoNo;

typedef struct tipoArvore{
    tipoNo *topo;
}tipoArvore;

tipoArvore arvore;

void criarArvore(tipoArvore *arvore){
    arvore->topo = NULL;
}

tipoNo* buscarPai(int numero, tipoNo *raiz){
    tipoNo *aux;

    if(raiz == NULL){
        return NULL;
    }

    if(raiz->noEsquerdo == NULL && raiz->noDireito == NULL){
        return NULL;
    }

    else if((raiz->noEsquerdo != NULL) && (raiz->noEsquerdo->dado == numero)){
        return raiz;
    }

    else if((raiz->noDireito != NULL) && (raiz->noDireito->dado == numero)){
        return raiz;
    }

    else{
        aux = buscarPai(numero,raiz->noEsquerdo);
        if(aux==NULL){
            aux = buscarPai(numero,raiz->noDireito);
        }
        return aux;
    }
}

tipoNo* buscarAvo(int numero, tipoNo *raiz){
    tipoNo *pai;

    pai = buscarPai(numero,raiz);

    if(pai == NULL){
        return NULL;
    }
    else{
        return buscarPai(pai->dado, raiz);
    }
}

tipoNo* buscarTio(int numero, tipoNo *raiz){
    tipoNo *avo;
    int pai;

    avo = buscarAvo(numero, raiz);

    if(avo == NULL){
        return NULL;
    }

    else{
        if(avo->noEsquerdo == NULL || avo->noDireito == NULL){
            return NULL;
        }
        else{
            pai = (buscarPai(numero, raiz)->dado);
            if(avo->noEsquerdo->dado == pai){
                return avo->noDireito;
            }
            if(avo->noDireito->dado == pai){
                return avo->noEsquerdo;
            }
        }
    }
}

tipoNo* balancearCor(tipoNo *raiz){
}

tipoNo* inserirElemento(int numero, tipoNo *raiz){
    if(raiz == NULL){
        tipoNo *aux;
        aux = (tipoNo *) malloc (sizeof(tipoNo));
        aux->dado = numero;
        aux->cor = 'V';
        aux->noEsquerdo = NULL;
        aux->noDireito = NULL;
        raiz = aux;
    }
    if(numero < raiz->dado){
        raiz->noEsquerdo = inserirElemento(numero, raiz->noEsquerdo);
    }
    else if (numero > raiz->dado){
        raiz->noDireito = inserirElemento(numero, raiz->noDireito);
    }
    //return balancearCor(raiz);
    return raiz;
}

void inserirArvore(int numero, tipoArvore* arvore){
    arvore->topo = inserirElemento(numero, arvore->topo);
}

tipoNo* buscarElemento(int numero, tipoNo *raiz){
    if(raiz == NULL){
        return NULL;
    }
    if (numero < raiz->dado){
        return buscarElemento(numero, raiz->noEsquerdo);
    }
    if(numero > raiz->dado){
        return buscarElemento(numero,raiz->noDireito);
    }
    return raiz;
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

int maior(int numeroA, int numeroB){
    if(numeroA > numeroB){
        return numeroA;
    }
    else {
        return numeroB;
    }
}

int calculaAltura(tipoNo *raiz){
    if(raiz == NULL){
        return 0;
    }
    else {
        return (maior(calculaAltura(raiz->noEsquerdo),calculaAltura(raiz->noDireito)) + 1);
    }
}

int imprimirArvoreInterno(tipoNo *raiz, int e_esquerda, int distancia, int nivelAtual, int alt, char str[][N_MAX*7]){
    char strAux[alt];
    int i, esquerda, direita, tamanhoNo = 7; //tamanhoNo: tamanho do nó que será impresso. No caso, um inteiro de 4 posiçoes + parênteses

    if (!raiz) return 0;

    sprintf(strAux, "(%05d)", raiz->dado);

      esquerda  = imprimirArvoreInterno(raiz->noEsquerdo,  1, distancia, nivelAtual + 1, alt, str);
      direita = imprimirArvoreInterno(raiz->noDireito, 0, distancia + esquerda + tamanhoNo, nivelAtual + 1, alt, str);

    for (i = 0; i < tamanhoNo; i++)
        str[nivelAtual][distancia + esquerda + i] = strAux[i];

    if (nivelAtual && e_esquerda) {

        for (i = 0; i < tamanhoNo + direita; i++)
            str[nivelAtual - 1][distancia + esquerda + tamanhoNo/2 + i] = '-';

        str[nivelAtual - 1][distancia + esquerda + tamanhoNo/2] = '.';

    } else if (nivelAtual && !e_esquerda) {

        for (i = 0; i < esquerda + tamanhoNo; i++)
            str[nivelAtual - 1][distancia - tamanhoNo/2 + i] = '-';

        str[nivelAtual - 1][distancia + esquerda + tamanhoNo/2] = '.';
    }

    return esquerda + tamanhoNo + direita;
}

int imprimirArvore(tipoNo *raiz){
    int i, alt = calculaAltura(raiz);
    char string[alt][N_MAX*7];

    for (i = 0; i < alt; i++)
        sprintf(string[i], "%80s", " ");

    imprimirArvoreInterno(raiz, 0, 0, 0, alt, string);

    for (i = 0; i < alt; i++)
        printf("%s\n", string[i]);
}

void imprimirOpcoes(int menu){

    if(menu == 0){
        printf("\n***************************** ARVORE RUBRO-NEGRA *****************************\n");
        printf("\nEscolha a opcao que gostaria de utilizar:\n");
        printf("1 - Inserir elementos na arvore.\n");
        printf("2 - Remover elementos na arvore.\n");
        printf("3 - Imprimir elementos da arvore.\n");
        printf("4 - Buscar um elemento na arvore.\n");
        printf("0 - Sair do programa.\n\n");
        printf("Opcao: ");
    }

    if(menu == 1){
        printf("\nInserir elementos na:\n");
        printf("1 - Arvore\n");
    }

    if(menu == 2){
        printf("\nRemover elemento da:\n")/
        printf("1 - Arvore\n");
    }
    if(menu == 3){
        printf("\nImprimir:\n");
        printf("1 - Arvore\n");
    }
    if(menu == 4){
        printf("\nBuscar elemento na:\n");
        printf("1 - Arvore\n");
    }
}

void menuInsercaoArvore(){
    int opcao = -1;
    char nomeDoArquivo[12];
    imprimirOpcoes(1);
    scanf("%d", &opcao);
    switch(opcao){
        case 1:
            printf("\nColoque o nome do arquivo para a insercao de elementos na arvore:\nO arquivo deve ter no maximo 12 caracteres no nome\n");
            scanf("%s", nomeDoArquivo);
            lerArquivo(&arvore, nomeDoArquivo);
            break;
        default:
            printf("Opcao Invalida.\n");
    }
}

void menuRemocaoArvore(){
    tipoNo *aux;
    int opcao = -1;
    int elemento;
    imprimirOpcoes(2);
    scanf("%d", &opcao);
    switch(opcao){
        case 1:
            printf("\nEscolha um elemento para remover da arvore: ");
            scanf("%d", &elemento);
            aux = buscarNaArvore(elemento, arvore);
            if(aux){
                removerDaArvore(elemento, &arvore);
                printf("\nSucesso. O elemento foi removido.\n");
            } else printf("\nEste elemento nao esta na arvore.\n");
            break;
        default:
            printf("Opcao Invalida.\n\n");
    }
}

void menuImpressaoArvore(){
    int opcao;
    imprimirOpcoes(3);
    scanf("%d", &opcao);
    switch(opcao){
        case 1:
            if(arvore.topo == NULL){
                printf("Arvore vazia!\n");
            }
            else {
                imprimirArvore(arvore.topo);
            }
            break;
        default:
            printf("Opcao Invalida\n\n");
    }
}

void menuBuscaArvore(){
    int opcao;
    int elemento;
    tipoNo *aux;
    imprimirOpcoes(4);
    scanf("%d", &opcao);
    switch(opcao){
        case 1:
            printf("\nEscolha um elemento para buscar: ");
            scanf("%d", &elemento);
            aux = buscarNaArvore(elemento, arvore);
            if(aux){
                printf("\nElemento encontrado!\n");
            }
            else {
                printf("\nElemento nao encontrado!\n");
            }
            break;
        default:
            printf("Opcao invalida.\n\n");
            break;
    }
}

void menuInicial(){

    int opcao = -1;
    while(opcao != 0){
        imprimirOpcoes(0);
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                menuInsercaoArvore();
                break;
            case 2:
                menuRemocaoArvore();
                break;
            case 3:
                menuImpressaoArvore();
                break;
            case 4:
                menuBuscaArvore();
                break;
            case 0:
                break;
        }
    }
}

int main(){

    criarArvore(&arvore);
    menuInicial();
}
