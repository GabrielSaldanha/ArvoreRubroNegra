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


tipoNo* rotacaoEsquerdaR(tipoNo** raiz, tipoNo* n){
    tipoNo *avo;
    tipoNo *aux;

    avo = noAvo(n);

    if(n->noPai == NULL){
        return *raiz;
    }

    if(n->noPai->noPai == NULL){
        aux = *raiz;

        if(aux->noEsquerdo == n){
            *raiz = n;
            if(n->noDireito == NULL){
                aux->noPai = n;
                n->noDireito = aux;
            }
            else{
                aux->noEsquerdo = n->noDireito;
                aux->noEsquerdo->noPai = aux;
                aux->noPai = n;
                n->noDireito = aux;
            }
        }

        else{
            *raiz = n;
            if(n->noEsquerdo == NULL){
                aux->noPai = n;
                n->noEsquerdo = aux;
            }

            else{
                aux->noDireito = n->noEsquerdo;
                aux->noDireito->noPai = aux;
                aux->noPai = n;
                n->noEsquerdo = aux;
            }
        }

        n->noPai = NULL;
        return *raiz;
    }

    if((n->noPai == avo->noDireito) && (n == n->noPai->noDireito)){
        aux = n->noPai;
        avo->noDireito = n;
        aux->noDireito = n->noEsquerdo;
        n->noEsquerdo = aux;
        aux->noDireito->noPai = aux;
        aux->noPai = n;
    }
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

    else if(n == n->noPai->noDireito && n->noPai == noAvo(n)->noDireito){       /// Correcao aqui, estava "!=" e "||".
        raiz = rotacaoEsquerda(raiz, noAvo(n));
    }

    return raiz;
}

tipoNo* balanceamentoCaso4(tipoNo* raiz, tipoNo* n){
    if(n == n->noPai->noDireito && n->noPai == noAvo(n)->noEsquerdo){      // A primeira comparacao de n estava "n == n->noPai->noEsq" !!!!!
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

tipoNo* verificaVermelho(tipoNo *n, tipoNo *raiz){
    if(raiz == NULL){
        return raiz;
    }

    if((n->noPai == raiz) && (verificaCor(raiz) == RUB)){
        raiz->cor = NEG;
    }

    if(verificaCor(raiz) == RUB){
        if(verificaCor(raiz->noEsquerdo) == RUB){
            raiz->noEsquerdo->cor = NEG;
        }

        if(verificaCor(raiz->noDireito) == RUB){
            raiz->noDireito->cor = NEG;
        }
    }

    verificaVermelho(n, raiz->noEsquerdo);
    verificaVermelho(n, raiz->noDireito);

    return raiz;
}

/*int verificaPretos(tipoNo *raiz){
    int preto = 0,noEsquerdo, noDireito;

    if(verificaCor(raiz) == NEG){
        if(raiz == NULL){
            return preto + 1;
        }
        else{
            preto++;
        }
    }

    noEsquerdo = verificaPretos(raiz->noEsquerdo);
    noDireito = verificaPretos(raiz->noDireito);

    if(noEsquerdo == noDireito){
        return 0;
    }

    else if(noEsquerdo < noDireito){
        return -1;
    }

    else{
        return 1;
    }
}*/

/*tipoNo* verificaCores(tipoNo *aux, tipoNo *raiz){
    tipoNo* aux;

    int qntpretos;

    //raiz = verificaVermelho(aux,raiz);

    Qntpretos = verificaPretos(raiz);

    if(Qntpretos == 0){
        return raiz;
    }

    else if(Qntpretos == -1){
        rotacaoEsquerda(raiz, aux);
    }

    else{
        rotacaoDireta(raiz, aux);
    }
}*/

tipoNo* removeSemiFolhaPreta(tipoNo *aux, tipoNo *raiz){
    tipoNo *irmao;
    tipoNo *pai;
    tipoNo *avo;
    tipoNo *tio;

    pai = aux->noPai;

    if(pai == NULL){
        free(aux);
        return NULL;
    }

    if(verificaCor(pai) == RUB){
        pai->cor = NEG;

        irmao = noIrmao(aux);

        if(irmao == NULL){
            if(pai->noEsquerdo != NULL && pai->noEsquerdo->dado == aux->dado){
                pai->noEsquerdo = NULL;
                free(aux);
                return raiz;
            }
            else{
                pai->noDireito = NULL;
                free(aux);
                return raiz;
            }
        }

        irmao->cor = RUB;

        //verificaCores(irmao);

        if(pai->noEsquerdo != NULL && pai->noEsquerdo->dado == aux->dado){
            pai->noEsquerdo = NULL;
            free(aux);
            return raiz;
        }
        else{
            pai->noDireito = NULL;
            free(aux);
            return raiz;
        }
    }

    if(verificaCor(aux->noPai) == NEG){
        irmao = noIrmao(aux);

        if(irmao == NULL){
            if(pai->noEsquerdo != NULL && pai->noEsquerdo->dado == aux->dado){
                pai->noEsquerdo = NULL;
                free(aux);
                return raiz;
            }
            else{
                pai->noDireito = NULL;
                free(aux);
                return raiz;
            }
        }

        irmao->cor = RUB;

        rotacaoEsquerdaR(&raiz, irmao);

        //verificaCores(irmao);

        avo = noAvo(aux);
        if(avo == NULL){
            if(pai->noEsquerdo != NULL && pai->noEsquerdo->dado == aux->dado){
                pai->noEsquerdo = NULL;
                free(aux);
                return raiz;
            }
            else{
                pai->noDireito = NULL;
                free(aux);
                return raiz;
            }
        }

        avo->cor = NEG;

        tio = noTio(aux);

        if(tio == NULL){
            if(pai->noEsquerdo != NULL && pai->noEsquerdo->dado == aux->dado){
                pai->noEsquerdo = NULL;
                free(aux);
                return raiz;
            }
            else{
                pai->noDireito = NULL;
                free(aux);
                return raiz;
            }
        }

        tio->cor = RUB;

        irmao = noIrmao(aux);

        if(irmao == NULL){
            if(pai->noEsquerdo != NULL && pai->noEsquerdo->dado == aux->dado){
                pai->noEsquerdo = NULL;
                free(aux);
                return raiz;
            }
            else{
                pai->noDireito = NULL;
                free(aux);
                return raiz;
            }
        }

        //verificaCores(irmao);

        if(pai->noEsquerdo != NULL && pai->noEsquerdo->dado == aux->dado){
            pai->noEsquerdo = NULL;
            free(aux);
            return raiz;
        }
        else{
            pai->noDireito = NULL;
            free(aux);
            return raiz;
        }
    }
}

tipoNo* removePreto(tipoNo *aux,tipoNo *raiz);

tipoNo* removeDuploPreto(tipoNo *aux,tipoNo *raiz){
    tipoNo *M;
    tipoNo *pai;
    int auxDado;

    if(aux->noEsquerdo == NULL && aux->noDireito == NULL){
        return removeSemiFolhaPreta(aux,raiz);
    }

    M = maiorDosMenores(raiz);

    if(verificaCor(M) == RUB){
        auxDado = aux->dado;
        aux->dado = M->dado;
        M->dado = auxDado;

        pai = M->noPai;

        pai->noDireito = NULL;

        free(M);
        return raiz;
    }

    M = menorDosMaiores(raiz);

    if(verificaCor(M) == RUB){
        auxDado = aux->dado;
        aux->dado = M->dado;
        M->dado = auxDado;

        pai = M->noPai;

        pai->noEsquerdo = NULL;

        free(M);
        return raiz;
    }

    if(M == NULL && aux->noPai == NULL){
        auxDado = aux->noEsquerdo->dado;
        aux->noEsquerdo->dado = raiz->dado;
        raiz->dado = auxDado;
        raiz->noEsquerdo = NULL;
        free(aux->noEsquerdo);
        return raiz;
    }

    auxDado = aux->dado;
    aux->dado = M->dado;
    M->dado = auxDado;
    return removePreto(M,raiz);
}

tipoNo* removeVermelho(tipoNo *aux,tipoNo *raiz);

tipoNo* removePreto(tipoNo *aux, tipoNo *raiz){
    int auxDado;

    if(verificaCor(aux->noEsquerdo) == NEG && verificaCor(aux->noDireito) == NEG){
        return removeDuploPreto(aux,raiz);
    }

    if(verificaCor(aux->noEsquerdo) == RUB){
        auxDado = aux->noEsquerdo->dado;
        aux->noEsquerdo->dado = aux->dado;
        aux->dado = auxDado;

        return removeVermelho(aux->noEsquerdo,raiz);
    }

    auxDado = aux->noDireito->dado;
    aux->noDireito->dado = aux->dado;
    aux->dado = auxDado;
    return removeVermelho(aux->noDireito,raiz);
}


tipoNo* removeVermelho(tipoNo *aux,tipoNo *raiz){
    tipoNo *pai;
    tipoNo *M;

    int auxDado;

    if(aux->noEsquerdo == NULL && aux->noDireito == NULL){
        pai = aux->noPai;

        if(pai->noEsquerdo != NULL && pai->noEsquerdo->dado == aux->dado){
            pai->noEsquerdo = NULL;
            free(aux);
            return raiz;
        }
        else{
            pai->noDireito = NULL;
            free(aux);
            return raiz;
        }
    }

    M = maiorDosMenores(raiz);

    if(verificaCor(M) == RUB){
        auxDado = aux->dado;
        aux->dado = M->dado;
        M->dado = auxDado;

        pai = M->noPai;

        pai->noDireito = NULL;

        free(M);
        return raiz;
    }

    M = menorDosMaiores(raiz);

    if(verificaCor(M) == RUB){
        auxDado = aux->dado;
        aux->dado = M->dado;
        M->dado = auxDado;

        pai = M->noPai;

        pai->noEsquerdo = NULL;

        free(M);
        return raiz;
    }

    auxDado = aux->dado;
    aux->dado = M->dado;
    M->dado = auxDado;
    return removePreto(M,raiz);
}

tipoNo* removerElemento(int numero, tipoNo *raiz){
    tipoNo *aux;

    aux = buscarElemento(numero,raiz);

    if(verificaCor(aux) == RUB){
        return removeVermelho(aux,raiz);
    }

    else{
        return removePreto(aux,raiz);
    }

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
    int i, esquerda, direita, tamanhoNo = 7; //tamanhoNo: tamanho do nó que será impresso. No caso, um inteiro de 4 posiçoes + parênteses

    if (!raiz) return 0;

    sprintf(strAux, "(%05d)", raiz->dado);

    if(raiz->cor == RUB){
        printf("Dado: %d, Cor: Vermelho\n", raiz->dado);
    }
    else{
        printf("Dado: %d, Cor: Preto\n", raiz->dado);
    }

    if(raiz->noPai == NULL){
        printf("%d nao tem pai\n", raiz->dado);
    }

    else{
        printf("%d e filho de %d\n",raiz->dado,raiz->noPai->dado);
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

    return 0;
}
