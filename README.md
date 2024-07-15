# LCD Driver [HD47780]
LCD Driver for STM32XXX Microcontrollers to use HD47780 based 16x01 or 16x02 LCD Displays. This library also supports error handling and scrolling of LCD.

>[!IMPORTANT]
Specify the HAL include files in "LCD.h"
+ STM32XXXX_HAL_HEADER_FILE
for your Microcontroller.

>[!IMPORTANT]
Intialize a I2C Handler to connect the LCD Device.

# Reference
## Types
- LCD_InitTypeDef
    + Addrs
    + Cols
    + Rows
    + Backlight
    + LCD_FuncSet
    + LCD_DisplayControl
    + LCD_EntryModeSet
    + LCD_Cursor_Display_Shift
    + I2C

## Functions
+ HAL_LCD_Init
+ HAL_LCD_State
+ HAL_LCD_Clear
+ HAL_LCD_Home
+ HAL_LCD_SetCursor
+ HAL_LCD_SetBacklight_State
+ HAL_LCD_SetCursor_State
+ HAL_LCD_SetCursorBlink_State
+ HAL_LCD_AutoScroll_State
+ HAL_LCD_PutChar
+ HAL_LCD_PutStr
+ HAL_LCD_Scroll
+ HAL_LCD_CharEntry

# Installation
Copy the "/Inc" & "/Src" directory into your STM32 project.

# Documentation
## Configuration Macros
+ FUNCTION_SET
    - DEFAULT_FUNCTION_SET_LINE1_5X8: Line=1, Font=5x8
    - DEFAULT_FUNCTION_SET_LINE1_5X10: Line=1, Font=5x10
    - DEFAULT_FUNCTION_SET_LINE2_5X8: Line=2, Font=5x8
    - DEFAULT_FUNCTION_SET_LINE2_5X10: Line=2, Font=5x10

+ DISPLAY_CONTROLS
    - DEFAULT_DISPLAY_CONTROLS_NO_CURSOR_NO_BLINK: Display=ON, Cursor=OFF, Blink=OFF
    - DEFAULT_DISPLAY_CONTROLS_CURSOR_NO_BLINK: Display=ON, Cursor=ON, Blink=OFF
    - DEFAULT_DISPLAY_CONTROLS_CURSOR_BLINK: Display=ON, Cursor=ON, Blink=ON

+ ENTRY_MODE_SET
    - DEFAULT_ENTRY_MODE_SET: Cursor=Increment

+ CURSOR_DISPLAY_SHIFT
    - DEFAULT_CURSOR_DISPLAY_SHIFT: Default

+ DEFAULT_CONFIGS: Display=ON, Cursor=OFF, Blink=OFF, Cursor=Increment
    - Arguments:
        - `Row` number of rows
        - `Cols` number of columns
        - `DevAddrs` i2c device address
        - `I2C` instace of a i2c handler
        - `FUNCTION_SET` config for the function set

+ DEVICE_ADDRS
    - Arguments:
        - `DevAddrs` i2c device address

    - Returns:
        - `DevAddrs` 1Bit left shifted device address

## Initialization
Use function `HAL_LCD_Init` to Initialize the Driver.

### HAL_LCD_Init
Intitalizes the DHT11 Driver.

- Arguments: 
    + `LCD` instance of a LCD driver.

- Returns:
    + HAL_StatusTypeDef

## Core Commands
### HAL_LCD_Clear
Clears the LCD.

- Arguments:
    + `LCD` instance of a LCD driver.

- Returns:
    + HAL_StatusTypeDef

### HAL_LCD_Home
Set the cursor to first column and row of the LCD.

- Arguments:
    + `LCD` instance of a LCD driver.

- Returns:
    + HAL_StatusTypeDef

### HAL_LCD_SetCursor
Sets cursor to a row and column of the LCD.

- Arguments:
    + `LCD` instance of a LCD driver.
    + `Col` column number
    + `Row` row number

- Returns:
    + HAL_StatusTypeDef

### HAL_LCD_Scroll
Scrolls the whole display Left or Right.

- Arguments:
    + `LCD` instance of a LCD driver.
    + `Direction` LEFT or RIGHT

- Returns:
    + HAL_StatusTypeDef

### HAL_LCD_CharEntry
Sets new character entry direction.

- Arguments:
    + `LCD` instance of a LCD driver.
    + `Direction` LEFT or RIGHT

- Returns:
    + HAL_StatusTypeDef

## Writing to LCD
### HAL_LCD_PutChar
Writes a character to LCD.

- Arguments:
    + `LCD` instance of a LCD driver.
    + `Character` character to write

- Returns:
    + HAL_StatusTypeDef

### HAL_LCD_PutStr
Writes a string to LCD.

- Arguments:
    + `LCD` instance of a LCD driver.
    + `String` string to write

- Returns:
    + HAL_StatusTypeDef

## Changing States of the LCD
### HAL_LCD_State
Turns ON or OFF the LCD.

- Arguments:
    + `LCD` instance of a LCD driver.
    + `State` ON of OFF.

- Returns:
    + HAL_StatusTypeDef

### HAL_LCD_SetBackLight_State
Turns ON or OFF the LCD Backlight.

- Arguments:
    + `LCD` instance of a LCD driver.
    + `State` ON of OFF.

- Returns:
    + HAL_StatusTypeDef

### HAL_LCD_SetCursor_State
Turns ON or OFF the Cursor.

- Arguments:
    + `LCD` instance of a LCD driver.
    + `State` ON of OFF.

- Returns:
    + HAL_StatusTypeDef

### HAL_LCD_SetCursorBlink_State
Turns ON or OFF the Cursor Blink.

- Arguments:
    + `LCD` instance of a LCD driver.
    + `State` ON of OFF.

- Returns:
    + HAL_StatusTypeDef

### HAL_LCD_AutoScroll_State
Turns ON or OFF the Autoscroll.

- Arguments:
    + `LCD` instance of a LCD driver.
    + `State` ON of OFF.

- Returns:
    + HAL_StatusTypeDef

# Version
>v1.0.0
