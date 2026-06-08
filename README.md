📘 Waveshare‑13892 RFID Driver
Driver and example firmware for MFRC522 RFID module (Waveshare 13892) on STM32

This repository contains a complete, lightweight driver for the Waveshare 13892 RFID kit, based on the MFRC522 reader, written for STM32 microcontrollers using the HAL library.
The project includes:

MFRC522 low‑level driver

Card database system

LCD text rendering

Card detection logic

Example application for STM32F303

📦 Features
MFRC522 communication via SPI

Anti‑collision UID reading

Card database lookup

LCD display support (ST7735 / Waveshare LCD)

Automatic screen clearing

Debounced card detection (1s timeout)

Modular code structure

Easy to extend (add more cards, actions, screens)

🧩 Project Structure
Kod
Core/
 ├── Inc/
 │    ├── lcd.h
 │    ├── lcd_text.h
 │    ├── lcd_run.h
 │    ├── RC522.h
 │    ├── table_of_cards.h
 │    └── ...
 ├── Src/
 │    ├── lcd.c
 │    ├── lcd_text.c
 │    ├── lcd_run.c
 │    ├── RC522.c
 │    ├── table_of_cards.c
 │    ├── main.c
 │    └── ...
⚙️ Hardware Requirements
STM32F303 (or any STM32 with SPI)

Waveshare 13892 RFID Kit (MFRC522)

ST7735 / Waveshare LCD display

SPI + GPIO wiring

MFRC522 → STM32 wiring
MFRC522	STM32
SDA	NSS / CS
SCK	SPI SCK
MOSI	SPI MOSI
MISO	SPI MISO
RST	GPIO
3.3V	3.3V
GND	GND


🚀 Getting Started
1. Clone the repository
Kod
git clone https://github.com/DawidWawrzeniuk/Waveshare-13892_rfid_driver
2. Open in STM32CubeIDE
Import as an existing project.

3. Configure SPI
Mode: SPI1

Prescaler: ≤ 8 MHz

CPOL = 0

CPHA = 0

4. Build & Flash
Compile and upload to your STM32 board.

🧠 How It Works
🔍 Card Detection
The function:

Kod
Read_data_from_rfid()
performs:

MFRC522_Request → check for card

MFRC522_Anticoll → read UID

Compare UID with database

Clear LCD lines

Display card name

📚 Card Database
Defined in:

Kod
table_of_cards.c
Example:

c
Card cards[] = {
    {{119,141,249,216,219}, "Karta pier"},
    {{172,198,79,35,6},     "Pestka pier"}
};
Lookup:

c
find_card(UID);
🖥️ LCD Output Example
Kod
MEMORY OF
CARDS:

Karta pier
Pestka pier
🛠️ Extending the Project
Add more cards → edit table_of_cards.c

Add actions per card → modify Read_data_from_rfid()

Add menu navigation → use GPIO buttons

Add UID display → extend lcd_print_line()

📄 License
MIT License — free to use, modify, and distribute.

🔗 Useful Follow‑ups
add new card

show UID on LCD

add scrolling card list

add buzzer or LED feedback
