/*****************************************************************************
 * 
 * This header file provides an interface for controlling a standard HD44780 LCD 
 * display in 4-bit mode, commonly used in embedded systems.
 * 
 * The LCD driver supports:
 * - 4-bit data interface
 * - 2-line display mode
 * - Custom character creation
 * - Display and cursor manipulation
 * 
 * Hardware configuration requires:
 * - 3 control pins (RS, RW, EN)
 * - 4 data pins (D4-D7)
 * 
 *****************************************************************************/

#ifndef LCD_H
#define LCD_H

#include "Std_Types.h"
#include "Gpio.h"

/* 
 * LCD Pin Configuration
 * Control Pins (Register Select, Enable, Read/Write)
 */
#define LCD_RS_PORT     GPIO_B  /* Register Select - Selects command or data register */
#define LCD_RS_PIN      0       
#define LCD_EN_PORT     GPIO_B  /* Enable - Latches data on falling edge */
#define LCD_EN_PIN      1

#define LCD_RW_PORT     GPIO_B  /* Read/Write - Selects read or write operation */
#define LCD_RW_PIN      2       

/* 
 * Data Pins (4-bit mode, only D4-D7 used)
 */
#define LCD_C4_PORT     GPIO_C  /* Data bit 4 */
#define LCD_C4_PIN      4       
#define LCD_C5_PORT     GPIO_C  /* Data bit 5 */
#define LCD_C5_PIN      5       
#define LCD_C6_PORT     GPIO_C  /* Data bit 6 */
#define LCD_C6_PIN      6       
#define LCD_C7_PORT     GPIO_C  /* Data bit 7 */
#define LCD_C7_PIN      7       

/*
 * Basic LCD Commands
 */
#define LCD_CLEAR_DISPLAY       0x01  /* Clears entire display and sets DDRAM address to 0 */
#define LCD_RETURN_HOME         0x02  /* Sets DDRAM address to 0 and returns display to original position */

/*
 * Entry Mode Commands - Control text entry direction and display shift
 */
#define LCD_ENTRY_MODE          0x04  /* Entry mode set base command */
#define LCD_ENTRY_RIGHT         0x00  /* Text direction right */
#define LCD_ENTRY_LEFT          0x02  /* Text direction left */
#define LCD_ENTRY_SHIFT_INC     0x01  /* Display shift on */
#define LCD_ENTRY_SHIFT_DEC     0x00  /* Display shift off */
#define LCD_ENTRY_MODE_DEFAULT  0x06  /* Default: increment cursor position, no shift */

/*
 * Display Control Commands - Control display, cursor and blinking
 */
#define LCD_DISPLAY_CONTROL     0x08  /* Display control base command */
#define LCD_DISPLAY_ON          0x04  /* Display on */
#define LCD_DISPLAY_OFF         0x00  /* Display off */
#define LCD_CURSOR_ON           0x02  /* Cursor on */
#define LCD_CURSOR_OFF          0x00  /* Cursor off */
#define LCD_BLINK_ON            0x01  /* Cursor blinking on */
#define LCD_BLINK_OFF           0x00  /* Cursor blinking off */
#define LCD_DISPLAY_DEFAULT     0x0C  /* Default: display on, cursor off, blink off */

/*
 * Cursor/Display Shift Commands - Move cursor or shift display without changing DDRAM
 */
#define LCD_CURSOR_SHIFT        0x10  /* Cursor/display shift base command */
#define LCD_DISPLAY_MOVE        0x08  /* Move display */
#define LCD_CURSOR_MOVE         0x00  /* Move cursor */
#define LCD_MOVE_RIGHT          0x04  /* Move right */
#define LCD_MOVE_LEFT           0x00  /* Move left */

/*
 * Function Set Commands - Configure LCD functionality
 */
#define LCD_FUNCTION_SET        0x20  /* Function set base command */
#define LCD_8BIT_MODE           0x10  /* 8-bit data interface */
#define LCD_4BIT_MODE           0x00  /* 4-bit data interface */
#define LCD_2LINE               0x08  /* 2 display lines */
#define LCD_1LINE               0x00  /* 1 display line */
#define LCD_5x10DOTS            0x04  /* 5x10 dot character font */
#define LCD_5x8DOTS             0x00  /* 5x8 dot character font */
#define LCD_FUNCTION_DEFAULT    0x28  /* Default: 4-bit, 2 lines, 5x8 dots */

/*
 * Address Setting Commands
 */
#define LCD_SET_CGRAM_ADDR      0x40  /* Set CGRAM address - For custom character creation */
#define LCD_SET_DDRAM_ADDR      0x80  /* Set DDRAM address - For cursor positioning */

/*
 * Line Address Offsets
 */
#define LCD_LINE1               0x00  /* First line address offset */
#define LCD_LINE2               0x40  /* Second line address offset */

/*
 * Function Prototypes
 */

/**
 * Initializes the LCD in 4-bit mode with default settings
 * Must be called before any other LCD functions
 */
void LCD_init(void);

/**
 * Sends a command to the LCD
 * @param cmd: The command byte to send
 */
void LCD_command(uint8 cmd);

/**
 * Writes a single character to the LCD at current cursor position
 * @param data: The character to display
 */
void LCD_write_char(uint8 data);

/**
 * Writes a string to the LCD at current cursor position
 * @param str: Null-terminated string to display
 */
void LCD_write_string(const char *str);

/**
 * Sets the cursor position
 * @param row: Row number (0 for first line, 1 for second line)
 * @param col: Column number (0-15)
 */
void LCD_set_cursor(uint8 row, uint8 col);

/**
 * Clears the display and returns cursor to home position
 */
void LCD_clear(void);

/**
 * Returns cursor to home position (0,0) without clearing display
 */
void LCD_home(void);

/**
 * Creates a custom character in CGRAM
 * @param location: Character location (0-7)
 * @param pattern: 8-byte array representing the character pattern
 */
void LCD_create_custom_char(uint8 location, uint8 *pattern);

/**
 * Displays a custom character at current cursor position
 * @param location: Character location (0-7)
 */
void LCD_write_custom_char(uint8 location);

/**
 * Shifts the entire display left or right
 * @param direction: LCD_MOVE_LEFT or LCD_MOVE_RIGHT
 */
void LCD_shift_display(uint8 direction);

/**
 * Shifts the cursor left or right without changing display data
 * @param direction: LCD_MOVE_LEFT or LCD_MOVE_RIGHT
 */
void LCD_shift_cursor(uint8 direction);

/**
 * Controls display, cursor visibility and blinking
 * @param display: LCD_DISPLAY_ON or LCD_DISPLAY_OFF
 * @param cursor: LCD_CURSOR_ON or LCD_CURSOR_OFF
 * @param blink: LCD_BLINK_ON or LCD_BLINK_OFF
 */
void LCD_display_control(uint8 display, uint8 cursor, uint8 blink);

/**
 * Millisecond delay function
 * @param ms: Delay time in milliseconds
 */
void delay_ms(uint32 ms);

/**
 * Microsecond delay function
 * @param us: Delay time in microseconds
 */
void delay_us(uint32 us);

#endif