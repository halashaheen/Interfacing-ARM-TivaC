#include <stdint.h>
#include <stdbool.h>
//#include <delay.h>

#include "..\tm4c123gh6pm.h"
#include "..\driverlib\gpio.h"
#include "..\driverlib\sysctl.h"
#include "..\inc\hw_memmap.h"
#include "LCD_config.h"
#include "LCD.h"


void LCD_init(void){
//initialize port data,rs,rw,e
	SysCtlPeripheralEnable(LCD_Data_port_clock); 
	while(!SysCtlPeripheralReady(LCD_Data_port_clock)){}
		SysCtlPeripheralEnable(LCD_control_port_clock); 
	while(!SysCtlPeripheralReady(LCD_control_port_clock)){}
	GPIOPadConfigSet( LCD_control_port,RS|RW|E ,GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD );
	GPIOPadConfigSet( LCD_Data_port,all_port ,GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD );
////////////////////
		GPIODirModeSet(LCD_control_port,RS|RW|E  , GPIO_DIR_MODE_OUT );
		GPIODirModeSet(LCD_Data_port, all_port  , GPIO_DIR_MODE_OUT );
		SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 50000)/3);
	  LCD_Vid_WriteCommand(0x3C);
	
		SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 1000)/3);
	
		LCD_Vid_WriteCommand(0x0E);
	
		SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 1000)/3);
	
		LCD_Vid_WriteCommand(0x01);
	
		SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 2000)/3);

		LCD_Vid_WriteCommand(0xFF);		//0x06
}





void LCD_Vid_WriteCommand (uint8_t command)
{
GPIOPinWrite(LCD_control_port,RW,0x00);
GPIOPinWrite(LCD_control_port,RS,0x00);
GPIOPinWrite(LCD_Data_port,all_port,command);
	/////pulse e////
	GPIOPinWrite(LCD_control_port,E,0x10);
	SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 1000)/3);
	GPIOPinWrite(LCD_control_port,E,0x00);
	SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 1000)/3);	
}

void LCD_Vid_WriteData (uint8_t data)
{
GPIOPinWrite(LCD_control_port,RW,0x00);
GPIOPinWrite(LCD_control_port,RS,0x04);
GPIOPinWrite(LCD_Data_port,all_port,data);
	/////pulse e////
	GPIOPinWrite(LCD_control_port,E,0x10);
	SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 1000)/3);
	GPIOPinWrite(LCD_control_port,E,0x00);
	SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 1000)/3);	
}


void LCD_Vid_Setposition(uint8_t row,uint8_t col)
{
	if(row ==0)
	{
		if(col>39){col=0;}
		LCD_Vid_WriteCommand(0x80|col);
	}
	else if (row==1)
	{

		LCD_Vid_WriteCommand(0xC0|col);

	}
}
void LCD_Vid_WriteString(uint8_t *ptr)
	{
	uint8_t i=0;
	while(ptr[i]!=0)
	{
		LCD_Vid_WriteData(ptr[i]);
		i++;
	}
}
	
void LCD_Vid_WriteNumber(uint32_t input)
{
	uint32_t num=1;
	/*inverted number */
	if(input==0)
	{
		LCD_Vid_WriteData('0');
	}

	while(input!=0)
	{
		num=num*10+input%10;
		input/=10;
	}
	/*display number */
	while(num!=1)
	{
		LCD_Vid_WriteData(num%10+'0');
		num/=10;
	}

}
