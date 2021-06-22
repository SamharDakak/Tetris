/*
 * IncFile2.h
 *
 * Created: 21/06/2021 19:55:21
 *  Author: dakak
 */ 


#ifndef Matrix_H_
#define Matrix_H_

#include <avr/io.h>
#define maxInUse 3
#define SLAVE_SELECT    PORTB &= ~(1 << PB2)
#define SLAVE_DESELECT  PORTB |= (1 << PB2)

void initMatrix(void);

void clearMatrix(void);

void writeWord(uint8_t address, uint8_t data);

void initSPI(void);

void writeByte(uint8_t byte);

void maxTransferOne(uint8_t whichMax, uint8_t address, uint8_t value);

void maxTransferSingle( uint8_t whichMax, uint8_t address, uint8_t value);


#endif /* INCFILE2_H_ */