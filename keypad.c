#include <stdint.h>
#include <stdbool.h>
#include "..\tm4c123gh6pm.h"
#include "..\driverlib\gpio.h"
#include "..\driverlib\sysctl.h"
#include "..\inc\hw_memmap.h"
#include "keypad_config.h"
#include "keypad.h"
#include "..\inc\hw_types.h"
#include "..\inc\hw_gpio.h"
void unlock()
{
	
	HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK)=GPIO_LOCK_KEY ;
	HWREG(GPIO_PORTF_BASE+GPIO_O_CR)=0xFF;
	HWREG(GPIO_PORTE_BASE+GPIO_O_LOCK)=GPIO_LOCK_KEY ;
	HWREG(GPIO_PORTE_BASE+GPIO_O_CR)=0xFF;
	
}

#define KEYPAD_ROW GPIO_PORTE_BASE// WRITE O/P
#define KEYPAD_COL GPIO_PORTF_BASE //READ I/P
/* this function initializes the ports connected to the keypad */
void keypad_init(void)
{

SysCtlPeripheralEnable(keypad_port_clock_row);  ////enable clock for ports SYS_RCGC_R
while(!SysCtlPeripheralReady( keypad_port_clock_row ));   ////check for clock is set or not re
SysCtlPeripheralEnable(keypad_port_clock_col);  ////enable clock for ports SYS_RCGC_R
while(!SysCtlPeripheralReady( keypad_port_clock_col ));
unlock();                 /* unlock port F , E */

GPIODirModeSet(keypad_port_row , R1 | R2 | R3 | R4, GPIO_DIR_MODE_OUT); //set rows to output
GPIOPadConfigSet(keypad_port_row , R1 | R2 | R3 | R4 ,GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_OD );   //digital for ROWS
GPIODirModeSet(keypad_port_col , C1 | C2 | C3 | C4 , GPIO_DIR_MODE_IN ); //Set columns to input
GPIOPadConfigSet(keypad_port_col , C1 | C2 | C3 | C4 ,GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD_WPU );//digital,pull-up for COLUMNS
}


unsigned char keypad_getkey(void)
{
const unsigned char keymap[4][4] = {
{ '1', '2', '3', 'A'},
{ '4', '5', '6', 'B'},
{ '7', '8', '9', 'C'},
{ '*', '0', '#', 'D'},
};
int row, col;
/* check to see any key pressed first */
//KEYPAD_ROW->DATA = 0; /* enable all rows */
GPIOPinWrite(keypad_port_row, R1 | R2 | R3 | R4 , 0x00);
col=((GPIOPinRead(keypad_port_col, C1 | C2 | C3 | C4 ))&0x0F);
//col = KEYPAD_COL->DATA & 0x0F; /* read all columns */
if (col == 0x0F) return 0; /* no key pressed */
/* If a key is pressed, it gets here to find out which key. */
/* Although it is written as an infinite loop, it will take one of the
breaks or return in one pass.*/
while (1)
{
row = 0;
//KEYPAD_ROW->DATA = 0x1C; /* enable row 0 */
GPIOPinWrite(keypad_port_row, R1 | R2 | R3 | R4 , 0x1C);
SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 2)/3);
//delayUs(2); /* wait for signal to settle */
//col = KEYPAD_COL->DATA & 0x0F;
col=((GPIOPinRead(keypad_port_col, C1 | C2 | C3 | C4 ))&0x0F);
if (col != 0x0F) break;  //sth in tis row is pressed exit while and check in which col //else continue to check rest of rows //col==0X0F no pressed key

row = 1;
//KEYPAD_ROW->DATA = 0x1A; /* enable row 1 */
GPIOPinWrite(keypad_port_row, R1 | R2 | R3 | R4 , 0x1A);
SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 2)/3);
//delayUs(2); /* wait for signal to settle */
//col = KEYPAD_COL->DATA & 0x0F;
col=((GPIOPinRead(keypad_port_col, C1 | C2 | C3 | C4 ))&0x0F);
if (col != 0x0F) break;

row = 2;
//KEYPAD_ROW->DATA = 0x16; /* enable row 2 */
GPIOPinWrite(keypad_port_row, R1 | R2 | R3 | R4 , 0x16);
SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 2)/3);
//delayUs(2); /* wait for signal to settle */
//col = KEYPAD_COL->DATA & 0x0F;
col=((GPIOPinRead(keypad_port_col, C1 | C2 | C3 | C4 ))&0x0F);
if (col != 0x0F) break;

row = 3;
//KEYPAD_ROW->DATA = 0x0E; /* enable row 3 */
GPIOPinWrite(keypad_port_row, R1 | R2 | R3 | R4 , 0x0E);
SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 2)/3);
//delayUs(2); /* wait for signal to settle */
//col = KEYPAD_COL->DATA & 0x0F;
col=((GPIOPinRead(keypad_port_col, C1 | C2 | C3 | C4 ))&0x0F);
if (col != 0x0F) break;
return 0; /* if no key is pressed */ //terminate function without getting any character returned
}
/* gets here when one of the rows has key pressed */
if (col == 0x0E) return keymap[row][0]; /* key in column 0 */
if (col == 0x0D) return keymap[row][1]; /* key in column 1 */
if (col == 0x0B) return keymap[row][2]; /* key in column 2 */
if (col == 0x07) return keymap[row][3]; /* key in column 3 */
return 0; /* just to be safe */
}

/* This is a non-blocking function. */
/* If a key is pressed, it returns 1. */
/* Otherwise, it returns a 0 (not ASCII 0).*/
unsigned char keypad_kbhit(void)
{
int col;
/* check to see any key pressed */
//KEYPAD_ROW->DATA = 0; /* enable all rows */
GPIOPinWrite(keypad_port_row, R1 | R2 | R3 | R4 , 0x00);
//col = KEYPAD_COL->DATA & 0x0F; /* read all columns */
col=((GPIOPinRead(keypad_port_col, C1 | C2 | C3 | C4 ))&0x0F);
if (col == 0x0F)
return 0; /* no key pressed */
else
return 1; /* a key is pressed */
}











































void keypad_vid_Init(void)
{
	 SysCtlPeripheralEnable(keypad_port_clock_row);  ////enable clock fo ports SYS_RCGC_R
	while(!SysCtlPeripheralReady( keypad_port_clock_row ));   ////check for clock is set or not read
	
	SysCtlPeripheralEnable(keypad_port_clock_col);  ////enable clock fo ports SYS_RCGC_R
	while(!SysCtlPeripheralReady( keypad_port_clock_col ));
	

GPIOPadConfigSet(keypad_port_row , R1 | R2 | R3 | R4 ,GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD_WPU );//digital,pull-up for rows
//GPIOPinWrite(keypad_port_row, R1 | R2 | R3 | R4 , 0x0F);
	GPIOPadConfigSet(keypad_port_col , C1 | C2 | C3 | C4 ,GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_OD );  	//digital for columns 
	
  GPIODirModeSet( keypad_port_row, R1 | R2 | R3 | R4 , GPIO_DIR_MODE_IN ); //Set rows to input
	GPIODirModeSet( keypad_port_col , C1 | C2 | C3 | C4 , GPIO_DIR_MODE_OUT); //set columns to output
}

uint8_t keypad_uint8_GetButtonStatus(uint8_t button)
{
	/* identify position from button number"notice"  1  2  3  4
                                                         5  6  7  8
                                                       9  10 11 12
                                                         13 14 15 16 */
	uint8_t row = ((button - 1) / 4) +1;
	uint8_t col = ((button - 1) % 4) +1;
	/* status =0   "unpressed"  status=1 "clicked" */
	uint8_t status = 0; /* initially*/
	uint8_t div[4]={1,2,3,4};

	uint8_t realCol[4] = {C1,C2,C3,C4};
	uint8_t realRow[4] = {R1,R2,R3,R4};
	uint8_t value;
	/* initially all columns 1 */
	/* only real column is set to zero */
	 GPIOPinWrite(keypad_port_col, C1 | C2 | C3 | C4 , 0x1E);//write 1 to columns

 GPIOPinWrite(keypad_port_col, realCol[col-1] ,0x00);//write to port
 value = GPIOPinRead(keypad_port_row,realRow[row-1]>>div[row-1]);//read


	if(value == 0)
	{
		SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 1000000)/3);
		value = GPIOPinRead( keypad_port_row ,realRow[row-1]>>div[row-1]);//read
		if(value == 0)
		{
			status = 1;
		}
	}
	return status;
}

