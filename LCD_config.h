#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


#define LCD_Data_port_clock      SYSCTL_PERIPH_GPIOB
#define LCD_control_port_clock   SYSCTL_PERIPH_GPIOA
#define LCD_Data_port            GPIO_PORTB_BASE
#define LCD_control_port 				 GPIO_PORTA_BASE
#define RS                       GPIO_PIN_2
#define RW                       GPIO_PIN_3
#define E                        GPIO_PIN_4

#endif /* LCD_CONFIG_H_ */