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
    for (c = 1; c <= 1000032767; c++)
            for (d = 1; d <= 99998192; d++)
            {}
}


unsigned char IntToGray(unsigned char input){
    return input ^ (input>> 1);
}

int main(void)
{
    unsigned char licznik=0;
    unsigned char display=0;



    while(1){

            display = IntToGray(licznik); //licznik;
            printf("\r");
            IntToBinary(display);
            Opoznienie();


            licznik ++;
    }
}
