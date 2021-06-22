/*
 * CFile1.c
 *
 * Created: 21/06/2021 23:25:51
 *  Author: dakak
 */ 
#include "Score.h"
#include "Matrix.h"

void send_score( unsigned int score,int c1)
{
	for(int i = 0;i<8;i++)
	{
		SLAVE_SELECT;
		writeWord (i,pgm_read_byte(&Nummern[0][i]));
		writeWord (i,pgm_read_byte(&Nummern[c1][i]));
		writeWord (i,pgm_read_byte(&Nummern[score-(c1*10)][i]));
		SLAVE_DESELECT;
	}
}
void findescore( unsigned int score)
{
	
	
	for(int i = 0;i<8;i++)
	{
		if (score>=10)
		{
			send_score(score,1);
			
		}
		else if(score>=20)
		{
			send_score(score,2);
			
		}
		else if(score>=30)
		{
			send_score(score,3);
			
		}
		else if(score>=40)
		{
			send_score(score,4);
			
		}
		else if(score>=50)
		{
			send_score(score,5);
			
		}
		else if(score>=60)
		{
			send_score(score,6);
			
		}
		else if(score>=70)
		{
			send_score(score,7);
		}
		else if(score>=80)
		{
			send_score(score,8);
			
		}
		else if(score>=90)
		{
			send_score(score,9);
			
		}
		else
		{
			
			send_score(score,0);
			
		}

		
	}
}