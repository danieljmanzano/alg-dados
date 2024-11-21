#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "ABB.h"

#define FILHO_ESQ 0
#define FILHO_DIR 1

typedef struct no_{
    struct no_ *esq, *dir;
    ITEM *chave;
}NO;

typedef struct abb{
    NO *raiz;
    int profundidade, tam; //acrescentei o 'tam' no campo da struct pra facilitar algumas operações. originalmente nao tem no do rudinei
}ABB;
 
ABB *abb_criar(void){
    ABB *t = malloc(sizeof(ABB));
    if(t != NULL){
        t->profundidade = -1; //uma ABB inicializada ainda nao tem nenhum nó, o que faz dela ter profundidade -1
        t->raiz = NULL;
        t->tam = 0;
    }
    return t;
}

NO *no_criar(ITEM *item){
    NO *no = malloc(sizeof(NO));
    if(!no) return NULL;

    no->chave = item;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

int altura(NO *no){ 
    if(!no) return -1;
    
    int alt_esq = altura(no->esq);
    int alt_dir = altura(no->dir);
    
    return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir); //vai pegar a maior altura (altura da maior subABB) com essa condiçao
}

int abb_profundidade(NO *no){ //serve pra ver de subABBs tambem, só passar o nó que quiser analisar
    if(!no) return -1;
    int e = abb_profundidade(no->esq);
    int d = abb_profundidade(no->dir);
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
    NO *subABBTransferida = novaRaiz->dir;

    novaRaiz->dir = desbalanceado;
    desbalanceado->esq = subABBTransferida;

    return novaRaiz;
}

NO* rotacaoEsquerda(NO *desbalanceado){
    NO *novaRaiz = desbalanceado->dir;
    NO *subABBTransferida = novaRaiz->esq;

    novaRaiz->esq = desbalanceado;
    desbalanceado->dir = subABBTransferida;

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
NO *abb_inserir_no(NO *raiz, NO *novo_no) { 
    if(!raiz)
        return novo_no; //chegou às folhas: local de inserção

    else if(item_get_chave(novo_no->chave) < item_get_chave(raiz->chave))
        raiz->esq = abb_inserir_no(raiz->esq, novo_no);

    else if(item_get_chave(novo_no->chave) > item_get_chave(raiz->chave))
        raiz->dir = abb_inserir_no(raiz->dir, novo_no);
    
    //return balancear(raiz);
    return raiz;
}

bool abb_inserir(ABB *t, ITEM *item){
    if(!t) return false;

    NO *novo_no = no_criar(item);
    if(!novo_no) return false;

    t->raiz = abb_inserir_no(t->raiz, novo_no);
    t->tam++;
    return true;
}
/*--------------*/

/*funções juntas*/
NO* acha_menor_valor(NO* no){ //função auxiliar pra achar menor valor presente numa subABB
    NO* atual = no;
    while(atual && atual->esq != NULL)
        atual = atual->esq;

    return atual;
}

NO* abb_remover_no(NO *raiz, int chave){
    if(!raiz)
        return raiz;
    
    if(chave < item_get_chave(raiz->chave))
        raiz->esq = abb_remover_no(raiz->esq, chave);
    else if(chave > item_get_chave(raiz->chave))
        raiz->dir = abb_remover_no(raiz->dir, chave);
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
        raiz->dir = abb_remover_no(raiz->dir, item_get_chave(temp->chave));
    }
    
    if(!raiz) //pra caso em que a ABB tinha só um nó (nao precisa balancear ali embaixo)
        return raiz;
    
    return balancear(raiz); //rebalancear em função do nó atual
}

bool abb_remover(ABB *t, int chave) {
    if (!t || !t->raiz) return false;
    t->raiz = abb_remover_no(t->raiz, chave);
    t->tam--;
    return true;
}
/*--------------*/


void verificar_altura(NO *raiz){ //função pra debugar, show da bola
    if(raiz == NULL) return;
    
    printf("nó %d: altura = %d, fb = %d\n", item_get_chave(raiz->chave), altura(raiz), fatorBalanceamento(raiz));
    
    verificar_altura(raiz->esq);
    verificar_altura(raiz->dir);
}


/*funçoes juntas*/
void apagar_abb(NO **raiz){
    if(*raiz != NULL){
        apagar_abb(&(*raiz)->esq);
        apagar_abb(&(*raiz)->dir);
        free(*raiz);
        *raiz = NULL;
    }

    return;
}

void abb_apagar(ABB **t){ //só pra nao confundir, essa é a funçao que o usuario tem acesso. a de cima é auxiliar
    apagar_abb(&(*t)->raiz);
    free(*t);
    *t = NULL;
    return;
}
/*--------------*/


/*funçoes juntas*/
void imprimir_em_ordem(NO *raiz){ 
    if(raiz != NULL){
        imprimir_em_ordem(raiz->esq);
        printf("%d ", item_get_chave(raiz->chave));
        imprimir_em_ordem(raiz->dir);
    }
    return;
}

void abb_imprimir(ABB *t){
    if(!t){
        printf("Árvore nula!\n");
        return;
    }

    imprimir_em_ordem(t->raiz);
}
/*--------------*/

bool percorre_balanceamento(NO *no){
    if(!no) return true;

    int fb = fatorBalanceamento(no);
    if (fb > 1 || fb < -1) {
        return false;
    }
    
    //printf("no: %d, fb: %d\n", item_get_chave(no->chave), fb);
    
    bool esq_balanceada = percorre_balanceamento(no->esq);
    bool dir_balanceada = percorre_balanceamento(no->dir);

    return esq_balanceada && dir_balanceada;

}

bool abb_perfeitamente_balanceada(ABB *T){
    if(!T) return true;
    return !percorre_balanceamento(T->raiz);
}

