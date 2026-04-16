#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(){
    // declaro e coleto as variáveis 
    int total, x, y, z;
    scanf("%d", &total);
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &z);

    int rebeka = 3;
    int investido = 0;
    int encontrado = 0;
    int a, b, c, troco;

    // tenta sem investir nd
    if ((total * x) % 100 == 0 && (total * y) % 100 == 0 && (total * z) % 100 == 0) {
        a = (total * x) / 100;
        b = (total * y) / 100;
        c = (total * z) / 100;
        troco = total - (a + b + c);
        investido = 0;
        encontrado = 1;
    } 
    // tenta investindo 1
    else if (((total + 1) * x) % 100 == 0 && ((total + 1) * y) % 100 == 0 && ((total + 1) * z) % 100 == 0) {
        a = ((total + 1) * x) / 100;
        b = ((total + 1) * y) / 100;
        c = ((total + 1) * z) / 100;
        troco = (total + 1) - (a + b + c);
        if (troco > 1) {
            investido = 1;
            encontrado = 1;
        }
    } 
    // tenta investindo 2
    else if (((total + 2) * x) % 100 == 0 && ((total + 2) * y) % 100 == 0 && ((total + 2) * z) % 100 == 0) {
        a = ((total + 2) * x) / 100;
        b = ((total + 2) * y) / 100;
        c = ((total + 2) * z) / 100;
        troco = (total + 2) - (a + b + c);
        if (troco > 2) {
            investido = 2;
            encontrado = 1;
        }
    } 
    // tenta investindo 3
    else if (((total + 3) * x) % 100 == 0 && ((total + 3) * y) % 100 == 0 && ((total + 3) * z) % 100 == 0) {
        a = ((total + 3) * x) / 100;
        b = ((total + 3) * y) / 100;
        c = ((total + 3) * z) / 100;
        troco = (total + 3) - (a + b + c);
        if (troco > 3) {
            investido = 3;
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nao foi dessa vez que Rebeka pode ajudar...\n"); // caso n seja possível dividir o dinheiro
        if (rebeka > 7) {
            printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
        } else {
            printf("E parece que Rebeka vai ter que voltar andando...\n");
        }
        
        return 0;
    }

    printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", a, b, c);

    rebeka = rebeka - investido + troco; // atualiza o valor de rebeka
    /* caso ela invista 2, receberá letras e indicará a soma delas
    caso invista 3, receberá as idades e verificará se são divisíveis por 3 */
    if (investido == 2) {
        char l1, l2, l3;
        scanf(" %c %c %c", &l1, &l2, &l3);
        printf("%d\n", (l1 - 'a' + 1) + (l2 - 'a' + 1) + (l3 - 'a' + 1));
    } else if (investido == 3) {
        int i1, i2, i3;
        scanf("%d %d %d", &i1, &i2, &i3);
        if (i1 % 3 == 0 || i2 % 3 == 0 || i3 % 3 == 0)
            printf("%d\n", i1 / 3 + i2 / 3 + i3 / 3);
    }

    // condicionais caso ela consiga o dinheiro
    if (rebeka >= 7) {
        printf("Rebeka conseguiu voltar para casa e apanhou da mae por sumir noite passada!\n");
    } else {
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }
}
