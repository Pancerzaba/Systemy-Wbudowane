/*#include <stdio.h>
#include <stdlib.h>
#include<conio.h>

#define SCALE 308L

void IntToBinary (unsigned char input){ //funkcja symuluje jak zaswiecily by sie diody
    short i= 7;
    while (i>=0){
        printf("%d", (input >> i)& 1);
        i--;
    }
    printf(" ");
}

int main(void)
{
    unsigned long i;
    unsigned char display=0;

    again:
        printf("\r");   //ma wracac na poczatek lini (np przy dopisaniu liczby na poczatki)
        IntToBinary(display);
        char ch;
        ch = getch();
        int c,d=0;

        for (c=1; c<=32767; c++)        //spowolnienie programu o 1/4 sekundy
            for(d=1;d<=8192; d++){

            }

        if(ch == 72)        //symulacja przycisków
            display--;
        else if (ch==80)
            display = 0;
        else if (ch==32)
            display++;

    goto again;
}
