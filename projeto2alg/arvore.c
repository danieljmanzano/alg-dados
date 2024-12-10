#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

typedef struct no_{
    struct no_ *esq, *dir, *pai;
    int chave, fb; //fb é o meu fator balanceamento do nó na arvore
}NO;

typedef struct arvore_{
    NO *raiz;
}ARVORE;
 
ARVORE *arvore_criar(void){
    ARVORE *t = malloc(sizeof(ARVORE));
    if(t != NULL)
        t->raiz = NULL;
    
    return t;
}

NO *no_criar(int chave){
    NO *no = malloc(sizeof(NO));
    if(!no) return NULL;

    no->chave = chave;
    no->fb = 0;
    no->esq = NULL;
    no->dir = NULL;
    no->pai = NULL;
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
    
    if(novaRaiz->dir) //atualiza filho direito da nova raiz se existir
        novaRaiz->dir->pai = desbalanceado;
    
    desbalanceado->esq = novaRaiz->dir;
    
    if(desbalanceado->pai){ //ajuste dos ponteiros pai caso o desbalanceado tinha um nó pai
        if(desbalanceado->pai->esq == desbalanceado) 
            desbalanceado->pai->esq = novaRaiz;
        else 
            desbalanceado->pai->dir = novaRaiz;
    }
        
    novaRaiz->dir = desbalanceado;
    novaRaiz->pai = desbalanceado->pai;
    desbalanceado->pai = novaRaiz;
    

    desbalanceado->fb = altura(desbalanceado->esq) - altura(desbalanceado->dir);
    novaRaiz->fb = altura(novaRaiz->esq) - altura(novaRaiz->dir);
    
    return novaRaiz;
}

NO *rotacaoEsquerda(NO *desbalanceado) {
    NO *novaRaiz = desbalanceado->dir;
    
    if (novaRaiz->esq) //atualiza filho esquerdo da nova raiz se existir
        novaRaiz->esq->pai = desbalanceado;
    
    desbalanceado->dir = novaRaiz->esq;
    
    if(desbalanceado->pai){ //ajuste dos ponteiros pai caso o desbalanceado tinha um nó pai
        if(desbalanceado->pai->esq == desbalanceado) 
            desbalanceado->pai->esq = novaRaiz;
        else 
            desbalanceado->pai->dir = novaRaiz;
    }
    
    novaRaiz->esq = desbalanceado;
    novaRaiz->pai = desbalanceado->pai;
    desbalanceado->pai = novaRaiz;
    

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
} 
/*--------------*/


/*funçoes juntas*/
NO *arvore_inserir_no(NO *raiz, NO *novo_no){

    if(!raiz){ //achou o local de inserção
        novo_no->pai = NULL; 
        return novo_no;        
    }

    else if(novo_no->chave < raiz->chave){
        raiz->esq = arvore_inserir_no(raiz->esq, novo_no);
        if(raiz->esq) //caso tenha um filho esquerdo, devo colocar seu "pai" como o nó atual
            raiz->esq->pai = raiz;
    }

    else if(novo_no->chave > raiz->chave){
        raiz->dir = arvore_inserir_no(raiz->dir, novo_no);
        if(raiz->dir) //mesma lógica de cima para um filho direito
            raiz->dir->pai = raiz;
    }

    else if(novo_no->chave == raiz->chave){ //caso o nó que eu quero inserir ja esteja alocado na arvore, desaloco ele antes de voltar
        free(novo_no);
        novo_no = NULL;
        return raiz;
    }

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
    
    if(chave < raiz->chave){
        raiz->esq = arvore_remover_no(raiz->esq, chave);
        if(raiz->esq) //caso exista um filho esquerdo, devo colocar o campo "pai" dele como o nó atual
            raiz->esq->pai = raiz;
    }

    else if(chave > raiz->chave){
        raiz->dir = arvore_remover_no(raiz->dir, chave);
        if(raiz->dir) //mesma lógica de cima para um filho direito
            raiz->dir->pai = raiz;
    }

    else{ //caso tenha achado o que é para remover

        //pra nó com um filho ou nenhum
        if(!raiz->esq){
            NO *temp = raiz->dir;
            if(temp)
                temp->pai = raiz->pai;

            free(raiz);
            return temp;
        }
        else if(!raiz->dir){
            NO *temp = raiz->esq;
            if(temp)
                temp->pai = raiz->pai;

            free(raiz);
            return temp;
        }
        
        //pra nó com dois filhos
        NO *temp = acha_menor_valor(raiz->dir);
        raiz->chave = temp->chave;
        raiz->dir = arvore_remover_no(raiz->dir, temp->chave);
        if(raiz->dir) //caso exista um filho direito para o nó, arruma o ponteiro pai
            raiz->dir->pai = raiz;
    }
    
    return balancear(raiz); //rebalancear em função do nó atual
}

bool arvore_remover(ARVORE *t, int chave) {
    if (!t || !t->raiz) return false;
    t->raiz = arvore_remover_no(t->raiz, chave);
    return true;
}
/*--------------*/


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

/*funções juntas*/
NO *buscabinT(NO *raiz, int chave) {
    if(!raiz) return NULL;
    
    if(chave == raiz->chave) return raiz;
    
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
/*--------------*/


NO *proximo_no(NO *no){ //função auxiliar para encontrar o próximo nó imediato a algum (faz isso com ajuda do campo no->pai). uso para união e intersecção
    if(!no) return NULL;

    if(no->dir){ //caso tenha filho direito, pega o menor desse lado
        no = no->dir;
        while(no->esq) no = no->esq;
        return no;
    }

    //se não tem filho direito, a saída é procurar a partir dos pais (faz o caminho "de volta" para achar o possível próximo)
    while(no->pai){
        if(no->pai->esq == no)  //se o nó atual é o filho esquerdo, retorna o pai
            return no->pai;
        
        no = no->pai;
    }

    return NULL; //se chegou na raiz sem encontrar, quer dizer que era o "último", nao tinha proximo. retorna nulo
}


void arvore_uniao(ARVORE *t1, ARVORE *t2, ARVORE *nova_arvore){
    if((!t1 && !t2) || !nova_arvore) return;

    NO *atual1 = acha_menor_valor(t1->raiz); //pega o menor valor de cada árvore para começar as comparações
    NO *atual2 = acha_menor_valor(t2->raiz);

    while(atual1 || atual2){ //percorre as arvores simultaneamente
        if(!atual1){ //se o 1 é nulo, insiro o 2 e ando pra frente
            arvore_inserir(nova_arvore, atual2->chave);
            atual2 = proximo_no(atual2);
            continue;
        }

        if(!atual2){ //se o 2 é nulo, insiro o 1 e ando pra frente
            arvore_inserir(nova_arvore, atual1->chave);
            atual1 = proximo_no(atual1);
            continue;
        }

        //compara os valores e insere o menor
        if(atual1->chave < atual2->chave){
            arvore_inserir(nova_arvore, atual1->chave);
            atual1 = proximo_no(atual1);
        }
        else if(atual1->chave > atual2->chave){
            arvore_inserir(nova_arvore, atual2->chave);
            atual2 = proximo_no(atual2);
        }

        else { //chaves iguais. insere 1 e anda os dois
            arvore_inserir(nova_arvore, atual1->chave);
            atual1 = proximo_no(atual1);
            atual2 = proximo_no(atual2);
        }
    }

    if(!nova_arvore->raiz) printf("união vazia");
    return;
}


void arvore_interseccao(ARVORE *t1, ARVORE *t2, ARVORE *nova_arvore) {
    if(!t1 || !t2 || !nova_arvore) return; //se uma das duas é vazia, ja nao tem intersecçao

    NO *atual1 = acha_menor_valor(t1->raiz); //pega o menor valor de cada arvore para começar as comparações
    NO *atual2 = acha_menor_valor(t2->raiz);

    while(atual1 && atual2){ //percorre as arvores simultaneamente (ambas devem ser não nulas para haver intersecção!)

        if(atual1->chave < atual2->chave) //caso 1 seja menor, anda ele
            atual1 = proximo_no(atual1);
        
        else if(atual1->chave > atual2->chave) //caso 2 seja menor, anda ele
            atual2 = proximo_no(atual2);
        
        else{ //chaves iguais
            arvore_inserir(nova_arvore, atual1->chave); //insere na intersecção e anda ambos
            atual1 = proximo_no(atual1);
            atual2 = proximo_no(atual2);
        }
    }

    if(!nova_arvore->raiz) printf("intersecção vazia");
    return;
}

