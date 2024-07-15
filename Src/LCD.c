#include <stdint.h>
#include <string.h>
#include "LCD.h"

#define CHECK_HAL_ERROR(x) do {\
                                HAL_StatusTypeDef err = (x);\
                                if(err != HAL_OK) return err; \
                            } while(0)\

static HAL_StatusTypeDef LCD_SendCmd(LCD_InitTypeDef*, uint8_t);
static HAL_StatusTypeDef LCD_SendData(LCD_InitTypeDef*, uint8_t);

HAL_StatusTypeDef HAL_LCD_Init(LCD_InitTypeDef* lcd) {
    HAL_Delay(60); // wait for > (15ms + 40ms)
    CHECK_HAL_ERROR(LCD_SendCmd(lcd, FUNCTION_SET | FUNCTION_SET_MODE_8B));
    HAL_Delay(5); //wait for > 4.1ms
    CHECK_HAL_ERROR(LCD_SendCmd(lcd, FUNCTION_SET | FUNCTION_SET_MODE_8B));
    HAL_Delay(1); //wait for > 100us
    CHECK_HAL_ERROR(LCD_SendCmd(lcd, FUNCTION_SET | FUNCTION_SET_MODE_8B));
    HAL_Delay(5); //waiting for > 4.1ms

    CHECK_HAL_ERROR(LCD_SendCmd(lcd, FUNCTION_SET | FUNCTION_SET_MODE_4B));
    HAL_Delay(10); //switching to 4Bit mode

    //intiializing functions
    CHECK_HAL_ERROR(LCD_SendCmd(lcd, FUNCTION_SET | lcd->LCD_FuncSet));
    HAL_Delay(1);

    //display, cursor and blink off
    CHECK_HAL_ERROR(LCD_SendCmd(lcd, DISPLAY_CONTROL));
    HAL_Delay(1);

    //clearing display
    CHECK_HAL_ERROR(LCD_SendCmd(lcd, CLEAR));
    HAL_Delay(2); //~2000us

    //intializing entry mode
    CHECK_HAL_ERROR(LCD_SendCmd(lcd, ENTRY_MODE_SET | lcd->LCD_EntryModeSet));
    HAL_Delay(1);

    //initializing display controls
    CHECK_HAL_ERROR(LCD_SendCmd(lcd, DISPLAY_CONTROL | lcd->LCD_DisplayControl));
    HAL_Delay(1);

    //initializing display data ram
    CHECK_HAL_ERROR(LCD_SendCmd(lcd, SET_DDRAM_ADDRS | 0x00));
    HAL_Delay(1);
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LCD_State(LCD_InitTypeDef* lcd, State s) {
    if(s == OFF) {
        lcd->LCD_DisplayControl &= ~DISPLAY_CONTROL_DISPLAY_ON;
        return LCD_SendCmd(lcd, DISPLAY_CONTROL | lcd->LCD_DisplayControl);
    }

    lcd->LCD_DisplayControl |= DISPLAY_CONTROL_DISPLAY_ON;
    return LCD_SendCmd(lcd, DISPLAY_CONTROL | lcd->LCD_DisplayControl);
}

HAL_StatusTypeDef HAL_LCD_Clear(LCD_InitTypeDef* lcd) {
    HAL_StatusTypeDef err = LCD_SendCmd(lcd, CLEAR);
    HAL_Delay(2);
    return err;
}

HAL_StatusTypeDef HAL_LCD_Home(LCD_InitTypeDef* lcd) {
    HAL_StatusTypeDef err = LCD_SendCmd(lcd, RETURN_HOME);
    HAL_Delay(1);
    return err;
}

HAL_StatusTypeDef HAL_LCD_SetCursor(LCD_InitTypeDef* lcd, uint8_t col, uint8_t row) {
    if(row > 1 || row > lcd->Rows ) return HAL_ERROR;
    if(col > lcd->Cols) return ERROR;

    uint8_t ram_addrs[] = {0x00, 0x40};
    return LCD_SendCmd(lcd, SET_DDRAM_ADDRS | (ram_addrs[row] + col));
}

HAL_StatusTypeDef HAL_LCD_SetBackLight_State(LCD_InitTypeDef* lcd, State s) {
    if(s == ON) {
        lcd->Backlight |= LCD_Backlight_ON;
        return LCD_SendCmd(lcd, lcd->LCD_DisplayControl);
    }

    lcd->Backlight &= LCD_Backlight_OFF;
    return LCD_SendCmd(lcd, lcd->LCD_DisplayControl);
}

HAL_StatusTypeDef HAL_LCD_SetCursor_State(LCD_InitTypeDef* lcd, State s) {
    if(s == ON) {
        lcd->LCD_DisplayControl |= DISPLAY_CONTROL_CURSOR_ON;
        return LCD_SendCmd(lcd, DISPLAY_CONTROL | lcd->LCD_DisplayControl);
    }

    lcd->LCD_DisplayControl &= ~DISPLAY_CONTROL_CURSOR_ON;
    return LCD_SendCmd(lcd, DISPLAY_CONTROL | lcd->LCD_DisplayControl);
}

HAL_StatusTypeDef HAL_LCD_SetCursorBlink_State(LCD_InitTypeDef* lcd, State s) {
    if(s == ON) {
        lcd->LCD_DisplayControl |= DISPLAY_CONTROL_CURSOR_BLINK_ON;
        return LCD_SendCmd(lcd, DISPLAY_CONTROL | lcd->LCD_DisplayControl);
    }

    lcd->LCD_DisplayControl &= ~DISPLAY_CONTROL_CURSOR_BLINK_ON;
    return LCD_SendCmd(lcd, DISPLAY_CONTROL | lcd->LCD_DisplayControl);
}

HAL_StatusTypeDef HAL_LCD_AutoScroll_State(LCD_InitTypeDef* lcd, State s) {
    if(s == ON) {
        lcd->LCD_EntryModeSet |= ENTRY_MODE_SET_SHIFT;
        return LCD_SendCmd(lcd, ENTRY_MODE_SET | lcd->LCD_EntryModeSet);
    }

    lcd->LCD_EntryModeSet &= ~ENTRY_MODE_SET_SHIFT;
    return LCD_SendCmd(lcd, ENTRY_MODE_SET | lcd->LCD_EntryModeSet);
}

HAL_StatusTypeDef HAL_LCD_PutChar(LCD_InitTypeDef* lcd, const char c) {    
    CHECK_HAL_ERROR(LCD_SendData(lcd, (uint8_t)c));
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LCD_PutStr(LCD_InitTypeDef* lcd, const char* s) {
    while(*s) {
        CHECK_HAL_ERROR(LCD_SendData(lcd, (uint8_t)*s++));        
    }

    return HAL_OK;
}

HAL_StatusTypeDef HAL_LCD_Scroll(LCD_InitTypeDef* lcd, Direction d) {
    if(d == RIGHT) {
        lcd->LCD_Cursor_Display_Shift |= (CURSOR_DISPLAY_SHIFT_DISPLAY_SHIFT | CURSOR_DISPLAY_SHIFT_TO_RIGHT);
        return LCD_SendCmd(lcd, CURSOR_DISPLAY_SHIFT | lcd->LCD_Cursor_Display_Shift);
    }

    lcd->LCD_Cursor_Display_Shift |= CURSOR_DISPLAY_SHIFT_DISPLAY_SHIFT;
    lcd->LCD_Cursor_Display_Shift &= ~CURSOR_DISPLAY_SHIFT_TO_RIGHT;
    return LCD_SendCmd(lcd, CURSOR_DISPLAY_SHIFT | lcd->LCD_Cursor_Display_Shift);
}

HAL_StatusTypeDef HAL_LCD_CharEntry(LCD_InitTypeDef* lcd, Direction d) {
    if(d == RIGHT) {
        lcd->LCD_EntryModeSet |= ENTRY_MODE_SET_INCREMENT;
        return LCD_SendCmd(lcd, ENTRY_MODE_SET | lcd->LCD_EntryModeSet);
    }

    lcd->LCD_EntryModeSet &= ~ENTRY_MODE_SET_INCREMENT;
    return LCD_SendCmd(lcd, ENTRY_MODE_SET | lcd->LCD_EntryModeSet);
}

HAL_StatusTypeDef LCD_SendCmd(LCD_InitTypeDef *lcd, uint8_t data) {
    uint8_t low = (data << 4) & 0xf0;
    uint8_t high = (data) & 0xf0;
    uint8_t tdata[4] = {
        high | LCD_EN ,
        high | lcd->Backlight,
        low  | LCD_EN,
        low  | lcd->Backlight
    };

    return HAL_I2C_Master_Transmit(lcd->I2C, lcd->Addrs, tdata, sizeof(tdata), 100);
}

HAL_StatusTypeDef LCD_SendData(LCD_InitTypeDef *lcd, uint8_t data) {
    uint8_t low = (data << 4) & 0xf0;
    uint8_t high = (data) & 0xf0;
    uint8_t tdata[4] = {
        high | LCD_EN | LCD_RS,
        high | lcd->Backlight | LCD_RS,
        low  | LCD_EN | LCD_RS,
        low  | lcd->Backlight | LCD_RS
    };

    return HAL_I2C_Master_Transmit(lcd->I2C, lcd->Addrs, tdata, sizeof(tdata), 100);
}
