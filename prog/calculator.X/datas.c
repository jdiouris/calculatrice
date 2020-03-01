#include "calculator.h"
#include "datas.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <xc.h>


union {
    double xd;
    byte b[sizeof (double)];
} vconv;

// Byte array for the dictionart and stack
byte mem[DICTSIZE + STACKSIZE];



void initDict() {
    pDict = -1;
}

// Structure of an object
//  s=5+sizeof(object)
// p: sH
// p+1: sL
// p+2: type
// p+3: object
// p+s-2 : sH
// p+s-1 : sL

void setSize(int p,unsigned int s)
{
    mem[p] = s/256;
    mem[p+1] = s & 255;
}

unsigned int getSize(int p)
{
   return mem[p]*256+mem[p+1]; 
}

void setType(int p, int ty)
{
  mem[p+2]=ty;  
}

int getType(int p)
{
    return mem[p+2];
}

// Double 
void setDouble(double x, int p) {
    int i;
    vconv.xd = x;
    for (i = 0; i<sizeof (double); i++)
        mem[p + i] = vconv.b[i];
    vconv.xd = 0.0;
}

double getDouble(int p) {
    int i;
    for (i = 0; i<sizeof (double); i++) {
        vconv.b[i] = mem[p + i];
        //  printf("%d ",mem[p+i]);
    }
    double v = vconv.xd;
    return (v);

}


void storeDouble(int p, double x) {
    unsigned int sz = 5 + sizeof (double);
    setSize(p,sz);
    setType(p,tDouble);
    setDouble(x, p + 3);
    setSize(p + sz - 2,sz);
    
}
// Int 
void setInt(int x, int p) {
    mem[p] = x/256;
    mem[p+1] = x & 255;
}

int getInt(int p) {
    
   return mem[p]*256+mem[p+1]; 

}


void storeInt(int p, int x) {
    unsigned int sz = 5 + 2;
    setSize(p,sz);
    setType(p,tInt);
    setInt(x, p + 3);
    setSize(p + sz - 2,sz);
    
}

// Instruction
void setInst(int x, int p) {
    mem[p] = x/256;
    mem[p+1] = x & 255;
}

int getInst(int p) {
    
   return mem[p]*256+mem[p+1]; 

}


void storeInst(int p, int x) {
    unsigned int sz = 5 + 2;
    setSize(p,sz);
    setType(p,tInst);
    setInst(x, p + 3);
    setSize(p + sz - 2,sz);
    
}
// instructions

// String
void setString(char * s, int p) {
    int len = strlen(s);
    int i;
    for (i = 0; i < len; i++)
        mem[p + i] = s[i];
}

void getString(char * s, int p) {
    int len = getSize(p) - 5; // length
    int i;
    for (i = 0; i < len; i++) s[i] = mem[p + 3 + i];
    s[len] = 0;
}

void storeString(int p, char *s) {
    int sz = 5 + strlen(s);
    setSize(p,sz);
    setType(p,tString);
    setString(s, p + 3);
    setSize(p+sz-2,sz);
}

void getFunc(char * s, int p) {
    int len = getSize(p) - 5; // length
    int i;
    for (i = 0; i < len; i++) s[i] = mem[p + 3 + i];
    s[len] = 0;
}

// Stack Manipulation

void initStack() {
    pStack = -1;
    sStack=0;
}

int nextpStack() {
    if (pStack == -1) pStack = STACK0;
    else pStack += getSize(pStack);
    sStack++;
    return pStack;
}

int stackPushDouble(double x) {
    int error;
    error = 0;
    nextpStack();
    storeDouble(pStack, x);
    return error;
}

double stackGetTopDouble() {
    double v=0;
    if (pStack==-1) execError=ErrorStackEmpty;
    else v = getDouble(pStack + 3);
 
    return v;
}

int stackPushInt(int x)
{
     int error;
    error = 0;
    nextpStack();
    storeInt(pStack, x);
    return error;
}

int stackPushInst(int x)
{
     int error;
    error = 0;
    nextpStack();
    storeInst(pStack, x);
    return error;
}

int stackPushString(char *s) {
    int error;
    error = 0;
    nextpStack();
    storeString(pStack, s);
    return error;
}

void stackGetTopString(char * s) {
    int len = getSize(pStack) - 5;
    int i;
    for (i = 0; i < len; i++) s[i] = mem[pStack + 3 + i];
    s[len] = 0;

}

int stackPop() {
    int error = 0;
    int s = getSize(pStack - 2);
    if (pStack == STACK0) { pStack = -1; sStack=0; }
    else if (pStack > 0) { pStack -= s; sStack--; }
    else {
        execError = ErrorStackEmpty;
    }
    
    return execError;
}

int stackGetTopType() {
    return mem[pStack + 2];
}

void disp(int p, char *s)
{
    double f;
    int i;
    char buffer[20];
    switch (getType(p)) {
                case tDouble:
                    f = getDouble(p + 3);
                    sprintf(s, "%f", f);
                    break;
                case tInt:
                    i = getInt(p + 3);
                    sprintf(s, "%d", i);
                break;
                case tInst:
                    i = getInst(p + 3);
                    sprintf(s,"Inst-%d", i);
                break;
                case tString:
                    getString(buffer, p);
                    sprintf(s,"%s",buffer);
                    break;
                case tVar:
                    getString(buffer, p);
                    sprintf(s,"var %s",buffer);
                    break;
                case tFunc:
                    getString(buffer, p);
                    sprintf(s,"Func %s",buffer);
                    break;
            }
}

int stackDisp(char *s, int ind) {
    int p;
    int trouve = 0;
    int i;
    double f;
    char buffer[20];
    strcpy(s,"");
    // printf("\n");
    p = pStack;
    
        for (i = 0; i < ind; i++) 
        {
            if (p>STACK0) p -= getSize(p-2);
            else p=STACK0-2;
        }
        if (p >= STACK0) {

            switch (getType(p)) {
                case tDouble:
                    f = getDouble(p + 3);
                    sprintf(s, "%g", f);
                    break;
                case tInt:
                    i = getInt(p + 3);
                    sprintf(s, "%d", i);
                break;
                case tInst:
                    i = getInst(p + 3);
                    sprintf(s,"Inst-%d", i);
                break;
                case tString:
                    
                    getString(buffer, p);
                    sprintf(s,"\'%s\'",buffer);
                    break;
            }

            trouve = 1;
        }
  
    return trouve;
}

void stackPrint()
{
    int i=0;
    char s[20];
    printf("Stack: ");
    while (stackDisp(s,i)==1)
    { 
        printf("%i : %s  ",i+1,s);
        i++;
    }
    printf("\n");
}

void dictPrint()
{
    int i = 0;
    char s[20];
    while (i <= pDict) {
        disp(i,s);
        printf("%i : %s  ",i,s);
        i += getSize(i);   
    }
   printf("\n");
}

    
 void setVarLevel(int p, int v)
 {
     mem[p+3]=v;
 }
 
 int getVarLevel(int p)
 {
     return mem[p+3];
 }
 
 void getVarName(char * s, int p) {
    int len = getSize(p) - 6; // length
    int i;
    for (i = 0; i < len; i++) s[i] = mem[p + 4 + i];
    s[len] = 0;
}

// Variables
void storeVar(int p, char *s) {
    int sz = 6 + strlen(s);
    setSize(p,sz);
    setType(p,tVar);
    setVarLevel(p,funcLevel);
    setString(s, p + 4);
    setSize(p+sz-2,sz);
}

int nextpDict() {
    if (pDict == -1) pDict = DICT0;
    else pDict += getSize(pDict);
    return pDict;
}




// store on Dict value on Stack

void storeValue() {
    int len = getSize(pStack);
    int i;
    if (pStack>-1)
    {
    nextpDict();
    for (i = 0; i < len; i++) {
        mem[pDict + i] = mem[pStack + i];
    }
    stackPop();
    }
    else execError = ErrorStackEmpty;
            
}


// get Value on the stack

void getValue(int p) {
    int len = getSize(p);
    int i;
    nextpStack();
    for (i = 0; i < len; i++) {
        mem[pStack + i] = mem[p + i];
    }
}


// Variables ---------------------------------------------------------------
// find var
int findVar(char *s)
{
    int i = 0;
    int p = -1;
    char svar[20];
    while ((i <= pDict)&&(p==-1)) {
        if (getType(i) == tVar) {
            getVarName(svar, i);
            if ((strcmp(s, svar) == 0)&&getVarLevel(i)==funcLevel) p = i;
        }
        i += getSize(i);
    }
    return p;
}

// Sup var at position p
void supVarp(int p)
{
        int pp;
        // supprime l'ente^te avecle nom
        int sz=getSize(p);
        int psave=pDict;
        int pmax=nextpDict();
        pDict=psave;
        for (pp=p+sz; pp<pmax; pp++)
        {
            mem[pp-sz]=mem[pp];
        }
        pDict-=sz; //getSize(pDict-2);
        // supprime le contenu
        sz=getSize(p);
        psave=pDict;
        pmax=nextpDict();
         pDict=psave;
        for (pp=p+sz; pp<pmax; pp++)
        {
            mem[pp-sz]=mem[pp];
        }
        pDict-=getSize(pDict-2);
    
}

// Sup var with name s
void supVar(char *s)
{
    int p=findVar(s);
    if (p>=0) supVarp(p);
   
}

// sup vars with funcLevel
void supVarLevel()
{
    int i = 0;
    while (i < pDict) {
        if (getType(i) == tVar)
        {
            if (getVarLevel(i)==funcLevel) supVarp(i);
        }   
        else i += getSize(i);
    }
}
// set variable
// stack before : 1:var name, 2: value
// stack after : 

void setVar() {
    char name[20];
    if (stackGetTopType()==tString)
    {
        stackGetTopString(name);
        stackPop();
        supVar(name);
        int p = nextpDict();
        storeVar(p, name);
        storeValue();
    }
    else execError=ErrorIncorrectArgument;
}


// get variable (name :s))
// stack before : 
// stack after : 1: value

void getVar(char *s) {
    int p=findVar(s);

    if (p >= 0) {
        p += getSize(p);
        getValue(p);
    } else 
    {
        execError=ErrorUnknownVar;
    }
}

// Functions *******************************************************************

void storeFunc(int p, char *s) {
   int sz = 5 + strlen(s);
    setSize(p,sz);
    setType(p,tFunc);
    setString(s, p + 3);
    setSize(p+sz-2,sz);
}
// set Func 
// 
void setFunc()
{
    char name[20];
    stackGetTopString(name);
    printf("setFunc: %s \n",name);
    stackPop();
    int p=nextpDict();
    storeFunc(p,name);
}


int findFunc(char *s)
{
    int i = 0;
    int p = -1;
    char svar[20];
    while ((i < pDict)&&(p==-1)) {
        if (getType(i) == tFunc) {
            getString(svar, i);
            if (strcmp(s, svar) == 0) p = i;
        }
        i += getSize(i);
    }
    return p;
}

int findFuncN(int N, char *s)
{
    int i = 0;
    int p = -1;
    int n=0;
    while ((i < pDict)&&(p==-1)) {
        if (getType(i) == tFunc) {
            n++;
            if (n==N)
            {
                getString(s, i);
                p = i;
            }
        }
        i += getSize(i);
    }
    return p;
}

int numberOfFunction()
{
    int n=0;
    int i = 0;
    while (i < pDict) {
        if (getType(i) == tFunc) n++;
        i += getSize(i);
    }
    return n;
}

void supFunc(char *s)
{
    int p0=findFunc(s);
    int end=0;
    int func;
    int p=p0;
    int i;
    if (p>=0){
        while (end==0)
        {
            if (getType(p)==tInst){
                func = getInst(p + 3);
                if (func==Func_rtn) end=1;
            }
            p+=getSize(p);
        }
        
        nextpDict();
        
        
        for (i=p; i<pDict; i++)
            mem[p0+i-p]=mem[i];
        pDict-=p-p0;
        pDict-=getSize(pDict-2);
    }
}
void who()
{
    int i = 0;
    char svar[20];
    while (i < pDict) {
        if (getType(i) == tVar) {
            clearLcd();
            getVarName(svar, i);
            strcat(svar," (var)");
            msg(svar);
            printf("who:var %s\n",svar);
            waitKey();
        }
        if (getType(i) == tFunc) {
            getString(svar, i);
            clearLcd();
            strcat(svar," (func)");
            msg(svar);
            printf("who:Func %s\n",svar);
            waitKey();
        }
        i += getSize(i);
     
    }
}
