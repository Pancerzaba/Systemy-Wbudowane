#include <stdio.h>
#include <stdlib.h>
#include<conio.h>



void IntToBinary (unsigned char input){ //funkcja symuluje jak zaswiecily by sie diody
    short i= 7;
    while (i>=0){
        printf("%d", (input >> i)& 1);
        i--;
    }
    printf(" ");
}
void Opoznienie()
{
    int c,d = 0;
    for (c = 1; c <= 32767; c++)
            for (d = 1; d <= 8192; d++)
            {}
}
unsigned char IntToBCD(unsigned char input){
    return ((input / 10) <<4) | (input % 10);
}


int main(void)
{


    unsigned char licznik=0;
    unsigned char display=0;

    while(1){
            if(licznik > 99)
                licznik = 99;




            display = IntToBCD(licznik);

            printf("\r %d ", licznik);
            IntToBinary(display);

            Opoznienie();

            licznik --;



           /* licznik ++;   dla idacego w góre
            if(licznik>99)
                licznik = 0; */
    }
}
