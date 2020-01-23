/* 
 * File:   main.c
 * Author: jeff
 *
 * Created on 1 janvier 2020, 13:39
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// PIC24FJ64GA002 Configuration Bit Settings

// 'C' source line config statements

// CONFIG2

#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary oscillator disabled)
#pragma config I2C1SEL = PRI            // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF            // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRCPLL           // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
#pragma config SOSCSEL = SOSC           // Sec Oscillator Select (Default Secondary Oscillator (SOSC))
#pragma config WUTSEL = LEG             // Wake-up timer Select (Legacy Wake-up Timer)
#pragma config IESO = OFF               // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) disabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = ON              // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx1               // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 8000000
#define FCY 8000000UL
#include <libpic30.h>

#define RS PORTBbits.RB2
#define EN PORTAbits.RA4
#define D4 PORTAbits.RA0
#define D5 PORTAbits.RA1
#define D6 PORTAbits.RA2
#define D7 PORTAbits.RA3

#define LCDON PORTBbits.RB5
#include "calculator.h"
#include "lcd.h"
#include "keyboard.h"
#include "datas.h"
#include "interpreteur.h"
#include "calculation.h"

int pDict;
int pProg;
int pStack;
int pReturnStack;

int execError;
char buff[20];

// Afficheur

void delay(float sec)
{

    int d=(int)(1000*sec);
    __delay_ms(d);  
   
}
#define MAXBUFFERFUNC 1000
char bufferFunc[MAXBUFFERFUNC];



void printStack()
{
      printf("S-------------------\n");
   
    if (stackDisp(buffer,1)==1) 
    {
        printString(buffer); 
        printf("2:%s\n",buffer);
    }
      else 
      {
        printString("");
        printf("2:%s\n","");
      }
     if (stackDisp(buffer,0)==1) 
     {
        printString(buffer); 
        printf("1:%s\n",buffer);
    }
      else 
      {
        printString("");
        printf("1:%s\n","");
      }
      
       printf("S-------------------\n");
    //delay(1);
}

void printError()
{
    printf("Error : %d \n",execError);
}

int main(int argc, char** argv) {
  AD1PCFG=0x1FFF;  
  TRISB=0;  
  TRISA=0;
  int wakeup;
  
  if (RCONbits.SLEEP==1) wakeup=1; else wakeup=0;
  
  LCDON = 1;
  
  Lcd_Init();
  initKbd();
  clearScreen();
  printString("Calc RPN v0.1");
  printf("\n-------------------- Calc RPN v0.1\n");
  if (wakeup==1) printString("Wakeup...");
  else printString("Hard reset");
  delay(1);   
 
  initStack();
  
  //stackPushDouble(2.0);
 
 
   printf("pDict=%d\n",pDict);
   
   strcpy(bufferFunc,"LOG 2 LOG / ");
   interpretString("'LOG2'");
   setFunc();
   compile();
   strcpy(bufferFunc,"0.5 LOG2 ");
   interpretString("'BIT'");
   setFunc();
   compile();
   
   printf("pDict=%d\n",pDict);
   
   dictPrint();
   
//   execFunc("LOG2");
//  
//   if (execError!=0) printError();
    execFunc("BIT");
   if (execError!=0) printError(); 
   stackPrint();
   interpretString("WHO");
   
 
  while(1);

//  printString("Enter sleep mode...");
//  delay(1);
//   LCDON = 0;
//   TRISBbits.TRISB6=1.
//   CNEN1.CN14IE=1;
//   CNPU1.CN14PU1=1;
//   IC14CON.ICM0=1;
  //Sleep();
 
  
  
  
  while(1)
  {
      PORTBbits.RB15 = 1; // LED ON
        __delay_ms(100);
        PORTBbits.RB15 = 0; // LED OFF
       // AFFE=1;
        __delay_ms(100);
        //AFFE=0;
  }
    return (EXIT_SUCCESS);
}

