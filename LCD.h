
#ifndef LCD_H_
#define LCD_H_

#define all_port    GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
#define CYCLES_FROM_TIME_US(ui32ClockFreq, ui32Time_uS)                       \
    (((ui32Time_uS) == 0) ? 0 :                                               \
    (((ui32ClockFreq) / 1000000) * ((((ui32Time_uS) * 1000) - 1) / 1000)) + 1)
		
#define ui32ClockFreq 16000000		
extern void LCD_init(void);
extern void LCD_Vid_WriteCommand (uint8_t command);
extern void LCD_Vid_WriteData (uint8_t data);
extern void LCD_Vid_Setposition(uint8_t row ,uint8_t col);
extern void LCD_Vid_WriteString (uint8_t *ptr);
extern void LCD_Vid_WriteNumber(uint32_t input);
#endif /* LCD_H_ */