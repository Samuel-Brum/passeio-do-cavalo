#include "passeio.h"


int main(void) {
    time_t t;
    srand((unsigned) time (&t));
    
    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < N + 1; j++) {
            clock_t begin = clock();

            passeio(i, j);

            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("%f segundos\n", time_spent);
        } 
    }
    
    
}