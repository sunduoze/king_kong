#include <stdio.h>
#include <stdlib.h>
#include "app_main.h"
extern KeyBoard kb_X13_ANSI;



int main()
{
    uint8_t *mem = (uint8_t *)malloc(sizeof(KeyBoard));

    KeyBoard kb_X1;
    printf("%d\r\n", sizeof(KeyBoard));

   // memcpy(kb_X1->BtnTyp, 1,sizeof(uint8_t));


    memcpy(mem, &kb_X13_ANSI, sizeof(KeyBoard));
    memcpy(&kb_X1, mem, sizeof(KeyBoard));
    KeyBoardParameterPrint(&kb_X1);
    free(mem);
    return 0;
}
