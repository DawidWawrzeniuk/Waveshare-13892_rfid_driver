#ifndef LCD_TEXT_H
#define LCD_TEXT_H

#include <stdint.h>
#define FONT_W 12
#define FONT_H 16
#define LINE_SPACING 2
#define LINE_H (FONT_H + LINE_SPACING)

#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define YELLOW  0xFFE0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
void lcd_draw_char(int x, int y, char c, uint16_t color, uint16_t bg);
void lcd_print(int x, int y, const char *str, uint16_t color, uint16_t bg);
void lcd_print_line(int line, const char *str, uint16_t color, uint16_t bg);
void lcd_clear_line(int y, uint16_t bg);
void lcd_clear(void);
#endif
