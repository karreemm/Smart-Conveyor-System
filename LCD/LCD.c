/**
 * This file contains the implementation of functions for interfacing with an
 * HD44780-compatible LCD in 4-bit mode.
 */

#include "LCD.h"
#include "Std_Types.h"
#include "Gpio.h"
#include "RCC.h"

/**
 * @brief Delays execution for a specified number of milliseconds.
 * @param ms Number of milliseconds to delay.
 *
 * This function uses a busy-wait loop for delaying execution. It assumes
 * a system clock of 84 MHz.
 */
void delay_ms(uint32 ms) {
    for (uint32 i = 0; i < ms * 8000; i++) {
        __asm__("NOP");
    }
}

/**
 * @brief Delays execution for a specified number of microseconds.
 * @param us Number of microseconds to delay.
 *
 * This function uses a busy-wait loop for delaying execution. It assumes
 * a system clock of 84 MHz.
 */
void delay_us(uint32 us) {
    uint32 cycles = (84 * us) / 4;
    for (volatile uint32 i = 0; i < cycles; i++);
}

/**
 * @brief Sends a nibble (4 bits) to the LCD.
 * @param nibble The nibble to send.
 *
 * This function maps the lower 4 bits of the nibble to the LCD data pins
 * (D4-D7) and pulses the Enable pin to latch the data.
 */
static void LCD_send_nibble(uint8 nibble) {
    Gpio_WritePin(LCD_C4_PORT, LCD_C4_PIN, (nibble & 0x01) ? GPIO_HIGH : GPIO_LOW);
    Gpio_WritePin(LCD_C5_PORT, LCD_C5_PIN, (nibble & 0x02) ? GPIO_HIGH : GPIO_LOW);
    Gpio_WritePin(LCD_C6_PORT, LCD_C6_PIN, (nibble & 0x04) ? GPIO_HIGH : GPIO_LOW);
    Gpio_WritePin(LCD_C7_PORT, LCD_C7_PIN, (nibble & 0x08) ? GPIO_HIGH : GPIO_LOW);

    // Pulse the Enable pin
    Gpio_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_HIGH);
    delay_us(5);
    Gpio_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_LOW);
    delay_us(100);
}

/**
 * @brief Sends a command to the LCD.
 * @param cmd The command to send.
 */
void LCD_command(uint8 cmd) {
    Gpio_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_LOW);
    LCD_send_nibble(cmd >> 4);
    LCD_send_nibble(cmd & 0x0F);
    delay_ms(2);
}

/**
 * @brief Writes a single character to the LCD.
 * @param data The character to write.
 */
void LCD_write_char(uint8 data) {
    Gpio_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_HIGH);
    LCD_send_nibble(data >> 4);
    LCD_send_nibble(data & 0x0F);
    delay_us(50);
}

/**
 * @brief Writes a string to the LCD.
 * @param str Pointer to the null-terminated string to write.
 */
void LCD_write_string(const char *str) {
    while (*str) {
        LCD_write_char(*str++);
    }
}

/**
 * @brief Initializes the LCD in 4-bit mode.
 *
 * Configures GPIO pins and sends the initialization sequence to the LCD.
 */
void LCD_init(void) {
    Gpio_Init(LCD_RS_PORT, LCD_RS_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_EN_PORT, LCD_EN_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_RW_PORT, LCD_RW_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_C4_PORT, LCD_C4_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_C5_PORT, LCD_C5_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_C6_PORT, LCD_C6_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_C7_PORT, LCD_C7_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);

    Gpio_WritePin(LCD_RS_PORT, GPIO_LOW);
    Gpio_WritePin(LCD_EN_PORT, GPIO_LOW);
    Gpio_WritePin(LCD_RW_PORT, GPIO_LOW);

    delay_ms(50);

    LCD_send_nibble(0x03);
    delay_ms(5);
    LCD_send_nibble(0x03);
    delay_ms(5);
    LCD_send_nibble(0x03);
    delay_ms(5);
    LCD_send_nibble(0x02);
    delay_ms(5);

    LCD_command(LCD_FUNCTION_DEFAULT);
    LCD_command(LCD_DISPLAY_DEFAULT);
    LCD_command(LCD_CLEAR_DISPLAY);
    LCD_command(LCD_ENTRY_MODE_DEFAULT);

    LCD_clear();
    LCD_home();
}

/**
 * @brief Clears the LCD display.
 */
void LCD_clear(void) {
    LCD_command(LCD_CLEAR_DISPLAY);
    delay_ms(5);
}

/**
 * @brief Returns the cursor to the home position.
 */
void LCD_home(void) {
    LCD_command(LCD_RETURN_HOME);
    delay_ms(2);
}

/**
 * @brief Sets the cursor position on the LCD.
 * @param row The row (0 or 1).
 * @param col The column (0 to 15).
 */
void LCD_set_cursor(uint8 row, uint8 col) {
    uint8 row_offsets[] = {0x00, 0x40};
    LCD_command(LCD_SET_DDRAM_ADDR | (row_offsets[row] + col));
}

/**
 * @brief Writes an integer number to the LCD.
 * @param num The integer value to display.
 */
void LCD_write_number(uint32 num) {
    if (num == 0) {
        LCD_write_char('0');
        return;
    }

    char buffer[12];
    uint8 i = 0;

    while (num > 0) {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }

    while (i > 0) {
        LCD_write_char(buffer[--i]);
    }
}

/**
 * @brief Writes a floating-point number to the LCD.
 * @param num The float value to display.
 * @param precision The number of decimal places to show (0-5).
 */
void LCD_write_float(float num, uint8 precision) {
    if (precision > 5) precision = 5;

    uint32 int_part = (uint32)num;
    LCD_write_number(int_part);

    if (precision > 0) {
        LCD_write_char('.');
        float decimal_part = num - int_part;
        for (uint8 i = 0; i < precision; i++) {
            decimal_part *= 10;
            LCD_write_char('0' + ((int)decimal_part % 10));
        }
    }
}