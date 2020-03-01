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
#define D4 PORTAbits.RA3
#define D5 PORTAbits.RA2
#define D6 PORTAbits.RA1
#define D7 PORTAbits.RA0

#define LCDON PORTBbits.RB5
#include "calculator.h"
#include "lcd.h"
#include "keyboard.h"
#include "datas.h"
#include "interpreteur.h"
#include "calculation.h"

int pDict; // Dict pointer
int pProg;
int pStack; // Stack pointer
int sStack; // Stack size
int pReturnStack; // Return stack pointer

int execError;
char buff[20];
char line[20];
char errorMsg[20];

int kbdState;

int funcLevel;

// Keyboard
#define fchar 1
#define faction 2
#define ffunc 3
#define Normal 0
#define Shift 1
#define Alpha 2


// insert a string m at position p in buffer

void strIns(int p, char *m, char *buffer) {
    int i;
    int lm = strlen(m);
    int lb = strlen(buffer);
    for (i = lb - 1; i >= p; i--) buffer[i + lm] = buffer[i];
    for (i = 0; i < lm; i++) buffer[i + p] = m[i];
    buffer[lb + lm] = 0;
}

int decAlphaKeyboard(int key, char *t) {
    int f;
    switch (key) {
        case 1: strcpy(t, "");
            f = fchar;
            break;
        case 2: strcpy(t, "UP");
            f = faction;
            break;
        case 3: strcpy(t, "");
            f = fchar;
            break;
        case 4: strcpy(t, "ALPHA");
            f = faction;
            break;
        case 5: strcpy(t, "SHIFT");
            f = faction;
            break;
        case 6: strcpy(t, "RIGHT");
            f = faction;
            break;
        case 7: strcpy(t, "C");
            f = fchar;
            break;
        case 8: strcpy(t, "LEFT");
            f = faction;
            break;
        case 9: strcpy(t, "B");
            f = fchar;
            break;
        case 10: strcpy(t, "A");
            f = fchar;
            break;
        case 11: strcpy(t, "<-");
            f = faction;
            break;
        case 12: strcpy(t, "DOWN");
            f = faction;
            break;
        case 13: strcpy(t, "F");
            f = fchar;
            break;
        case 14: strcpy(t, "E");
            f = fchar;
            break;
        case 15: strcpy(t, "D");
            f = fchar;
            break;
        case 16: strcpy(t, "K");
            f = fchar;
            break;
        case 17: strcpy(t, "J");
            f = fchar;
            break;
        case 18: strcpy(t, "I");
            f = fchar;
            break;
        case 19: strcpy(t, "H");
            f = fchar;
            break;
        case 20: strcpy(t, "G");
            f = fchar;
            break;
        case 21: strcpy(t, "P");
            f = fchar;
            break;
        case 22: strcpy(t, "O");
            f = fchar;
            break;
        case 23: strcpy(t, "N");
            f = fchar;
            break;
        case 24: strcpy(t, "M");
            f = fchar;
            break;
        case 25: strcpy(t, "L");
            f = fchar;
            break;
        case 26: strcpy(t, "U");
            f = fchar;
            break;
        case 27: strcpy(t, "T");
            f = fchar;
            break;
        case 28: strcpy(t, "S");
            f = fchar;
            break;
        case 29: strcpy(t, "R");
            f = fchar;
            break;
        case 30: strcpy(t, "Q");
            f = fchar;
            break;
        case 31: strcpy(t, "Z");
            f = fchar;
            break;
        case 32: strcpy(t, "Y");
            f = fchar;
            break;
        case 33: strcpy(t, "X");
            f = fchar;
            break;
        case 34: strcpy(t, "W");
            f = fchar;
            break;
        case 35: strcpy(t, "V");
            f = fchar;
            break;

    }
    return f;
}

int decShiftKeyboard(int key, char *t) {
    int f;

    switch (key) {
        case 1: strcpy(t, "");
            f = 0;
            break;
        case 2: strcpy(t, "'");
            f = 0;
            break;
        case 3: strcpy(t, "");
            f = 0;
            break;
        case 4: strcpy(t, "");
            f = 0;
            break;
        case 5: strcpy(t, "SHIFT");
            f = faction;
            break;
        case 6: strcpy(t, "END");
            f = ffunc;
            break;
        case 7: strcpy(t, "DO");
            f = ffunc;
            break;
        case 8: strcpy(t, "WHILE");
            f = ffunc;
            break;
        case 9: strcpy(t, "FOR");
            f = ffunc;
            break;
        case 10: strcpy(t, "IF");
            f = ffunc;
            break;
        case 11: strcpy(t, "PI");
            f = ffunc;
            break;
        case 12: strcpy(t, "WHO");
            f = ffunc;
            break;
        case 13: strcpy(t, "DISP");
            f = ffunc;
            break;
        case 14: strcpy(t, "INP");
            f = ffunc;
            break;
        case 15: strcpy(t, "STEP");
            f = ffunc;
            break;
        case 16: strcpy(t, "SQRT");
            f = ffunc;
            break;
        case 17: strcpy(t, "SQ");
            f = ffunc;
            break;
        case 18: strcpy(t, "LN");
            f = ffunc;
            break;
        case 19: strcpy(t, "INV");
            f = ffunc;
            break;
        case 20: strcpy(t, "COMP");
            f = ffunc;
            break;
        case 21: strcpy(t, "SWAP");
            f = ffunc;
            break;
        case 22: strcpy(t, "DUP");
            f = ffunc;
            break;
        case 23: strcpy(t, "POW");
            f = ffunc;
            break;
        case 24: strcpy(t, "POW10");
            f = ffunc;
            break;
        case 25: strcpy(t, "LOG");
            f = ffunc;
            break;
        case 26: strcpy(t, "FACT");
            f = ffunc;
            break;
        case 27: strcpy(t, "");
            f = 0;
            break;
        case 28: strcpy(t, "VAR");
            f = ffunc;
            break;
        case 29: strcpy(t, "MATH");
            f = ffunc;
            break;
        case 30: strcpy(t, "DROP");
            f = ffunc;
            break;
        case 31: strcpy(t, "=");
            f = fchar;
            break;
        case 32: strcpy(t, ">");
            f = fchar;
            break;
        case 33: strcpy(t, "<");
            f = fchar;
            break;
        case 34: strcpy(t, " ");
            f = fchar;
            break;
        case 35: strcpy(t, "OFF");
            f = faction;
            break;

    }
    return f;
}

int decKeyboard(int key, char *t) {
    int f;

    switch (key) {
        case 1: strcpy(t, "EDIT");
            f = faction;
            break;
        case 2: strcpy(t, "UP");
            f = faction;
            break;
        case 3: strcpy(t, "USER");
            f = faction;
            break;
        case 4: strcpy(t, "ALPHA");
            f = faction;
            break;
        case 5: strcpy(t, "SHIFT");
            f = faction;
            break;
        case 6: strcpy(t, "RIGHT");
            f = faction;
            break;
        case 7: strcpy(t, "'");
            f = fchar;
            break;
        case 8: strcpy(t, "LEFT");
            f = faction;
            break;
        case 9: strcpy(t, "STO");
            f = ffunc;
            break;
        case 10: strcpy(t, "ARC");
            f = faction;
            break;
        case 11: strcpy(t, "<-");
            f = faction;
            break;
        case 12: strcpy(t, "DOWN");
            f = faction;
            break;
        case 13: strcpy(t, "TAN");
            f = ffunc;
            break;
        case 14: strcpy(t, "SIN");
            f = ffunc;
            break;
        case 15: strcpy(t, "COS");
            f = ffunc;
            break;
        case 16: strcpy(t, "/");
            f = ffunc;
            break;
        case 17: strcpy(t, "9");
            f = fchar;
            break;
        case 18: strcpy(t, "8");
            f = fchar;
            break;
        case 19: strcpy(t, "7");
            f = fchar;
            break;
        case 20: strcpy(t, "ENTER");
            f = faction;
            break;
        case 21: strcpy(t, "*");
            f = ffunc;
            break;
        case 22: strcpy(t, "6");
            f = fchar;
            break;
        case 23: strcpy(t, "5");
            f = fchar;
            break;
        case 24: strcpy(t, "4");
            f = fchar;
            break;
        case 25: strcpy(t, "E");
            f = fchar;
            break;
        case 26: strcpy(t, "-");
            f = ffunc;
            break;
        case 27: strcpy(t, "3");
            f = fchar;
            break;
        case 28: strcpy(t, "2");
            f = fchar;
            break;
        case 29: strcpy(t, "1");
            f = fchar;
            break;
        case 30: strcpy(t, "-");
            f = fchar;
            break;
        case 31: strcpy(t, "+");
            f = ffunc;
            break;
        case 32: strcpy(t, " ");
            f = fchar;
            break;
        case 33: strcpy(t, ".");
            f = fchar;
            break;
        case 34: strcpy(t, "0");
            f = fchar;
            break;
        case 35: strcpy(t, "C");
            f = faction;
            break;

    }
    return f;
}
// LCD

void delay(float sec) {

    int d = (int) (1000 * sec);
    __delay_ms(d);

}
#define MAXBUFFERFUNC 1000
char bufferFunc[MAXBUFFERFUNC];

// Disp Stack content on LCD

void dispStack() {
    clearLcd();
    if (stackDisp(buffer, 1) == 1) dispLine1(buffer);
    else dispLine1("");
    if (stackDisp(buffer, 0) == 1) dispLine2(buffer);
    else dispLine2("                ");
    if (pStack == -1) strcpy(buffer, "0");
    else sprintf(buffer, "%d", sStack);
    msgCrt(buffer);
}

void printError() {
    printf("Error : %d \n", execError);
}

// define a new function 

void defineFunction(char *name, char *source) {
    char buffer[20];
    strcpy(bufferFunc, source);
    sprintf(buffer, "'%s'", name);
    interpretString(buffer);
    setFunc();
    compile();
}

// Disp error message if any

void messageError() {
    if (execError != 0) {
        Lcd_Clear();
        switch (execError) {
            case Error: writeError(errorMsg, "Error");
                break;
            case ErrorStackEmpty: writeError(errorMsg, "Stack Empty");
                break;
            case ErrorIncorrectArgument: writeError(errorMsg, "Incorrect Arg.");
                break;
            case ErrorUnknownVar: writeError(errorMsg, "Unknown var");
                break;
            case ErrorFuncNotFound: writeError(errorMsg, "Unknown Func");
                break;
            case ErrorUnknownIdentifier: writeError(errorMsg, "Unknown Id");
                break;
            case ErrorString: writeError(errorMsg, "Incorrect String");
                break;
            case ErrorForVar: writeError(errorMsg, "Incorrect For Var");
                break;
        }
        __delay_ms(1000);

        dispStack();
    }
}

// disp edited line on LCD second line 

void dispEditLine() {
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String("                ");
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String(line);
}

// Set indicator s on LCD

void indicator(char *s) {
    Lcd_Set_Cursor(1, 15);
    Lcd_Write_String(s);
}

//Find the  number n word in bufferFunc

int mot(int n, char *m) {
    int found = 0;
    int ip = -1;
    int i;
    int im = 0;
    int state = 0;
    int j = 0;
    char c;
    i = 0;
    if (strlen(bufferFunc) > 0)
        if (bufferFunc[strlen(bufferFunc) - 1] != ' ')
            strcat(bufferFunc, " ");
    while ((i < strlen(bufferFunc))&&(!found)) {
        c = bufferFunc[i++];
        switch (state) {
            case 0: if (c > ' ') {
                    state = 1;
                    im++;
                    if (im == n) {
                        ip = i - 1;
                        m[j++] = c;
                    }
                }
                break;
            case 1:
                if (c <= ' ') {
                    state = 0;
                    if (im == n) {
                        m[j] = 0;
                        found = 1;
                    }
                } else if (im == n) {
                    m[j++] = c;
                }
                break;
        }


    }
    return ip;
}

void motInsert(int pm, char *m) {
    int p;
    char s[20];
    p = mot(pm, s);
    strcpy(s, m);
    strcat(s, " ");

    if (p == -1) {
        p = strlen(bufferFunc) - 1;
        strIns(0, " ", s);
    }
    strIns(p, s, bufferFunc);
}

void motSup(int pm)
{
    int p;
    int i;
    int len;
    char s[20];
    p=mot(pm,s);
    len=strlen(s);
    for (i=p; i<strlen(bufferFunc)-len; i++)
    {
        bufferFunc[i]=bufferFunc[i+len];
    }
    bufferFunc[strlen(bufferFunc)-len]=0;
}

void editFunction()
{
    int i;
    char c;
    int k;
    int fin = 0;
    char m[20];
    char func[10];
    char inst[20];

    int f;
    i = 1;
    kbdState=Normal;
    if (menuFunc(func)) {
        decompFunc(func);
        strcpy(line,"");
        while (!fin) {
            Lcd_Clear();
            f = mot(i, m);

            if (f >= 0) {
                sprintf(inst, "%d  %s", i, m);
                Lcd_Set_Cursor(1, 1);
                Lcd_Write_String(inst);
            }
            
            if (strlen(line)>0) dispEditLine();
            else {
            f = mot(i + 1, m);

            if (f >= 0) {
                sprintf(inst, "%d> %s", i + 1, m);
                Lcd_Set_Cursor(2, 1);
                Lcd_Write_String(inst);
            }
            }
            
            if (kbdState==Shift) indicator("S");
            else if (kbdState==Alpha) indicator("A");
            else indicator(" ");
            
            while ((c = readKey()) == 0);

            if (kbdState == Alpha) f = decAlphaKeyboard(c, buffer);
            else if (kbdState == Shift) f = decShiftKeyboard(c, buffer);
            else f = decKeyboard(c, buffer);
            if (f==fchar)
            {
                 strcat(line, buffer);
            }
            if (f == faction) {
                if (cmp(buffer, "C")) {
                    fin = 1;
                }
                else if (cmp(buffer, "<-")) {
                   k = strlen(line);
                    if (k > 0) {
                        line[k - 1] = 0;
                    } else motSup(i+1);
                    
                }
                    else if (cmp(buffer, "DOWN")) {
                    if  (strlen(line)>0) { motInsert(i + 1, line); strcpy(line,""); }
                    i = i + 1;
                } 
                    else if (cmp(buffer, "UP")) {
                     if  (strlen(line)>0) { motInsert(i + 1, line); strcpy(line,""); }
                    if (i > 1) i = i - 1;
                } else if (cmp(buffer, "ALPHA")) {
                    if (kbdState != Alpha) kbdState = Alpha;
                    else  kbdState = Normal;                    
                } else if (cmp(buffer, "SHIFT")) {
                    if (kbdState != Shift) kbdState = Shift;
                    else kbdState = Normal;
                }
            } else if (f == ffunc) {
                if  (strlen(line)>0) { motInsert(i + 1, line); strcpy(line,""); }
                motInsert(i + 1, buffer);
            }
            while (readKey() != 0);
             if (kbdState == Shift)
                if (!cmp(buffer, "SHIFT")) {
                    kbdState = Normal;
                    indicator(" ");
                }

        }
        supFunc(func);
        defineFunction(func, bufferFunc);
    }
}


int iMF = 0;

int menuFunc(char * func) {
    char s[10];

    int c = 1;
    int fin = 0;
    strcpy(line, "");
    int imax = numberOfFunction();
    if (iMF > imax - 3) iMF = imax - 1;

    while (fin == 0) {
        Lcd_Clear();
        if (findFuncN(1 + iMF, s)>-1) menu(1, s);
        if (findFuncN(2 + iMF, s)>-1) menu(2, s);
        if (findFuncN(3 + iMF, s)>-1) menu(3, s);

        while ((c = readKey()) == 0);
        if (c == 4) {
            findFuncN(1 + iMF, func);
            fin = 2;
        } else if (c == 3) {
            findFuncN(2 + iMF, func);
            fin = 2;
        } else if (c == 2) {
            findFuncN(3 + iMF, func);
            fin = 2;
        } else if (c == 1) {
            if (iMF < imax - 3) iMF += 3;
            else iMF = 0;
        } else if (c == 5) {
            if (iMF > 3) iMF -= 3;
            else iMF = imax - 3;
        } else fin = 1;
        while (readKey() != 0);
    }

    return fin;
}

void goSleep() {
    msg("Enter sleep mode...");
    __delay_ms(300);
    LCDON = 0;
    // TRISBbits.TRISB6=1.
    // CNEN1.CN14IE=1;
    // CNPU1.CN14PU1=1;
    // IC14CON.ICM0=1;
    // Ports in input
    TRISB = 0xFFFF;
    TRISA = 0x1F;
    Sleep();
}

int main(int argc, char** argv) {

    // Init Ports
    AD1PCFG = 0x1FFF;

    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB5 = 0;
    TRISA = 0;

    // determine if wake up or reset
    int wakeup;

    if (RCONbits.SLEEP == 1) wakeup = 1;
    else wakeup = 0;

    // Start the LCD
    LCDON = 1;
    __delay_ms(100);
    // Initialise the Keyborad
    initKbd();
    // Initialise the LCD
    Lcd_Init();



    dispLine1("Calc RPN v0.101");
    if (wakeup == 1) dispLine2("Wakeup...");
    else dispLine2("Hard reset");
    __delay_ms(300);



    initStack();
    clearLcd();

    // Init buffer for console
    strcpy(line, "");
    // Flag first char or console
    int fnew = 1;
    // State of keyboard
    kbdState = Normal;

    // Useful functions
    defineFunction("FORT", "0 1 5 'I' FOR I + END");
    //defineFunction("FACT", " 'N' STO 1 'I' STO  1 'A' STO WHILE I N <= DO  A I * 'A' STO I 1 + 'I' STO   END A ");
    defineFunction("FACT", " 'N' STO 1 1 N 'I' FOR  I * END ");
    defineFunction("INC", "1 + ");
    defineFunction("SGN", " 0 < IF -1 ELSE 1 END ");
    defineFunction("SU", "'N' STO 0 1 N 'I' FOR I INV + END  ");
    defineFunction("LOG2", "LOG 2 LOG /");

    //supFunc("FACT");

    // defineFunction("FACT", " 'N' STO 1 1 N 'I' FOR  I * END ");

    //interpretString("10");
    //interpretString("FACT");
    //    interpretString("10");
    //     interpretString("FACT");
    //decompFunc("SU");
    //strIns(4,"ESSAI ",bufferFunc);
    //    motInsert(2, "ESSAI");
    messageError();

    dispStack();

    //  interpretString("A");
    //   interpretString("B");
    //    interpretString("*");
    //   printStack();
    //interpretString("whiletest");
    if (execError != 0) printf("Error: %d\n", execError);
    while (1) {
        int c = readKey();
        if (c != 0) {
            sprintf(buffer, "Key %d", c);
            int f;
            if (kbdState == Alpha) f = decAlphaKeyboard(c, buffer);
            else if (kbdState == Shift) f = decShiftKeyboard(c, buffer);
            else f = decKeyboard(c, buffer);
            if (f == fchar) {
                strcat(line, buffer);
                // Lcd_Clear();
                if (fnew) {
                    if (stackDisp(buffer, 0) == 1)
                        dispLine1(buffer);
                    else dispLine1("                ");
                }
                dispEditLine();
                fnew = 0;
            } else if (f == faction) {

                if (cmp(buffer, "OFF")) {
                    goSleep();
                } else if (cmp(buffer, "ENTER")) {
                    if (strlen(line) > 0) interpretString(line);
                    else interpretString("DUP");
                    messageError();
                    strcpy(line, "");
                    fnew = 1;
                    dispStack();
                } else if (cmp(buffer, "<-")) {
                    int k = strlen(line);
                    if (k > 0) {
                        line[k - 1] = 0;
                        dispEditLine();
                    } else {
                        stackPop();
                        if (execError == 0) stackPushDouble(0.0);
                        dispStack();
                    }
                } else if (cmp(buffer, "ALPHA")) {
                    if (kbdState != Alpha) {
                        kbdState = Alpha;
                        indicator("A");
                    } else {
                        kbdState = Normal;
                        indicator(" ");
                    }
                } else if (cmp(buffer, "SHIFT")) {
                    if (kbdState != Shift) {
                        kbdState = Shift;
                        indicator("S");
                    } else {
                        kbdState = Normal;
                        indicator(" ");
                    }
                } else if (cmp(buffer, "USER")) {
                    if (strlen(line) > 0) {
                        interpretString(line);
                        messageError();
                    }
                    if (menuFunc(line) == 2) {
                        Lcd_Clear();
                        interpretString(line);
                        messageError();
                        strcpy(line, "");
                        fnew = 1;
                        dispStack();
                    }
                } else if (cmp(buffer, "EDIT")) {
                    editFunction();
                    dispStack();
                }
            } else if (f == ffunc) {
                if (strlen(line) > 0) {
                    interpretString(line);
                    messageError();
                }
                interpretString(buffer);
                messageError();
                strcpy(line, "");
                fnew = 1;
                dispStack();
            }
            if (kbdState == Shift)
                if (!cmp(buffer, "SHIFT")) {
                    kbdState = Normal;
                    indicator(" ");
                }
            while (readKey() != 0);


            //__delay_ms(100);
        }
    };

    //  printString("Enter sleep mode...");
    //  delay(1);
    //   LCDON = 0;
    //   TRISBbits.TRISB6=1.
    //   CNEN1.CN14IE=1;
    //   CNPU1.CN14PU1=1;
    //   IC14CON.ICM0=1;
    //Sleep();




    while (1) {
        PORTBbits.RB15 = 1; // LED ON
        __delay_ms(100);
        PORTBbits.RB15 = 0; // LED OFF
        // AFFE=1;
        __delay_ms(100);
        //AFFE=0;
    }
    return (EXIT_SUCCESS);
}

