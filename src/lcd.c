/*
 * lcd.c
 *
 *  Created on: Feb 13, 2024
 *      Author: kerollos
 */


/*
lcd.c
Author:Kirollos Gerges
*/

#include "lcd.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stdint.h"


void init_Data_pins(void)
{

     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitTypeDef GPIO_InitDef_D;
    GPIO_InitDef_D.GPIO_Pin = GPIO_Pin_All;
	     GPIO_InitDef_D.GPIO_Mode = GPIO_Mode_OUT;
	     GPIO_InitDef_D.GPIO_OType = GPIO_OType_PP;
	     GPIO_InitDef_D.GPIO_PuPd = GPIO_PuPd_NOPULL;
	     GPIO_InitDef_D.GPIO_Speed = GPIO_Speed_2MHz;


	     GPIO_Init(GPIOD, &GPIO_InitDef_D);
         //make it initialization as low
	    GPIO_ResetBits(GPIOD,GPIO_Pin_0);
        GPIO_ResetBits(GPIOD,GPIO_Pin_1);
        GPIO_ResetBits(GPIOD,GPIO_Pin_2);
        GPIO_ResetBits(GPIOD,GPIO_Pin_3);
        GPIO_ResetBits(GPIOD,GPIO_Pin_4);
        GPIO_ResetBits(GPIOD,GPIO_Pin_5);
        GPIO_ResetBits(GPIOD,GPIO_Pin_6);
        GPIO_ResetBits(GPIOD,GPIO_Pin_7);
}


void init_command_pins(void)
{

     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitDef_C;
    GPIO_InitDef_C.GPIO_Pin = GPIO_Pin_All;
	     GPIO_InitDef_C.GPIO_Mode = GPIO_Mode_OUT;
	     GPIO_InitDef_C.GPIO_OType = GPIO_OType_PP;
	     GPIO_InitDef_C.GPIO_PuPd = GPIO_PuPd_NOPULL;
	     GPIO_InitDef_C.GPIO_Speed = GPIO_Speed_2MHz;


	     GPIO_Init(GPIOC, &GPIO_InitDef_C);
         //make it initialization as low
	    GPIO_ResetBits(GPIOC,GPIO_Pin_0);
        GPIO_ResetBits(GPIOC,GPIO_Pin_1);
        GPIO_ResetBits(GPIOC,GPIO_Pin_2);
        GPIO_ResetBits(GPIOC,GPIO_Pin_3);
        GPIO_ResetBits(GPIOC,GPIO_Pin_4);
        GPIO_ResetBits(GPIOC,GPIO_Pin_5);
        GPIO_ResetBits(GPIOC,GPIO_Pin_6);
        GPIO_ResetBits(GPIOC,GPIO_Pin_7);
}

void lcd_command(unsigned char cmd)
{
	init_Data_pins();
    init_command_pins();
   GPIOD->ODR = cmd;

GPIO_ResetBits(GPIOC,GPIO_Pin_0);
GPIO_ResetBits(GPIOC,GPIO_Pin_1);
GPIO_SetBits(GPIOC,GPIO_Pin_2);
Delay(1);
GPIO_ResetBits(GPIOC,GPIO_Pin_2);
Delay(3);

}

void LCD_Char (unsigned char char_data)
{
init_Data_pins();
    init_command_pins();
 GPIOD->ODR = char_data;
 GPIO_SetBits(GPIOC,GPIO_Pin_0);
GPIO_ResetBits(GPIOC,GPIO_Pin_1);
GPIO_SetBits(GPIOC,GPIO_Pin_2);
Delay(1);
GPIO_ResetBits(GPIOC,GPIO_Pin_2);
Delay(1);
}

void LCD_Init (void)
{
    init_Data_pins();
    init_command_pins();
	 GPIOC->ODR = 0XFF;
GPIOD->ODR = 0xFF;
	Delay(20);

	lcd_command(0x38);  //8_bit
	lcd_command(0x0C);
	lcd_command(0x80);
	//lcd_command (0x01);  //to clear
	//lcd_command(0x0E);  //cursor on
}

void LCD_String (char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)
	{
		LCD_Char (str[i]);
	}
}


void LCD_String_xy (char row, char pos, char *str)
{
	if (row == 0 && pos<16)
	lcd_command((pos & 0x0F)|0x80);
	else if (row == 1 && pos<16)
	lcd_command((pos & 0x0F)|0xC0);
	LCD_String(str);
}


void LCD_Clear()
{
	lcd_command (0x01);
lcd_command(0x80);
}

void lcd_into_string(char data)
{
	char buff[16];
	itoa(data,buff,10);
	LCD_String(buff);
}

void Delay(int nCount)
{
    while (nCount--);
}
