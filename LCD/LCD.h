/**
 * This driver provides functions to interface with an HD44780-compatible LCD
 * in 4-bit mode. It includes initialization, command sending, and data writing
 * functionalities.
 *
 * Features:
 * - Initialize the LCD in 4-bit mode.
 * - Send commands and data to the LCD.
 * - Write strings, integers, and floating-point numbers to the LCD.
 * - Control cursor position and display settings.
 * - Create and display custom characters.
 *
 * Usage:
 * 1. Call `LCD_init()` to initialize the LCD.
 * 2. Use `LCD_write_string()` to display text.
 * 3. Use `LCD_set_cursor()` to move the cursor.
 * 4. Use `LCD_write_number()` or `LCD_write_float()` to display numbers.
 * 5. Use `LCD_create_custom_char()` and `LCD_write_custom_char()` for custom characters.
 *
 * @author Ahmed Mahmoud
 * @date 2025-06-02
 */

#ifndef LCD_H
#define LCD_H

#include "Std_Types.h"
#include "Gpio.h"

// Pin definitions
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

// LCD Commands
#define LCD_CLEAR_DISPLAY       0x01  
#define LCD_RETURN_HOME         0x02  
#define LCD_ENTRY_MODE_DEFAULT  0x06  
#define LCD_DISPLAY_DEFAULT     0x0C  
#define LCD_FUNCTION_DEFAULT    0x28  

#define LCD_SET_DDRAM_ADDR      0x80

// Function prototypes
/**
 * @brief Initializes the LCD in 4-bit mode.
 *
 * Configures GPIO pins and sends the initialization sequence to the LCD.
 */
void LCD_init(void);

/**
 * @brief Sends a command to the LCD.
 * @param cmd The command to send.
 */
void LCD_command(uint8 cmd);

/**
 * @brief Writes a single character to the LCD.
 * @param data The character to write.
 */
void LCD_write_char(uint8 data);

/**
 * @brief Writes a string to the LCD.
 * @param str Pointer to the null-terminated string to write.
 */
void LCD_write_string(const char *str);

/**
 * @brief Sets the cursor position on the LCD.
 * @param row The row (0 or 1).
 * @param col The column (0 to 15).
 */
void LCD_set_cursor(uint8 row, uint8 col);

/**
 * @brief Clears the LCD display.
 */
void LCD_clear(void);

/**
 * @brief Returns the cursor to the home position.
 */
void LCD_home(void);

/**
 * @brief Writes an integer number to the LCD.
 * @param num The integer value to display.
 */
void LCD_write_number(uint32 num);

/**
 * @brief Writes a floating-point number to the LCD.
 * @param num The float value to display.
 * @param precision The number of decimal places to show (0-5).
 */
void LCD_write_float(float num, uint8 precision);

/**
 * @brief Creates a custom character in CGRAM.
 * @param location The CGRAM location (0-7).
 * @param pattern Pointer to the 8-byte pattern array.
 */
void LCD_create_custom_char(uint8 location, uint8 *pattern);

/**
 * @brief Displays a previously defined custom character.
 * @param location The CGRAM location (0-7).
 */
void LCD_write_custom_char(uint8 location);

/**
 * @brief Delays execution for a specified number of milliseconds.
 * @param ms Number of milliseconds to delay.
 */
void delay_ms(uint32 ms);

/**
 * @brief Delays execution for a specified number of microseconds.
 * @param us Number of microseconds to delay.
 */
void delay_us(uint32 us);

#endif 