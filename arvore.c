#include <stdio.h>
#include <stdlib.h>
#define RUB 0
#define NEG 1
#define N_MAX 1027

typedef struct tipoNo{
    int dado;
    char cor;
    struct tipoNo *noPai;
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

tipoNo* noAvo(tipoNo *n){
    if(n == NULL){
        return NULL;
    }

    if(n->noPai == NULL){
        return NULL;
    }

    else{
        return n->noPai->noPai;
    }
}

tipoNo* noIrmao(tipoNo *n){
    if(n == NULL){
        return NULL;
    }

    if(n->noPai == NULL){
        return NULL;
    }

    if(n == n->noPai->noEsquerdo){
        return n->noPai->noDireito;
    }

    else{
        return n->noPai->noEsquerdo;
    }
}

tipoNo* noTio(tipoNo *n){
    if(n == NULL){
        return NULL;
    }

    return noIrmao(n->noPai);
}


tipoNo* rotacaoEsquerda(tipoNo* raiz, tipoNo* n){
    tipoNo* r = n->noDireito;

    if(n == NULL){
        return raiz;
    }

    if(raiz == n){
        raiz = r;
    }

    else if(n == n->noPai->noEsquerdo){
        n->noPai->noEsquerdo = r;
    }

    else{
        n->noPai->noDireito = r;
    }

    n->noDireito = r->noEsquerdo;

    if(r->noEsquerdo != NULL){
        r->noEsquerdo->noPai = n;
    }

    r->noEsquerdo = n;
    r->noPai = n->noPai;
    n->noPai = r;

    return raiz;
}

void rotacaoEsquerdaRR(tipoNo **x){

    tipoNo *y;
    y = *x;
    *x = (*x)->noDireito;
    (*x)->noPai = y->noPai;
    y->noDireito = (*x)->noEsquerdo;
    if(y->noDireito)    y->noDireito->noPai = y;
    (*x)->noEsquerdo = y;
    y->noPai = *x;

}


tipoNo* rotacaoDireita(tipoNo* raiz, tipoNo* n){
    tipoNo* l = n->noEsquerdo;

    if(n == NULL){
        return raiz;
    }

    if(raiz == n){
        raiz = l;
    }

    else if(n == n->noPai->noEsquerdo){
        n->noPai->noEsquerdo = l;
    }

    else{
        n->noPai->noDireito = l;
    }

    n->noEsquerdo = l->noDireito;

    if(l->noDireito != NULL){
        l->noDireito->noPai = n;
    }

    l->noDireito = n;
    l->noPai = n->noPai;
    n->noPai = l;

    return raiz;
}

void rotacaoDireitaRR(tipoNo **x){
    tipoNo *y;
    y = *x;
    *x = (*x)->noEsquerdo;
    (*x)->noPai = y->noPai;
    y->noEsquerdo = (*x)->noDireito;
    if(y->noEsquerdo)   y->noEsquerdo->noPai = y;
    (*x)->noDireito = y;
    y->noPai = *x;
}

int verificaCor(tipoNo* n){
    if(n == NULL){
        return NEG;
    }

    else{
        return n->cor;
    }
}

tipoNo* balanceamentoCaso5(tipoNo* raiz, tipoNo* n){
    n->noPai->cor = NEG;
    noAvo(n)->cor = RUB;

    if(n == n->noPai->noEsquerdo && n->noPai == noAvo(n)->noEsquerdo){
        raiz = rotacaoDireita(raiz, noAvo(n));
    }

    else if(n == n->noPai->noDireito && n->noPai == noAvo(n)->noDireito){
        raiz = rotacaoEsquerda(raiz, noAvo(n));
    }

    return raiz;
}

tipoNo* balanceamentoCaso4(tipoNo* raiz, tipoNo* n){
    if(n == n->noPai->noDireito && n->noPai == noAvo(n)->noEsquerdo){
        raiz = rotacaoEsquerda(raiz, n->noPai);
        n = n->noEsquerdo;
    }

    else if(n == n->noPai->noEsquerdo && n->noPai == noAvo(n)->noDireito){
        raiz = rotacaoDireita(raiz, n->noPai);
        n = n->noDireito;
    }

    return balanceamentoCaso5(raiz, n);
}

tipoNo* balanceamentoCaso1(tipoNo* raiz, tipoNo* n);

tipoNo* balanceamentoCaso3(tipoNo* raiz, tipoNo* n){
    if(verificaCor(noTio(n)) == RUB){
        n->noPai->cor = NEG;
        noTio(n)->cor = NEG;
        noAvo(n)->cor = RUB;
        return balanceamentoCaso1(raiz, noAvo(n));
    }

    else{
        return balanceamentoCaso4(raiz, n);
    }
}

tipoNo* balanceamentoCaso2(tipoNo* raiz, tipoNo* n){
    if(n->noPai->cor == NEG){
        return raiz;
    }

    else{
        return balanceamentoCaso3(raiz, n);
    }
}

tipoNo* balanceamentoCaso1(tipoNo* raiz, tipoNo* n){
    if(n->noPai == NULL){
        n->cor = NEG;
        return raiz;
    }

    else{
        return balanceamentoCaso2(raiz, n);
    }
}

tipoNo* noNovo(int dado){
    tipoNo* aux;

    aux = (tipoNo *) malloc (sizeof(tipoNo));
    aux->dado = dado;
    aux->cor = RUB;
    aux->noEsquerdo = NULL;
    aux->noDireito = NULL;
    aux->noPai = NULL;
    return aux;
}

tipoNo* inserirElemento(int numero, tipoNo *raiz){
    tipoNo* novo = noNovo(numero);

    if(raiz == NULL){
        novo->cor = NEG;
        return novo;
    }

    tipoNo* aux = raiz;

    while(1){
        if(novo->dado == aux->dado){
            free (novo);
            return raiz;
        }

        else if(novo->dado < aux->dado){
            if(aux->noEsquerdo == NULL){
                aux->noEsquerdo = novo;
                novo->noPai = aux;
                return balanceamentoCaso1(raiz, novo);
            }

            else{
                aux = aux->noEsquerdo;
            }
        }

        else {
            if (aux->noDireito == NULL){
                aux->noDireito = novo;
                novo->noPai = aux;
                return balanceamentoCaso1(raiz, novo);
            }

            else{
                aux = aux->noDireito;
            }
        }
    }
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

tipoNo* maiorDosMenores(tipoNo *raiz){
    tipoNo *aux;

    aux = raiz->noEsquerdo;

    if(aux == NULL){
        return NULL;
    }
    else{
        while (aux->noDireito != NULL){
            aux = aux->noDireito;
        }

    return aux;
    }
}

tipoNo* menorDosMaiores(tipoNo *raiz){
    tipoNo *aux;

    aux = raiz->noDireito;

    if(aux == NULL){
        return NULL;
    }
    else{
        while(aux->noEsquerdo != NULL){
            aux = aux->noEsquerdo;
        }
    return aux;
    }
}

tipoNo* conserta(tipoNo** raiz, tipoNo* no){
    tipoNo* aux;
    while((no != *raiz) && (verificaCor(no) == NEG)){
        if(no == no->noPai->noEsquerdo){
            aux = no->noPai->noDireito;

            if(verificaCor(aux) == RUB){
                aux->cor = NEG;
                no->noPai->cor = RUB;
                rotacaoEsquerdaRR(&no->noPai);
                aux = no->noPai->noDireito;
                continue;
            }

            if(verificaCor(aux->noEsquerdo) == NEG && verificaCor(aux->noDireito) == NEG){
                aux->cor = RUB;
                no = no->noPai;
                continue;
            }

            else if(verificaCor(aux->noDireito) == RUB){
                aux->noEsquerdo->cor = NEG;
                aux->cor = RUB;
                rotacaoDireitaRR(&aux);
                aux = aux->noPai->noDireito;
                continue;
            }
            aux->cor = no->noPai->cor;
            no->noPai->cor = NEG;
            aux->noDireito->cor = NEG;
            rotacaoEsquerdaRR(&no->noPai);
            no = *raiz;
        }

        else{
            aux = no->noPai->noEsquerdo;

            if(verificaCor(aux) == RUB){
                aux->cor = NEG;
                no->noPai->cor = RUB;
                rotacaoDireitaRR(&no->noPai);
                aux = no->noPai->noEsquerdo;
                continue;
            }

            if(verificaCor(aux->noEsquerdo) == NEG && verificaCor(aux->noDireito) == NEG){
                aux->cor = RUB;
                no = no->noPai;
                continue;
            }

            else if(verificaCor(aux->noEsquerdo) == RUB){
                aux->noDireito->cor = NEG;
                aux->cor = RUB;
                rotacaoEsquerdaRR(&aux);
                aux = aux->noPai->noEsquerdo;
                continue;
            }
            aux->cor = no->noPai->cor;
            no->noPai->cor = NEG;
            aux->noEsquerdo->cor = NEG;
            rotacaoDireitaRR(&no->noPai);
            no = *raiz;
        }
    }

    if(no != NULL){
        no->cor = NEG;
    }
    return *raiz;
}

tipoNo* transplante(tipoNo **raiz, tipoNo* no,tipoNo* noAux){
    if(no->noPai == NULL){
        *raiz = noAux;
    }

    else if(no == no->noPai->noEsquerdo){
        no->noPai->noEsquerdo = noAux;
    }

    else{
        no->noPai->noDireito = noAux;
    }

    if(noAux == NULL){
        return *raiz;
    }
    else{
        noAux->noPai = no->noPai;
        return *raiz;
    }
}

tipoNo* removerElemento(int numero, tipoNo *raiz){
    tipoNo *no;
    tipoNo *aux;
    tipoNo *M;

    int auxCor;

    no = buscarElemento(numero, raiz);

    if(raiz == NULL || no == NULL){
        return raiz;
    }

    auxCor = no->cor;

    if(no->noEsquerdo == NULL){
        aux = no->noDireito;
        transplante(&raiz,no, no->noDireito);
    }

    else if(no->noDireito == NULL){
        aux = no->noEsquerdo;
        transplante(&raiz, no, no->noEsquerdo);
    }

    else{
        M = menorDosMaiores(no);
        auxCor = M->cor;
        aux = M->noDireito;

        if(M->noPai == no){
            if(aux != NULL){
                aux->noPai = M;
            }
        }

        else{
            transplante(&raiz, M, M->noDireito);
            M->noDireito = no->noDireito;
            M->noDireito->noPai = M;
        }

        transplante(&raiz, no, M);
        M->noEsquerdo = no->noEsquerdo;
        M->noEsquerdo->noPai = M;
        M->cor = no->cor;
    }

    if(auxCor == NEG){
        if(aux!= NULL){
            conserta(&raiz, aux);
        }
    }

    free(no);

    return raiz;
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
    }

    else {
        while((fscanf(arquivo,"%d",&valor) != EOF)){
            inserirArvore(valor, arvore);
        }
        printf("\nOs elementos do arquivo foram inseridos na arvore com sucesso.\n\n");
    }
    //fclose(arquivo);
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
    int i, esquerda, direita, tamanhoNo = 7;

    if (!raiz) return 0;

    if(raiz->cor == RUB){
        sprintf(strAux,"%04d(V)",raiz->dado);
    }

    else{
        sprintf(strAux,"%04d(P)",raiz->dado);
    }

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

void imprimirArvore(tipoNo *raiz){
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
        printf("\nRemover elemento da:\n");
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
    tipoNo* aux;
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
        default:
            printf("Opcao invalida.\n\n");
        }
    }
}

int main(){

    criarArvore(&arvore);
    menuInicial();

    return 0;
}
