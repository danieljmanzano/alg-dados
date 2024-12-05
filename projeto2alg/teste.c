#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//codigo para criar os casos teste e saídas esperadas
//claudio ei ai fez quase tudo. arrumei algumas logicas para ficarem de acordo com minhas saídas esperadas

// Estrutura simplificada para simular o conjunto
typedef struct {
    int* elementos;
    int tamanho;
} Conjunto;

// Função para criar um conjunto
Conjunto* criar_conjunto(int* arr, int tamanho) {
    Conjunto* conj = malloc(sizeof(Conjunto));
    conj->elementos = malloc(tamanho * sizeof(int));
    conj->tamanho = tamanho;
    
    for (int i = 0; i < tamanho; i++) {
        conj->elementos[i] = arr[i];
    }
    
    return conj;
}

// Função para liberar memória do conjunto
void liberar_conjunto(Conjunto* conj) {
    free(conj->elementos);
    free(conj);
}

// Função para verificar se um elemento pertence ao conjunto
bool pertence(Conjunto* conj, int elemento) {
    for (int i = 0; i < conj->tamanho; i++) {
        if (conj->elementos[i] == elemento) {
            return true;
        }
    }
    return false;
}

// Função para remover um elemento do conjunto
Conjunto* remover_elemento(Conjunto* conj, int elemento) {
    int novo_tamanho = 0;
    int* novo_arr = malloc(conj->tamanho * sizeof(int));
    
    for (int i = 0; i < conj->tamanho; i++) {
        if (conj->elementos[i] != elemento) {
            novo_arr[novo_tamanho++] = conj->elementos[i];
        }
    }
    
    Conjunto* novo_conj = malloc(sizeof(Conjunto));
    novo_conj->elementos = novo_arr;
    novo_conj->tamanho = novo_tamanho;
    
    return novo_conj;
}

// Função para fazer união de conjuntos
Conjunto* uniao(Conjunto* A, Conjunto* B) {
    int novo_tamanho = A->tamanho + B->tamanho;
    int* novo_arr = malloc(novo_tamanho * sizeof(int));

    int tamA = A->tamanho, tamB = B->tamanho;
    int i = 0, j = 0, k = 0;
    while(i < tamA && j <tamB){
        if(A->elementos[i] < B->elementos[j])
            novo_arr[k++] = A->elementos[i++];
        else if(A->elementos[i] > B->elementos[j])
            novo_arr[k++] = B->elementos[j++];
        else{
            novo_arr[k++] = A->elementos[i++];
            j++;
        }   
    }
    
    while(i < tamA)
        novo_arr[k++] = A->elementos[i++];
    while(j < tamB)
        novo_arr[k++] = B->elementos[j++];

    novo_arr = realloc(novo_arr, sizeof(int) * k);
    Conjunto* novo_conj = malloc(sizeof(Conjunto));
    novo_conj->elementos = novo_arr;
    novo_conj->tamanho = k;
    
    return novo_conj;
}

// Função para fazer interseção de conjuntos
Conjunto* interseccao(Conjunto* A, Conjunto* B) {
    int max_tamanho = A->tamanho < B->tamanho ? A->tamanho : B->tamanho;
    int* novo_arr = malloc(max_tamanho * sizeof(int));
    int novo_tamanho = 0;
    
    for (int i = 0; i < A->tamanho; i++) {
        for (int j = 0; j < B->tamanho; j++) {
            if (A->elementos[i] == B->elementos[j]) {
                novo_arr[novo_tamanho++] = A->elementos[i];
                break;
            }
        }
    }
    
    Conjunto* novo_conj = malloc(sizeof(Conjunto));
    novo_conj->elementos = novo_arr;
    novo_conj->tamanho = novo_tamanho;
    
    return novo_conj;
}

int comparador(const void *a, const void *b) {
   return ( *(int*)a - *(int*)b );
}

// Função para gerar números únicos
int* generate_unique_array(int size, int max_value) {
    int* arr = malloc(size * sizeof(int));
    int* used = calloc(max_value + 1, sizeof(int));
    
    for (int i = 0; i < size; i++) {
        int num;
        do {
            num = rand() % (max_value + 1);
        } while (used[num]);
        
        arr[i] = num;
        used[num] = 1;
    }
    
    free(used);
    qsort(arr, size, sizeof(int), comparador);
    return arr;
}

void generate_test_cases(int num_cases) {
    // Abre os arquivos de saída
    FILE* test_file = fopen("test_cases.txt", "w");
    FILE* output_file = fopen("expected_output.txt", "w");
    
    if (!test_file || !output_file) {
        perror("Erro ao abrir arquivos");
        return;
    }
    
    // Seed para geração de números aleatórios
    srand(time(NULL));
    
    for (int caso = 1; caso <= num_cases; caso++) {
        // Escolhe tipo de estrutura 
        int tipo = rand() % 2;
        
        // Gera tamanhos dos conjuntos
        int n_a = rand() % 30 + 1; // 1 a 30 elementos
        int n_b = rand() % 30 + 1; // 1 a 30 elementos
        
        // Gera conjuntos com números únicos (números até 100 no máximo)
        int* conjunto_a = generate_unique_array(n_a, 100); // Alterar aqui para números maiores
        int* conjunto_b = generate_unique_array(n_b, 100);
        
        // Cria conjuntos para simulação
        Conjunto* A = criar_conjunto(conjunto_a, n_a);
        Conjunto* B = criar_conjunto(conjunto_b, n_b);
        
        // Escolhe operação aleatória
        int op = rand() % 4 + 1;
        
        // Escreve no arquivo de teste
        fprintf(test_file, "%d\n", tipo);
        fprintf(test_file, "%d %d\n", n_a, n_b);
        
        // Imprime elementos do primeiro conjunto
        for (int i = 0; i < n_a; i++) {
            fprintf(test_file, "%d ", conjunto_a[i]);
        }
        fprintf(test_file, "\n");
        
        // Imprime elementos do segundo conjunto
        for (int i = 0; i < n_b; i++) {
            fprintf(test_file, "%d ", conjunto_b[i]);
        }
        fprintf(test_file, "\n");
        
        // Gera entrada e saída para cada operação
        switch (op) {
            case 1: { // Pertence
                int chave = conjunto_b[rand() % n_b];
                fprintf(test_file, "%d\n", op);
                fprintf(test_file, "%d\n", chave);
                
                // Saída esperada
                fprintf(output_file, "--- Teste %d ---\n", caso);
                if(pertence(A, chave))
                    fprintf(output_file, "Pertence\n");
                else    
                    fprintf(output_file, "Nao pertence\n");
                break;
            }
            case 2: { // União
                fprintf(test_file, "%d\n", op);
                
                // Saída esperada
                Conjunto* uniao_conj = uniao(A, B);
                fprintf(output_file, "--- Teste %d ---\n", caso);
                fprintf(output_file, "União dos conjuntos: [");
                for (int i = 0; i < uniao_conj->tamanho; i++) {
                    fprintf(output_file, "%d%s", uniao_conj->elementos[i], 
                            i < uniao_conj->tamanho - 1 ? ", " : "");
                }
                fprintf(output_file, "]\n");
                liberar_conjunto(uniao_conj);
                break;
            }
            case 3: { // Remoção
                int chave = conjunto_a[rand() % n_a];
                fprintf(test_file, "%d\n", op);
                fprintf(test_file, "%d\n", chave);
                
                // Saída esperada
                Conjunto* removido = remover_elemento(A, chave);
                fprintf(output_file, "--- Teste %d ---\n", caso);
                fprintf(output_file, "Remoção bem sucedida. Conjunto atualizado: [");
                for (int i = 0; i < removido->tamanho; i++) {
                    fprintf(output_file, "%d%s", removido->elementos[i], 
                            i < removido->tamanho - 1 ? ", " : "");
                }
                fprintf(output_file, "]\n");
                liberar_conjunto(removido);
                break;
            }
            case 4: { // Interseção
                fprintf(test_file, "%d\n", op);
                
                // Saída esperada
                Conjunto* inter_conj = interseccao(A, B);
                fprintf(output_file, "--- Teste %d ---\n", caso);
                fprintf(output_file, "Interseção dos conjuntos: [");
                for (int i = 0; i < inter_conj->tamanho; i++) {
                    fprintf(output_file, "%d%s", inter_conj->elementos[i], 
                            i < inter_conj->tamanho - 1 ? ", " : "");
                }
                fprintf(output_file, "]\n");
                liberar_conjunto(inter_conj);
                break;
            }
        }
        
        // Libera memória
        liberar_conjunto(A);
        liberar_conjunto(B);
        free(conjunto_a);
        free(conjunto_b);
    }
    
    fclose(test_file);
    fclose(output_file);
    
    printf("Gerador de casos de teste criado com sucesso!\n");
    printf("Arquivo de entradas: test_cases.txt\n");
    printf("Arquivo de saídas esperadas: expected_output.txt\n");
}

int main(void) {
    // Gera 10 casos de teste diferentes
    generate_test_cases(20);
    return 0;
}