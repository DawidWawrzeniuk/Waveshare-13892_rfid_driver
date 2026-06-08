#include "lcd.h"
extern SPI_HandleTypeDef hspi2;
#define ST7735S_SLPOUT			0x11
#define ST7735S_DISPOFF			0x28
#define ST7735S_DISPON			0x29
#define ST7735S_CASET			0x2a
#define ST7735S_RASET			0x2b
#define ST7735S_RAMWR			0x2c
#define ST7735S_MADCTL			0x36
#define ST7735S_COLMOD			0x3a
#define ST7735S_FRMCTR1			0xb1
#define ST7735S_FRMCTR2			0xb2
#define ST7735S_FRMCTR3			0xb3
#define ST7735S_INVCTR			0xb4
#define ST7735S_PWCTR1			0xc0
#define ST7735S_PWCTR2			0xc1
#define ST7735S_PWCTR3			0xc2
#define ST7735S_PWCTR4			0xc3
#define ST7735S_PWCTR5			0xc4
#define ST7735S_VMCTR1			0xc5
#define ST7735S_GAMCTRP1		0xe0
#define ST7735S_GAMCTRN1		0xe1
/**
 * Sends a command byte to the LCD controller.
 *
 * This function is declared as static, which means it is only visible
 * within this source file. Using static functions helps avoid name
 * collisions between modules and improves encapsulation.
 *
 * Static functions should not be declared in header files.
 */
void lcd_cmd(uint8_t cmd)		//funkcja statyczna bo tylko w tym pliku (nie widoczna dla innych plików)To bardzo ważne, bo dzięki temu nie pojawia się ryzyko konfliktu nazw, a nasze moduły są lepiej od siebie odizolowane.
{
	// Set DC low to indicate command transmission									//W przypadku funkcji statycznych nie umieszczamy ich deklaracji w pliku nagłówkowym. Ograniczamy się jedynie do umieszczenia funkcji w pliku źródłowym!
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);	//ustawienie stanu niskiego na pinie DC aby wyslac komende
	 // Select the LCD controller (active low)
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);	//ustawienie stanu niskiego na pinie CS aby wybrac sterownik wyswietlacza
	 // Transmit one command byte over SPI
	HAL_SPI_Transmit(&hspi2, &cmd, 1, HAL_MAX_DELAY);					//wyslanie danych
	// Deselect the LCD controller
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);		//stan wysoki na linii CS
}
/**
 * Sends a data byte to the LCD controller.
 */
void lcd_data(uint8_t data)		//funkcja do wysylania danych
{
	// Set DC high to indicate data transmission
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	// Select the LCD controller
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	 // Transmit one data byte over SPI
	HAL_SPI_Transmit(&hspi2, &data, 1, HAL_MAX_DELAY);
	// Deselect the LCD controller
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}
/**
 * Marks a value as an LCD command by setting bit 8.
 *
 * Values without this flag are treated as display data.
 */
#define CMD(x)			((x) | 0x100)
/**
 * Sends either a command or data depending on bit 8.
 *
 * Bit 8 acts as a flag:
 *   - set   -> command
 *   - clear -> data
 */
void lcd_send(uint16_t value)
{
	if (value & 0x100) {
		lcd_cmd(value);
	} else {
		lcd_data(value);
	}
}
/**
 * LCD initialization sequence.
 *
 * Commands are marked using CMD(), while the remaining values
 * are interpreted as data bytes associated with the preceding command.
 */
static const uint16_t init_table[] = {						//tablica jedno wymiarowa
  CMD(ST7735S_FRMCTR1), 0x01, 0x2c, 0x2d,
  CMD(ST7735S_FRMCTR2), 0x01, 0x2c, 0x2d,
  CMD(ST7735S_FRMCTR3), 0x01, 0x2c, 0x2d, 0x01, 0x2c, 0x2d,
  CMD(ST7735S_INVCTR), 0x07,
  CMD(ST7735S_PWCTR1), 0xa2, 0x02, 0x84,
  CMD(ST7735S_PWCTR2), 0xc5,
  CMD(ST7735S_PWCTR3), 0x0a, 0x00,
  CMD(ST7735S_PWCTR4), 0x8a, 0x2a,
  CMD(ST7735S_PWCTR5), 0x8a, 0xee,
  CMD(ST7735S_VMCTR1), 0x0e,
  CMD(ST7735S_GAMCTRP1), 0x0f, 0x1a, 0x0f, 0x18, 0x2f, 0x28, 0x20, 0x22,
                         0x1f, 0x1b, 0x23, 0x37, 0x00, 0x07, 0x02, 0x10,
  CMD(ST7735S_GAMCTRN1), 0x0f, 0x1b, 0x0f, 0x17, 0x33, 0x2c, 0x29, 0x2e,
                         0x30, 0x30, 0x39, 0x3f, 0x00, 0x07, 0x03, 0x10,
  CMD(0xf0), 0x01,
  CMD(0xf6), 0x00,
  CMD(ST7735S_COLMOD), 0x05,
  CMD(ST7735S_MADCTL), 0xa0,
};
/**
 * Initializes the ST7735S LCD controller.
 *
 * The display is first hardware-reset, then configured using
 * the initialization table. Finally, sleep mode is disabled
 * and the display is turned on.
 */
void lcd_init(void)
{
  int i;
  // Perform hardware reset
  HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
  HAL_Delay(100);
  // Send all commands and data from initialization table
  for (i = 0; i < sizeof(init_table) / sizeof(uint16_t); i++) //To popularny sposób w C na policzenie ile elementów ma tablica.

	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	 // sizeof(init_table) → rozmiar całej tablicy w bajtach

																 // sizeof(uint16_t) → rozmiar jednego elementu (2 bajty)
  {
    lcd_send(init_table[i]);
  }

  HAL_Delay(200);
  // Exit sleep mode
  lcd_cmd(ST7735S_SLPOUT);		//budzenie z trybu uspienia
  HAL_Delay(120);
  // Turn display on
  lcd_cmd(ST7735S_DISPON);		//wlaczenie wyswietlacza
}
/**
 * Sends a 16-bit value as two consecutive bytes (MSB first).
 */
void lcd_data16(uint16_t value)		//funkcja do wysylania slow 16 bitowych
{
	lcd_data(value >> 8);   // High byte
	lcd_data(value);        // Low byte
}

/*
 * CASET (Column Address Set)
 *     Defines the start and end column of the drawing area.
 *
 * RASET (Row Address Set)
 *     Defines the start and end row of the drawing area.
 *
 * RAMWR (Memory Write)
 *     Starts pixel data transfer to the selected area.
 */
/*
 * The ST7735S controller supports a resolution up to 162×132 pixels,
 * while the display panel itself has a resolution of 160×128 pixels.
 *
 * Due to the way the display module is wired internally, the visible
 * image area is shifted relative to the controller memory.
 *
 * To compensate for this offset:
 *   - X coordinates must be shifted by 1 pixel
 *   - Y coordinates must be shifted by 2 pixels
 *
 * Without these offsets, the image would appear displaced.
 */
#define LCD_OFFSET_X  1
#define LCD_OFFSET_Y  2
/**
 * Defines the active drawing window.
 *
 * All subsequent pixel data written with RAMWR will be placed
 * inside the specified rectangular area.
 *
 * @param x      Left coordinate
 * @param y      Top coordinate
 * @param width  Window width in pixels
 * @param height Window height in pixels
 */
void lcd_set_window(int x, int y, int width, int height)
{
  lcd_cmd(ST7735S_CASET);
  lcd_data16(LCD_OFFSET_X + x);
  lcd_data16(LCD_OFFSET_X + x + width - 1);

  lcd_cmd(ST7735S_RASET);
  lcd_data16(LCD_OFFSET_Y + y);
  lcd_data16(LCD_OFFSET_Y + y + height- 1);
}
#define LCD_OFFSET_X 2
#define LCD_OFFSET_Y 1
/**
 * Fills a rectangular area with a single color.
 *
 * The LCD controller automatically advances through all pixels
 * inside the selected window while data is being transmitted.
 *
 * @param x      Left coordinate
 * @param y      Top coordinate
 * @param width  Rectangle width
 * @param height Rectangle height
 * @param color  RGB565 color value
 */
void lcd_fill_box(int x, int y, int width, int height, uint16_t color)
{
	lcd_set_window(x, y, width, height);

	lcd_cmd(ST7735S_RAMWR);
	for (int i = 0; i < width * height; i++)
		lcd_data16(color);
}
