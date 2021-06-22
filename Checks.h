/*
 * IncFile2.h
 *
 * Created: 21/06/2021 17:46:24
 *  Author: dakak
 */ 
#include <stdbool.h>

#ifndef Checks_H_
#define Checks_H_

extern int cnt;
extern unsigned int score;
extern bool gameoverFlag ;
 extern unsigned long startTime;
 void gameover();
 
bool space_below();

bool space_left();

bool space_left2();

bool space_left3();

bool space_right();

bool space_right2();

bool space_right3();

void check_gameover();

bool check_overlap();

#endif /* INCFILE2_H_ */