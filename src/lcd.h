/*
lcd.h
Author:Kirollos Gerges
*/

#ifndef LCD_H
#define LCD_H
void init_Data_pins(void);
void init_command_pins(void);
void lcd_command(unsigned char cmd);
void LCD_Char (unsigned char char_data);
void LCD_Init (void);
void LCD_String (char *str);
void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear();
void lcd_into_string(char data);
void Delay(int nCount);


#endif
