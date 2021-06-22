/*
 * CFile1.c
 *
 * Created: 21/06/2021 17:34:18
 *  Author: dakak
 */ 

#include "Moves.h"


 bool block[8][18]; //2 extra for rotation
 bool pile[8][16];
 bool disp[8][16];
 unsigned char blocktype;
 unsigned char blockrotation;
   long delays = 0;
   short delay_ = 500;

void rotate()
{
	//skip for square block(3)
	if (blocktype == 3) return;
	
	int xi;
	int yi;
	int i;
	int j;
	//detect left
	for (i=7;i>=0;i--)
	{
		for (j=0;j<16;j++)
		{
			if (block[i][j])
			{
				xi = i;
			}
		}
	}
	
	//detect up
	for (i=15;i>=0;i--)
	{
		for (j=0;j<8;j++)
		{
			if (block[j][i])
			{
				yi = i;
			}
		}
	}
	
	if (blocktype == 0)
	{
		if (blockrotation == 0)
		{
			
			
			if (!space_left())
			{
				if (space_right3())
				{
					if (!moveright())
					return;
					xi++;
				}
				else return;
			}
			else if (!space_right())
			{
				if (space_left3())
				{
					if (!moveleft())
					return;
					if (!moveleft())
					return;
					xi--;
					xi--;
				}
				else
				return;
			}
			else if (!space_right2())
			{
				if (space_left2())
				{
					if (!moveleft())
					return;
					xi--;
				}
				else
				return;
			}
			
			
			block[xi][yi]=0;
			block[xi][yi+2]=0;
			block[xi][yi+3]=0;
			
			block[xi-1][yi+1]=1;
			block[xi+1][yi+1]=1;
			block[xi+2][yi+1]=1;

			blockrotation = 1;
		}
		else
		{
			block[xi][yi]=0;
			block[xi+2][yi]=0;
			block[xi+3][yi]=0;
			
			block[xi+1][yi-1]=1;
			block[xi+1][yi+1]=1;
			block[xi+1][yi+2]=1;

			blockrotation = 0;
		}
	}
	
	//offset to mid
	xi ++;
	yi ++;
	
	if (blocktype == 1)
	{
		if (blockrotation == 0)
		{
			block[xi-1][yi-1] = 0;
			block[xi-1][yi] = 0;
			block[xi+1][yi] = 0;

			block[xi][yi-1] = 1;
			block[xi+1][yi-1] = 1;
			block[xi][yi+1] = 1;
			
			blockrotation = 1;
		}
		else if (blockrotation == 1)
		{
			if (!space_left())
			{
				if (!moveright())
				return;
				xi++;
			}
			xi--;
			
			block[xi][yi-1] = 0;
			block[xi+1][yi-1] = 0;
			block[xi][yi+1] = 0;
			
			block[xi-1][yi] = 1;
			block[xi+1][yi] = 1;
			block[xi+1][yi+1] = 1;
			
			blockrotation = 2;
		}
		else if (blockrotation == 2)
		{
			yi --;
			
			block[xi-1][yi] = 0;
			block[xi+1][yi] = 0;
			block[xi+1][yi+1] = 0;
			
			block[xi][yi-1] = 1;
			block[xi][yi+1] = 1;
			block[xi-1][yi+1] = 1;
			
			blockrotation = 3;
		}
		else
		{
			if (!space_right())
			{
				if (!moveleft())
				return;
				xi--;
			}
			block[xi][yi-1] = 0;
			block[xi][yi+1] = 0;
			block[xi-1][yi+1] = 0;

			block[xi-1][yi-1] = 1;
			block[xi-1][yi] = 1;
			block[xi+1][yi] = 1;
			
			blockrotation = 0;
		}
	}



	if (blocktype == 2)
	{
		if (blockrotation == 0)
		{
			block[xi+1][yi-1] = 0;
			block[xi-1][yi] = 0;
			block[xi+1][yi] = 0;

			block[xi][yi-1] = 1;
			block[xi+1][yi+1] = 1;
			block[xi][yi+1] = 1;
			
			blockrotation = 1;
		}
		else if (blockrotation == 1)
		{
			if (!space_left())
			{
				if (!moveright())
				return;
				xi++;
			}
			xi--;
			
			block[xi][yi-1] = 0;
			block[xi+1][yi+1] = 0;
			block[xi][yi+1] = 0;
			
			block[xi-1][yi] = 1;
			block[xi+1][yi] = 1;
			block[xi-1][yi+1] = 1;
			
			blockrotation = 2;
		}
		else if (blockrotation == 2)
		{
			yi --;
			
			block[xi-1][yi] = 0;
			block[xi+1][yi] = 0;
			block[xi-1][yi+1] = 0;
			
			block[xi][yi-1] = 1;
			block[xi][yi+1] = 1;
			block[xi-1][yi-1] = 1;
			
			blockrotation = 3;
		}
		else
		{
			if (!space_right())
			{
				if (!moveleft())
				return;
				xi--;
			}
			block[xi][yi-1] = 0;
			block[xi][yi+1] = 0;
			block[xi-1][yi-1] = 0;

			block[xi+1][yi-1] = 1;
			block[xi-1][yi] = 1;
			block[xi+1][yi] = 1;
			
			blockrotation = 0;
		}
	}
	
	if (blocktype == 4)
	{
		if (blockrotation == 0)
		{
			block[xi+1][yi-1] = 0;
			block[xi-1][yi] = 0;

			block[xi+1][yi] = 1;
			block[xi+1][yi+1] = 1;
			
			blockrotation = 1;
		}
		else
		{
			if (!space_left())
			{
				if (!moveright())
				return;
				xi++;
			}
			xi--;
			
			block[xi+1][yi] = 0;
			block[xi+1][yi+1] = 0;
			
			block[xi-1][yi] = 1;
			block[xi+1][yi-1] = 1;
			
			blockrotation = 0;
		}
	}


	if (blocktype == 5)
	{
		if (blockrotation == 0)
		{
			block[xi][yi-1] = 0;
			block[xi-1][yi] = 0;
			block[xi+1][yi] = 0;

			block[xi][yi-1] = 1;
			block[xi+1][yi] = 1;
			block[xi][yi+1] = 1;
			
			blockrotation = 1;
		}
		else if (blockrotation == 1)
		{
			if (!space_left())
			{
				if (!moveright())
				return;
				xi++;
			}
			xi--;
			
			block[xi][yi-1] = 0;
			block[xi+1][yi] = 0;
			block[xi][yi+1] = 0;
			
			block[xi-1][yi] = 1;
			block[xi+1][yi] = 1;
			block[xi][yi+1] = 1;
			
			blockrotation = 2;
		}
		else if (blockrotation == 2)
		{
			yi --;
			
			block[xi-1][yi] = 0;
			block[xi+1][yi] = 0;
			block[xi][yi+1] = 0;
			
			block[xi][yi-1] = 1;
			block[xi-1][yi] = 1;
			block[xi][yi+1] = 1;
			
			blockrotation = 3;
		}
		else
		{
			if (!space_right())
			{
				if (!moveleft())
				return;
				xi--;
			}
			block[xi][yi-1] = 0;
			block[xi-1][yi] = 0;
			block[xi][yi+1] = 0;
			
			block[xi][yi-1] = 1;
			block[xi-1][yi] = 1;
			block[xi+1][yi] = 1;
			
			blockrotation = 0;
		}
	}
	
	if (blocktype == 6)
	{
		if (blockrotation == 0)
		{
			block[xi-1][yi-1] = 0;
			block[xi][yi-1] = 0;

			block[xi+1][yi-1] = 1;
			block[xi][yi+1] = 1;
			
			blockrotation = 1;
		}
		else
		{
			if (!space_left())
			{
				if (!moveright())
				return;
				xi++;
			}
			xi--;
			
			block[xi+1][yi-1] = 0;
			block[xi][yi+1] = 0;
			
			block[xi-1][yi-1] = 1;
			block[xi][yi-1] = 1;
			
			blockrotation = 0;
		}
	}

	//if rotating made block and pile overlap, push rows up
	while (!check_overlap())
	{
		for (i=0;i<18;i++)
		{
			for (j=0;j<8;j++)
			{
				block[j][i] = block[j][i+1];
			}
		}
		delays = millis() + delay_;
	}
	
	
	updateLED();
}
//**********************************************************************************************************************************************************
bool moveleft()
{

	
	if (space_left())
	{
		int i;
		int j;
		for (i=0;i<7;i++)
		{
			for (j=0;j<16;j++)
			{
				block[i][j]=block[i+1][j];
			}
		}
		
		for (j=0;j<16;j++)
		{
			block[7][j]=0;
		}

		updateLED();
		return 1;
	}

	return 0;
}
//**********************************************************************************************************************************************************
void movedown()
{
	if (space_below())
	{
		//move down
		int i;
		for (i=15;i>=0;i--)
		{
			int j;
			for (j=0;j<8;j++)
			{
				block[j][i] = block[j][i-1];
			}
		}
		for (i=0;i<7;i++)
		{
			block[i][0] = 0;
		}
	}
	else
	{
		//merge and new block
		int i;
		int j;
		for (i=0;i<8;i++)
		{
			for(j=0;j<16;j++)
			{
				if (block[i][j])
				{
					pile[i][j]=1;
					block[i][j]=0;
				}
			}
		}

		myrand();
		newBlock();
		
	}
	updateLED();
}
//***********************************************************
bool moveright()
{

	
	if (space_right())
	{
		int i;
		int j;
		for (i=7;i>0;i--)
		{
			for (j=0;j<16;j++)
			{
				block[i][j]=block[i-1][j];
			}
		}

		for (j=0;j<16;j++)
		{
			block[0][j]=0;
		}
		
		updateLED();
		return 1;
		
	}
	return 0;
}