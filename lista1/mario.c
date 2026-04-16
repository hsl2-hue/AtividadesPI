#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(){
  // declaro as variáveis para receber o input
  int x,y,c;
  scanf("%d %d %d", &x, &y, &c); // x,y são as coordenadas e c é o quadrante q ele quer ir 

  // quadrante 1
  if (x > 0 && y > 0){ /*verifica qual quadrante pertence 
    e depois verifica se choca com restrição de não poder ser no mesmo */
    if (c == 1) {
      printf("caminhada invalida"); // caso seja o mesmo quadrante
    } else {
      /*caso não seja do mesmo quadrante, faço a distancia do ponto inicial 
      até o ponto final na diagonal*/
      int x1 = abs(x) + 1;
      int y1 = abs(y) + 1;
      printf("%d passos em y e %d passos em x", y1, x1);
    }
  } // a lógica se mantem nos próx if
  
  // quadrante 2
  if (x < 0 && y > 0){
    if (c == 2) {
      printf("caminhada invalida");
    } else {
      int x1 = abs(x) + 1;
      int y1 = abs(y) + 1;
      printf("%d passos em y e %d passos em x", y1, x1);
    }
  }
  
  // quadrante 3
  if (x < 0 && y < 0){
    if (c == 3) {
      printf("caminhada invalida");
    } else {
      int x1 = abs(x) + 1;
      int y1 = abs(y) + 1;
      printf("%d passos em y e %d passos em x", y1, x1);
    }
  }
  
  // quadrante 4
  if (x > 0 && y < 0){
    if (c == 4) {
      printf("caminhada invalida");
    } else {
      int x1 = abs(x) + 1;
      int y1 = abs(y) + 1;
      printf("%d passos em y e %d passos em x", y1, x1);
    }
  }
  
  return 0;
}