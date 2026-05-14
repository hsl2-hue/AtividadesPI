#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union {
    unsigned char byte;

    struct {
        unsigned char bit0 : 1;
        unsigned char bit1 : 1;
        unsigned char bit2 : 1;
        unsigned char bit3 : 1;
        unsigned char bit4 : 1;
        unsigned char bit5 : 1;
        unsigned char bit6 : 1;
        unsigned char bit7 : 1;
    } bits;
} Registrador;

int main(){
    Registrador reg;
    int num;

    scanf("%d", &num);
    //coverte ao atribuir ao byte da union
    reg.byte = (unsigned char)num;

    printf("Byte bruto: %u | ", reg.byte);

    //bit menos significativo indica o erro
    printf("Erro: %u | ", reg.bits.bit0);

    //segundo ao quarto bit indicam o Modo, em forma de decimal
    int modo = (reg.bits.bit3 << 2) | (reg.bits.bit2 << 1) | reg.bits.bit1; //ou (reg.bits.bit1 << 0)
    printf("Modo: %d | ", modo);

    //quinto ao oitavo bit indicam a leitura, em forma de decimal
    int leitura = (reg.bits.bit7 << 3) | (reg.bits.bit6 << 2) | (reg.bits.bit5 << 1) | (reg.bits.bit4 << 0);
    printf("Leitura: %d\n", leitura);

    return 0;
}
