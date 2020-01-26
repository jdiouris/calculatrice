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
#define KBDCOL1 PORTBbits.RB4

#define KBDRAW1  PORTBbits.RB6
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

#define DIRKBCOL1  TRISBbits.TRISB4


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
    
    DIRKBCOL1=0;  // Other are initialized for the LCD
    // Résistances pull-up
    PULLUPRB6=1;
    PULLUPRB7=1;
    PULLUPRB10=1;
    PULLUPRB11=1;
    PULLUPRB12=1;
    PULLUPRB13=1;
    PULLUPRB14=1;
}



int readRow()
{
    int row=0;
    if (KBDRAW1==0) row=1;
    if (KBDRAW2==0) row=2;
    if (KBDRAW3==0) row=3;
    if (KBDRAW4==0) row=4;
    if (KBDRAW5==0) row=5;
    if (KBDRAW6==0) row=6;
    if (KBDRAW7==0) row=7;
    return row;
}
void delayKbd()
{
   __delay_ms(10); 
}

int findKey()
{
    int key=0;
    int r;
    
    KBDCOL1=1;
    KBDCOL2=1;
    KBDCOL3=1;
    KBDCOL4=1;
    KBDCOL5=1;
    delayKbd();
    KBDCOL1=0;
    delayKbd();
    r=readRow();
    if (r!=0)
    {
       key=(r-1)*5+1; 
    }
    KBDCOL1=1;
    if (key==0)
    {
        KBDCOL2=0;
        delayKbd();
        r=readRow();
        if (r!=0)
        {
            key=(r-1)*5+2; 
        }  
    }
    KBDCOL2=1;
    if (key==0)
    {
        KBDCOL3=0;
        delayKbd();
        r=readRow();
        if (r!=0)
        {
            key=(r-1)*5+3; 
        }  
    }
    KBDCOL3=1;
    if (key==0)
    {
        KBDCOL4=0;
        delayKbd();
        r=readRow();
        if (r!=0)
        {
            key=(r-1)*5+4; 
        }  
    }
    KBDCOL4=1;
    if (key==0)
    {
        KBDCOL5=0;
        delayKbd();
        r=readRow();
        if (r!=0)
        {
            key=(r-1)*5+5; 
        }  
    }
   return key;
    
    
    
}

int readKey()
{
    int k=0;
    
    int key=findKey();
    if (key!=0)
    {
        // anti-rebond
        delayKbd();
        if (key==findKey()) 
        {
            k=key;
        }
    }
    
    return k;
}

#endif	/* KEYBOARD_H */

