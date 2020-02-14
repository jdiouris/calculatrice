
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"
#include "datas.h"
#include "interpreteur.h"
#include "calculation.h"




int isNumber(char * s, double *value)
{
    int is_valid=1;
    char *endPtr;
   // is_valid=( sscanf(s,"%f", value) == 1 );  
    double v = strtod( s, &endPtr ); 
    *value=v;
    if (endPtr==s) is_valid=0;
    return is_valid;
}
void supDel(char *s)
{
    int i;
    int L;
    L=strlen(s);
    for (i=0; i<L-2; i++)
    {
        s[i]=s[i+1];
    }
    s[L-2]=0; 
}
char buf[20];

int decInst(char *s) {
    int resu = -1;
    if cmp(s, "+") resu = Op_add;
    else if cmp(s, "*") resu = Op_mul;
    else if cmp(s, "-") resu = Op_sub;
    else if cmp(s, "/") resu = Op_div;
    else if cmp(s, "COS") resu = Func_cos;
    else if cmp(s, "SIN") resu = Func_sin;
    else if cmp(s, "TAN") resu = Func_tan;
    else if cmp(s, "LOG") resu = Func_log;
    else if cmp(s, "STO") resu = Func_sto;
    else if cmp(s, "SWAP") resu = Func_swap;
    else if cmp(s, "DUP") resu = Func_dup;
    else if cmp(s, "RCL") resu = Func_rcl;
    else if cmp(s, "WHO") resu = Func_who;
    else if cmp(s, "PI") resu = Func_pi;
    else if cmp(s, "IF") resu = Func_if;
    else if cmp(s, "END") resu = Func_end;
    else if cmp(s, "ELSE") resu = Func_else;
    else if cmp(s, "WHILE") resu = Func_while;
    else if cmp(s, "DO") resu = Func_do;
    else if cmp(s, "==") resu = Op_eq;
    else if cmp(s, "<>") resu = Op_neq;
    else if cmp(s, "<") resu = Op_lt;
    else if cmp(s, ">") resu = Op_gt;
    else if cmp(s, ">=") resu = Op_gte;
    else if cmp(s, "<=") resu = Op_lte;
    else if cmp(s, "INV") resu = Func_inv;
    else if cmp(s, "DROP") resu = Func_drop;
    else if cmp(s, "SWAP") resu = Func_swap;
    else if cmp(s, "LN") resu = Func_ln;
    else if cmp(s, "DUP") resu = Func_dup;
    else if cmp(s, "SQ") resu = Func_sq;
    else if cmp(s, "SQRT") resu = Func_sqrt;
    else if cmp(s, "POW") resu = Op_pow;
     else if cmp(s, "POW10") resu = Func_pow10;

    return resu;
}

int interpretString(char *line)
{
    double v;
    int inst;
    execError=0;
    funcLevel=0;
    printf("interp(%s)\n",line);
    if (strlen(line)==0) ;
    else
    if (isNumber(line, &v))
    {
        stackPushDouble(v);
    }
    else if (line[0]=='\'') 
    {
        int k=strlen(line);
        if ((k>1)&&(line[k-1]=='\''))
        {
            strcpy(buf,line);
            supDel(buf);
            stackPushString(buf);
        }
        else execError=Error;
    } 
    else if ((inst=decInst(line))!=-1)  execError=exec(inst);
    else
     {
         int pp=findFunc(line);
         if (pp>=0) execFunc(line);
         else 
         {
           pp=findVar(line);
           if (pp>=0) getVar(line);
           else 
           {
               strcpy(errorMsg,line);
               execError=ErrorUnknownIdentifier;
           }
         }
     }
    
    
    stackPrint();
    
    return execError;
}


int interpretFunction(int f)
{
    execError=0;
    
    execError=exec(f);
    return execError;
}

int compileString(char *s)
{
    double v;
    int inst;
    execError=0;
    printf("comp(%s)\n",s);
    if (strlen(s)==0) ;
    else
    {
        if (isNumber(s, &v))
        {
            stackPushDouble(v);
        }  
        else if ((inst=decInst(s))!=-1) execError=stackPushInst(inst);
        
        else execError=stackPushString(s);

        storeValue();
    }
    return execError;
}

void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

int sep(char c)
{
    if (c<=' ') return 1; else return 0;
}

int compile()
{
    execError=0;
    int i;
    char c;
    char mot[20];
    strcpy(mot,"");
    strcat(bufferFunc," ");  // ad a space at the end
    for ( i=0; i<strlen(bufferFunc); i++)
    {
        c=bufferFunc[i];
        if (sep(c)==1) 
        {
            if (strlen(mot)>0) 
            {
                compileString(mot);
                printf("mot=%s\n",mot);
            }
            strcpy(mot,"");
        }
        else append(mot,c);
    }
    stackPushInst(Func_rtn);
    storeValue();
    return execError;
}


// Stack and Programing functions



void decompile(int f, char *s)
{
    
    switch (f)
    {
        // operators
        case Op_add: strcpy(s,"+"); break;       
        case Op_sub: strcpy(s,"-"); break;
        case Op_mul: strcpy(s,"*"); break;
        case Op_div: strcpy(s,"/"); break;
        case Op_eq: strcpy(s,"=="); break;
        case Op_gt: strcpy(s,">"); break;
        case Op_lt: strcpy(s,"<"); break;
        case Op_gte: strcpy(s,">="); break;
        case Op_lte: strcpy(s,"<="); break;
        case Op_neq: strcpy(s,"<>"); break;
        // Math functions
        case Func_abs: strcpy(s,"ABS"); break;
        case Func_cos: strcpy(s,"COS"); break;
        case Func_sin: strcpy(s,"SIN"); break;
        case Func_sto: strcpy(s,"STO"); break;
        case Func_rcl: strcpy(s,"RCL"); break;
        case Func_disp: strcpy(s,"DISP"); break;

        case Func_tan: strcpy(s,"TAN"); break;
        case Func_atan: strcpy(s,"ATAN"); break;
        case Func_exp: strcpy(s,"EXP"); break;
        case Func_log: strcpy(s,"LOG"); break;
        case Func_neg: strcpy(s,"NEG"); break;
        case Func_exec: strcpy(s,"EXEC"); break;
        case Func_rand: strcpy(s,"RAND"); break;
        case Func_end: strcpy(s,"END"); break;
        case Func_sqrt: strcpy(s,"SQRT"); break;
        case Func_int: strcpy(s,"INT"); break;
        case Func_inv: strcpy(s,"1/X"); break;

        case Func_swap: strcpy(s,"SWAP"); break;
        case Func_dup: strcpy(s,"DUP"); break;

        case Func_pi: strcpy(s,"PI"); break;

        case Func_for: strcpy(s,"FOR"); break;
        case Func_step: strcpy(s,"STEP"); break;
        case Func_if: strcpy(s,"IF"); break;
        case Func_do: strcpy(s,"DO"); break;
        case Func_else: strcpy(s,"ELSE"); break;
        case Func_while: strcpy(s,"WHILE"); break;
        case Func_rtn: strcpy(s,"RTN"); break;
        case Func_who: strcpy(s,"WHO"); break;       
    }
}

void decompFunc(char *name)
{
    int end=0;
    int p;
    int ty;
    char buffer[20];
    p=findFunc(name);
    execError=0;
    strcpy(bufferFunc,"");
     if (p>=0)
     {
         while (end==0)
        {
            p=p+getSize(p);
           
            ty=getType(p);
            switch (ty)
                {
                    case tDouble: disp(p,buffer); break;
                    case tString: disp(p,buffer); break;
                    case tInst: decompile(getInst(p+3),buffer); break;
                }
                
            strcat(bufferFunc,buffer);
            strcat(bufferFunc," ");
            if (ty==tInst) if (getInst(p+3)==Func_rtn) end=1;
        }
     }
}