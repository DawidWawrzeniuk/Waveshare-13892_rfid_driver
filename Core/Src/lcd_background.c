#include "lcd.h"

void lcd_draw_background(void)
{
    // pełne czarne tło (pewne 100%)
    lcd_fill_box(0, 0, 160, 160, 0x0000);

    // delikatna siatka (subtelna, NIE oczojebna)
    for (int y = 0; y < 200; y += 16)
    {
        lcd_fill_box(0, y, 160, 1, 0x0841);
    }

    for (int x = 0; x < 200; x += 16)
    {
        lcd_fill_box(x, 0, 1, 160, 0x0841);
    }
}
