/**
 * @file      uart.c
 * @brief     串口模块驱动
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#include "uart.h"
#include "common.h"
#include "timer.h"

/**
 * 串口波特率配置
 * @param[in] u8UartNum  串口号
 * -# UART_0
 * -# UART_1
 * @param[in] u8Timer 定时器选择
 * -# UART_TIMER1
 * -# UART_TIMER3
 * @param[in] u32BaudRate 串口波特率
 * @param[in] u8Double 波特率加倍是否开启
 * -# ENABLE_DOUBLE_BRT   开启加倍使能
 * -# DISABLE_DOUBLE_BRT  不开启加倍使能
 */
void UART_ConfigBaudRate(uint8_t u8UartNum, uint8_t u8Timer, uint32_t u32BaudRate, uint8_t u8Double)
{
    uint16_t u16Timer3PS;
    uint8_t  u8UartDouble; /* UART加倍使能变量 */

    if (u8Double == DISABLE_DOUBLE_BRT) {
        if (UART_0 == u8UartNum) {
            DISABLE_UART0_SMOD; /* UART0不开启加倍使能 */
        } else {
            DISABLE_UART1_SMOD; /* UART1不开启加倍使能 */
        }
        u8UartDouble = 0;
    } else {
        if (UART_0 == u8UartNum) {
            ENABLE_UART0_SMOD; /* UART0开启加倍使能 */
        } else {
            ENABLE_UART1_SMOD; /* UART1开启加倍使能 */
        }
        u8UartDouble = 1;
    }

    switch (u8Timer) {
    case UART_TIMER1:
        if (UART_0 == u8UartNum) {
            UART0_SCKS_SET(UART_TIMER1);                                              /* 串口0选择TIMER1为时钟源 */
        } else {
            UART1_SCKS_SET(UART_TIMER1);                                              /* 串口1选择TIMER1为时钟源 */
        }
        TIMER1_TMOD_CNT1_SET(CLR_BIT);                                                /* 选择的驱动时钟从内部时钟输入 */
        TIMER1_TMOD_GATE1_SET(CLR_BIT);                                               /* 当TCON.TR1位为1时，开始计数 */
        TIMER1_TMOD_MODE_SET(TIMER01_MODE2);                                          /* 8位自动重装定时/计数器 */
        TH1 = 256 - ((1 + u8UartDouble) * g_u32SystemClock) / (32 * 2 * u32BaudRate); /* 波特率配置 */
        ENABLE_TIMER1;                                                                /* TIMER1启动 */
        break;
    case UART_TIMER3:
        if (UART_0 == u8UartNum) {
            UART0_SCKS_SET(UART_TIMER3);           /* 串口0选择TIMER3为时钟源 */
        } else {
            UART1_SCKS_SET(UART_TIMER3);           /* 串口1选择TIMER3为时钟源 */
        }
        TIMER3_T3CON_DIV_SET(UART_TIMER3_DIV_SLE); /* TIMER3分频选择 */
        u16Timer3PS = 65536 - ((1 + u8UartDouble) * g_u32SystemClock) / (32 * (1 << UART_TIMER3_DIV_SLE) * u32BaudRate);
        T3RH        = (u16Timer3PS >> 8) & 0xFF;
        T3RL        = (u16Timer3PS >> 0) & 0xFF;
        ENABLE_TIMER3; /* TIMER3启动 */
        break;
    default:
        break;
    }
}
