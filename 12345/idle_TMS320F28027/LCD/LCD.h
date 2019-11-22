/*
 * LCD.h
 *
 *  Created on: Nov 21, 2019
 *      Author: marki
 */

#ifndef LCD_H_
#define LCD_H_

#define BAUD_RATE 9600
#define FRAME_BIT 10
#define VALID_BIT 9
#define IDLE 1
#define TRANSMIT 0
#define NOT_READY 0
#define READY 1
#define START_BIT 0
#define STOP_BIT 1



void lcdinit(void);
void lcdclear(void);
void lcdwrite(void);




#endif /* LCD_H_ */
