/*
 * IncFile2.h
 *
 * Created: 21/06/2021 17:34:04
 *  Author: dakak
 */ 
#include <stdbool.h>

#ifndef Moves_H_
#define Moves_H_

 extern bool block[8][18]; //2 extra for rotation
 extern bool pile[8][16];
 extern  bool disp[8][16];
 extern unsigned char blocktype;
 extern unsigned char blockrotation;
 extern long delays ;
 extern short delay_ ;
bool moveleft();
bool moveright();
void rotate();
void movedown();

#endif /* INCFILE2_H_ */