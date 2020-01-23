/* 
 * File:   keyboard.h
 * Author: jeff
 *
 * Created on 2 janvier 2020, 18:11
 */

#ifndef KEYBOARD_H
#define	KEYBOARD_H
#define KBDCOL5 PORTAbits.RA0
#define KBDCOL4 PORTAbits.RA1
#define KBDCOL3 PORTAbits.RA2
#define KBDCOL2 PORTAbits.RA3
#define KBDCOL1 PORTBbits.RB12
#define KBBRAW1  PORTBbits.RB6
#define KBDRAW2  PORTBbits.RB7
#define KBDRAW3  PORTBbits.RB10
#define KBDRAW4  PORTBbits.RB11
#define KBDRAW5  PORTBbits.RB12
#define KBDRAW6  PORTBbits.RB13
#define KBDRAW7  PORTBbits.RB14


#define DIRKBDRAW1  TRISBbits.TRISB6
#define DIRKBDRAW2  TRISBbits.TRISB7
#define DIRKBDRAW3  TRISBbits.TRISB10
#define DIRKBDRAW4  TRISBbits.TRISB11
#define DIRKBDRAW5  TRISBbits.TRISB12
#define DIRKBDRAW6  TRISBbits.TRISB13
#define DIRKBDRAW7  TRISBbits.TRISB14


#define PULLUPRB5  CNPU2bits.CN27PUE 
#define PULLUPRB6  CNPU2bits.CN24PUE 
#define PULLUPRB7  CNPU2bits.CN23PUE 
#define PULLUPRB8  CNPU2bits.CN22PUE
#define PULLUPRB9 CNPU2bits.CN21PUE
#define PULLUPRB10 CNPU2bits.CN16PUE
#define PULLUPRB11 CNPU1bits.CN15PUE
#define PULLUPRB12  CNPU1bits.CN14PUE 
#define PULLUPRB13 CNPU1bits.CN13PUE
#define PULLUPRB14  CNPU1bits.CN12PUE 
#define PULLUPRB15 CNPU1bits.CN11PUE

void initKbd()
{
    
    DIRKBDRAW1=1;
    DIRKBDRAW2=1;
    DIRKBDRAW3=1;
    DIRKBDRAW4=1;
    DIRKBDRAW5=1;
    DIRKBDRAW6=1;
    DIRKBDRAW7=1;
    // Résistances pull-up
    PULLUPRB6=1;
    PULLUPRB7=1;
    PULLUPRB10=1;
    PULLUPRB11=1;
    PULLUPRB12=1;
    PULLUPRB13=1;
    PULLUPRB14=1;
}

int readKey()
{
    int key=0;
    
    KBDCOL5=0;
    __delay_ms(10);
    if (KBDRAW7==0) key=1;
     KBDCOL5=1;
   return key;
    
    
    
}

#endif	/* KEYBOARD_H */

