/*
 * CFile1.c
 *
 * Created: 21/06/2021 19:55:10
 *  Author: dakak
 */ 
#include "Matrix.h"
#include <avr/io.h>

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
	for(i = 0; i < maxInUse; i++)	// Loop through number of cascaded devices
	{
		writeByte(0x0A); // Select Intensity register
		writeByte(0x1F); // Set brightness
	}
	SLAVE_DESELECT;

	
	// Set display refresh
	SLAVE_SELECT;
	for(i = 0; i < maxInUse; i++)
	{
		writeByte(0x0B); // Select Scan-Limit register
		writeByte(0x07); // Select columns 0-7
	}
	SLAVE_DESELECT;

	
	// Turn on the display
	SLAVE_SELECT;
	for(i = 0; i < maxInUse; i++)
	{
		writeByte(0x0C); // Select Shutdown register
		writeByte(0x01); // Select Normal Operation mode
	}
	SLAVE_DESELECT;

	
	// Disable Display-Test
	SLAVE_SELECT;
	for(i = 0; i < maxInUse; i++)
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
		for(uint8_t i = 0; i < maxInUse; i++)
		{
			writeByte(x);    // Select column x
			writeByte(0x00); // Set column to 0
		}
		SLAVE_DESELECT;
	}
}
//**********************************************************************************************************************************************************
void maxTransferOne(uint8_t whichMax, uint8_t address, uint8_t value) {

	uint8_t noop_reg = 0x00;    //max7219 No op register
	uint8_t noop_value = 0x00;  //value


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

}
//**********************************************************************************************************************************************************
void maxTransferSingle( uint8_t whichMax, uint8_t address, uint8_t value) {  //whichColor = 1 for RED, 2 for GREEN

	uint8_t noop_reg = 0x00;    //max7219 No op register
	uint8_t noop_value = 0x00;  //value


	SLAVE_SELECT;




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

		// Send the register address
		// Send the value
	}

	SLAVE_DESELECT;

}