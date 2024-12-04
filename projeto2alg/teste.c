#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// codigo feito para gerar um txt de casos teste pra main. é só usar o make que ele funciona

// Funções auxiliares para geração de casos de teste
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
    return arr;
}

void generate_test_cases(int num_cases) {
    // Abre o arquivo de saída para os casos de teste
    FILE* test_file = fopen("test_cases.txt", "w");
    if (!test_file) {
        perror("Erro ao abrir arquivo de teste");
        return;
    }

    // Seed para geração de números aleatórios
    srand(time(NULL));

    for (int caso = 1; caso <= num_cases; caso++) {
        // Escolhe tipo de estrutura (0 para lista, 1 para AVL)
        int tipo = rand() % 2;
        
        // Gera tamanhos dos conjuntos
        int n_a = rand() % 30 + 1;  // 1 a 10 elementos
        int n_b = rand() % 30 + 1;  // 1 a 10 elementos
        
        // Gera conjuntos com números únicos
        int* conjunto_a = generate_unique_array(n_a, 100);
        int* conjunto_b = generate_unique_array(n_b, 100);
        
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
        
        // Gera entrada específica para cada operação
        switch (op) {
            case 1: // Pertence
                fprintf(test_file, "%d\n", op);
                fprintf(test_file, "%d\n", conjunto_a[rand() % n_a]);
                break;
            
            case 2: // União
                fprintf(test_file, "%d\n", op);
                break;
            
            case 3: // Remoção
                fprintf(test_file, "%d\n", op);
                fprintf(test_file, "%d\n", conjunto_a[rand() % n_a]);
                break;
            
            case 4: // Interseção
                fprintf(test_file, "%d\n", op);
                break;
        }
        
        // Libera memória
        free(conjunto_a);
        free(conjunto_b);
    }
    
    fclose(test_file);
    printf("Gerador de casos de teste criado com sucesso! Arquivo: test_cases.txt\n");
}

int main() {
    // Gera 10 casos de teste diferentes
    generate_test_cases(10);
    return 0;
}