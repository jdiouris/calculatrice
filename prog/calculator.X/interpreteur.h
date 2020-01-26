/* 
 * File:   interpreteur.h
 * Author: jeff
 *
 * Created on 3 janvier 2020, 10:06
 */

#ifndef INTERPRETEUR_H
#define	INTERPRETEUR_H
int interpretString(char *line);
int interpretFunction(int f);

int compile();

#define cmp(s1,s2) (strcmp(s1,s2)==0)



#endif	/* INTERPRETEUR_H */

