#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "LCD.h"

/*IMPORTANT: I2C*/
I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef hlpuart1;
TIM_HandleTypeDef htim1;

/*Microcontroller specific functions*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM1_Init(void);
static void MX_LPUART1_UART_Init(void);

int main(void) {
	HAL_Init();
	SystemClock_Config();
    MX_GPIO_Init();

    /*INITIALIZING THE I2C*/
    MX_I2C1_Init();
    
    MX_TIM1_Init();
    MX_LPUART1_UART_Init()

    LCD_InitTypeDef lcd = DEFAULT_CONFIGS(2, 16, 0x27, &hi2c1, DEFAULT_FUNCTION_SET_LINE2_5X8);
    HAL_LCD_Init(&lcd);
    HAL_LCD_Clear(&lcd);
    HAL_LCD_Home(&lcd);

    HAL_LCD_PutStr(&lcd, "Hello, World!");
    HAL_LCD_SetCursor(&lcd, 0, 1);
    HAL_LCD_PutStr(&lcd, "from LCD Driver!");

	while(1) {}
    return 0;
}