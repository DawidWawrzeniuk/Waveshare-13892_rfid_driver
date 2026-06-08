#include "main.h"
#include "string.h"
#include "stdint.h"

#define LCD_MAX_LINES 4
void Read_data_from_rfid(void);
char* find_card(uint8_t *UID);
typedef struct{
uint8_t UID[5];
char name[16];
} Card;
