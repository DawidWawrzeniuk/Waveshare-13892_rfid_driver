#include "table_of_cards.h"
#include "lcd_run.h"
extern const uint8_t cards_count;
extern Card cards[];
extern uint8_t disp;
void show_cards(void)
{
    if (HAL_GPIO_ReadPin(menu_right_GPIO_Port, menu_right_Pin) == GPIO_PIN_SET)
    {
        lcd_print_line(1, "MEMORY OF", WHITE, BLACK);
        lcd_print_line(2, "CARDS:", WHITE, BLACK);
        for(int i=0; i<= cards_count;i++)
        {
        lcd_print_line(3+i, cards[i].name, WHITE, BLACK);
        }

    }
}

