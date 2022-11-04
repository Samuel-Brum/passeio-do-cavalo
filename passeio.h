#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <unistd.h> // para função sleep na impressão de debug
#include <time.h> // para função de timeout

#define index(i,j) i*N + j // facilita manipulação de matrizes

#define FALSE -1 // para descartar movimentos falsos sem atrapalhar tabuleiro de zeros
                 // peço perdão aos meus ancestrais 
#define TRUE 1
#define N 8 // tamanho do tabuleiro

typedef struct {
    int linha;
    int coluna;
}coordenada ;

void cria_tabuleiro(int* tabuleiro) {
    int tamanho = N * N;

    for (int i = 0; i < tamanho; i++) {
        tabuleiro[i] = 0;
    }
} // atribui tabuleiro NxN com valores nulos

void imprime_tabuleiro(int* tabuleiro) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", tabuleiro[index(i, j)]);

        }
    printf("\n");
    }
    sleep(1);
} // para propositos de debug somente

void f_imprime_tabuleiro(int* tabuleiro, FILE* file, int casas_avancadas, int casas_retrocedidas) {
    file = fopen("saida.txt", "a");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(file, "%d ", tabuleiro[index(i, j)]);

        }
    fprintf(file, "\n");
    }
    fprintf(file, "%d %d\n\n", casas_avancadas, casas_retrocedidas);
    fclose(file);
} // como requerido, a função escreve a saida em um arquivo no formato especificado

void movimento_invalido (coordenada* movimento) {
    movimento->linha = FALSE;
    movimento->coluna = FALSE;
} 

void movimentos_possiveis (int posicao, int* tabuleiro, coordenada* movimentos, int setup_id) {
    int linha = posicao / N;
    int coluna = posicao % N;

    int mov_linha[8] = {2, 1, -1, -2, -2, -1, 1, 2}; //cria passos apropriados em uma tentativa de
    int mov_coluna[8] = {1, 2, 2, 1, -1, -2, -2, -1}; // reduzir o número de casas retrocedidas
    
    int count = 0;

    for (int i = 0; i < 8; i++) {
        movimentos[i].linha = linha + mov_linha[i];
        movimentos[i].coluna = coluna + mov_coluna[i];
    } // lista movimentos possíveis a partir de uma posicao especificada

    for (int i = 0; i < 8; i++) {
        if (movimentos[i].linha < 0 || movimentos[i].coluna < 0) {
            movimento_invalido(&movimentos[i]);
        } if (movimentos[i].linha >= N || movimentos[i].coluna >= N) {
            movimento_invalido(&movimentos[i]);
        }
        int casa = index(movimentos[i].linha, movimentos[i].coluna);
        if (tabuleiro[casa] != 0 && !(setup_id)) {
            movimento_invalido(&movimentos[i]);
        }
    } // retira movimentos que estão fora do tabuleiro ou já estão preenchidos

}

void tabuleiro_de_movimentos (int* casas_movimentaveis) {   
    coordenada movimentos[8];


    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            movimentos_possiveis(index(i, j), casas_movimentaveis, movimentos, TRUE);
            int numero_de_movimentos = 0;
            for (int k = 0; k < 8; k++) {
                if (movimentos[k].linha != -1) {
                    numero_de_movimentos++;
                }
            }
            casas_movimentaveis[index(i, j)] = numero_de_movimentos;
        }
    }
    //imprime_tabuleiro(casas_movimentaveis);

} // cria tabela de consulta de quantos movimentos são possíveis a partir de cada casa

void ordenador_de_movimentos (coordenada* movimentos, int* casas_movimentaveis) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7 - i; j++) {
            int casa_j = index(movimentos[j].linha, movimentos[j].coluna);
            int casa_j_1 = index(movimentos[j+1].linha, movimentos[j+1].coluna);
            if (casas_movimentaveis[casa_j] > casas_movimentaveis[casa_j_1] || casa_j == -9) {
                coordenada temp = movimentos[j];
                movimentos[j] = movimentos[j+1];
                movimentos[j+1] = temp;
            }
        }
    }
} // bubble sort para ordenar os oito movimentos possíveis do cavalo
  // essencialmente aplica a heuristica de Warnsdoff aos movimentos 

int passo (int* tabuleiro, int turno, int posicao, coordenada* movimento_anterior, long long int* casas_retrocedidas, long long int* casas_avancadas, int* casas_movimentaveis) {
    int linha = posicao / N;
    int coluna = posicao % N;
    //imprime_tabuleiro(tabuleiro);
    coordenada movimentos[8];
    movimentos_possiveis(posicao, tabuleiro, movimentos, 0);
    ordenador_de_movimentos(movimentos, casas_movimentaveis);
    clock_t begin = clock();

    for (int i = 0; i < 8; i++) {
        int casa = index(movimentos[i].linha, movimentos[i].coluna);
        clock_t now = clock();
        double time_diff = (double)(now - begin) / CLOCKS_PER_SEC;
        if (time_diff > 30) {
            printf("timeout!\n");
            return TRUE;
        }
        if (begin)
        if (movimentos[i].linha != FALSE) {
            tabuleiro[casa] = turno + 1;
            *casas_avancadas += 1;
            if (turno == N * N - 1) {
                return TRUE;
            }
            if (passo(tabuleiro, turno + 1, casa, &movimentos[i], casas_retrocedidas, casas_avancadas, casas_movimentaveis)) {
                return TRUE;
            }
            tabuleiro[casa] = 0;
            *casas_retrocedidas += 1;
            //imprime_tabuleiro(tabuleiro);
        } if (i == 7) {  
            turno -= 1;
            return 0;
            }
        }        
}
    


void passeio (int x, int y) {
    x = x-1; // normaliza a notação para adequar o formato requerido
    y = y-1; // ao resto do código (1, 1) -> (0, 0) || (3, 2) -> (2, 1) ...

    int posicao_inicial = index(x, y);

    // ajusta parametros da função 
    int tabuleiro[N * N];
    cria_tabuleiro(tabuleiro);
    int turno = 1;
    long long int casas_retrocedidas = 0;
    long long int casas_avancadas = 1;
    tabuleiro[posicao_inicial] = turno;
    int casas_movimentaveis[N * N];
    tabuleiro_de_movimentos(casas_movimentaveis);

    //imprime_tabuleiro(tabuleiro);

    passo(tabuleiro, turno, posicao_inicial, NULL, &casas_retrocedidas, &casas_avancadas, casas_movimentaveis);

    //imprime_tabuleiro(tabuleiro);


    FILE *fptr;
    f_imprime_tabuleiro(tabuleiro, fptr, casas_avancadas, casas_retrocedidas);

} // serve de casca para a chamada especificada