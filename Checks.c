/*
 * CFile1.c
 *
 * Created: 21/06/2021 17:46:17
 *  Author: dakak
 */ 
#include "Checks.h"
#include "Moves.h"
#include "read.h"

#include <stdbool.h>

int cnt = 0;
unsigned int score = 0;
bool gameoverFlag = false;
unsigned long startTime;

void check_gameover()
{
	
	int i;
	int j;
	int cnt=0;;
	
	for(i=15;i>=0;i--)
	{
		cnt=0;
		for (j=0;j<8;j++)
		{
			if (pile[j][i])
			{
				cnt ++;
			}
		}
		if (cnt == 8)
		{
			for (j=0;j<8;j++)
			{
				pile[j][i]=0;
			}
			updateLED();
			
			
			int k;
			for(k=i;k>0;k--)
			{
				for (j=0;j<8;j++)
				{
					pile[j][k] = pile[j][k-1];
				}
			}
			for (j=0;j<8;j++)
			{
				pile[j][0] = 0;
			}
			updateLED();
			
			i++;
			score++;
			
			
		}
	}
	
	
	for(i=0;i<8;i++)
	{
		if (pile[i][0])
		gameover();
	}
	return;
}
//**********************************************************************************************************************************************************
void gameover()
{
	int i;
	int j;
	

	gameoverFlag = true;
	startTime = millis();
	
	
	clearMatrix();

	findescore(score);


	while(true)      //To re-play if any buttons depressed again
	{
		int button = readBut();
		
		if (sw1_slope|sw2_slope|sw3_slope|sw4_slope)
		{
			clearMatrix();
			score=0;
			gameoverFlag = false;
			
			for(i=15;i>=0;i--)
			{
				for (j=0;j<8;j++)
				{
					pile[j][i]=0;
				}
			}
			
			break;
		}
	}
}
//**********************************************************************************************************************************************************
bool check_overlap()
{
	
	int i;
	int j;
	for (i=0;i<16;i++)
	{
		for (j=0;j<7;j++)
		{
			if (block[j][i])
			{
				if (pile[j][i])
				return false;
			}
		}
	}
	for (i=16;i<18;i++)
	{
		for (j=0;j<7;j++)
		{
			if (block[j][i])
			{
				return false;
			}
		}
	}
	return true;
}
//**********************************************************************************************************************************************************
bool space_below()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (i == 15)
           return false;
         if (pile[j][i+1])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}



//**********************************************************************************************************************************************************  
bool space_left2()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 0 || j == 1)
           return false;
         if (pile[j-1][i] | pile[j-2][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}



//**********************************************************************************************************************************************************  
bool space_left3()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 0 || j == 1 ||j == 2 )
           return false;
         if (pile[j-1][i] | pile[j-2][i]|pile[j-3][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}



//**********************************************************************************************************************************************************  
bool space_left()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 0)
           return false;
         if (pile[j-1][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}



//**********************************************************************************************************************************************************  
bool space_right()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 7)
           return false;
         if (pile[j+1][i])
         {
           return false;
         }      
       }        
    
  }
  }
  return true;

	}


//**********************************************************************************************************************************************************  
bool space_right3()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 7||j == 6||j == 5)
           return false;
         if (pile[j+1][i] |pile[j+2][i] | pile[j+3][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}



//**********************************************************************************************************************************************************  
bool space_right2()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 7 || j == 6)
           return false;
         if (pile[j+1][i] |pile[j+2][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}