// CONFIG1H
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF

#include <xc.h>

#define LENA  PORTEbits.RE1
#define LDAT  PORTEbits.RE2
#define LPORT PORTD

#define L_ON	0x0F
#define L_OFF	0x08
#define L_CLR	0x01
#define L_L1	0x80
#define L_L2	0xC0
#define L_CR	0x0F		
#define L_NCR	0x0C	

#define L_CFG   0x38

void delay(unsigned int ms)
{
    unsigned int i;
    unsigned char j;
    
 for (i =0; i< ms; i++)
 {
 
  for (j =0 ; j < 200; j++)
   {
      Nop();
      Nop();
      Nop();
      Nop();
      Nop();
   }
 }
}

unsigned int adc(unsigned char kanal)
{
    switch(kanal)
    {
        case 0: ADCON0=0x01; break; //P1
        case 1: ADCON0=0x05; break; //P2
        case 2: ADCON0=0x09; break; 
    }
    
    ADCON0bits.GO=1;
    while(ADCON0bits.GO == 1);

   return ((((unsigned int)ADRESH)<<2)|(ADRESL>>6));
}

void lcd_wr(unsigned char val)
{
  LPORT=val;
}

void lcd_cmd(unsigned char val)
{
	LENA=1;
        lcd_wr(val);
        LDAT=0;
        //delay(3);
        LENA=0;
        //delay(3);
	LENA=1;
}
 
void lcd_dat(unsigned char val)
{
	LENA=1;
        lcd_wr(val);
        LDAT=1;
        //delay(3);
        LENA=0;
        //delay(3);
	LENA=1;
}

void lcd_init(void)
{
	LENA=0;
	LDAT=0;
	delay(20);
	LENA=1;
	
	lcd_cmd(L_CFG);
	delay(5);
	lcd_cmd(L_CFG);
        delay(1);
	lcd_cmd(L_CFG); //configura
	lcd_cmd(L_OFF);
	lcd_cmd(L_ON); //liga
	lcd_cmd(L_CLR); //limpa
	lcd_cmd(L_CFG); //configura
        lcd_cmd(L_L1);
}

void lcd_str(const char* str)
{
 unsigned char i=0;
  
 while(str[i] != 0 )
 {
   lcd_dat(str[i]);
   i++;
 }  
}

void main(void) {
    
    //Inicjalizacja konwertera analogowo cyfrowego
    ADCON0=0x01;
    ADCON1=0x0B;
    ADCON2=0x01;
    
    TRISA=0xC3;
    TRISB=0x3F;   
    TRISC=0x01;
    TRISD=0x00;
    TRISE=0x00;
    
    lcd_init(); //Inicjalizacja wy?wietlacza
    lcd_cmd(L_CLR); //Czyszczenie wy?wietlacza
    unsigned int tmp = 0;          // wynik z potencjometra
    unsigned int tmp1 = 0;      //wartosc zastepcza dla tmo uzywana do obliczen
    unsigned int min=0;         //l. min 2 gracza
    unsigned int min2=0;        //l. min 1 gracza
    unsigned int sek=0;         //l. sek 2 gracza
    unsigned int sek2=0;        //l. sekund 1 gracz
    unsigned int time=7;        //czas rozgrywki poczatkowo poza zakresem mozliwosci
    
    while(1)
    {
        delay(1000);        //opoznienie
        
        
        tmp=((unsigned int)adc(1) / 170);   //zczytanie danych z potecjonometru co 170 co daje nam 3 bloki
        if(time == 7 ){     //jezeli wartosc czasu równe jest siedem czyli jest poza mozliwosciami to
            tmp1=tmp;       //do tmp1 na ktorym bedziemy pracowa? przypisuje tmp
            if(tmp1<1)      //jezeli tmp1 jest przed 1 progiem to
                time=5;     //czas rozgrywki jest 5min
            else if(tmp1<2)    //jezeli tmp jest za 1 progiem ale przed drugim
                time=3;         //to czas rozgrywki rowny jest 3 min

            else if(tmp1<6)     // jezeli wartosc tmp jest za drugim progiem
                time=1;         //to czas rozgrywki rowny jest 1 min
            min=time;       //przypisuje czas 1 graczowi
            min2=time;      //przypisuje czas 2 graczowi
        }
        lcd_cmd(L_CLR);     //czysci ekran
        lcd_cmd(L_L1);      //ustawia kursor w 1 lini
        lcd_dat(71);        //"G"
        lcd_dat(114);       //"R"
        lcd_dat(97);        //"A"
        lcd_dat(99);        //"C"
        lcd_dat(122);       //"Z"
        lcd_dat(160);       //" "
        lcd_dat(49);        //"1"
        lcd_dat(160);       //" "
        lcd_dat(48+min2/10);//wyswietlenie 1 cyfry czasu 1 gracza w minutach
        lcd_dat(48+min2%10);//wyswietlenie 12cyfry czasu 1 gracza w minutach
        lcd_dat(58);        //":"
        lcd_dat(48+sek2/10);//wyswietlenie 1 cyfry czasu 1 gracza w sekundach
        lcd_dat(48+sek2%10);//wyswietlenie 2 cyfry czasu 1 gracza w sekundach
        
        lcd_cmd(L_L2);  //przejscie do 2 lini
        lcd_dat(71);    //"G"
        lcd_dat(114);   //"r"
        lcd_dat(97);    //"a"
        lcd_dat(99);    //"c"
        lcd_dat(122);   //"z"
        lcd_dat(160);   //" "
        lcd_dat(50);    //"2"
        lcd_dat(160);   //" "
        lcd_dat(48+min/10);//wyswietlenie 1 cyfry czasu 2 gracza w minutach
        lcd_dat(48+min%10);//wyswietlenie 2 cyfry czasu 2 gracza w minutach
        lcd_dat(58);
        lcd_dat(48+sek/10);//wyswietlenie 1 cyfry czasu 2 gracza w sekundach
        lcd_dat(48+sek%10);//wyswietlenie 2 cyfry czasu 2 gracza w sekundach
            
                  unsigned int i = 6000;
        while(PORTBbits.RB4 && PORTBbits.RB3 && i && PORTBbits.RB2 && PORTBbits.RB5> 0)
        {
            i--;
        }
                  
        if(PORTBbits.RB3 == 0){ //jezeli wcisniety guzik RB3
           if(sek>0){sek--;}    // jezeli sekundy sa wieksze od zera to odejmij sekunde
           else if(sek <= 0){ //jezeli sekundy si? sko?cz?
                    if(min>0){  //i s? jakie? minuty
                    min=min-1;  //to odejmij minute
                    sek=59;     //i ustaw licznik sekund na 59
                    }else{      //jesli ich nie ma to
                        
                        min=0;  //zeruj minuty
                        sek=0;  //zeruj sekundy
                        lcd_cmd(L_CLR); //wyczysc ekran
                        lcd_cmd(L_L1);  //ustaw kursor w 1 lini
                        lcd_str("Gracz 2 Przegral"); //wyswietl komunikat
                    
                        lcd_cmd(L_L2);  //ustaw w drugiej
                        lcd_str("Koniec czasu    "); //wyswietl komunikat
                        time=7;     // wroc z czasem do pozycji poczatkowej
                        delay(3000); //wstrzymaj na ekranie przez 3 sekundy
                    }
              }
          
              
        }
        
         if(PORTBbits.RB4 == 0){    //analogicznie jak dla gracza 1
             if(sek2>0){sek2--;}
             else if(sek2 <= 0){
                    if(min2>0){
                    min2=min2-1;
                    sek2=59;
                    }else{
                        
                        min2=0;
                        sek2=0;
                        lcd_cmd(L_CLR);
                        lcd_cmd(L_L1);
                        lcd_str("Gracz 1 Przegral");
                    
                        lcd_cmd(L_L2);
                        lcd_str("Koniec czasu    ");
                        time=7;
                        delay(3000);
                    }
              }
          
            
             
        }

    }
    
    return;
}
