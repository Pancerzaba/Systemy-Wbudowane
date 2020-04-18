#include <stdio.h>
#include <stdlib.h>
#include<conio.h>



void IntToBinary (unsigned char input){ //funkcja symuluje jak zaswiecily by sie diody przez zamienienie liczb na ciag binarny
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
unsigned char wezyk(unsigned char input){
    /* short i= 7;
     char licz;
     licz = input;
    while (i>=0){
        //printf("%d", (input >> i)& 1);
        licz =licz^2;
        i--;
    }*/
    input = (!input |input)&input;
    return input ;//licz;//input^(input >>2);
}/*
unsigned char wezykR(unsigned char input){
    return input >>1;
} */


int main(void)
{

    unsigned char licz=7;       //1 pozycja weza

    while(1){       //petla nieskonczona
        if(licz<224 ){      //petla z warunkiem  ¿e w¹¿ mo¿e siê przesówaæ w lewo a¿ dotrze do lewej "sciany"
        IntToBinary(licz);
        printf("\n");       // pozwala wyswietlac kolejne wyniki jeden pod drugim

        licz =licz<<1;      //przesuniecie bitowe w lewo
        }
         else if(licz =224 ){     //jezeli wez dotknie  lewej sciany zmieniany jest jego kierunek
                while(licz>7){      //petla z warunekiem koncowym po ktorym ma przestaæ przesowac w lewo
                    IntToBinary(licz);//petla ktora przesowa weza w prawo

                printf("\n");       // pozwala wyswietlac kolejne wyniki jeden pod drugim
                licz = licz>>1;}        //przesuniecie bitowe w prawo
                }

       /* else if((licz<224 &licz>6) ) {
        IntToBinary(licz);
        printf("%d \n", licz);

        licz =licz>>1;
        }*/









    }
/*

    unsigned char licznik=7;
    unsigned char display=0;

    while(1){

          //  input ^ (input>> 1);


            display = wezyk(licznik );

            printf("\n  ", licznik);
            IntToBinary(display);

            Opoznienie();

            licznik ++;






    }*/
}
