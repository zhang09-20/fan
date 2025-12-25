/**
 * @file      uart.h
 * @brief     UART驱动配置
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#ifndef __UART_H__
#define __UART_H__

#include "WY8S9003xx.h"

#define UART_0 (0)
#define UART_1 (1)

/**@name UART控制寄存器-SCON、SCON_1
 * @{
 */
#define UART_SCON_SM01_POS  (6)
#define UART_SCON_SM01_MSK  (0x3 << UART_SCON_SM01_POS)

#define UART_8BIT_SYN_MODE  (0x00) /*!< 8位主控同步模式，CLK_P/2 */
#define UART_8BIT_ASY_MODE  (0x01) /*!< 8位异步模式，波特率可变 */
#define UART_9BIT_ASY_SMODE (0x02) /*!< 9位异步模式，波特率为CLK_P/32或者CLK_P/64 */
#define UART_9BIT_ASY_CMODE (0x03) /*!< 9位异步模式，波特率可变 */
/**
 * UART0模式选择位
 * @param[in] mode
 * -# UART_8BIT_SYN_MODE:  8位主控同步模式，CLK_P/2
 * -# UART_8BIT_ASY_MODE:  8位异步模式，波特率可变
 * -# UART_9BIT_ASY_SMODE: 9位异步模式，波特率为CLK_P/32或者CLK_P/64
 * -# UART_9BIT_ASY_CMODE: 9位异步模式，波特率可变
 */
#define UART0_SCON_MODE_SET(mode) (SCON = ((SCON & (~UART_SCON_SM01_MSK)) | ((mode) << UART_SCON_SM01_POS)))

#define ENABLE_UART0_SM2          (SM2 = 1) /*!< UART0多机通信模式使能 */
#define DISABLE_UART0_SM2         (SM2 = 0) /*!< UART0多机通信模式禁止 */

#define ENABLE_UART0_REN          (REN = 1) /*!< UART0接收使能 */
#define DISABLE_UART0_REN         (REN = 0) /*!< UART0接收禁止 */

/**
 * UART0发送中断标志位
 * @return 1: 完成发送一个byte，必须软件清零\n
 *         0: 正在发送一个byte或者未发送数据
 */
#define IS_UART0_TI_FLAG  (TI)
#define CLR_UART0_TI_FLAG (TI = 0) /*!< 清除接收中断标志位 */

/**
 * UART0接收中断标志位
 * @return 1: 完成接收一个byte，必须软件清零\n
 *         0: 正在接收一个byte或者未接收数据
 */
#define IS_UART0_RI_FLAG  (RI)
#define CLR_UART0_RI_FLAG (RI = 0) /*!< 清除发送中断标志位 */
/**
 * UART1模式选择位
 * @param[in] mode
 * -# UART_8BIT_SYN_MODE: 8位主控同步模式，CLK_P/2
 * -# UART_8BIT_ASY_MODE:  8位异步模式，波特率可变
 * -# UART_9BIT_ASY_SMODE: 9位异步模式，波特率为CLK_P/32或者CLK_P/64
 * -# UART_9BIT_ASY_CMODE: 9位异步模式，波特率可变
 */
#define UART1_SCON_MODE_SET(mode) (SCON_1 = ((SCON_1 & (~UART_SCON_SM01_MSK)) | ((mode) << UART_SCON_SM01_POS)))

#define ENABLE_UART1_SM2          (SM2_1 = 1) /*!< UART1多机通信模式使能 */
#define DISABLE_UART1_SM2         (SM2_1 = 0) /*!< UART1多机通信模式禁止 */

#define ENABLE_UART1_REN          (REN_1 = 1) /*!< UART1接收使能 */
#define DISABLE_UART1_REN         (REN_1 = 0) /*!< UART1接收禁止 */

/**
 * UART1接收中断标志位
 * @return 1: 完成接收一个byte，必须软件清零\n
 *         0: 正在接收一个byte或者未接收数据
 */
#define IS_UART1_RI_FLAG  (RI_1)
#define CLR_UART1_RI_FLAG (RI_1 = 0) /*!< 清除接收中断标志位 */
/**
 * UART1发送中断标志位
 * @return 1: 完成发送一个byte，必须软件清零\n
 *         0: 正在发送一个byte或者未发送数据
 */
#define IS_UART1_TI_FLAG  (TI_1)
#define CLR_UART1_TI_FLAG (TI_1 = 0) /*!< 清除发送中断标志位 */
/**@} */

/**@name UART0/1波特率选择寄存器-SCKS
 * @{
 */
#define UART_SCKS_SMOD1_POS (7)
#define UART_SCKS_SMOD1_MSK (0x1 << UART_SCKS_SMOD1_POS)
#define UART_SCKS_SCKS1_POS (6)
#define UART_SCKS_SCKS1_MSK (0x1 << UART_SCKS_SCKS1_POS)
#define UART_SCKS_SCKS0_POS (5)
#define UART_SCKS_SCKS0_MSK (0x1 << UART_SCKS_SCKS0_POS)

#define ENABLE_UART1_SMOD   (SCKS |= UART_SCKS_SMOD1_MSK)  /*!< UART1波特率加倍使能 */
#define DISABLE_UART1_SMOD  (SCKS &= ~UART_SCKS_SMOD1_MSK) /*!< UART1波特率加倍不使能 */

#define UART_TIMER3         (0)
#define UART_TIMER1         (1)
/**
 * UART1波特率时钟源选择位
 * @param[in] status
 * -# UART_TIMER1: 波特率时钟源TIMER1
 * -# UART_TIMER3: 波特率时钟源TIMER3
 */
#define UART1_SCKS_SET(status) (SCKS = ((SCKS & (~UART_SCKS_SCKS1_MSK)) | ((status) << UART_SCKS_SCKS1_POS)))

/**
 * UART0波特率时钟源选择位
 * @param[in] status
 * -# UART_TIMER1: 波特率时钟源TIMER1
 * -# UART_TIMER3: 波特率时钟源TIMER3
 */
#define UART0_SCKS_SET(status) (SCKS = ((SCKS & (~UART_SCKS_SCKS0_MSK)) | ((status) << UART_SCKS_SCKS0_POS)))
/**@} */

/**@name UART0波特率加倍使能配置
 * @{
 */
#define POWER_PCON_SMOD0_POS (7)
#define POWER_PCON_SMOD0_MSK (0x1 << POWER_PCON_SMOD0_POS)

#define ENABLE_UART0_SMOD    (PCON |= POWER_PCON_SMOD0_MSK)  /*!< UART0波特率加倍使能 */
#define DISABLE_UART0_SMOD   (PCON &= ~POWER_PCON_SMOD0_MSK) /*!< UART0波特率加倍不使能 */
/**@} */
#define ENABLE_DOUBLE_BRT  (1) /*!< UART波特率加倍使能选择 */
#define DISABLE_DOUBLE_BRT (0) /*!< UART波特率加倍不使能选择 */

/**
 * UART0 SBUF写入数据
 * @param[in] u8data 写入的数据
 */
#define UART0_WRITE_SBUF(u8data) (SBUF = (u8data))
/**
 * UART0 SBUF读出数据
 * @return SBUF 读出的数据
 */
#define UART0_READ_SBUF (SBUF)
/**
 * UART1 SBUF_1写入数据
 * @param[in] u8data 写入的数据
 */
#define UART1_WRITE_SBUF(u8data) (SBUF_1 = (u8data))
/**
 * UART1 SBUF_1读出数据
 * @return SBUF_1 读出的数据
 */
#define UART1_READ_SBUF (SBUF_1)

/**
 * UART0 TB8写入数据
 * @param[in] bdata 写入的数据(宽度为1bit)
 */
#define UART0_WRITE_TB8(bdata) (TB8 = (bdata))
/**
 * UART0 RB8读出数据
 * @return RB8 读出的数据(宽度为1bit)
 */
#define UART0_READ_RB8 (RB8)
/**
 * UART1 TB8_1写入数据
 * @param[in] bdata 写入的数据(宽度为1bit)
 */
#define UART1_WRITE_TB8(bdata) (TB8_1 = (bdata))
/**
 * UART1 RB8_1读出数据
 * @return RB8_1 读出的数据(宽度为1bit)
 */
#define UART1_READ_RB8 (RB8_1)

/**@name 外部函数
 * @{
 */
void UART_ConfigBaudRate(uint8_t u8UartNum, uint8_t u8Timer, uint32_t u32BaudRate, uint8_t u8Double);
/**@} */

#endif /* __UART_H__ */
