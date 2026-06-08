# 📘 Waveshare-13892 RFID Driver

![License](https://img.shields.io/github/license/DawidWawrzeniuk/Waveshare-13892_rfid_driver)
![Stars](https://img.shields.io/github/stars/DawidWawrzeniuk/Waveshare-13892_rfid_driver)

Driver and example firmware for the **MFRC522 RFID module (Waveshare 13892)** paired with an **ST7735 LCD display** on **STM32**.

This repository contains a complete, lightweight driver written for STM32 microcontrollers using the **HAL library**. It features an integrated card database lookup system and real-time LCD visual feedback.

---

## 📦 Features

* **MFRC522 Communication:** Native SPI implementation.
* **Anti-collision Handling:** Accurate UID reading for overlapping targets.
* **Card Database Lookup:** Local storage and indexing of authorized badges.
* **LCD Display Support:** Built-in driver for ST7735 / Waveshare LCD.
* **Automatic Screen Management:** Smart line clearing and formatting.
* **Debounced Detection:** Built-in timeout (1s) to prevent continuous card polling spam.
* **Modular Architecture:** Clean separation between hardware abstraction and application logic.

---

## 🧩 Project Structure



```text
Core/
 ├── Inc/
 │    ├── lcd.h              - Low-level LCD driver & color configs
 │    ├── lcd_text.h         - Font rendering logic & character mapping
 │    ├── lcd_run.h          - Higher-level display macros & layout states
 │    ├── RC522.h            - MFRC522 register map & command protocols
 │    └── table_of_cards.h   - Database structures & definitions
 └── Src/
      ├── lcd.c
      ├── lcd_text.c
      ├── lcd_run.c
      ├── RC522.c
      ├── table_of_cards.c   - Local database instances & hardcoded lookups
      └── main.c             - Application loop & initialization routines
```


## ⚙️ Hardware Requirements
* Microcontroller: STM32F303 (or any STM32 device with SPI peripherals)

* RFID Module: Waveshare 13892 RFID Kit (MFRC522)

* Display: ST7735 / Waveshare LCD display

* Interface: SPI + dedicated GPIO pins


## MFRC522 ➔ STM32 Wiring Reference
* SDA / NSS ➔ GPIO Output (e.g., PA4) [Chip Select]

* SCK ➔ SPI SCK (e.g., PA5) [Serial Clock]

* MOSI ➔ SPI MOSI (e.g., PA7) [Master Out Slave In]

* MISO ➔ SPI MISO (e.g., PA6) [Master In Slave Out]

* RST ➔ GPIO Output (e.g., PA9) [Hardware Reset]

* 3.3V ➔ 3.3V Power Supply

* GND ➔ GND Ground Reference






##🧠 How It Works
🔍 Card Detection Pipeline
The core application flow runs through Read_data_from_rfid(), performing the following operations sequentially:

MFRC522_Request: Checks if any RFID card/tag is present in the induction field.

MFRC522_Anticoll: Reads the unique identifier (UID) of the card.

find_card: Queries the internal database array using the fetched UID.

Clear LCD Lines: Prepares the ST7735 screen layout by wiping specific text areas.

Print Text: Renders the assigned cardholder name or status onto the display.

📚 Card Database Definition
The localized card matrix is mapped directly within table_of_cards.c:


```text
Card cards[] = {
    {{119, 141, 249, 216, 219}, "Karta pier"},
    {{172, 198, 79, 35, 6},     "Pestka pier"}
};

```

