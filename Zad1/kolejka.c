#include <stdio.h>
#include <stdlib.h>
#include<conio.h>

/*

void IntToBinary (unsigned char input){ //funkcja symuluje jak zaswiecily by sie diody przez zamienienie liczb na ciag binarny
    short i= 7;
    while (i>=0){
        printf("%d", (input >> i)& 1);
        i--;
    }
    printf(" ");
}




int main(void)
{

    unsigned char p=1;       //prawa strona
    unsigned char l=128;    //lewa strona
    unsigned char wynik=0;
    unsigned char slewa=l;      //suma z lewej strony

    while(wynik<255){       //petla nieskonczona

        if(p<l ){
            wynik =slewa+p;
            p=p<<1;
        }
         else if(l=p ){
                l=l>>1;
                p=1;
                slewa=slewa+l;
                }
            IntToBinary(wynik);
            printf("\n");










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






    }
}*/
