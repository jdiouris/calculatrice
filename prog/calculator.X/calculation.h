/* 
 * File:   calculation.h
 * Author: jdiouris
 *
 * Created on January 20, 2020, 5:48 PM
 */

#ifndef CALCULATION_H
#define	CALCULATION_H

extern int funcLevel;
extern char errorMsg[20];

// Execution

int exec(int func); // exec function defined by its identifier

int execFunc(char *name); // exec a user function (defined in the dictionary))








#endif	/* CALCULATION_H */

