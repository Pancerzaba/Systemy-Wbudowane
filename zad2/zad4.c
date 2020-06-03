p   // CONFIG1H
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
    
    int a=1;
    unsigned int min=0;
    unsigned int sek=0;
    
    while(1){   
        delay(500);
        if(sek>59) //jezeli pokaze wiecej niz 60 sekund to zeruj
            sek=0;
        lcd_cmd(L_L1);
         if(a%4 == 1)       //jezeli jest na 1 etapie to
                lcd_str("Moc 800W        "); //wyswietl napis
         else if(a%4 == 2)   //jesli na 2 to
                lcd_str("Moc 600W        "); //wyswietl napis
         else if(a%4 == 3)   //jesli na 3 to
                lcd_str("Moc 350W        "); //wyswietl napis
         else if(a%4 == 0)   //jesli na 4 to
                lcd_str("Moc 200W        "); //wyswietl napis
        lcd_cmd(L_L2); //Ustawienie karetki w pierwszej linii
                lcd_dat(67);    //wyswietlaj po literze
                lcd_dat(122);
                lcd_dat(97);
                lcd_dat(115);
                lcd_dat(160);
         
                lcd_dat(min/10+48); //wyswietlaja
                lcd_dat(min%10+48); //aktualny
                lcd_dat(58);        //czas
                lcd_dat(sek/10+48); 
                lcd_dat(sek%10+48);
                lcd_dat(160);
                lcd_dat(160);
                lcd_dat(160);
                lcd_dat(160);
                lcd_dat(160);
                lcd_dat(160);
                
                unsigned int i = 6000;
        while(PORTBbits.RB4 && PORTBbits.RB3 && i && PORTBbits.RB2 && PORTBbits.RB5> 0)
        {
            i--;
        }
                
        if(PORTBbits.RB5 == 0)  //jesli nacisniety
        {
            a++;        //to przelacz na kolejny etap mocy
            delay(1000);    //spowolnienie o 1 sek
        }
        if(PORTBbits.RB4 == 0){   
            min++;      //dodaj minute przy wcisietym guziku
            if(min>59)  //jesli minut jest wiecej niz 59 to wyzeruj
                min=0;
        }
        if(PORTBbits.RB3 == 0){      
            
            sek=sek+10; //dodaj 10 sek
             if(sek>59) //jesli przekroczy 59 zeruj
                sek=0;
        }
        if(PORTBbits.RB2 == 0){  //jesli wcisniety to startuj zegar
            delay(500);
            
            if (sek==0& min!=0){    //jesli sekundy wybija 0 a sa jeszcze minuty
                
                min--;  //odejmij minute
                sek=59; //ustaw sekundy na 59
            }
            if(sek<=0 & min<=0){    //jesli minuty i sekundy wybija 0
                min=0;
                sek=0;
                lcd_cmd(L_L2); //Ustawienie karetki w pierwszej linii
                lcd_dat(75);    //WYSWIETL NAPIS
                lcd_dat(111);
                lcd_dat(110);
                lcd_dat(105);
                lcd_dat(101);
                lcd_dat(99);
                lcd_dat(160);
                lcd_dat(160);
                lcd_dat(160);
                lcd_dat(160);
                lcd_dat(160);
                lcd_dat(160);    
                lcd_dat(160);
                lcd_dat(160);
                lcd_dat(160);
                lcd_dat(160);
                }
                sek=sek-1;          //odejmij 1 sekunde
            }
           if(PORTBbits.RB1 == 0){  //jezeli wcisniety
               min=0;   //wyzeruj wszystkie ustawienia
               sek=0;
               a=1;
           
           }  
    }
    
    return;
}
