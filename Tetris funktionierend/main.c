/*
 * Tetris_V1.c
 *
 * Created: 06/04/2021 19:41:36
 * Author : dakak
 */ 



#include "Tetris.h"



#define NUM_DEVICES    3	 // Number of cascaded max7219's, or just 1
void initSPI(void)
{
	DDRB |= (1 << PB2);		// Set SS output
	PORTB |= (1 << PB2);      // Begin high (unselected)

	DDRB |= (1 << PB3);       // Output on MOSI
	DDRB |= (1 << PB5);       // Output on SCK

	SPCR |= (1 << MSTR);            // Clockmaster
	SPCR |= (1 << SPE);       // Enable SPI
	
}
//**********************************************************************************************************************************************************
// Send byte through SPI
void writeByte(uint8_t byte)
{
	SPDR = byte;                      // SPI starts sending immediately
	while(!(SPSR & (1 << SPIF)));     // Loop until complete bit set
}



//**********************************************************************************************************************************************************
// Sends word through SPI
void writeWord(uint8_t address, uint8_t data)
{
	writeByte(address);	// Write first byte
	writeByte(data);      // Write Second byte
}


//**********************************************************************************************************************************************************
// Initializes all cascaded devices

void initMatrix()
{
	uint8_t i;	// Var used in for loops

	// Set display brighness
	SLAVE_SELECT;
	for(i = 0; i < NUM_DEVICES; i++)	// Loop through number of cascaded devices
	{
		writeByte(0x0A); // Select Intensity register
		writeByte(0x1F); // Set brightness
	}
	SLAVE_DESELECT;

	
	// Set display refresh
	SLAVE_SELECT;
	for(i = 0; i < NUM_DEVICES; i++)
	{
		writeByte(0x0B); // Select Scan-Limit register
		writeByte(0x07); // Select columns 0-7
	}
	SLAVE_DESELECT;

	
	// Turn on the display
	SLAVE_SELECT;
	for(i = 0; i < NUM_DEVICES; i++)
	{
		writeByte(0x0C); // Select Shutdown register
		writeByte(0x01); // Select Normal Operation mode
	}
	SLAVE_DESELECT;

	
	// Disable Display-Test
	SLAVE_SELECT;
	for(i = 0; i < NUM_DEVICES; i++)
	{
		writeByte(0x0F); // Select Display-Test register
		writeByte(0x00); // Disable Display-Test
	}
	SLAVE_DESELECT;
}
//**********************************************************************************************************************************************************
void clearMatrix(void)
{
	for(uint8_t x = 1; x < 9; x++) // for all columns
	{
		SLAVE_SELECT;
		for(uint8_t i = 0; i < NUM_DEVICES; i++)
		{
			writeByte(x);    // Select column x
			writeByte(0x00); // Set column to 0
		}
		SLAVE_DESELECT;
	}
}
//**********************************************************************************************************************************************************
void initTaster(void)
{
	DDRD = DDRD & 0xF0;             // Port B auf Eingabe schalten
	PORTD |= 0x0F;                  // Pullup-Rs eingeschaltet
	_delay_ms(10);                  // Wartezeit Umstellung Hardware-Signal
}
//**********************************************************************************************************************************************************

int readBut()
{
	if (bdelay > millis())
	{
		return 0;
	}
	// Einlesen der 4 Tastensignale
	sw1_neu = (PIND & (1 << DDD0));
	sw2_neu = (PIND & (1 << DDD1));
	sw3_neu = (PIND & (1 << DDD2));
	sw4_neu = (PIND & (1 << DDD3));
	
	// Auswerten der Flanken beim Druecken
	
	if ((sw1_neu==0)&(sw1_alt==1))  // wenn Taste 1 soeben gedrueckt wurde:
	sw1_slope = 1;						// Links
	
	if ((sw2_neu==0)&(sw2_alt==1))  // wenn Taste 2 eben gedrueckt wurde:
	sw2_slope = 1;						// Rechts
	
	if ((sw3_neu==0)&(sw3_alt==1))  // wenn Taste 3 eben gedrueckt wurde:
	sw3_slope = 1;						// Drehen
	
	if ((sw4_neu==0)&(sw4_alt==1))  // wenn Taste 4 eben gedrueckt wurde:
	sw4_slope = 1;					    // Fallen lassen
	
	// Zwischenspeichern aktuelle Tastenwerte
	
	sw1_alt = sw1_neu;              // aktuelle Tastenwerte speichern
	sw2_alt = sw2_neu;              //    in Variable fuer alte Werte
	sw3_alt = sw3_neu;
	sw4_alt = sw4_neu;
	
	
	
	
}

//**********************************************************************************************************************************************************
void get_seed(void){
	if (sw4_neu==1||sw1_neu==1)
	{
		zufallZaehler++;
	}
	
	if (zufallZaehler>LONG_MAX-100)
	{
		zufallZaehler%=900;
	}
	} //Startwert für rand() erzeugen

////**********************************************************************************************************************************************************

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
//**********************************************************************************************************************************************************
void updateLED()
{
	int i;
	int j;
	for (i=0;i<8;i++)
	{
		for (j=0;j<16;j++)
		{
			disp[i][j] = block[i][j] | pile[i][j];
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
    readBut();
    
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
    sw1_slope = 0;             
    sw2_slope = 0;             
	sw3_slope = 0;             
	sw4_slope = 0;
	zaehler=1; 
      break;
    }  
  }
  
    
}



//**********************************************************************************************************************************************************  
void newBlock()
{
  check_gameover();
  
if (zaehler==1)
{
	srand(zufallZaehler);
	blocktype = rand()%6;
	blocktypeFutur = rand()%6;
}
else{
	srand(zufallZaehler);
	blocktype = blocktypeFutur;
	blocktypeFutur = rand()%6;
}
 
  

  
  if (blocktype == 0)
  // 0
  // 0
  // 0
  // 0
  {
    block[3][0]=1;
    block[3][1]=1;
    block[3][2]=1;
    block[3][3]=1;      
  }

  if (blocktype == 1)
  // 0
  // 0 0 0
  {
    block[2][0]=1;
    block[2][1]=1;
    block[3][1]=1;
    block[4][1]=1;        
  }
  
  if (blocktype == 2)
  //     0
  // 0 0 0
  {
    block[4][0]=1;
    block[2][1]=1;
    block[3][1]=1;
    block[4][1]=1;         
  }

  if (blocktype == 3)
  // 0 0
  // 0 0
  {
    block[3][0]=1;
    block[3][1]=1;
    block[4][0]=1;
    block[4][1]=1;          
  }    

  if (blocktype == 4)
  //   0 0
  // 0 0
  {
    block[4][0]=1;
    block[5][0]=1;
    block[3][1]=1;
    block[4][1]=1;         
  }    
  
  if (blocktype == 5)
  //   0
  // 0 0 0
  {
    block[4][0]=1;
    block[3][1]=1;
    block[4][1]=1;
    block[5][1]=1;       
  }        

  if (blocktype == 6)
  // 0 0
  //   0 0
  {
    block[3][0]=1;
    block[4][0]=1;
    block[4][1]=1;
    block[5][1]=1;         
  }    

  blockrotation = 0;
 
 futurBlock();
 zaehler++;
  
}



//********************************************************************************************************************************************************** 
void futurBlock(){
	
	for (int i=0;i<8;i++)
	{
		
		
		SLAVE_SELECT;
		writeWord (i,pgm_read_byte(&blockFutur[blocktypeFutur][i]));
		SLAVE_DESELECT;
		
	}

	
	
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



//**********************************************************************************************************************************************************  
ISR(TIMER0_COMPA_vect){  //change the 0 to 1 for timer1 and 2 for timer2
    LEDRefresh();
}



//**********************************************************************************************************************************************************  
void LEDRefresh()
{
    int i;
    int k;

    bool tmpdispUpper[8][8];
    bool tmpdispLower[8][8];
     
    bool tmppileUpper[8][8];
    bool tmppileLower[8][8];
     
  
    //rotate 90 degrees for upper Bicolor LED matrix
    for (k=0;k<8;k++)
    {
      for(i=0;i<8;i++)
      {
        tmpdispUpper[k][i]=disp[i][k];
      }
    }  
  
  
    //rotate 90 degrees for lower Bicolor LED matrix
    for (k=8;k<16;k++)
    {
      for(i=0;i<8;i++)
      {
        tmpdispLower[k-8][i]=disp[i][k];
      }
    }  



    //For pile
    //rotate 90 degrees for upper Bicolor LED matrix
    for (k=0;k<8;k++)
    {
      for(i=0;i<8;i++)
      {
        tmppileUpper[k][i]=pile[i][k];
      }
    }  
  
  
    //rotate 90 degrees for lower Bicolor LED matrix
    for (k=8;k<16;k++)
    {
      for(i=0;i<8;i++)
      {
        tmppileLower[k-8][i]=pile[i][k];
      }
    }  

  

    for(i=0;i<8;i++)
    {      
       uint8_t upper = 0;
       int b;
       for(b = 0;b<8;b++)
       {
         upper <<= 1;
         if (tmpdispUpper[b][i]) upper |= 1;
       }
       
       
       uint8_t lower = 0;
       for(b = 0;b<8;b++)
       {
         lower <<= 1;
         if (tmpdispLower[b][i]) lower |= 1;
       }

            
      if (gameoverFlag == true)
      {  
        elapsedTime = millis() - startTime;

         maxTransferSingle( /*RED,*/2, i,  0x0F);
         maxTransferSingle( 3, i, 0x0F);
         
//           maxTransferSingle(/*GREEN,*/ 1, i, ((rand()%255+1)));
//           maxTransferSingle(/*GREEN,*/2, i, ((rand()%255+1)));
        // Display random pattern for pre-defined period before blanking display
        if (elapsedTime < 2000)
        {            
      
          cnt = cnt + 1;
          
//           if (cnt > 80)
//           {
//             TriggerSound();
//             TriggerSound();
//             cnt = 0;
//           }
         }   
        else
        {
          maxTransferSingle(/*RED,*/ 2, i, 0x00);  // clear
          maxTransferSingle(/*RED, */3, i, 0x00);  // clear

          maxTransferSingle(/*GREEN,*/ 2, i, 0x00);  // clear
          maxTransferSingle( /*GREEN,*/3, i, 0x00);  // clear        
        }  
      
      }
      else
      {
     /* if (selectColor == RED)*/
       {
          maxTransferSingle(/*GREEN,*/ 1, i, lower);
          maxTransferSingle( /*GREEN,*/2, i, upper);
		  
	   }
      /* else*/
//        {
// 	       maxTransferSingle(/*RED,*/ 1, i, lower);
// 	       maxTransferSingle(/*RED,*/ 2, i, upper);
//        }
           
      }      
    } 
    
    
    
    if (gameoverFlag == false)
    {  
      // For pile - to display orange    
      for(i=0;i<8;i++)
      {      
         unsigned char  upper = 0;
         int b;
         for(b = 0;b<8;b++)
         {
           upper <<= 1;
           if (tmppileUpper[b][i]) upper |= 1;
         }
       
       
         unsigned char lower = 0;
         for(b = 0;b<8;b++)
         {
           lower <<= 1;
           if (tmppileLower[b][i]) lower |= 1;
         }

      
/*        To alternate color of new block between RED and GREEN*/
                /* if (selectColor == RED)*/
//                 {
//                   maxTransferSingle(/*RED*//*,*/ 1, i, lower);
//                   maxTransferSingle( /*RED*//*,*/2, i, upper);
// 				   _delay_ms(100);
// 				}
              
              /*else*/
			  
	  }
	   
    }    
}

	

//**********************************************************************************************************************************************************  
// Change Max72xx brightness
void setBrightness()
{      
    maxTransferAll(0x0A, SetbrightnessValue);      //Set Brightness
    maxTransferAll(0x00, 0x00);  //No-op commands
}



//**********************************************************************************************************************************************************  

// 
//  * Transfers data to a MAX7219/MAX7221 register of a particular Bi-color LED Matrix module.
//  *
//  * @param whichMax The Max72xx to load data and value into
//  * @param address The register to load data into
//  * @param value Value to store in the register

 
//**********************************************************************************************************************************************************  

void maxTransferAll(uint8_t address, uint8_t value) {
	/*stopISR();*/
	SLAVE_SELECT;

	for ( int c=1; c<= maxInUse*2;c++) {
		writeByte(address);  // specify register
		writeByte(value);  // put data
	}

	SLAVE_DESELECT;
/*startISR();*/
}
//**********************************************************************************************************************************************************  
void maxTransferOne(uint8_t whichMax, uint8_t address, uint8_t value) {

  uint8_t noop_reg = 0x00;    //max7219 No op register
  uint8_t noop_value = 0x00;  //value

 /*stopISR();*/
  SLAVE_SELECT; 

  for (int i=maxInUse; i>0; i--)   // Loop through our number of Bi-color LED Matrices
  {
	  if (i==whichMax)
	  {
		  writeByte(address);  // Send the register address
		  writeByte(value);    // Send the value

		  writeByte(address);  // Send the register address
		  writeByte(value);    // Send the value
	  }
	  
	  else
	  {
		  writeByte(noop_reg);    // Send the register address
		  writeByte(noop_value);  // Send the value

		  writeByte(noop_reg);    // Send the register address
		  writeByte(noop_value);  // Send the value
	  }
  }
  

  SLAVE_DESELECT;
/* startISR();*/
}



//**********************************************************************************************************************************************************  
void maxTransferSingle(/*uint8_t wich_color*//*,*/ uint8_t whichMax, uint8_t address, uint8_t value) {  //whichColor = 1 for RED, 2 for GREEN

 uint8_t noop_reg = 0x00;    //max7219 No op register
  uint8_t noop_value = 0x00;  //value

/* stopISR();*/
  SLAVE_SELECT;


/*if (wich_color==GREEN)*/
/*{*/
  for (int i=maxInUse; i>0; i--)   // Loop through our number of Bi-color LED Matrices
  {

	  if (whichMax==2)
	  {
		  writeByte(noop_reg);    // Send the register address
		  writeByte(noop_value);  // Send the value
		  writeByte(address+1);   // Send the register address
		  writeByte(value);       // Send the value

		  

		  writeByte(noop_reg);    // Send the register address
		  writeByte(noop_value);  // Send the value
	  }
	  else  if (whichMax==1)
	  {
		  writeByte(noop_reg);    // Send the register address
		  writeByte(noop_value);  // Send the value
		  
		  
		  writeByte(noop_reg);    // Send the register address
		  writeByte(noop_value);
		  writeByte(address+1);    // Send the register address
		  writeByte(value);  // Send the value
	  }
	  
	  else
	  {
		  writeByte(address+1);    // Send the register address
		  writeByte(value);
		  writeByte(noop_reg);    // Send the register address
		  writeByte(noop_value);  // Send the value
		  writeByte(noop_reg);    // Send the register address
		  writeByte(noop_value);  // Send the value
		  
	  }
// }
// else 
// {
// 	for (int i=maxInUse; i>0; i--)   // Loop through our number of Bi-color LED Matrices
// 	{
// 		if (whichMax==1)
// 		{
// 			
// 			writeByte(noop_reg);    // Send the register address
// 			writeByte(noop_value);
// 			
// 			writeByte(address+1);   // Send the register address
// 			writeByte(value);       // Send the value
// 
// 			  // Send the value
// 
// 		}
// 		else
// 		{
// 			writeByte(noop_reg);    // Send the register address
// 			writeByte(noop_value);  // Send the value
// 
// 			writeByte(noop_reg);    // Send the register address
// 			writeByte(noop_value);  // Send the value
// 		}

		// Send the register address
		// Send the value
	/*}*/
/*}*/
}
 SLAVE_DESELECT;
/* startISR();*/
}



//**********************************************************************************************************************************************************  
void maxShutdown(uint8_t cmd) 
{
  uint8_t noop_reg = 0x00;      //max7219_reg_no_op
   uint8_t shutdown_reg = 0x0c;  //max7219_reg_shutdown
   uint8_t col = 0x01;  //shutdown false
   uint8_t col2 = 0x00;  //shutdown true


  /*  stopISR();*/
   SLAVE_SELECT;

    for (int c =1; c<= maxInUse; c++)
    {
      writeByte(shutdown_reg);  // Send the register address
      writeByte(col2);          // Send the value

      writeByte(shutdown_reg);  // Send the register address
     writeByte(col2);          // Send the value
    }

    SLAVE_DESELECT;
    startISR();
 
 


  //No ops register to shift out instructions   
/*  stopISR();*/
 SLAVE_SELECT;

  for (int c =1; c<= maxInUse; c++) 
  {      
   writeByte(noop_reg);  // Send the register address
  writeByte(0x00);      // Send the value

   writeByte(noop_reg);  // Send the register address
   writeByte(0x00);      // Send the value
  }

 SLAVE_DESELECT;
/*  startISR();*/
 
}

void init_millis(unsigned long f_cpu)
{
	unsigned long ctc_match_overflow;
	
	ctc_match_overflow = ((f_cpu/ 1000) / 8); //when timer1 is this value, 1ms has passed
	
	// (Set timer to clear when matching ctc_match_overflow) | (Set clock divisor to 8)
	TCCR1B |= (1 << WGM12) | (1 << CS11);
	
	// high byte first, then low byte
	OCR1AH = (ctc_match_overflow >> 8);
	OCR1AL = ctc_match_overflow;
	
	// Enable the compare match interrupt
	TIMSK1 |= (1 << OCIE1A);
	
	//REMEMBER TO ENABLE GLOBAL INTERRUPTS AFTER THIS WITH sei(); !!!
}

unsigned long millis ()
{
	unsigned long millis_return;
	
	// Ensure this cannot be disrupted
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		millis_return = timer1_millis;
	}
	return millis_return;
}
 ISR(TIMER1_COMPA_vect)
 {
	 timer1_millis++;
 }

//**********************************************************************************************************************************************************
/////////////////////////////ISR Timer Functions using Timer2///////////////////////////
ISR(TIMER2_COMPA_vect) {  //This ISR toggles shutdown between the 2MAX7221's

    // ORANGE
  
    if(maxInShutdown==1){
      maxShutdown(1);
     
    } 

 
 //Blank Display
  {
    maxShutdown(0);       
    
  }
} 
// 
// 
// 
// //**********************************************************************************************************************************************************
void setISRtimer() // setup ISR timer controling toggleing
{ 
  TCCR2A = 0x02;                        // WGM22=0 + WGM21=1 + WGM20=0 = Mode2 (CTC)
  TCCR2B = 0x05;                // CS22=1 + CS21=0 + CS20=1 = /128 prescaler (125kHz)
  TCNT2 = 0;                            // clear counter
  OCR2A = ISR_FREQ;                     // set TOP (divisor) - see #define
}
// //      
// //  
// //      
// // //**********************************************************************************************************************************************************
void startISR()    // Starts the ISR
{
  TCNT2 = 0;                            // clear counter (needed here also)
  TIMSK2|=(1<<OCIE2A);                  // set interrupts=enabled (calls ISR(TIMER2_COMPA_vect)
}
// // 
// //   
// //      
// // //**********************************************************************************************************************************************************
void stopISR()    // Stops the ISR
{
  TIMSK2&=~(1<<OCIE2A);                  // disable interrupts
}
// 


//**********************************************************************************************************************************************************

int  seeder (unsigned int *seed)
{
	unsigned int next = *seed;
	int result;

	next *= 1103515245;
	next += 12345;
	result = (unsigned int) (next / 65536) % 2048;

	next *= 1103515245;
	next += 12345;
	result <<= 10;
	result ^= (unsigned int) (next / 65536) % 1024;

	next *= 1103515245;
	next += 12345;
	result <<= 10;
	result ^= (unsigned int) (next / 65536) % 1024;

	*seed = next;

	return result;
}
//**********************************************************************************************************************************************************
uint16_t ReadADC(uint8_t ADCchannel)
{
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
	//single conversion mode
	ADCSRA |= (1<<ADSC);
	// wait until ADC conversion is complete
	while( ADCSRA & (1<<ADSC) );
	return ADC;
}
//**********************************************************************************************************************************************************
void InitADC()
{
	// Select Vref=AVcc
	ADMUX |= (1<<REFS0);
	//set prescaller to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}
//**********************************************************************************************************************************************************

void findescore( unsigned int score)
{
	
	
	for(int i = 0;i<8;i++)
	{
		if (score>=10)
		{
			SLAVE_SELECT;
			writeWord (i,pgm_read_byte(&Nummern[0][i]));
			writeWord (i,pgm_read_byte(&Nummern[1][i]));
			writeWord (i,pgm_read_byte(&Nummern[score-10][i]));
			SLAVE_DESELECT;
			
		}
		else if(score>=20)
		{
			SLAVE_SELECT;
			writeWord (i,pgm_read_byte(&Nummern[0][i]));
			writeWord (i,pgm_read_byte(&Nummern[2][i]));
			writeWord (i,pgm_read_byte(&Nummern[score-20][i]));
			SLAVE_DESELECT;
			
		}
		else if(score>=30)
		{
			SLAVE_SELECT;
			writeWord (i,pgm_read_byte(&Nummern[0][i]));
			writeWord (i,pgm_read_byte(&Nummern[3][i]));
			writeWord (i,pgm_read_byte(&Nummern[score-30][i]));
			SLAVE_DESELECT;
			
		}
		else if(score>=40)
		{
			SLAVE_SELECT;
			writeWord (i,pgm_read_byte(&Nummern[0][i]));
			writeWord (i,pgm_read_byte(&Nummern[4][i]));
			writeWord (i,pgm_read_byte(&Nummern[score-40][i]));
			SLAVE_DESELECT;
			
		}
		else if(score>=50)
		{
			SLAVE_SELECT;
			writeWord (i,pgm_read_byte(&Nummern[0][i]));
			writeWord (i,pgm_read_byte(&Nummern[5][i]));
			writeWord (i,pgm_read_byte(&Nummern[score-50][i]));
			SLAVE_DESELECT;
			
		}
		else if(score>=60)
		{
			SLAVE_SELECT;
			writeWord (i,pgm_read_byte(&Nummern[0][i]));
			writeWord (i,pgm_read_byte(&Nummern[6][i]));
			writeWord (i,pgm_read_byte(&Nummern[score-60][i]));
			SLAVE_DESELECT;
			
		}
		else if(score>=70)
		{
			SLAVE_SELECT;
			writeWord (i,pgm_read_byte(&Nummern[0][i]));
			writeWord (i,pgm_read_byte(&Nummern[7][i]));
			writeWord (i,pgm_read_byte(&Nummern[score-70][i]));
			SLAVE_DESELECT;
			
		}
		else if(score>=80)
		{
			SLAVE_SELECT;
			writeWord (i,pgm_read_byte(&Nummern[0][i]));
			writeWord (i,pgm_read_byte(&Nummern[8][i]));
			writeWord (i,pgm_read_byte(&Nummern[score-80][i]));
			SLAVE_DESELECT;
			
		}
		else if(score>=90)
		{
			SLAVE_SELECT;
			writeWord (i,pgm_read_byte(&Nummern[0][i]));
			writeWord (i,pgm_read_byte(&Nummern[9][i]));
			writeWord (i,pgm_read_byte(&Nummern[score-90][i]));
			SLAVE_DESELECT;
			
		}
		else
		{
			
			SLAVE_SELECT;
			writeWord (i,pgm_read_byte(&Nummern[0][i]));
			writeWord (i,pgm_read_byte(&Nummern[0][i]));
			writeWord (i,pgm_read_byte(&Nummern[score][i]));
			SLAVE_DESELECT;
			
		}

		
	}
}
//**********************************************************************************************************************************************************


//**********************************************************************************************************************************************************
// void ADCRNG_init(void)
// {
// 	ADMUX |= (1<<REFS0); // use internal 2.56V voltage reference
// 	ADMUX |= (1<<ADLAR); // set left adjustment of ADC result (8bit mode)
// 	ADCSRA |= (1<<ADPS0); // set division factor to 2
// 	ADCSRA |= (1<<ADEN)|(1<<ADIE); // enable ADC0 (interrupt)
////**********************************************************************************************************************************************************

uint32_t ADCRNG_next(void) {
	uint8_t i;
	uint32_t result = 0;
	counter = 0; // reset counter
	ADCSRA |= (1<<ADSC); // start signal acquisition
	while (counter != N); // wait for data
	for (i = 0; i < N; ++i, result <<= 1) {
		result |= (data[i] & 1); // use least significant bit
	}
	return result;
}
//**********************************************************************************************************************************************************

int main(void)
{
	initSPI();
	initMatrix();
	clearMatrix();
	init_millis(f_cpu);
	initTaster();
	InitADC();

// setISRtimer();                        // setup the timer
// startISR();

srand(ReadADC(DDC0));
setBrightness();


// int seed =
// (analogRead(0)+1)*
// (analogRead(1)+1)*
// (analogRead(2)+1)*
// (analogRead(3)+1);
// randomSeed(seed);
// random(10,9610806);
// seed = seed *random(3336,15679912)+analogRead(random(4)) ;
// randomSeed(seed);
// random(10,98046);


/*cli();*///stop interrupts

//set timer0 interrupt at 2kHz
// TCCR0A = 0;// set entire TCCR0A register to 0
// TCCR0B = 0;// same for TCCR0B
// TCNT0  = 0;//initialize counter value to 0
// // set compare match register for 2khz increments
// OCR0A = 259;// = (16*10^6) / (2000*64) - 1 (must be <256)
// // turn on CTC mode
// TCCR0A |= (1 << WGM01);
// // Set CS11 and CS10 bits for 1024 prescaler
// TCCR0B |= (1 << CS02) | (1 << CS00);
// // enable timer compare interrupt
// TIMSK0 |= (1 << OCIE0A);
// 
// sei();//allow interrupts
futurBlock();
newBlock();
updateLED();
//     for(int i= 0;i<8;i++)
//     {
// 	    
// 	    
// 	    maxTransferSingle(i,0xFF);
// 		_delay_ms(100);
//     }

    while (1)
	{
		
	

    /* Replace with your application code */


		LEDRefresh();
// 		maxTransferSingle(2,0x02,0x0F);
// 		maxTransferSingle(1,0x01,0x01);
	
// 		SLAVE_SELECT;
// 		writeWord(0x02,0x0F);
// 		SLAVE_DESELECT;
		
		 
		 
		 if (delays < millis())
		 {
			 delays = millis() + delay_;
			 movedown();
		 }
		 
		 //button actions
		 readBut();
		 get_seed();
		 
		 if (sw1_slope)
		 {
			 rotate();
			 sw1_slope=0;
			 } //up=rotate
		 
		 if (sw2_slope) 
		 {
			 moveright();
			 sw2_slope=0;
		 } 
		 //right=moveright
		 
		 if (sw3_slope)
		 {
			 moveleft();
			 sw3_slope=0;
		 }  //left=moveleft
		 
		 if (sw4_slope) 
		 {
			 movedown();
			 sw4_slope=0;
		 } //down=movedown
		 
    }
}

