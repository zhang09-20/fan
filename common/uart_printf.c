/**
 * @file      uart_printf.c
 * @brief     实现printf函数构建
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#include "uart_printf.h"
#include "common.h"
#include "timer.h"
#include "uart.h"

/**
 * @brief UART0初始化配置
 * @note 该串口0用于各模块的打印测试
 * @note 调用printf函数会增加代码量(约2KB)，建议只在调试阶段使用
 *
 */
void uart_config(void)
{
    PORT_SET_MUX(PIO21CFG, UART0_TXD_MUX_MODE); /* P21引脚配置为UART0_TX */

    UART0_SCON_MODE_SET(UART_8BIT_ASY_MODE);    /* 8位异步模式，波特率可变 */
    ENABLE_UART0_SM2;                           /* 1停止位 */
    UART_ConfigBaudRate(UART_0, UART_TIMER1, 115200, ENABLE_DOUBLE_BRT);
    TI  = 0;
    ET4 = 0;
}

/**
 * @brief 调用"stdio.h"库构建printf函数
 *
 * @param c 待发送的数据
 * @return char 串口发送的数据
 */
char putchar(char c)
{
    SBUF = c;
    while (TI == 0)
        ;
    TI = 0;
    return c;
}
