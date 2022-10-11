#include <stdio.h>
#include <math.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
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

int* movimentos_validos(int posicao, int* tabuleiro) {
    int linha = posicao / N;
    int coluna = posicao % N;
    int movimentos[] = {index(linha-2, coluna+1), index(linha-1, coluna+2),
                        index(linha+1, coluna+2), index(linha+2, coluna+1),
                        index(linha+2, coluna-1), index(linha+1, coluna-2),
                        index(linha-1, coluna-2), index(linha-2, coluna-1)}; 
    // lista movimentos possiveis a partir de uma posicao especificada

    for (int i = 0; i < 8; i++) {
        if (movimentos[i] < 1 || movimentos[i] > 63) {
            movimentos[i] = FALSE;
        } else {
            if (tabuleiro[movimentos[i]] != 0) {
                movimentos[i] = FALSE;
            } else {
                movimentos[i] = TRUE;
            }
        }
    }
    return movimentos;
}


void passeio (int x, int y) {
    int* tabuleiro = cria_tabuleiro();
    int turno = 1;
    tabuleiro[index(x,y)] = turno;

}