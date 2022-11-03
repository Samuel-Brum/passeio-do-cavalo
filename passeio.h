#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define index(i,j) i*N + j
#define FALSE -1
#define TRUE 1
#define N 7

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
    printf("\n");
    //sleep(1);
}

void movimento_invalido (coordenada* movimento) {
    movimento->linha = FALSE;
    movimento->coluna = FALSE;
}

int passo (int* tabuleiro, int turno, int posicao, coordenada* movimento_anterior, int* casas_retrocedidas, int* casas_avancadas) {
    int linha = posicao / N;
    int coluna = posicao % N;
    //imprime_tabuleiro(tabuleiro);

    coordenada movimentos[8];
    int count = 0;

    for (int i = 2; i >= -2; i--) {
        for (int j = 2; j >= -2; j--) {
            if (i == j || i == 0 || j == 0 || abs(i) == abs(j)) {
                continue;
            }
            coordenada temp;
            temp.linha = linha + i;
            temp.coluna = coluna + j;
            movimentos[count] = temp;
            count++;
        }
    } // lista movimentos possiveis a partir de uma posicao especificada

    for (int i = 0; i < 8; i++) {
        if (movimentos[i].linha < 0 || movimentos[i].coluna < 0) {
            movimento_invalido(&movimentos[i]);
        } if (movimentos[i].linha >= N || movimentos[i].coluna >= N) {
            movimento_invalido(&movimentos[i]);
        }
        int casa = index(movimentos[i].linha, movimentos[i].coluna);
        if (tabuleiro[casa] != 0) {
            movimento_invalido(&movimentos[i]);
        }
    } // retira movimentos que estão fora do tabuleiro

    for (int i = 0; i < 8; i++) {
        int casa = index(movimentos[i].linha, movimentos[i].coluna);
        if (movimentos[i].linha != FALSE) {
            tabuleiro[casa] = turno + 1;
            *casas_avancadas += 1;
            if (turno == N * N - 1) {
                return TRUE;
            }
            if (passo(tabuleiro, turno + 1, casa, &movimentos[i], casas_retrocedidas, casas_avancadas)) {
                return TRUE;
            }
            tabuleiro[casa] = 0;
            *casas_retrocedidas += 1;
        } if (i == 7) {  
            turno -= 1;
            return 0;
            }
        }        
}
    


void passeio (int x, int y) {
    x = x-1; // normaliza a notação para adequar ao formato requerido
    y = y-1; // do resto do código (1, 1) -> (0, 0) || (3, 2) -> (2, 1) ...

    int posicao_inicial = index(x, y);

    // ajusta parametros da função 
    int tabuleiro[N * N];
    cria_tabuleiro(tabuleiro);
    int turno = 1;
    int casas_retrocedidas = 0;
    int casas_avancadas = 1;
    tabuleiro[posicao_inicial] = turno;

    passo(tabuleiro, turno, posicao_inicial, NULL, &casas_retrocedidas, &casas_avancadas);

    imprime_tabuleiro(tabuleiro);
    printf("%d %d", turno, casas_retrocedidas);
} // serve de casca para a chamada especificada