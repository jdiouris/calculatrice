#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calculation.h"
#include "datas.h"
#include "interpreteur.h"




// Internal func execution

int exec(int func) {
    execError = 0;
    double x1;
    double x2;
    printf("exec: %d \n",func);
    switch (func) {
        case Op_add:
            x1 = stackGetTopDouble();
            if (execError==0) stackPop();
            if (execError==0) x2 = stackGetTopDouble();
            if (execError==0) stackPop();
            if (execError==0) stackPushDouble(x1 + x2);
            break;
        case Op_sub:
            x1 = stackGetTopDouble();
            if (execError==0) stackPop();
            if (execError==0) x2 = stackGetTopDouble();
            if (execError==0) stackPop();
            if (execError==0) stackPushDouble(x2 - x1);
            break;
        case Op_mul:
            x1 = stackGetTopDouble();
            if (execError==0) stackPop();
            if (execError==0) x2 = stackGetTopDouble();
            if (execError==0) stackPop();
            if (execError==0) stackPushDouble(x2 * x1);
            break;
        case Op_div:
            x1 = stackGetTopDouble();
            if (execError==0) stackPop();
            if (execError==0) x2 = stackGetTopDouble();
            if (execError==0) stackPop();
            if (execError==0) stackPushDouble(x2 / x1);
            break;
        case Func_cos:
            x1 = stackGetTopDouble();
            if (execError==0) stackPop();
            if (execError==0) stackPushDouble(cos(x1));
            break;
        case Func_sin:
            x1 = stackGetTopDouble();
            if (execError==0) stackPop();
            if (execError==0) stackPushDouble(sin(x1));
            break;
         case Func_tan:
            x1 = stackGetTopDouble();
            if (execError==0) stackPop();
            if (execError==0) stackPushDouble(tan(x1));
            break; 
         case Func_log:
            x1 = stackGetTopDouble();
            if (execError==0) stackPop();
            if (execError==0) stackPushDouble(log(x1));
            break;
        case Func_disp:
            x1 = stackGetTopDouble();
            if (execError==0) stackPop();
         //   printf("%f\n", x1);
            break;
        case Func_sto:
           setVar();
           break;
        case Func_rcl:
           stackGetTopString(buff); 
           if (execError==0) stackPop();
           if (execError==0) getVar(buff);
        break;
        case Func_dup:
            stackPushString("$");
            if (execError==0) setVar();
            if (execError==0) getVar("$");
            if (execError==0) getVar("$");
        break;
        case Func_swap:
            stackPushString("$");
            if (execError==0) setVar();
            if (execError==0) stackPushString("$$");
            if (execError==0) setVar();
            if (execError==0) getVar("$");
            if (execError==0) getVar("$$");
        break;
        case Func_who:
            who();
            break;
        case Func_inv:
            x1 = stackGetTopDouble();
            if (execError==0) stackPop();
            if (execError==0) stackPushDouble(1.0/x1);
            break;
        case Func_pi:
            stackPushDouble(3.14159265359);
            break;
    }

    return execError;
}

// user func execution
int execFunc(char *name)
{
    int p;
    int pp;
    p=findFunc(name);
    printf("execFunc %s %i\n",name,p);
    int end=0;
    if (p>=0)
    {
        while (end==0)
        {
            p=p+getSize(p);
            int ty=getType(p);
            switch (ty)
            {
                case tDouble:
                    getValue(p);
                    break;
                case tString:
                    getString(buff,p);
                    pp=findFunc(buff);
                    if (pp>=0) execFunc(buff);
                    else 
                    {
                        pp=findVar(buff);
                        getVar(buff);
                        // getValue(pp);)
                    }
                    break;
                case tInst:
                    if (getInst(p+3)==Func_rtn) end=1;
                    else exec(getInst(p+3));
                break;       
            }
            if (end==0) stackPrint();
                
        }
    } else execError=ErrorFuncNotFound;
    return execError;
}
