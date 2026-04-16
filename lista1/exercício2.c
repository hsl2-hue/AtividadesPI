#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int somaMultiplos(int N, int K) {
  int m = N / K; // calcula quantos m�ltiplos de K existem at� N 
  return K * m * (m + 1) / 2; // usa a f�rmula de Gauss
} 

int main() {
  int N, A, B;
  scanf("%d", &N);
  scanf("%d %d", &A, &B);

  int somaA = somaMultiplos(N, A);
  int somaB = somaMultiplos(N, B);
  int somaAB = somaMultiplos(N, A * B);

  int total = N * (N + 1) / 2 - somaA - somaB + somaAB;

  if (total & 2 == 0) {
    printf("%d\n", total);
    printf("L� ele!!!");
  } else {
    printf("%d\n", total);
    printf("Opa xupenio AULAS...");
  }
	return 0;
}
