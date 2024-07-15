/*
** 16x01 or 16x02 LCD Driver using I2C [Uses 4Bit Mode]
** Author: github.com/xunicatt
** DATASHEET: https://www.sparkfun.com/datasheets/LCD/HD44780.pdf
*/

#ifndef __HAL_LCD_DRIVER_H
#define __HAL_LCD_DRIVER_H

#define STM32XXXX_HAL_HEADER_FILE "" //example "stm32f4xx_hal.h"

#include <stdint.h>
#include STM32XXXX_HAL_HEADER_FILE

#define __LCD_VER_MAJ__ 1
#define __LCD_VER_MIN__ 0
#define __LCD_VER_PATCH__ 0

#ifdef __cplusplus
extern "C" {
#endif

/*
===============================================================================
---------------------------------LCD COMMANDS----------------------------------
===============================================================================
*/

//CORE COMMANDS
typedef enum LCD_Cmd {
    CLEAR = 0x01,
    RETURN_HOME = 0x02,
    ENTRY_MODE_SET = 0x04,
    DISPLAY_CONTROL = 0x08,
    CURSOR_DISPLAY_SHIFT = 0x10,
    FUNCTION_SET = 0x20,
    SET_CGRAM_ADDRS = 0x40,
    SET_DDRAM_ADDRS = 0x80
} LCD_Cmd;

/*ENTRY_MODE_SET ARGUMENTS*/
typedef enum LCD_EntryShift {
    ENTRY_MODE_SET_INCREMENT = 0x02,
    ENTRY_MODE_SET_DECREMENT = 0x00,
    ENTRY_MODE_SET_SHIFT = 0x01
} LCD_EntryShift;

/*DISPLAY_CONTROL ARGUMENTS*/
typedef enum LCD_DisplayControls {
    DISPLAY_CONTROL_DISPLAY_ON = 0x04,
    DISPLAY_CONTROL_DISPLAY_OFF = 0x00,
    DISPLAY_CONTROL_CURSOR_ON = 0x02,
    DISPLAY_CONTROL_CURSOR_OFF = 0x00,
    DISPLAY_CONTROL_CURSOR_BLINK_ON = 0x01,
    DISPLAY_CONTROL_CURSOR_BLINK_OFF = 0x00
} LCD_DisplayControls;

/*REQUIRES CURSOR_DISPLAY_SHIFT*/
typedef enum LCD_CursorDisplayShift {
    CURSOR_DISPLAY_SHIFT_DISPLAY_SHIFT = 0x08,
    CURSOR_DISPLAY_SHIFT_CURSOR_MOVE = 0x00,
    CURSOR_DISPLAY_SHIFT_TO_RIGHT = 0x04,
    CURSOR_DISPLAY_SHIFT_TO_LEFT = 0x00,
} LCD_Move;

/*REQUIRES FUNCTION_SET*/
typedef enum LCD_FunctionSet {
    FUNCTION_SET_MODE_8B = 0x10,
    FUNCTION_SET_MODE_4B = 0x00,
    FUNCTION_SET_LINE_2 = 0x08,
    FUNCTION_SET_LINE_1 = 0x00,
    FUNCTION_SET_DOTS_5x10 = 0x04,
    FUNCTION_SET_DOTS_5x8 = 0x00,
} LCD_Mode;

typedef enum LCD_CoreControl {
    LCD_Backlight_ON = 0x08,
    LCD_Backlight_OFF = 0x00,
    LCD_EN = 0x04,
    LCD_RW = 0x02,
    LCD_RS = 0x01
} LCD_CoreControl;

typedef enum State {
    OFF = 0,
    ON = 1
} State;

typedef enum Direction {
    LEFT = 0,
    RIGHT = 1
} Direction;


/*
===============================================================================
---------------------------------LCD INSTANCE----------------------------------
===============================================================================
*/

typedef struct LCD_InitTypeDef {
    uint16_t Addrs;
    uint8_t Cols;
    uint8_t Rows;
    uint8_t Backlight;
    uint8_t LCD_FuncSet;
    uint8_t LCD_DisplayControl;
    uint8_t LCD_EntryModeSet;
    uint8_t LCD_Cursor_Display_Shift;
    I2C_HandleTypeDef* I2C;
} LCD_InitTypeDef;

/*ADDRS*/
#define DEVICE_ADDRS(x) ((uint16_t)(x) << 1)

/*
===============================================================================
------------------------------DEFINE DEFAULTS----------------------------------
===============================================================================
*/

/*
** CONFIGURATION:> LINE: 1 | FONT: 5x8
 */
#define DEFAULT_FUNCTION_SET_LINE1_5X8 (FUNCTION_SET_MODE_4B | FUNCTION_SET_LINE_1 | FUNCTION_SET_DOTS_5x8)

/*
** CONFIGURATION:> LINE: 1 | FONT: 5x10
 */
#define DEFAULT_FUNCTION_SET_LINE1_5X10 (FUNCTION_SET_MODE_4B | FUNCTION_SET_LINE_1 | FUNCTION_SET_DOTS_5x10)

/*
** CONFIGURATION:> LINE: 2 | FONT: 5x8
 */
#define DEFAULT_FUNCTION_SET_LINE2_5X8 (FUNCTION_SET_MODE_4B | FUNCTION_SET_LINE_2 | FUNCTION_SET_DOTS_5x8)

/*
** CONFIGURATION:> LINE: 2 | FONT: 5x10
 */
#define DEFAULT_FUNCTION_SET_LINE2_5X10 (FUNCTION_SET_MODE_4B | FUNCTION_SET_LINE_2 | FUNCTION_SET_DOTS_5x10)

/*DISPLAY CONTROLS DEFAULTS*/
/*
** CONFIGURATION:> DISPLAY: ON | CURSOR: OFF | CURSOR BLINK: OFF
 */
#define DEFAULT_DISPLAY_CONTROLS_NO_CURSOR_NO_BLINK (DISPLAY_CONTROL_DISPLAY_ON | DISPLAY_CONTROL_CURSOR_OFF | DISPLAY_CONTROL_CURSOR_BLINK_OFF)

/*
** CONFIGURATION:> DISPLAY: ON | CURSOR: ON | CURSOR BLINK: OFF
 */
#define DEFAULT_DISPLAY_CONTROLS_CURSOR_NO_BLINK (DISPLAY_CONTROL_DISPLAY_ON | DISPLAY_CONTROL_CURSOR_ON | DISPLAY_CONTROL_CURSOR_BLINK_OFF)

/*
** CONFIGURATION:> DISPLAY: ON | CURSOR: ON | CURSOR BLINK: ON
 */
#define DEFAULT_DISPLAY_CONTROLS_CURSOR_BLINK (DISPLAY_CONTROL_DISPLAY_ON | DISPLAY_CONTROL_CURSOR_OFF | DISPLAY_CONTROL_CURSOR_BLINK_ON)

/*ENTRY MODE DEFAULTS*/
#define DEFAULT_ENTRY_MODE_SET (ENTRY_MODE_SET_INCREMENT)

/*LCD CURSOR DISPLAY SHIFT DEFAULTS*/
#define DEFAULT_CURSOR_DISPLAY_SHIFT (0x00)


/*
===============================================================================
--------------------------------INIT DEFAULT-----------------------------------
===============================================================================
*/

/**
  * @brief  Intitalizes the LCD_InitTypeDef.
  * @param	row no of rows in display.
  * @param  col no of cols in display.
  * @param  addrs I2C address of the LCD Device. Note: No need to shift the address. It is done automatically.
  * @param  i2c I2C handler
  * @param  FUNCTION_SET_CONF display function set configuration
  * @retval HAL_StatusTypeDef
  */
#define DEFAULT_CONFIGS(row, col, addrs, i2c, FUNCTION_SET_CONF) (LCD_InitTypeDef){ \
    .Addrs = DEVICE_ADDRS((addrs)),\
    .Backlight = LCD_Backlight_ON,\
    .Cols = (col),\
    .I2C = (i2c),\
    .LCD_Cursor_Display_Shift = DEFAULT_CURSOR_DISPLAY_SHIFT,\
    .LCD_DisplayControl = DEFAULT_DISPLAY_CONTROLS_NO_CURSOR_NO_BLINK,\
    .LCD_EntryModeSet = DEFAULT_ENTRY_MODE_SET,\
    .LCD_FuncSet = (FUNCTION_SET_CONF),\
    .Rows = (row)\
}\

/*
===============================================================================
-----------------------------AVAILABLE FUNCTIONS-------------------------------
===============================================================================
*/

/**
  * @brief  Intitalizes the LCD Driver.
  * @param	lcd instance of a LCD driver.
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_LCD_Init(LCD_InitTypeDef* lcd);

/**
  * @brief  Turns ON or OFF the LCD.
  * @param	lcd instance of a LCD driver.
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_LCD_State(LCD_InitTypeDef* lcd, State s);

/**
  * @brief  Clears the LCD.
  * @param	lcd instance of a LCD driver.
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_LCD_Clear(LCD_InitTypeDef* lcd);

/**
  * @brief  Set the cursor to first column and row of the LCD.
  * @param	lcd instance of a LCD driver.
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_LCD_Home(LCD_InitTypeDef* lcd);

/**
  * @brief  Sets cursor to a row and column of the LCD.
  * @param	lcd instance of a LCD driver.
  * @param  col column number
  * @param  row row number
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_LCD_SetCursor(LCD_InitTypeDef* lcd, uint8_t col, uint8_t row);

/**
  * @brief  Turns ON or OFF the LCD Backlight.
  * @param	lcd instance of a LCD driver.
  * @param  s state: ON or OFF
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_LCD_SetBackLight_State(LCD_InitTypeDef* lcd, State s);

/**
  * @brief  Turns ON or OFF the Cursor.
  * @param	lcd instance of a LCD driver.
  * @param  s state: ON or OFF
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_LCD_SetCursor_State(LCD_InitTypeDef* lcd, State s);

/**
  * @brief  Turns ON or OFF the Cursor Blink.
  * @param	lcd instance of a LCD driver.
  * @param  s state: ON or OFF
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_LCD_SetCursorBlink_State(LCD_InitTypeDef* lcd, State s);

/**
  * @brief  Turns ON or OFF the Autoscroll. Note: AutoScroll must be turn on when the display line gets almost full.
  * @param	lcd instance of a LCD driver.
  * @param  s state: ON or OFF
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_LCD_AutoScroll_State(LCD_InitTypeDef* lcd, State s);

/**
  * @brief  Writes a character to LCD.
  * @param	lcd instance of a LCD driver.
  * @param  c character to write
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_LCD_PutChar(LCD_InitTypeDef* lcd, const char c);

/**
  * @brief  Writes a string to LCD.
  * @param	lcd instance of a LCD driver.
  * @param  s string to write
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_LCD_PutStr(LCD_InitTypeDef* lcd, const char* s);

/**
  * @brief  Scrolls the whole display Left or Right.
  * @param	lcd instance of a LCD driver.
  * @param  d direction: LEFT or RIGHT
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_LCD_Scroll(LCD_InitTypeDef* lcd, Direction d);

/**
  * @brief  Sets new character entry direction. Note: The cursor must be set accordingly, so that the cursor can move towards the direction.
  * @param	lcd instance of a LCD driver.
  * @param  d direction: LEFT or RIGHT
  * @retval HAL_StatusTypeDef
  */
HAL_StatusTypeDef HAL_LCD_CharEntry(LCD_InitTypeDef* lcd, Direction d);

#ifdef __cplusplus
}
#endif
#endif
