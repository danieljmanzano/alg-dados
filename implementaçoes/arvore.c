#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

#define FILHO_ESQ 0
#define FILHO_DIR 1

typedef struct no_{
    struct no_ *esq, *dir;
    int chave, fb; //fb é o meu fator balanceamento do nó na arvore
}NO;

typedef struct arvore_{
    NO *raiz;
    int profundidade;
}ARVORE;
 
ARVORE *arvore_criar(void){
    ARVORE *t = malloc(sizeof(ARVORE));
    if(t != NULL){
        t->profundidade = -1; //uma arvore inicializada ainda nao tem nenhum nó, o que faz dela ter profundidade -1
        t->raiz = NULL;
    }
    return t;
}

NO *no_criar(int chave){
    NO *no = malloc(sizeof(NO));
    if(!no) return NULL;

    no->chave = chave;
    no->fb = 0;
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

/*funçoes juntas*/
/*rotações simples e balanceamento*/
NO *rotacaoDireita(NO *desbalanceado){ 
    NO *novaRaiz = desbalanceado->esq;
    desbalanceado->esq = novaRaiz->dir;
    novaRaiz->dir = desbalanceado;

    desbalanceado->fb = altura(desbalanceado->esq) - altura(desbalanceado->dir); //acerta o fator balanceamento novo
    novaRaiz->fb = altura(novaRaiz->esq) - altura(novaRaiz->dir);

    return novaRaiz;
}

NO *rotacaoEsquerda(NO *desbalanceado){ //mesma coisa de cima mas pra esquerda
    NO *novaRaiz = desbalanceado->dir;
    desbalanceado->dir = novaRaiz->esq;
    novaRaiz->esq = desbalanceado;

    desbalanceado->fb = altura(desbalanceado->esq) - altura(desbalanceado->dir);
    novaRaiz->fb = altura(novaRaiz->esq) - altura(novaRaiz->dir);

    return novaRaiz;
}

NO *balancear(NO *raiz){
    raiz->fb = altura(raiz->esq) - altura(raiz->dir);
    
    if(raiz->fb > 1 && raiz->esq->fb >= 0) //roda direita
        return rotacaoDireita(raiz);
    
    if(raiz->fb < -1 && raiz->dir->fb <= 0) //roda esquerda
        return rotacaoEsquerda(raiz);
    
    if(raiz->fb > 1 && raiz->esq->fb < 0){ //roda esquerda direita
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }
    
    if(raiz->fb < -1 && raiz->dir->fb > 0){ //roda direita esquerda
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }
    
    return raiz;
} //talvez seja meio obvio pra onde roda, mas por desencargo de consciencia deixei anotado ali

/*--------------*/


/*funçoes juntas*/
NO *arvore_inserir_no(NO *raiz, NO *novo_no) {
    if(!raiz)
        return novo_no; //chegou às folhas: local de inserção

    else if(novo_no->chave < raiz->chave)
        raiz->esq = arvore_inserir_no(raiz->esq, novo_no);

    else if(novo_no->chave > raiz->chave)
        raiz->dir = arvore_inserir_no(raiz->dir, novo_no);

    raiz->fb = altura(raiz->esq) - altura(raiz->dir); //ja atualizo o fator balanceamento do nó
    return balancear(raiz);
}

bool arvore_inserir(ARVORE *t, int chave){
    if(!t) return false;

    NO *novo_no = no_criar(chave);
    if(!novo_no) return false;

    t->raiz = arvore_inserir_no(t->raiz, novo_no);
    return true;
}
/*--------------*/

/*funções juntas*/
NO *acha_menor_valor(NO* no){ //função auxiliar pra achar menor valor presente numa subarvore
    NO* atual = no;
    while(atual && atual->esq != NULL)
        atual = atual->esq;

    return atual;
}

NO *arvore_remover_no(NO *raiz, int chave){
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
    return true;
}
/*--------------*/


void verificar_altura(NO *raiz){ //função pra debugar, show da bola
    if(!raiz) return;
    
    printf("nó %d: altura = %d, fb = %d\n", raiz->chave, altura(raiz), raiz->fb);
    
    verificar_altura(raiz->esq);
    verificar_altura(raiz->dir);
} //teoricamente nao é pra usar em nenhum momento, mas é bom pra se der ruim aqui e eu tenho que ver (acontece bastante...)


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
    printf("\n");
    return;
}
/*--------------*/


bool buscabinT(NO *raiz, int chave) {
    if(!raiz) return false;
    
    if(chave == raiz->chave) return true;
    
    if(chave < raiz->chave)
        return buscabinT(raiz->esq, chave);
    else
        return buscabinT(raiz->dir, chave);
}

bool arvore_pertence(ARVORE *t, int chave){
    if(!t) return false;

    if(buscabinT(t->raiz, chave))
        return true;

    else return false;
}


/*funçoes juntas*/
void copia_arvore(NO *raiz, ARVORE *nova_arvore){ //percorre uma arvore (parte da raiz aqui) e vai inserindo na outra em ordem
    if(!raiz) return;
    
    copia_arvore(raiz->esq, nova_arvore);
    arvore_inserir(nova_arvore, raiz->chave); //como minha inserçao nao repete numero, posso só sair tacando tudo das duas que vai dar a uniao
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
    if(!t1 || !t2) return NULL; //se uma das duas é vazia, ja nao tem intersecçao

    ARVORE *nova_arvore = arvore_criar();
    if(!nova_arvore) return NULL;

    percorre_interseccao(t1->raiz, t2, nova_arvore);

    return nova_arvore;
}
/*--------------*/

/*funçoes juntas*/
int conta_no(NO *raiz){
    if(!raiz) return 0;

    return 1 + (conta_no(raiz->esq) + conta_no(raiz->dir));
}


int arvore_nos(ARVORE *t){ //retorna o numero de nós de uma arvore
    if(!t) return 0;

    return conta_no(t->raiz);
}
/*--------------*/

/*funçoes juntas*/
int soma_total(NO *raiz){ 
    if(!raiz) return 0;

    return (raiz->chave + soma_total(raiz->esq) + soma_total(raiz->dir));
}

int arvore_soma(ARVORE *t){ //soma os valores de todos os nós de uma arvore
    if(!t) return 0;

    return soma_total(t->raiz);
}
/*--------------*/

/*funçoes juntas*/
bool checa_fb(NO *no){
    if(!no) return true;
    if(no->fb != 0) return false;

    return (checa_fb(no->esq) && checa_fb(no->dir));
}

bool arvore_cc(ARVORE *t){ //ve se uma arvore é completa cheia
    if(!t) return false;

    return checa_fb(t->raiz);
}
/*--------------*/

/*pra testar as operações aqui em baixo (depois vou tirar pq nao é pra ter main aqui né)*/

int main(void){
    ARVORE *arvore = arvore_criar();

    /*arvore_inserir(arvore, 10);
    arvore_inserir(arvore, 20);
    arvore_inserir(arvore, 1);
    arvore_inserir(arvore, 3);
    arvore_inserir(arvore, 4);
    arvore_inserir(arvore, 8);
    arvore_inserir(arvore, 30);
    arvore_inserir(arvore, 40);*/
    arvore_inserir(arvore, 35);
    arvore_inserir(arvore, 50);
    arvore_inserir(arvore, 45);
    arvore_inserir(arvore, 55);
    arvore_inserir(arvore, 51);
    arvore_inserir(arvore, 100);


    printf("Árvore em ordem: ");
    arvore_imprimir(arvore);
    printf("\n");
    verificar_altura(arvore->raiz);

    printf("\nnúmero de nós: %d", arvore_nos(arvore));
    printf("\nsoma de todos os nós: %d", arvore_soma(arvore));
    printf("\né completa cheia? %d\n", arvore_cc(arvore));

    return 0;
}

/*pelo visto ta dando certo!!!!! graças a Deus!!!*/