/* 
 * File:   datas.h
 * Author: jeff
 *
 * Created on 3 janvier 2020, 10:09
 */

#ifndef DATAS_H
#define	DATAS_H

typedef unsigned char byte;

// define type of objects

#define tDouble 0
#define tString 1
#define tInt 2
#define tMatrix 3
#define tFunc 4
#define tVar 5
#define tInst 6


// define sizes of Dictionary, data stack and return stack
#define DICTSIZE 1000
#define RETURNSTACKSIZE 100
#define STACKSIZE 1000
#define STACK0 DICTSIZE
#define DICT0 0

// Operators
#define Op_add 0
#define Op_sub 1
#define Op_mul 2
#define Op_div 3
#define Op_eq 4
#define Op_gt 5
#define Op_lt 6
#define Op_gte 7
#define Op_lte 8

// Math functions
#define Func_abs 100
#define Func_cos 101
#define Func_sin 102
#define Func_sto 103
#define Func_rcl 104
#define Func_disp 105
#define Func_set 106
#define Func_inc 107
#define Func_dec 108
#define Func_nraw 109
#define Func_ncol 110
#define Func_let1 111
#define Func_let2 112
#define Func_get1 113
#define Func_get2 114
#define Func_tan 115
#define Func_atan 116
#define Func_exp 117
#define Func_log 118
#define Func_neg 119
#define Func_exec 120
#define Func_rand 121
#define Func_call 122
#define Func_end 123
#define Func_sqrt 124
#define Func_int 125
#define Func_inv 126


#define Func_swap 127
#define Func_dup 128

#define Func_pi 129


// Stack and Programing functions

#define Func_for 1000
#define Func_next 1001
#define Func_if 1002
#define Func_endif 1003
#define Func_else 1004
#define Func_goto 1005
#define Func_while 1009
#define Func_rtn 1010

#define Func_who 1011

// Errors
#define Error 1
#define ErrorStackEmpty 2
#define ErrorIncorrectArgument 3
#define ErrorUnknownVar 4
#define ErrorFuncNotFound 5
#define ErrorUnknownIdentifier 6
#define ErrorString 7


// Pointers
extern int pDict;            // dictionary pointer
extern int pStack;           // Stack pointer
extern int pReturnStack;     // Return stack pointer

// Other variable
extern int execError;        // Execution error
extern char bufferFunc[1000]; // Editing function buffer

extern char buff[20];

unsigned int getSize(int p);
int getType(int p);

// Initialisations
void initDict();   // Dictionary initialisation




// Stack
void initStack(); // Stack initialization

int stackPushDouble(double x); // Push double on stack 
double stackGetTopDouble(); // Get double from stack

int stackPushString(char *s); // Push a string on stack
void stackGetTopString(char * s); // Get a string on stack

int stackPushInt(int x); // Push int on stack

void storeValue(); // Store stack top on dictionary

void getValue(int p) ; // get dictionary Value on the stack

int stackPop(); // pop top of stack

int stackDisp(char *s, int ind);

int getInst(int p);
int stackPushInst(int x);
// Variables

// Var
void setVar();          // set var defined on the stack (value varname -- )
void getVar(char *s);   //
void supVar(char *s);   // sup var given by its name

// Func

void setFunc();

int findFunc(char *s);

// Print on console
void stackPrint();
void dictPrint();

// Other functions

void who();

#endif	/* DATAS_H */

