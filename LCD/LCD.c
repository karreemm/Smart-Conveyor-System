#include "LCD.h"
#include "Std_Types.h"
#include "Gpio.h"
#include "RCC.h"

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

void delay_ms(uint32 ms) {
    for (uint32 i = 0; i < ms * 8000; i++) {
        __asm__("NOP");
    }
}

void delay_us(uint32 us) {
    uint32 cycles = (84 * us) / 4;
    for (volatile uint32 i = 0; i < cycles; i++);
}

// Helper function to send a nibble (4 bits) to the LCD
static void LCD_send_nibble(uint8 nibble) {
    // Map the lower 4 bits of nibble to the LCD data pins D4-D7
    Gpio_WritePin(LCD_C4_PORT, LCD_C4_PIN, (nibble & 0x01) ? HIGH : LOW);  
    Gpio_WritePin(LCD_C5_PORT, LCD_C5_PIN, (nibble & 0x02) ? HIGH : LOW);  
    Gpio_WritePin(LCD_C6_PORT, LCD_C6_PIN, (nibble & 0x04) ? HIGH : LOW);  
    Gpio_WritePin(LCD_C7_PORT, LCD_C7_PIN, (nibble & 0x08) ? HIGH : LOW);  

    // Pulse the Enable pin - with timing suitable for Proteus simulation
    Gpio_WritePin(LCD_EN_PORT, LCD_EN_PIN, HIGH);
    delay_us(5);  
    Gpio_WritePin(LCD_EN_PORT, LCD_EN_PIN, LOW);
    delay_us(100); 
}

// Send a command to the LCD
void LCD_command(uint8 cmd) {
    // Command mode (RS = 0)
    Gpio_WritePin(LCD_RS_PORT, LCD_RS_PIN, LOW);
    
    // Send high nibble first
    LCD_send_nibble(cmd >> 4);
    // Then send low nibble
    LCD_send_nibble(cmd & 0x0F);
    
    // Most commands need ~40μs, but use 2ms for Proteus simulation
    delay_ms(2);
}

void LCD_write_char(uint8 data) {
    Gpio_WritePin(LCD_RS_PORT, LCD_RS_PIN, HIGH);
    
    LCD_send_nibble(data >> 4);
    LCD_send_nibble(data & 0x0F);
    
    delay_us(50);
}

void LCD_write_string(const char *str) {
    while (*str) {
        LCD_write_char(*str++);
    }
}

void LCD_init(void) {

    Gpio_Init(LCD_RS_PORT, LCD_RS_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_EN_PORT, LCD_EN_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);

    Gpio_Init(LCD_RW_PORT, LCD_RW_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_WritePin(LCD_RW_PORT, LCD_RW_PIN, LOW); 
    
    Gpio_Init(LCD_C4_PORT, LCD_C4_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_C5_PORT, LCD_C5_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_C6_PORT, LCD_C6_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_C7_PORT, LCD_C7_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);

    Gpio_WritePin(LCD_RS_PORT, LCD_RS_PIN, LOW);
    Gpio_WritePin(LCD_EN_PORT, LCD_EN_PIN, LOW);
    
    delay_ms(50);

    // Special 4-bit initialization sequence according to HD44780 datasheet
    // Send 0x03 three times (in 4-bit mode, only send the upper nibble 0x3)
    Gpio_WritePin(LCD_RS_PORT, LCD_RS_PIN, LOW);
    
    LCD_send_nibble(0x03);
    delay_ms(5);
    
    LCD_send_nibble(0x03);
    delay_ms(5);
    
    LCD_send_nibble(0x03);
    delay_ms(5);
    
    LCD_send_nibble(0x02);
    delay_ms(5);

    LCD_command(LCD_FUNCTION_SET | LCD_4BIT_MODE | LCD_2LINE | LCD_5x8DOTS); 
    delay_ms(5);
    
    LCD_command(LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINK_OFF); 
    delay_ms(5);
    
    LCD_command(LCD_CLEAR_DISPLAY); 
    delay_ms(5);
    
    LCD_command(LCD_ENTRY_MODE | LCD_ENTRY_RIGHT | LCD_ENTRY_SHIFT_DEC); 
    delay_ms(5);
    
    LCD_clear();
    LCD_home();
}

void LCD_clear(void) {
    LCD_command(LCD_CLEAR_DISPLAY);
    delay_ms(5); 
}

void LCD_home(void) {
    LCD_command(LCD_RETURN_HOME);
    delay_ms(2);
}

void LCD_set_cursor(uint8 row, uint8 col) {
    uint8 row_offsets[] = {0x00, 0x40, 0x14, 0x54}; 
    if (row > 1) {
        row = 0; 
    }
    LCD_command(LCD_SET_DDRAM_ADDR | (row_offsets[row] + col));
}

void LCD_create_custom_char(uint8 location, uint8 *pattern) {
    location &= 0x7; 
    LCD_command(LCD_SET_CGRAM_ADDR | (location << 3));
    for (uint8 i = 0; i < 8; i++) {
        LCD_write_char(pattern[i]);
    }
}

void LCD_write_custom_char(uint8 location) {
    location &= 0x7;
    LCD_write_char(location);
}

void LCD_shift_display(uint8 direction) {
    if (direction) {
        LCD_command(LCD_CURSOR_SHIFT | LCD_DISPLAY_MOVE | LCD_MOVE_RIGHT);
    } else {
        LCD_command(LCD_CURSOR_SHIFT | LCD_DISPLAY_MOVE | LCD_MOVE_LEFT);
    }
}

void LCD_shift_cursor(uint8 direction) {
    if (direction) {
        LCD_command(LCD_CURSOR_SHIFT | LCD_CURSOR_MOVE | LCD_MOVE_RIGHT);
    } else {
        LCD_command(LCD_CURSOR_SHIFT | LCD_CURSOR_MOVE | LCD_MOVE_LEFT);
    }
}

void LCD_display_control(uint8 display, uint8 cursor, uint8 blink) {
    uint8 command = LCD_DISPLAY_CONTROL;
    if (display) command |= LCD_DISPLAY_ON;
    if (cursor) command |= LCD_CURSOR_ON;
    if (blink) command |= LCD_BLINK_ON;
    LCD_command(command);
}