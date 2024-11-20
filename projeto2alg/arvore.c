#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

#define FILHO_ESQ 0
#define FILHO_DIR 1

typedef struct no_{
    struct no_ *esq, *dir;
    int chave;
}NO;

typedef struct arvore_{
    NO *raiz;
    int profundidade, tam; //acrescentei o 'tam' no campo da struct pra facilitar algumas operações. originalmente nao tem no do rudinei
}ARVORE;
 
ARVORE *arvore_criar(void){
    ARVORE *t = malloc(sizeof(ARVORE));
    if(t != NULL){
        t->profundidade = -1; //uma arvore inicializada ainda nao tem nenhum nó, o que faz dela ter profundidade -1
        t->raiz = NULL;
        t->tam = 0;
    }
    return t;
}

NO *no_criar(int chave){
    NO *no = malloc(sizeof(NO));
    if(!no) return NULL;

    no->chave = chave;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

int altura(NO *no){ 
    if(!no) return -1;
    
    int alt_esq = altura(no->esq);
    int alt_dir = altura(no->dir);
    
    return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir); //vai pegar a maior altura (altura da maior subarvore) com essa condiçao
}

int arvore_profundidade(NO *no){ //serve pra ver de subarvores tambem, só passar o nó que quiser analisar
    if(!no) return -1;
    int e = arvore_profundidade(no->esq);
    int d = arvore_profundidade(no->dir);
    return((e > d) ? e : d) + 1;
}

int fatorBalanceamento(NO *no){
    if(!no) return 0;
    return altura(no->esq) - altura(no->dir);
}

/*funçoes juntas*/
/*rotações simples e balanceamento*/
NO* rotacaoDireita(NO *desbalanceado){ 
    NO *novaRaiz = desbalanceado->esq;
    NO *subarvoreTransferida = novaRaiz->dir;

    novaRaiz->dir = desbalanceado;
    desbalanceado->esq = subarvoreTransferida;

    return novaRaiz;
}

NO* rotacaoEsquerda(NO *desbalanceado){
    NO *novaRaiz = desbalanceado->dir;
    NO *subarvoreTransferida = novaRaiz->esq;

    novaRaiz->esq = desbalanceado;
    desbalanceado->dir = subarvoreTransferida;

    return novaRaiz;
}

NO* balancear(NO *raiz){
    int balance = fatorBalanceamento(raiz);
    
    //rotaçao direita
    if(balance > 1 && fatorBalanceamento(raiz->esq) >= 0)
        return rotacaoDireita(raiz);
    
    //rotaçao esquerda
    if(balance < -1 && fatorBalanceamento(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);
    
    //rotaçao esquerda-direita (dupla)
    if(balance > 1 && fatorBalanceamento(raiz->esq) < 0){
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }
    
    //rotaçao direita-esquerda (dupla)
    if(balance < -1 && fatorBalanceamento(raiz->dir) > 0){
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }
    
    return raiz;
}
/*--------------*/


/*funçoes juntas*/
NO *arvore_inserir_no(NO *raiz, NO *novo_no) {
    if(!raiz)
        return novo_no; //chegou às folhas: local de inserção

    else if(novo_no->chave < raiz->chave)
        raiz->esq = arvore_inserir_no(raiz->esq, novo_no);

    else if(novo_no->chave > raiz->chave)
        raiz->dir = arvore_inserir_no(raiz->dir, novo_no);
    
    return balancear(raiz);
}

bool arvore_inserir(ARVORE *t, int chave){
    if(!t) return false;

    NO *novo_no = no_criar(chave);
    if(!novo_no) return false;

    t->raiz = arvore_inserir_no(t->raiz, novo_no);
    t->tam++;
    return true;
}
/*--------------*/

/*funções juntas*/
NO* acha_menor_valor(NO* no){ //função auxiliar pra achar menor valor presente numa subarvore
    NO* atual = no;
    while(atual && atual->esq != NULL)
        atual = atual->esq;

    return atual;
}

NO* arvore_remover_no(NO *raiz, int chave){
    if(!raiz)
        return raiz;
    
    if(chave < raiz->chave)
        raiz->esq = arvore_remover_no(raiz->esq, chave);
    else if(chave > raiz->chave)
        raiz->dir = arvore_remover_no(raiz->dir, chave);
    else{ //caso tenha achado o que é pra remover

        /*pra nó com um filho ou nenhum*/
        if(!raiz->esq){
            NO *temp = raiz->dir;
            free(raiz);
            return temp;
        }
        else if(!raiz->dir){
            NO *temp = raiz->esq;
            free(raiz);
            return temp;
        }
        
        /*pra nó com dois filhos*/
        NO *temp = acha_menor_valor(raiz->dir);
        raiz->chave = temp->chave;
        raiz->dir = arvore_remover_no(raiz->dir, temp->chave);
    }
    
    if(!raiz) //pra caso em que a arvore tinha só um nó (nao precisa balancear ali embaixo)
        return raiz;
    
    return balancear(raiz); //rebalancear em função do nó atual
}

bool arvore_remover(ARVORE *t, int chave) {
    if (!t || !t->raiz) return false;
    t->raiz = arvore_remover_no(t->raiz, chave);
    t->tam--;
    return true;
}
/*--------------*/


void verificar_altura(NO *raiz){ //função pra debugar, show da bola
    if(raiz == NULL) return;
    
    printf("nó %d: altura = %d, fb = %d\n", raiz->chave, altura(raiz), fatorBalanceamento(raiz));
    
    verificar_altura(raiz->esq);
    verificar_altura(raiz->dir);
}


/*funçoes juntas*/
void apagar_arvore(NO **raiz){
    if(*raiz != NULL){
        apagar_arvore(&(*raiz)->esq);
        apagar_arvore(&(*raiz)->dir);
        free(*raiz);
        *raiz = NULL;
    }

    return;
}

void arvore_apagar(ARVORE **t){ //só pra nao confundir, essa é a funçao que o usuario tem acesso. a de cima é auxiliar
    apagar_arvore(&(*t)->raiz);
    free(*t);
    *t = NULL;
    return;
}
/*--------------*/


/*funçoes juntas*/
void imprimir_em_ordem(NO *raiz){ 
    if(raiz != NULL){
        imprimir_em_ordem(raiz->esq);
        printf("%d ", raiz->chave);
        imprimir_em_ordem(raiz->dir);
    }
    return;
}

void arvore_imprimir(ARVORE *t){
    if(!t){
        printf("Árvore nula!\n");
        return;
    }

    imprimir_em_ordem(t->raiz);
}
/*--------------*/


bool buscabin(NO *raiz, int chave) {
    if(raiz == NULL) return false;
    
    if(chave == raiz->chave) return true;
    
    if(chave < raiz->chave)
        return buscabin(raiz->esq, chave);
    else
        return buscabin(raiz->dir, chave);
}

bool arvore_pertence(ARVORE *t, int chave){
    if(!t) return false;

    if(buscabin(t->raiz, chave))
        return true;

    else return false;
}


/*funçoes juntas*/
void copia_arvore(NO *raiz, ARVORE *nova_arvore){ //percorre uma arvore (parte da raiz aqui) e vai inserindo na outra em ordem
    if(!raiz) return;
    
    copia_arvore(raiz->esq, nova_arvore);
    arvore_inserir(nova_arvore, raiz->chave);
    copia_arvore(raiz->dir, nova_arvore);
}

ARVORE *arvore_uniao(ARVORE *t1, ARVORE *t2){
    if (!t1 && !t2) return NULL;

    ARVORE *nova_arvore = arvore_criar();
    if(!nova_arvore) return NULL;
    if(!t1){ //caso a t1 seja vazia, a união é só a segunda arvore
        copia_arvore(t2->raiz, nova_arvore);
        return nova_arvore;
    }
    if(!t2){ //mesma logica de cima
        copia_arvore(t1->raiz, nova_arvore);
        return nova_arvore;
    }

    //caso as duas existam, basicamente só vai copiar as duas na nova
    copia_arvore(t1->raiz, nova_arvore);
    copia_arvore(t2->raiz, nova_arvore);

    return nova_arvore;
}
/*--------------*/


/*funçoes juntas*/
void percorre_interseccao(NO *raiz, ARVORE *t2, ARVORE *nova_arvore){ //basicamente percorre em ordem uma arvore procurando se o nó atual ta em algum lugar na outra
    if(!raiz) return;
    
    percorre_interseccao(raiz->esq, t2, nova_arvore);
    
    if(arvore_pertence(t2, raiz->chave)) //ve se ta na segunda arvore
        arvore_inserir(nova_arvore, raiz->chave);
    
    percorre_interseccao(raiz->dir, t2, nova_arvore);
}

ARVORE *arvore_interseccao(ARVORE *t1, ARVORE *t2) {
    if(!t1 || !t2) return NULL;

    ARVORE *nova_arvore = arvore_criar();
    if(!nova_arvore) return NULL;

    percorre_interseccao(t1->raiz, t2, nova_arvore);

    return nova_arvore;
}
/*--------------*/


/*pra testar as operações aqui em baixo (depois vou tirar pq nao é pra ter main aqui né)*/
int main(void){
    ARVORE *arvore = arvore_criar();

    arvore_inserir(arvore, 8);
    arvore_remover(arvore, 8);
    arvore_inserir(arvore, 4);
    arvore_inserir(arvore, 2);
    arvore_inserir(arvore, 6);
    arvore_inserir(arvore, 10);
    arvore_inserir(arvore, 5);

    printf("Árvore em ordem: ");
    arvore_imprimir(arvore);
    printf("\n");
    verificar_altura(arvore->raiz);

    ARVORE *arvore2 = arvore_criar();
    arvore_inserir(arvore2, 2);
    arvore_remover(arvore2, 1);
    arvore_inserir(arvore2, 23);
    arvore_inserir(arvore2, 8);
    arvore_inserir(arvore2, 3);
    arvore_inserir(arvore2, 1);
    arvore_inserir(arvore2, 4);

    printf("Árvore em ordem: ");
    arvore_imprimir(arvore2);
    printf("\n");
    verificar_altura(arvore2->raiz);

    printf("uniao: ");
    ARVORE *uniao = arvore_uniao(arvore, arvore2);
    arvore_imprimir(uniao);
    printf("\n");
    verificar_altura(uniao->raiz);

    printf("intersecçao: ");
    ARVORE *inter = arvore_interseccao(arvore, arvore2);
    arvore_imprimir(inter);
    printf("\n");
    verificar_altura(inter->raiz);

    return 0;
}

/*pelo visto ta dando certo!!!!! graças a Deus!!!*/