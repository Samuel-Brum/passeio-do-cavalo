#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define FALSE -1
#define TRUE 1
#define N 5
#define index(i,j) i*N + j // facilita construção e chamada de índices de matrizes 

void cria_tabuleiro(int* tabuleiro) {
    int tamanho = N * N;

    for (int i = 0; i < tamanho; i++) {
        tabuleiro[i] = 0;
    }
} // atribui tabuleiro NxN com valores nulos

int* movimentos_validos(int posicao, int* tabuleiro) {
    int linha = posicao / N;
    int coluna = posicao % N;
    int movimentos[] = {index(linha-2, coluna+1), index(linha-1, coluna+2),
                        index(linha+1, coluna+2), index(linha+2, coluna+1),
                        index(linha+2, coluna-1), index(linha+1, coluna-2),
                        index(linha-1, coluna-2), index(linha-2, coluna-1)}; 
    // lista movimentos possiveis a partir de uma posicao especificada

    for (int i = 0; i < 8; i++) {
        if (movimentos[i] < 0 || movimentos[i] > (N * N)) {
            movimentos[i] = FALSE;
        } else {
            if (tabuleiro[movimentos[i]] != 0) {
                movimentos[i] = FALSE;
            }
        }
    }
    return movimentos;
} // retorna lista de movimentos válidos dada uma posição inicial

int passo (int* tabuleiro, int turno, int i, int j) {
    tabuleiro[index(i, j)] = turno;
    int* movimentos = movimentos_validos(index(i, j), tabuleiro);

    for (int k = 0; k < sizeof(movimentos)/sizeof(int); k++) {
        if (movimentos[k] != FALSE) {
            tabuleiro[movimentos[k]] = turno + 1;
            int linha = movimentos[k] / N;
            int coluna = movimentos[k] % N;

            if (passo(tabuleiro, turno + 1, linha, coluna)) {
                return TRUE;
            }
        tabuleiro[k] = 0; 
        }
    }
    return 0;
}


void passeio (int x, int y) {
    x = x-1; // normaliza a notação para adequar ao formato 
    y = y-1; // do resto do código (1, 1) -> (0, 0)

    int tabuleiro[N * N];
    cria_tabuleiro(tabuleiro);

    int turno = 1;
    passo(tabuleiro, turno, x , y);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", tabuleiro[index(i, j)]);
        }
    printf("\n");
    }
}