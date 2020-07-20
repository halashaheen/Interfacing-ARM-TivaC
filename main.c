#include <stdbool.h>
#include <stdint.h>
#include "..\inc\tm4c123gh6pm.h"
#include "..\driverlib\gpio.h"
#include "..\driverlib\sysctl.h"
#include "..\driverlib\eeprom.h"
#include "..\driverlib\interrupt.h"
#include "..\inc\hw_gpio.h"
#include "..\inc\hw_memmap.h"
#include "..\inc\hw_eeprom.h"

#include "LCD.h"
#include "LCD_config.h"
#include "keypad.h"
#include "keypad_config.h"
#include "..\driverlib\uart.h"
#include "..\inc\hw_uart.h"

#define SW1       0x10                      // on the left side of the Launchpad board
#define SW2       0x01                      // on the right side of the Launchpad board

//void SystemInit(){}


/*int main()

{

  ///MAKE b4 b0 pullup input
    volatile uint32_t delay;

    SYSCTL_RCGCGPIO_R|=0x00000002;
    delay=SYSCTL_RCGCGPIO_R;

    //to make sure that it is unlocked although no pins in port b needs to be unlocked =)


  GPIO_PORTB_AMSEL_R =0x00;
    GPIO_PORTB_PCTL_R  =0x00000000;
    //input b4 b0
   GPIO_PORTB_DIR_R|= 0xF0;
   GPIO_PORTB_AFSEL_R= 0x00;
    //pull up to b4 b0
    GPIO_PORTB_DEN_R=0xF0;


      SYSCTL_RCGCGPIO_R|=0x00000008;
      delay=SYSCTL_RCGCGPIO_R;

      //to make sure that it is unlocked although no pins in port b needs to be unlocked =)

      GPIO_PORTD_LOCK_R=0x4C4F434B;
      GPIO_PORTD_CR_R =0x0F;
      GPIO_PORTD_AMSEL_R =0x00;
      GPIO_PORTD_PCTL_R  =0x00000000;
      //input b4 b0
       *
       *
       *
       *
       *
       *
       *
      GPIO_PORTD_DIR_R &=~(0x0F);


      GPIO_PORTD_AFSEL_R=0x00;
      //pull up to b4 b0
      GPIO_PORTD_PUR_R =0x0F;
      GPIO_PORTD_DEN_R=0x0F;
      //GPIO_PORTB_DATA_R |=(GPIO_PORTD_DATA_R<<4) ;
}*/
/*int main()
{
    volatile uint32_t delay;
    SYSCTL_RCGCGPIO_R|=0x00000008;
    delay=SYSCTL_RCGCGPIO_R;
    GPIO_PORTD_AMSEL_R =0x00;
       GPIO_PORTD_PCTL_R  =0x00000000;
       //input b4 b0
      GPIO_PORTD_DIR_R|= 0xFF;
      GPIO_PORTD_AFSEL_R= 0x00;
       //pull up to b4 b0
       GPIO_PORTD_DEN_R=0xFF;
       GPIO_PORTD_DATA_R =0xFF;


}*/
/*
int main()
{

    uint32_t i =0;
    uint8_t flag[16]={0};
    keypad_vid_Init();
    LCD_init();
    LCD_Vid_Setposition(0,0);
             LCD_Vid_WriteString((uint8_t*)"welcome...");
             SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 500000000)/3);
             LCD_Vid_WriteCommand(0x01);
    LCD_Vid_Setposition(0,0);

    while(1)
    {
        for(;i<16;i++)
    {

        if(keypad_uint8_GetButtonStatus(i+1)&&flag[i]==0)
        {
            flag[i]=1;
            LCD_Vid_WriteNumber(i);
        }
        else if(keypad_uint8_GetButtonStatus(i+1)==0)

        {
            flag[i]=0;
        }
    }
    }

}
*/


int main(void)
{
unsigned char key;
keypad_init();
LCD_init();
LCD_Vid_Setposition(0,0);
while(1)
{
    if( keypad_kbhit())
    {
        LCD_Vid_Setposition(0,0);
        LCD_Vid_WriteCommand(0x01);
        LCD_Vid_WriteString((uint8_t*)"pressed");
        LCD_Vid_Setposition(1,0);
        LCD_Vid_WriteData(keypad_getkey());
        SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 2000000)/3);
    }
    else




    {
        LCD_Vid_Setposition(0,0);
        LCD_Vid_WriteCommand(0x01);
        LCD_Vid_WriteString((uint8_t*)"not pressed");
        SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 2000000)/3);
    }
}
}
/*int main(void)
{
    LCD_init();
    LCD_Vid_Setposition(1, 7);
    LCD_Vid_WriteNumber(77);
    SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 2000000)/3);
    LCD_Vid_WriteCommand(0x01);
    SysCtlDelay(CYCLES_FROM_TIME_US(ui32ClockFreq, 2000000)/3);
    LCD_Vid_WriteData('C');
    LCD_Vid_WriteData('A');
    LCD_Vid_WriteData('T');
    LCD_Vid_WriteString((uint8_t*)"kwala");

}*/



