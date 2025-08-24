/*
 * File:   liftinput.c
 * Author: ashva
 *
 * Created on 1 August, 2025, 3:07 PM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
int S,F;
int lift;
void enable();
void delay(unsigned int);
void command(char,char);
void display(char *);
void compare();
char gnd[30]="-G";
char flr1[30]="-1ST";
char flr2[30]="-2ND";
char flr3[30]="-3RD";
char flr4[30]="-4TH";
void main(void) 
{
    PORTA=PORTB=PORTC=PORTD=PORTE=0X00;
    TRISC=TRISE=TRISD=0X00;
    TRISA=0X1F;
    TRISB=0X1F;
    ANSEL=0X00;
    ANSELH=0X00;
    command(0,0x38);
    command(0,0x0E);
    command(0,0x80);
    command(1,'L');
    command(0,0xc0);
    command(1,'F');
    while(1)
    {   
   
        if(S == F)
        {
            RB7=RB6=0;
        }
      
        
        if(S<F)
        {
            RB7=0; RB6=1;
        }
           
            
            if(S>F)
            {
                RB6=0; RB7=1;
            }
        if(RB4==0)
        {
            S=0; 
             command(0,0x81);  
             command(1,'G');
        }
      if(RB1==0)
        {
           S=1;  
           command(0,0x81);
           command(1,'1');
        }
        if(RB2==0)
        {
            S=2; 
            command(0,0x81);   
            command(1,'2');
        }
        if(RB3==0)
        {
           S=3; 
            command(0,0x81);    command(1,'3');
   
        }
        if(RA0==1)
        {
           F=0; 
            command(0,0xc1);
            display(gnd);
        }
       if(RA1==1) 
        {
           F=1;  
            command(0,0xc1);
           display(flr1);
        }
        if(RA2==1)
        {
           F=2; 
            command(0,0xc1);
            display(flr2);
        }
        if(RA3==1)
        {
           F=3; 
            command(0,0xc1);
            display(flr3);
        }
    }

}

void compare()
{
    
}
void command(char re,char rs)
{
    RE0=re;
    PORTD=rs;
    enable();
}
void enable()
{
    RE1=1;
    delay(50);
    RE1=0;
    delay(50);
}
void delay(unsigned int a)
{
    while(a--);
}
void display(char *str)
{
    for(int i=0;str[i]!='\0';i++)
    {
        command(1,str[i]);
    }
} 