#include <stdio.h>
#include <math.h>
#include <string.h>

#define N 5
#define index(i,j) i*N + j

int* cria_tabuleiro() {
    int tamanho = N * N;
    int tabuleiro[tamanho - 1];

    for (int i = 0; i < tamanho; i++) {
        tabuleiro[i] = 0;
    }
    return tabuleiro;
} // constroi tabuleiro nxn com valores nulos


void passeio (int x, int y) {

}