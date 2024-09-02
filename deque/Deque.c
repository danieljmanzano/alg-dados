#include <stdio.h>
#include <stdlib.h>
#include "Deque.h"
#include "item.h"

//exercicio basicamente só pra implementar um deque.c relativo pro .h que a gente recebeu aí na pasta
//tem o item.h tb mas só uso o item_apagar e é isso, nao tinha que implementar ele alias

typedef struct deque_{
    int in, fim, tam;
    ITEM *deque[MAX_TAMANHO];
}DEQUE;

DEQUE* deque_criar(){ //só o basico, criando e inicializando geral em 0
    DEQUE *deque = (DEQUE*)malloc(sizeof(DEQUE));
    if(deque == NULL) return NULL;

    deque->in = 0;
    deque->fim = 0;
    deque->tam = 0;
    return deque;
}

void deque_apagar(DEQUE** deque){ 
    if(*deque != NULL){
        for(int i = 0; i < MAX_TAMANHO; i++){ //vou apagando cada posição do vetor deque (meio bosta por ter que percorrer mó espaço mas acho que é o mais certo)
            if((*deque)->deque[i] != NULL) item_apagar(&((*deque)->deque[i])); //vou apagando cada posição do deque de itens
        }

        free(*deque);
        *deque = NULL;
    }
    return;
}

bool deque_inserir_inicio(DEQUE* deque, ITEM* item){ 
    if(deque == NULL || deque_cheia(deque)) return false; //caso esteja cheio ou nulo nao da pra fazer a operação
    if(item == NULL) return false; //caso o item nao exista nao faço nada

    deque->in = (deque->in-1 + MAX_TAMANHO) % MAX_TAMANHO; //jogo o inicio um pra tras (o %max_tamanho é pra que, se tiver passado o tamanho maximo, ele volta pro começo do deque)
    deque->deque[deque->in] = item; //coloco o item passado no inicio "novo"
    deque->tam++; //aumenta o tamanho
    return true;
}

bool deque_inserir_fim(DEQUE* deque, ITEM* item){ //mesma logica de cima, só troca o inicio por fim e anda pra frente ao inves de pra tras
    if(deque == NULL || deque_cheia(deque)) return false;
    if(item == NULL) return false;

    deque->deque[deque->fim] = item;
    deque->fim = (deque->fim+1) % MAX_TAMANHO;
    deque->tam++;
    return true;
}//obs.: fim aqui é a posição logo a frente da ultima ocupada no deque de itens

ITEM* deque_remover_inicio(DEQUE* deque){ 
    if(deque == NULL || deque_vazia(deque)) return NULL; //caso esteja vazio nao da pra dale
    
    ITEM *aux = deque->deque[deque->in]; //guardo o que vou apagar
    deque->deque[deque->in] = NULL; //apago
    deque->in = (deque->in+1) % MAX_TAMANHO; //se remove um do inicio tem que andar pra frente
    deque->tam--; //tira do tamanho
    return aux; //volto o que tava la
}

ITEM* deque_remover_fim(DEQUE* deque){ 
    if(deque == NULL || deque_vazia(deque)) return NULL;

    deque->fim = (deque->fim-1 + MAX_TAMANHO) % MAX_TAMANHO; //ando o fim pra tras antes (lembrando que o fim marca uma posição vazia)
    ITEM *aux = deque->deque[deque->fim]; //pego o conteudo do fim novo (que tenho que apagar)
    deque->deque[deque->fim] = NULL; //apago
    deque->tam--; //tira do tamanho
    return aux; //volto o que tava la
}

ITEM* deque_primeiro(DEQUE* deque){ //só o basico pt.2
    if(deque == NULL || deque_vazia(deque)) return NULL;

    ITEM *aux = deque->deque[deque->in];
    return aux;
} //obs.: nao tenho ctz do que seria o "primeiro", fui no obvio e deduzi que fosse o inicio

ITEM* deque_ultimo(DEQUE* deque){ //mesma coisa de cima com fim no lugar de inicio (e puxando a posição anterior ao fim real, ou seja, o que tem conteudo)
    if(deque == NULL || deque_vazia(deque)) return NULL;

    ITEM *aux = deque->deque[(deque->fim-1 + MAX_TAMANHO) % MAX_TAMANHO]; //kkkkkkkkk bagulho feio filho
    return aux;
}

int deque_contar(DEQUE* deque){ //retorna a quantidade de coisa dentro do deque
    if(deque == NULL || deque_vazia(deque)) return 0;
    return deque->tam;
}

bool deque_vazia(DEQUE* deque){
    if(deque == NULL || deque->tam == 0) return true; //retorno que ta vazio se o tamanho for 0 ou se ele é nulo
    return false;
}

bool deque_cheia(DEQUE* deque){
    if(deque == NULL || deque->tam == MAX_TAMANHO) return true; //retorno que ta cheio caso realmente esteja cheio ou se nao existir
    return false;
}//obs.: caso nao exista é bom retornar que ta cheio pra impossibilitar que sejam feitas operações nesse deque