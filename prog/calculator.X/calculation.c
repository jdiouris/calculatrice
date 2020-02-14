#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "calculation.h"
#include "datas.h"
#include "interpreteur.h"

struct pelt {
    int func;
    int factif;
    int p;
    //  char s[20];
    double i1;
    double i2;
};

#define RETURNSTACKSIZE 20

struct pelt retStack[RETURNSTACKSIZE];

int pRetStack;

void initReturnStack() {
    pRetStack = -1;
}

void pushRetStack() {
    if (pRetStack + 1 < RETURNSTACKSIZE) {
        pRetStack++;
    } else execError = ErrorReturnStackFull;
}

void popRetStack() {
    if (pRetStack >= 0) pRetStack--;
    else execError = ErrorReturnStackEmpty;

}

// Internal func execution

int exec(int func) {
    execError = 0;
    double x1;
    double x2;
    //printf("exec: %d \n",func);
    switch (func) {
        case Op_add:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) x2 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(x1 + x2);
            break;
        case Op_sub:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) x2 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(x2 - x1);
            break;
        case Op_mul:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) x2 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(x2 * x1);
            break;
        case Op_div:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) x2 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(x2 / x1);
            break;
        case Op_eq:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) x2 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(x2 == x1);
            break;
        case Op_neq:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) x2 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(x2 != x1);
            break;
        case Op_lt:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) x2 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(x2 < x1);
            break;
        case Op_gt:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) x2 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(x2 > x1);
            break;
        case Op_lte:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) x2 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(x2 <= x1);
            break;
        case Op_gte:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) x2 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(x2 >= x1);
            break;
        case Func_cos:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(cos(x1));
            break;
        case Func_sin:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(sin(x1));
            break;
        case Func_tan:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(tan(x1));
            break;
        case Func_ln:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(log(x1));
            break;
        case Func_log:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(log(x1) / log(10));
            break;
        case Func_sqrt:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(sqrt(x1));
            break;
        case Func_sq:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(x1 * x1);
            break;
        case Func_disp:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            //   printf("%f\n", x1);
            break;
        case Func_sto:
            setVar();
            break;
        case Func_rcl:
            stackGetTopString(buff);
            if (execError == 0) stackPop();
            if (execError == 0) getVar(buff);
            break;
        case Func_dup:
            stackPushString("$");
            if (execError == 0) setVar();
            if (execError == 0) getVar("$");
            if (execError == 0) getVar("$");
            break;
        case Func_swap:
            stackPushString("$");
            if (execError == 0) setVar();
            if (execError == 0) stackPushString("$$");
            if (execError == 0) setVar();
            if (execError == 0) getVar("$");
            if (execError == 0) getVar("$$");
            break;
        case Func_pow10:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(pow(10, x1));
            break;
        case Func_drop:
            stackPop();
            break;
        case Func_who:
            who();
            break;
        case Func_inv:
            x1 = stackGetTopDouble();
            if (execError == 0) stackPop();
            if (execError == 0) stackPushDouble(1.0 / x1);
            break;
        case Func_pi:
            stackPushDouble(3.14159265359);
            break;
    }

    return execError;
}

// user func execution

int execFunc(char *name) {
    int p;
    int p0;
    int pp;
    int ty;
    int func = 0;
    int fexec = 1;
    double x1;
    int debug = 0;
    char buffer[20];
    execError = 0;
    p0 = findFunc(name);
    p = 0;
    msg("Running...");
    printf("execFunc %s %i\n", name, p0);
    funcLevel++;
    int end = 0;
    if (p0 >= 0) {
        while (end == 0) {
            p = p + getSize(p + p0);

            ty = getType(p + p0);
            if (fexec == 1)
                switch (ty) // active mode
                {
                    case tDouble:
                        getValue(p + p0);
                        break;
                    case tString:
                        getString(buff, p + p0);
                        if (buff[0] == '\'') {
                            int k = strlen(buff);
                            if ((k > 1)&&(buff[k - 1] == '\'')) {

                                supDel(buff);
                                stackPushString(buff);
                                if (debug == 1) {
                                    sprintf(buffer, "%s", buff);
                                    msg(buffer);
                                    waitKey();
                                }

                            }
                        } else {

                            pp = findFunc(buff);
                            if (pp >= 0) {
                                execFunc(buff);
                                p0 = findFunc(name); // Function can change Dict
                            } else {
                                pp = findVar(buff);
                                if (pp > 0) getVar(buff);
                                else {
                                    strcpy(errorMsg,buff);
                                    execError = ErrorUnknownIdentifier;
                                    end = 1;
                                }
                                // getValue(pp);)
                            }
                        }

                        break;
                    case tInst:
                        func = getInst(p + p0 + 3);

                        switch (func) {
                            case Func_rtn: end = 1;
                                break;
                            case Func_if:
                                pushRetStack();
                                retStack[pRetStack].func = Func_if;
                                retStack[pRetStack].factif = 1;
                                x1 = stackGetTopDouble();
                                if (execError == 0) stackPop();
                                if (x1 == 0) {
                                    fexec = 0;
                                }
                                break;
                            case Func_while:
                                pushRetStack();
                                if (execError != 0) end = 1;
                                else {
                                    retStack[pRetStack].func = Func_while;
                                    retStack[pRetStack].factif = 1;
                                    retStack[pRetStack].p = p;
                                }
                                break;
                            case Func_do:
                                x1 = stackGetTopDouble();
                                if (execError == 0) stackPop();
                                else end = 1;
                                if (x1 == 0) {
                                    fexec = 0;
                                }
                                break;
                            case Func_end:
                                if (retStack[pRetStack].func == Func_if) {
                                    popRetStack();
                                    if (execError != 0) end = 1;
                                }
                                if (retStack[pRetStack].func == Func_while) {
                                    p = retStack[pRetStack].p;
                                }
                                break;
                            case Func_else:
                                fexec = 0;
                                break;
                            case Func_sto:
                                exec(func);
                                p0 = findFunc(name); // variable change can change Dict
                                break;
                            default: exec(func);
                        }
                        break;
                } else // passive mode
                if (ty == tInst) {
                func = getInst(p + p0 + 3);
                switch (func) {
                    case Func_rtn: end = 1;
                        break;
                    case Func_end:
                        if (retStack[pRetStack].func == Func_if) {
                            if (retStack[pRetStack].factif == 1) fexec = 1;
                            popRetStack();
                        }
                        if (retStack[pRetStack].func == Func_while) {
                            popRetStack();
                            if (execError != 0) end = 1;
                            fexec = 1;
                        }
                        break;
                    case Func_if:
                        pushRetStack();
                        retStack[pRetStack].func = Func_if;
                        retStack[pRetStack].factif = 1;
                        break;
                    case Func_else:
                        if (retStack[pRetStack].func != Func_if) {
                            execError = Error;
                            end = 1;
                        } else
                            if (retStack[pRetStack].factif == 1) fexec = 1;
                        break;
                }

            }
            // if (end==0) dispStack();

            if (debug == 1) {
                clearLcd();
                strcpy(buffer, "--");
                if (fexec) {
                    switch (ty) {
                        case tDouble: stackDisp(buffer, 0);
                            break;
                        case tString: stackDisp(buffer, 0);
                            break;
                        case tInst: decompile(func, buffer);
                            break;
                    }
                }
                dispLine2(buffer);
                if (stackDisp(buffer, 0)) dispLine1(buffer);
                waitKey();
                //dispStack();

            }

            if (execError != 0) end = 1;
        }
    } else execError = ErrorFuncNotFound;
    supVarLevel();
    funcLevel--;

    return execError;
}
