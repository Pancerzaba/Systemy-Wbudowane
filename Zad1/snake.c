
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


int main(void)
{

    unsigned char licz=7;       //1 pozycja weza
    int a=0;        //parametr kierunku

    while(1){       //petla nieskonczona


            if(a==0){       //jesli jest a = 0 to waz idzie w lewo
                    licz = licz<<1;     // implementacja kroku weza w lewo
                    IntToBinary(licz);//ZAMIENIA NA BINARNY
                    printf("\n");
                   if (licz==224){ //JESLI WAZ OSIAGNIE GRNANICE TO ZMIENIA PARAMETR ODPOWIEDZIALNY ZA KIERUNEK
                        a=1;
                    }

            }else if (a=1){ //jesli parametr kierunku jest 1
                    licz = licz>>1;     // waz zaczyna isc w prawo
                    IntToBinary(licz);
                    printf("\n");
                    if(licz==7){        // jesli dojdzie do prawej granicy to znow zmienia parametr kierunki
                        a=0;
                    }
            }


            /*


        if(licz<224 & a==0 ){      //petla z warunkiem  ¿e w¹¿ mo¿e siê przesówaæ w lewo a¿ dotrze do lewej "sciany"
        IntToBinary(licz);
        printf("\n");       // pozwala wyswietlac kolejne wyniki jeden pod drugim

        licz =licz<<1;      //przesuniecie bitowe w lewo
        }
         else if(licz =224 & a == 0 ){     //jezeli wez dotknie  lewej sciany zmieniany jest jego kierunek
                a==1;
                      //przesuniecie bitowe w prawo
                }

        else if((licz<=224 &licz>6 & a==1) ) {
        IntToBinary(licz);
        printf("%d \n", licz);

        licz =licz>>1;
        }else if(licz=6 & a==1){
            a=0;
        }*/

    }
}

