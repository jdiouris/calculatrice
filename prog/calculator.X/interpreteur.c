
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

int interpretString(char *line)
{
    double v;
    execError=0;
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
    else if cmp(line,"+") execError=exec(Op_add);
    else if cmp(line,"*") execError=exec(Op_mul);
    else if cmp(line,"-") execError=exec(Op_sub);
    else if cmp(line,"/") execError=exec(Op_div);
    else if cmp(line,"COS") execError=exec(Func_cos);
    else if cmp(line,"SIN") execError=exec(Func_sin);
    else if cmp(line,"TAN") execError=exec(Func_tan);
     else if cmp(line,"LOG") execError=exec(Func_log);
    else if cmp(line,"STO") execError=exec(Func_sto);
    else if cmp(line,"SWAP") execError=exec(Func_swap);
    else if cmp(line,"DUP") execError=exec(Func_dup);
    else if cmp(line,"RCL") execError=exec(Func_rcl);
    else if cmp(line,"WHO") execError=exec(Func_who);
     else if cmp(line,"PI") execError=exec(Func_pi);
     else if cmp(line,"INV") execError=exec(Func_inv);
     else
     {
         int pp=findFunc(line);
         if (pp>=0) execFunc(line);
         else 
         {
           pp=findVar(line);
           if (pp>=0) getVar(line);
           else execError=ErrorUnknownIdentifier;
         }
     }
    
    
    stackPrint();
    //msgCrt(line);
    
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
    execError=0;
    printf("comp(%s)\n",s);
    if (strlen(s)==0) ;
    else
    {
        if (isNumber(s, &v))
        {
            stackPushDouble(v);
        }
        else if (s[0]=='\'') 
        {

            strcpy(buf,s);
            supDel(buf);
            stackPushString(buf);
        }   
        else if cmp(s,"+") execError=stackPushInst(Op_add);
        else if cmp(s,"*") execError=stackPushInst(Op_mul);
        else if cmp(s,"-") execError=stackPushInst(Op_sub);
        else if cmp(s,"/") execError=stackPushInst(Op_div);
        else if cmp(s,"COS") execError=stackPushInst(Func_cos);
        else if cmp(s,"SIN") execError=stackPushInst(Func_sin);
        else if cmp(s,"TAN") execError=stackPushInst(Func_tan);
        else if cmp(s,"LOG") execError=stackPushInst(Func_log);
        else if cmp(s,"STO") execError=stackPushInst(Func_sto);
        else if cmp(s,"SWAP") execError=stackPushInst(Func_swap);
        else if cmp(s,"DUP") execError=stackPushInst(Func_dup);
        else if cmp(s,"RCL") execError=stackPushInst(Func_rcl);
        else if cmp(s,"WHO") execError=stackPushInst(Func_who);
        else if cmp(s,"PI") execError=stackPushInst(Func_pi);
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