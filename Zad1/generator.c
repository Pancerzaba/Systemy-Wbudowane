
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>



void IntToBinary (unsigned char input){ //funkcja symuluje jak zaswiecily by sie diody przez zamienienie liczb na ciag binarny
    short i= 5;
    while (i>=0){
        printf("%d ", (input >> i)& 1);
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
char ntybit(unsigned char n, unsigned char input){
    int bit;
    bit=input >>(n-1) & 1;
    return bit;

}


int main(void)
{
    unsigned char licznik=1;
    unsigned char licz;

    unsigned char xorowane;
    unsigned char wynik;
    unsigned char b1, b2, b5, b6;   //oznaczenie kolejnych wyciagnietych bitow

    while(1){
    int i=1;
    licz=licznik>>i;       //przesuwamy calosc w prawo o 1

    b1=ntybit(1, licznik);
    b2=ntybit(2, licznik);
    b5=ntybit(5, licznik);
    b6=ntybit(6, licznik);

    xorowane = b1^b2^b5^b6;

    wynik= licz | xorowane <<5;

    IntToBinary(wynik);
    printf("\n");
    licznik = wynik;
    /*
    while(i<8){
    if(i=3)i=5;
    x= ntybit(i, licznik);
    y=ntybit(i, licz);
    z=x^y;
    printf("%d \n", z);
    wynik=wynik|((x^y)<<i);
    IntToBinary(wynik);
    printf("\n");
    i++;
    }licznik =licz;
    }*/

    }

}
