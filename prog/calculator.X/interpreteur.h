/* 
 * File:   interpreteur.h
 * Author: jeff
 *
 * Created on 3 janvier 2020, 10:06
 */

#ifndef INTERPRETEUR_H
#define	INTERPRETEUR_H
extern char errorMsg[20];

int interpretString(char *line);
int interpretFunction(int f);

int compile();
void decompile(int f, char *s);

void supDel(char *s);

#define cmp(s1,s2) (strcmp(s1,s2)==0)



#endif	/* INTERPRETEUR_H */

