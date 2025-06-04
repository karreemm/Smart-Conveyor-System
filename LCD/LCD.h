#ifndef LCD_H
#define LCD_H

#include "Std_Types.h"
#include <Gpio.h>

#define LCD_RS_PORT     GPIO_B  
#define LCD_RS_PIN      0       
#define LCD_EN_PORT     GPIO_B  
#define LCD_EN_PIN      1

#define LCD_RW_PORT     GPIO_B  
#define LCD_RW_PIN      2       

#define LCD_C4_PORT     GPIO_C  
#define LCD_C4_PIN      4       
#define LCD_C5_PORT     GPIO_C  
#define LCD_C5_PIN      5       
#define LCD_C6_PORT     GPIO_C  
#define LCD_C6_PIN      6       
#define LCD_C7_PORT     GPIO_C  
#define LCD_C7_PIN      7       

#define LCD_CLEAR_DISPLAY       0x01  
#define LCD_RETURN_HOME         0x02  

#define LCD_ENTRY_MODE          0x04  // Entry mode set base command
#define LCD_ENTRY_RIGHT         0x00  // Text direction right
#define LCD_ENTRY_LEFT          0x02  // Text direction left
#define LCD_ENTRY_SHIFT_INC     0x01  // Display shift on
#define LCD_ENTRY_SHIFT_DEC     0x00  // Display shift off
#define LCD_ENTRY_MODE_DEFAULT  0x06  // Default: increment cursor position, no shift

#define LCD_DISPLAY_CONTROL     0x08  // Display control base command
#define LCD_DISPLAY_ON          0x04  // Display on
#define LCD_DISPLAY_OFF         0x00  // Display off
#define LCD_CURSOR_ON           0x02  // Cursor on
#define LCD_CURSOR_OFF          0x00  // Cursor off
#define LCD_BLINK_ON            0x01  // Blinking cursor on
#define LCD_BLINK_OFF           0x00  // Blinking cursor off
#define LCD_DISPLAY_DEFAULT     0x0C  // Default: display on, cursor off, blink off

#define LCD_CURSOR_SHIFT        0x10  // Cursor/display shift base command
#define LCD_DISPLAY_MOVE        0x08  // Move display
#define LCD_CURSOR_MOVE         0x00  // Move cursor
#define LCD_MOVE_RIGHT          0x04  // Move right
#define LCD_MOVE_LEFT           0x00  // Move left

#define LCD_FUNCTION_SET        0x20  // Function set base command
#define LCD_8BIT_MODE           0x10  // 8-bit data mode
#define LCD_4BIT_MODE           0x00  // 4-bit data mode
#define LCD_2LINE               0x08  // 2 display lines
#define LCD_1LINE               0x00  // 1 display line
#define LCD_5x10DOTS            0x04  // 5x10 dot character font
#define LCD_5x8DOTS             0x00  // 5x8 dot character font
#define LCD_FUNCTION_DEFAULT    0x28  // Default: 4-bit, 2 lines, 5x8 dots

#define LCD_SET_CGRAM_ADDR      0x40  // Set CGRAM address
#define LCD_SET_DDRAM_ADDR      0x80  // Set DDRAM address

#define LCD_LINE1               0x00  
#define LCD_LINE2               0x40  

#define LOW                 0x00
#define HIGH                0x01

void LCD_init(void);
void LCD_command(uint8 cmd);
void LCD_write_char(uint8 data);
void LCD_write_string(const char *str);
void LCD_set_cursor(uint8 row, uint8 col);
void LCD_clear(void);
void LCD_home(void);
void LCD_create_custom_char(uint8 location, uint8 *pattern);
void LCD_write_custom_char(uint8 location);
void LCD_shift_display(uint8 direction);
void LCD_shift_cursor(uint8 direction);
void LCD_display_control(uint8 display, uint8 cursor, uint8 blink);
void delay_ms(uint32 ms);
void delay_us(uint32 us);

#endif