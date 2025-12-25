/**
 * @file      acmp.h
 * @brief     ACMP驱动配置
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#ifndef __ACMP_H__
#define __ACMP_H__

#include "WY8S9003xx.h"
#include "common.h"

/**@name ACMP0正端输入通道对应的PORT管脚
 * @{
 */
#define ACMP0_PIN0_PORT (PIO15CFG)
#define ACMP0_PIN1_PORT (PIO07CFG)
#define ACMP0_PIN2_PORT (PIO12CFG)
#define ACMP0_PIN3_PORT (PIO06CFG)
/**@} */

/**@name ACMP0负端输入通道对应的PORT管脚
 * @{
 */
#define ACMP0_NIN0_PORT (PIO05CFG)
#define ACMP0_NIN1_PORT (PIO04CFG)
/**@} */

/**@name ACMP1正端输入通道对应的PORT管脚
 * @{
 */
#define ACMP1_PIN0_PORT (PIO02CFG)
#define ACMP1_PIN1_PORT (PIO13CFG)
#define ACMP1_PIN2_PORT (PIO14CFG)
#define ACMP1_PIN3_PORT (PIO16CFG)
/**@} */

/**@name ACMP1负端输入通道对应的PORT管脚
 * @{
 */
#define ACMP1_NIN0_PORT (PIO03CFG)
#define ACMP1_NIN1_PORT (PIO25CFG)
/**@} */

/**@name ACMP0控制寄存器ACMP0CON0
 * @{
 */

#define ACMP_ACMP0CON0_COIF_Pos       (7)
#define ACMP_ACMP0CON0_COIF_Msk       (0x1 << ACMP_ACMP0CON0_COIF_Pos)

#define ACMP_ACMP0CON0_COEN_Pos       (6)
#define ACMP_ACMP0CON0_COEN_Msk       (0x1 << ACMP_ACMP0CON0_COEN_Pos)

#define ACMP_ACMP0CON0_CONS_Pos       (4)
#define ACMP_ACMP0CON0_CONS_Msk       (0x3 << ACMP_ACMP0CON0_CONS_Pos)

#define ACMP_ACMP0CON0_COPS_Pos       (2)
#define ACMP_ACMP0CON0_COPS_Msk       (0x3 << ACMP_ACMP0CON0_COPS_Pos)

#define ACMP_ACMP0CON0_C0POLARITY_Pos (1)
#define ACMP_ACMP0CON0_C0POLARITY_Msk (0x1 << ACMP_ACMP0CON0_C0POLARITY_Pos)

#define ACMP_ACMP0CON0_C0OUT_Pos      (0)
#define ACMP_ACMP0CON0_C0OUT_Msk      (0x1 << ACMP_ACMP0CON0_C0OUT_Pos)

/**
 * ACMP中断标志位
 * @note 软件需要写0清除该位。
 */
#define CLR_ACMP0_IF_FLAG (ACMP0CON0 &= ~ACMP_ACMP0CON0_COIF_Msk)

#define ENABLE_ACMP0      (ACMP0CON0 |= ACMP_ACMP0CON0_COEN_Msk)
#define DISABLE_ACMP0     (ACMP0CON0 &= ~ACMP_ACMP0CON0_COEN_Msk)

#define ACMP0_INN0        (0x00)
#define ACMP0_INN1        (0x01)
#define ACMP0_VDIV        (0x03)

/**
 * ACMP负端输入信号选择位
 * @param[in] status:
 * -# ACMP0_INN0:选择ACMP0INN0作为输入
 * -# ACMP0_INN1:选择ACMP0INN1作为输入
 * -# ACMP0_VDIV:选择分压输出VDIV作为输入
 */

#define ACMP_ACMP0CON0_CONS_SEL(mode)                                                                                  \
    (ACMP0CON0 = ((ACMP0CON0 & (~ACMP_ACMP0CON0_CONS_Msk))) | ((mode) << ACMP_ACMP0CON0_CONS_Pos))

#define ACMP0_INP0 (0x00)
#define ACMP0_INP1 (0x01)
#define ACMP0_INP2 (0x02)
#define ACMP0_INP3 (0x03)

/**
 * ACMP0正端输入信号选择位
 * @param[in] status:
 * -# ACMP0_INP0:选择ACMP0INP0作为输入
 * -# ACMP0_INP1:选择ACMP0INP1作为输入
 * -# ACMP0_INP2:选择ACMP0INP2作为输入・
 * -# ACMP0_INP3:选择ACMP0INP3作为输入
 */

#define ACMP_ACMP0CON0_COPS_SEL(mode)                                                                                  \
    (ACMP0CON0 = ((ACMP0CON0 & (~ACMP_ACMP0CON0_COPS_Msk))) | ((mode) << ACMP_ACMP0CON0_COPS_Pos))

/**
 * ACMP0输出极性选择位。
 */
#define ACMP0_POLARITY_NORMAL  (ACMP0CON0 &= (~ACMP_ACMP0CON0_C0POLARITY_Msk)) /* 直接输出 */
#define ACMP0_POLARITY_REVERSE (ACMP0CON0 |= (ACMP_ACMP0CON0_C0POLARITY_Msk))  /* 反相输出 */

#define ACMP0_READ_OUT         (ACMP0CON0 & (ACMP_ACMP0CON0_C0OUT_Msk) >> ACMP_ACMP0CON0_C0OUT_Pos)

/**@name ACMP0控制寄存器ACMP0CON1
 * @{
 */
#define ACMP0_ACMP0CON1_C0PROG_Pos     (0)
#define ACMP0_ACMP0CON1_C0PROG_Msk     (0x03 << ACMP0_ACMP0CON1_C0PROG_Pos)

#define ACMP0_ACMP0CON1_C0PNS_Pos      (2)
#define ACMP0_ACMP0CON1_C0PNS_Msk      (0x03 << ACMP0_ACMP0CON1_C0PNS_Pos)

#define ACMP0_ACMP0CON1_C0FILTTIME_Pos (4)
#define ACMP0_ACMP0CON1_C0FILTTIME_Msk (0x07 << ACMP0_ACMP0CON1_C0FILTTIME_Pos)

#define ACMP0_ACMP0CON1_C0FILTEN_Pos   (7)
#define ACMP0_ACMP0CON1_C0FILTEN_Msk   (0x01 << ACMP0_ACMP0CON1_C0FILTEN_Pos)

/**
 * ACMP0输迟滞电压
 */
#define ACMP0_HYS_VOLT0MV  (0)
#define ACMP0_HYS_VOLT20MV (1)
#define ACMP0_HYS_VOLT10MV (2)
#define ACMP0_HYS_VOLT60MV (3)

/**
 * ACMP0输迟滞控制
 */
#define ACMP0_HYSCTL_CLOSE (0)
#define ACMP0_HYSCTL_P     (1)
#define ACMP0_HYSCTL_N     (2)
#define ACMP0_HYSCTL_BOUTH (3)

/**
 * ACMP0滤波长度
 */
#define ACMP0_NFCLK_2_TSYS   (0)
#define ACMP0_NFCLK_4_TSYS   (1)
#define ACMP0_NFCLK_8_TSYS   (2)
#define ACMP0_NFCLK_16_TSYS  (3)
#define ACMP0_NFCLK_32_TSYS  (4)
#define ACMP0_NFCLK_64_TSYS  (5)
#define ACMP0_NFCLK_128_TSYS (6)

#define ENABLE_ACMP0_FILT    (ACMP0CON1 |= ACMP0_ACMP0CON1_C0FILTEN_Msk)
#define DISABLE_ACMP0_FILT   (ACMP0CON1 &= ~ACMP0_ACMP0CON1_C0FILTEN_Msk)

/**
 * ACMP0滤波长度配置位
 * @param[in] length:
 * -# ACMP0_NFCLK_2_TSYS:滤波长度为2个ACMP_CLK周期
 * -# ACMP0_NFCLK_4_TSYS:滤波长度为4个ACMP_CLK周期
 * -# ACMP0_NFCLK_8_TSYS:滤波长度为8个ACMP_CLK周期
 * -# ACMP0_NFCLK_16_TSYS:滤波长度为16个ACMP_CLK周期
 * -# ACMP0_NFCLK_32_TSYS:滤波长度为32个ACMP_CLK周期
 * -# ACMP0_NFCLK_64_TSYS:滤波长度为64个ACMP_CLK周期
 * -# ACMP0_NFCLK_128_TSYS:滤波长度为128个ACMP_CLK周期
 */
#define ACMP0_FILT_SEL(length)                                                                                         \
    (ACMP0CON1 = ((ACMP0CON1 & (~ACMP0_ACMP0CON1_C0FILTTIME_Msk))) | ((length) << ACMP0_ACMP0CON1_C0FILTTIME_Pos))

/**
 * ACMP0迟滞控制位
 * @param[in] mode:
 * -# ACMP0_HYSCTL_CLOSE:关闭迟滞
 * -# ACMP0_HYSCTL_P:正迟滞
 * -# ACMP0_HYSCTL_N:负迟滞
 * -# ACMP0_HYSCTL_BOUTH:双边迟滞
 */
#define ACMP0_HYSCTL_SEL(mode)                                                                                         \
    (ACMP0CON1 = ((ACMP0CON1 & (~ACMP0_ACMP0CON1_C0PNS_Msk))) | ((mode) << ACMP0_ACMP0CON1_C0PNS_Pos))

/**
 * ACMP0迟滞电压选择位
 * @param[in] volt:
 * -# ACMP0_HYS_VOLT0MV:迟滞0mV
 * -# ACMP0_HYS_VOLT10MV:迟滞10mv
 * -# ACMP0_HYS_VOLT20MV:迟滞20mV
 * -# ACMP0_HYS_VOLT60MV:迟滞60mV
 */

#define ACMP0_HYS_VOLT_SEL(volt)                                                                                       \
    (ACMP0CON1 = ((ACMP0CON1 & (~ACMP0_ACMP0CON1_C0PROG_Msk))) | ((volt) << ACMP0_ACMP0CON1_C0PROG_Pos))

/**@name ACMP1控制寄存器ACMP1CON0
 * @{
 */

#define ACMP_ACMP1CON0_C1IF_Pos       (7)
#define ACMP_ACMP1CON0_C1IF_Msk       (0x01 << ACMP_ACMP1CON0_C1IF_Pos)

#define ACMP_ACMP1CON0_C1EN_Pos       (6)
#define ACMP_ACMP1CON0_C1EN_Msk       (0x01 << ACMP_ACMP1CON0_C1EN_Pos)

#define ACMP_ACMP1CON0_C1NS_Pos       (4)
#define ACMP_ACMP1CON0_C1NS_Msk       (0x03 << ACMP_ACMP1CON0_C1NS_Pos)

#define ACMP_ACMP1CON0_C1PS_Pos       (2)
#define ACMP_ACMP1CON0_C1PS_Msk       (0x03 << ACMP_ACMP1CON0_C1PS_Pos)

#define ACMP_ACMP1CON0_C1POLARITY_Pos (1)
#define ACMP_ACMP1CON0_C1POLARITY_Msk (0x01 << ACMP_ACMP1CON0_C1POLARITY_Pos)

#define ACMP_ACMP1CON0_C1OUT_Pos      (0)
#define ACMP_ACMP1CON0_C1OUT_Msk      (0x01 << ACMP_ACMP1CON0_C1OUT_Pos)

/**
 * ACMP中断标志位
 * @note 软件需要写0清除该位。
 */
#define CLR_ACMP1_IF_FLAG (ACMP1CON0 &= ~ACMP_ACMP1CON0_C1IF_Msk)

#define ENABLE_ACMP1      (ACMP1CON0 |= ACMP_ACMP1CON0_C1EN_Msk)
#define DISABLE_ACMP1     (ACMP1CON0 &= ~ACMP_ACMP1CON0_C1EN_Msk)

#define ACMP1_INN0        (0x00)
#define ACMP1_INN1        (0x01)
#define ACMP1_VDIV        (0x03)

/**
 * ACMP负端输入信号选择位
 * @param[in] mode:
 * -# ACMP1_INN0:选择ACMP1INN0作为输入
 * -# ACMP1_INN1:选择ACMP1INN1作为输入
 * -# ACMP1_VDIV:选择分压输出VDIV作为输入
 */

#define ACMP_ACMP1CON0_C1NS_SEL(mode)                                                                                  \
    (ACMP1CON0 = ((ACMP1CON0 & (~ACMP_ACMP1CON0_C1NS_Msk))) | ((mode) << ACMP_ACMP1CON0_C1NS_Pos))

#define ACMP1_INP0 (0x00)
#define ACMP1_INP1 (0x01)
#define ACMP1_INP2 (0x02)
#define ACMP1_INP3 (0x03)

/**
 * ACMP1正端输入信号选择位
 * @param[in] mode:
 * -# ACMP1_INP0:选择ACMP1INP0作为输入
 * -# ACMP1_INP1:选择ACMP1INP1作为输入
 * -# ACMP1_INP2:选择ACMP1INP2作为输入・
 * -# ACMP1_INP3:选择ACMP1INP3作为输入
 */

#define ACMP_ACMP1CON0_C1PS_SEL(mode)                                                                                  \
    (ACMP1CON0 = ((ACMP1CON0 & (~ACMP_ACMP1CON0_C1PS_Msk))) | ((mode) << ACMP_ACMP1CON0_C1PS_Pos))

/**
 * ACMP1输出极性选择位。
 */
#define ACMP1_POLARITY_NORMAL  (ACMP1CON0 &= (~ACMP_ACMP1CON0_C1POLARITY_Msk)) /* 直接输出 */
#define ACMP1_POLARITY_REVERSE (ACMP1CON0 |= (~ACMP_ACMP1CON0_C1POLARITY_Msk)) /* 反相输出 */

#define ACMP1_READ_OUT         (ACMP1CON0 & (~ACMP_ACMP1CON0_C1OUT_Msk) >> ACMP_ACMP1CON0_C1OUT_Pos)

/**@name ACMP1控制寄存器ACMP1CON1
 * @{
 */
#define ACMP1_ACMP1CON1_C1PROG_Pos     (0)
#define ACMP1_ACMP1CON1_C1PROG_Msk     (0x03 << ACMP1_ACMP1CON1_C1PROG_Pos)

#define ACMP1_ACMP1CON1_C1PNS_Pos      (2)
#define ACMP1_ACMP1CON1_C1PNS_Msk      (0x03 << ACMP1_ACMP1CON1_C1PNS_Pos)

#define ACMP1_ACMP1CON1_C1FILTTIME_Pos (4)
#define ACMP1_ACMP1CON1_C1FILTTIME_Msk (0x07 << ACMP1_ACMP1CON1_C1FILTTIME_Pos)

#define ACMP1_ACMP1CON1_C1FILTEN_Pos   (7)
#define ACMP1_ACMP1CON1_C1FILTEN_Msk   (0x01 << ACMP1_ACMP1CON1_C1FILTEN_Pos)

/**
 * ACMP1输迟滞电压
 */
#define ACMP1_HYS_VOLT0MV  (0)
#define ACMP1_HYS_VOLT20MV (1)
#define ACMP1_HYS_VOLT10MV (2)
#define ACMP1_HYS_VOLT60MV (3)

/**
 * ACMP1输迟滞控制
 */
#define ACMP1_HYSCTL_CLOSE (0)
#define ACMP1_HYSCTL_P     (1)
#define ACMP1_HYSCTL_N     (2)
#define ACMP1_HYSCTL_BOUTH (3)

/**
 * ACMP1滤波长度
 */
#define ACMP1_NFCLK_2_TSYS   (0)
#define ACMP1_NFCLK_4_TSYS   (1)
#define ACMP1_NFCLK_8_TSYS   (2)
#define ACMP1_NFCLK_16_TSYS  (3)
#define ACMP1_NFCLK_32_TSYS  (4)
#define ACMP1_NFCLK_64_TSYS  (5)
#define ACMP1_NFCLK_128_TSYS (6)

#define ENABLE_ACMP1_FILT    (ACMP1CON1 |= ACMP1_ACMP1CON1_C1FILTEN_Msk)
#define DISABLE_ACMP1_FILT   (ACMP1CON1 &= ~ACMP1_ACMP1CON1_C1FILTEN_Msk)

/**
 * ACMP1滤波长度配置位
 * @param[in] length:
 * -# ACMP1_NFCLK_2_TSYS:滤波长度为2个ACMP_CLK周期
 * -# ACMP1_NFCLK_4_TSYS:滤波长度为4个ACMP_CLK周期
 * -# ACMP1_NFCLK_8_TSYS:滤波长度为8个ACMP_CLK周期
 * -# ACMP1_NFCLK_16_TSYS:滤波长度为16个ACMP_CLK周期
 * -# ACMP1_NFCLK_32_TSYS:滤波长度为32个ACMP_CLK周期
 * -# ACMP1_NFCLK_64_TSYS:滤波长度为64个ACMP_CLK周期
 * -# ACMP1_NFCLK_128_TSYS:滤波长度为128个ACMP_CLK周期
 */
#define ACMP1_FILT_SEL(length)                                                                                         \
    (ACMP1CON1 = ((ACMP1CON1 & (~ACMP1_ACMP1CON1_C1FILTTIME_Msk))) | ((length) << ACMP1_ACMP1CON1_C1FILTTIME_Pos))

/**
 * ACMP1迟滞控制位
 * @param[in] mode:
 * -# ACMP1_HYSCTL_CLOSE:关闭迟滞
 * -# ACMP1_HYSCTL_P:正迟滞
 * -# ACMP1_HYSCTL_N:负迟滞
 * -# ACMP1_HYSCTL_BOUTH:双边迟滞
 */
#define ACMP1_HYSCTL_SEL(mode)                                                                                         \
    (ACMP1CON1 = ((ACMP1CON1 & (~ACMP1_ACMP1CON1_C1PNS_Msk))) | ((mode) << ACMP1_ACMP1CON1_C1PNS_Pos))

/**
 * ACMP1迟滞电压选择位
 * @param[in] volt:
 * -# ACMP1_HYS_VOLT0MV:迟滞0mV
 * -# ACMP1_HYS_VOLT10MV:迟滞10mv
 * -# ACMP1_HYS_VOLT20MV:迟滞20mV
 * -# ACMP1_HYS_VOLT60MV:迟滞60mV
 */

#define ACMP1_HYS_VOLT_SEL(volt)                                                                                       \
    (ACMP1CON1 = ((ACMP1CON1 & (~ACMP1_ACMP1CON1_C1PROG_Msk))) | ((volt) << ACMP1_ACMP1CON1_C1PROG_Pos))

/**@name ACMP分压控制寄存器ACMPDIV
 * @{
 */

#define ACMP_ACMPDIV_DIVEN_Pos (5)
#define ACMP_ACMPDIV_DIVEN_Msk (0x01 << ACMP_ACMPDIV_DIVEN_Pos)

#define ACMP_ACMPDIV_DIVS_Pos  (4)
#define ACMP_ACMPDIV_DIVS_Msk  (0x01 << ACMP_ACMPDIV_DIVS_Pos)

#define ACMP_ACMPDIV_DIVC_Pos  (0)
#define ACMP_ACMPDIV_DIVC_Msk  (0x0F << ACMP_ACMPDIV_DIVC_Pos)

#define ACMP_DIV_20_2          (0)
#define ACMP_DIV_20_3          (1)
#define ACMP_DIV_20_4          (2)
#define ACMP_DIV_20_5          (3)
#define ACMP_DIV_20_6          (4)
#define ACMP_DIV_20_7          (5)
#define ACMP_DIV_20_8          (6)
#define ACMP_DIV_20_9          (7)
#define ACMP_DIV_20_10         (8)
#define ACMP_DIV_20_11         (9)
#define ACMP_DIV_20_12         (10)
#define ACMP_DIV_20_13         (11)
#define ACMP_DIV_20_14         (12)
#define ACMP_DIV_20_15         (13)
#define ACMP_DIV_20_16         (14)
#define ACMP_DIV_20_17         (15)

#define ENABLE_ACMP_DIV        (ACMPDIV |= ACMP_ACMPDIV_DIVEN_Msk)
#define DISABLE_ACMP_DIV       (ACMPDIV &= ~ACMP_ACMPDIV_DIVEN_Msk)

#define ACMP_DIV_SEL_BGR12     (ACMPDIV |= ACMP_ACMPDIV_DIVS_Msk)
#define ACMP_DIV_SEL_VDD5V     (ACMPDIV &= ~ACMP_ACMPDIV_DIVS_Msk)

/**
 * ACMP1迟滞电压选择位
 * @param[in] div:
 * -# ACMP_DIV_20_2:VDIV是VDD 2/20
 * -# ACMP_DIV_20_3:VDIV是VDD 3/20
 * -# ACMP_DIV_20_4:VDIV是VDD 4/20
 * -# ACMP_DIV_20_5:VDIV是VDD 5/20
 * -# ACMP_DIV_20_6:VDIV是VDD 6/20
 * -# ACMP_DIV_20_7:VDIV是VDD 7/20
 * -# ACMP_DIV_20_8:VDIV是VDD 8/20
 * -# ACMP_DIV_20_9:VDIV是VDD 9/20
 * -# ACMP_DIV_20_10:VDIV是VDD 10/20
 * -# ACMP_DIV_20_11:VDIV是VDD 11/20
 * -# ACMP_DIV_20_12:VDIV是VDD 12/20
 * -# ACMP_DIV_20_13:VDIV是VDD 13/20
 * -# ACMP_DIV_20_14:VDIV是VDD 14/20
 * -# ACMP_DIV_20_15:VDIV是VDD 15/20
 * -# ACMP_DIV_20_16:VDIV是VDD 16/20
 * -# ACMP_DIV_20_17:VDIV是VDD 17/20
 */

#define ACMP_VDIV_SEL(div) (ACMPDIV = ((ACMPDIV & (~ACMP_ACMPDIV_DIVC_Msk))) | ((div) << ACMP_ACMPDIV_DIVC_Pos))

/**@name ACMP刹车控制寄存器ACMPBCON
 * @{
 */

#define ACMP_ACMPBCON_C1BEN_Pos  (7)
#define ACMP_ACMPBCON_C1BEN_Msk  (0x01 << ACMP_ACMPBCON_C1BEN_Pos)

#define ACMP_ACMPBCON_C1BLE_Pos  (6)
#define ACMP_ACMPBCON_C1BLE_Msk  (0x01 << ACMP_ACMPBCON_C1BLE_Pos)

#define ACMP_ACMPBCON_C1BLES_Pos (4)
#define ACMP_ACMPBCON_C1BLES_Msk (0x03 << ACMP_ACMPBCON_C1BLES_Pos)

#define ACMP_ACMPBCON_C0BEN_Pos  (3)
#define ACMP_ACMPBCON_C0BEN_Msk  (0x01 << ACMP_ACMPBCON_C0BEN_Pos)

#define ACMP_ACMPBCON_C0BLE_Pos  (2)
#define ACMP_ACMPBCON_C0BLE_Msk  (0x01 << ACMP_ACMPBCON_C0BLE_Pos)

#define ACMP_ACMPBCON_C0BLES_Pos (0)
#define ACMP_ACMPBCON_C0BLES_Msk (0x03 << ACMP_ACMPBCON_C0BLES_Pos)

/**
 * ACMP1输出刹车使能
 */
#define ENABLE_ACMP1_PWMFB  (ACMPBCON |= ACMP_ACMPBCON_C1BEN_Msk)
#define DISABLE_ACMP1_PWMFB (ACMPBCON &= ~ACMP_ACMPBCON_C1BEN_Msk)

/**
 * ACMP1输出刹车电平边沿控制位
 */
#define ACMP1_OUTPUT_EDGEFB (ACMPBCON |= ACMP_ACMPBCON_C1BLE_Msk)  /* 电平刹车 */
#define ACMP1_OUTPUT_VOLTFB (ACMPBCON &= ~ACMP_ACMPBCON_C1BLE_Msk) /* 边沿刹车 */

/**
 * ACMP1输出事件和刹车电平边沿选择位
 */

#define ACMP1_VOLTFB_CLOSE       (1)
#define ACMP1_HIGH_VOLTFB        (2)
#define ACMP1_LOW_VOLTFB         (3)

#define ACMP1_EDGEFB_INC_CLOSE   (0)
#define ACMP1_RISING_INC_EDGEFB  (1)
#define ACMP1_FALLING_INC_EDGEFB (2)
#define ACMP1_BOTH_INC_EDGEFB    (3)

/**
 * ACMP1刹车电平或边沿选择位
 * @param[in] mode:
 *  # 当选择电平刹车控制时输入如下
 * -# ACMP1_VOLTFB_CLOSE: 不产生刹车
 * -# ACMP1_HIGH_VOLTFB:  高电平刹车
 * -# ACMP1_LOW_VOLTFB:   低电平刹车
 *  # 当选择边沿刹车控制时输入如下
 * -# ACMP1_EDGEFB_INC_CLOSE:   不产生刹车
 * -# ACMP1_RISING_INC_EDGEFB:  上升沿产生刹车
 * -# ACMP1_FALLING_INC_EDGEFB: 下降沿产生刹车
 * -# ACMP1_BOTH_INC_EDGEFB:    上升沿/下降沿产生刹车
 */
#define ACMP1_FB_SEL(mode)                                                                                             \
    (ACMPBCON = ((ACMPBCON & (~ACMP_ACMPBCON_C1BLES_Msk))) | ((mode) << ACMP_ACMPBCON_C1BLES_Pos))
/**
 * ACMP0输出刹车使能
 */
#define ENABLE_ACMP0_PWMFB  (ACMPBCON |= ACMP_ACMPBCON_C0BEN_Msk)
#define DISABLE_ACMP0_PWMFB (ACMPBCON &= ~ACMP_ACMPBCON_C0BEN_Msk)

/**
 * ACMP0输出刹车电平边沿控制位
 */
#define ACMP0_OUTPUT_VOLTFB (ACMPBCON |= ACMP_ACMPBCON_C0BLE_Msk)  /* 电平刹车 */
#define ACMP0_OUTPUT_EDGEFB (ACMPBCON &= ~ACMP_ACMPBCON_C0BLE_Msk) /* 边沿刹车 */

/**
 * ACMP0输出事件和刹车电平边沿选择位
 */
#define ACMP0_VOLTFB_CLOSE       (1)
#define ACMP0_LOW_VOLTFB         (2)
#define ACMP0_HIGH_VOLTFB        (3)

#define ACMP0_EDGEFB_INC_CLOSE   (0)
#define ACMP0_RISING_INC_EDGEFB  (1)
#define ACMP0_FALLING_INC_EDGEFB (2)
#define ACMP0_BOTH_INC_EDGEFB    (3)

/**
 * ACMP0刹车电平或边沿选择位
 * @param[in] mode:
 *  # 当选择电平刹车控制时输入如下
 * -# ACMP0_VOLTFB_CLOSE: 不产生刹车
 * -# ACMP0_HIGH_VOLTFB:  低电平刹车
 * -# ACMP0_LOW_VOLTFB:   高电平刹车
 *  # 当选择边沿刹车控制时输入如下
 * -# ACMP0_EDGEFB_INC_CLOSE:   不产生刹车
 * -# ACMP0_RISING_INC_EDGEFB:  上升沿产生刹车
 * -# ACMP0_FALLING_INC_EDGEFB: 下降沿产生刹车
 * -# ACMP0_BOTH_INC_EDGEFB:    上升沿/下降沿产生刹车
 */
#define ACMP0_FB_SEL(mode)                                                                                             \
    (ACMPBCON = ((ACMPBCON & (~ACMP_ACMPBCON_C0BLES_Msk))) | ((mode) << ACMP_ACMPBCON_C0BLES_Pos))

/**@name ACMP测试寄存器ACMPTEST
 * @{
 */

#define ACMP_ACMPTSET_TICK_TIME_Pos (1)
#define ACMP_ACMPTSET_TICK_TIME_Msk (0x03 << ACMP_ACMPTSET_TICK_TIME_Pos)
#define ACMP_ACMPTSET_TESTACMP_Pos  (0)
#define ACMP_ACMPTSET_TESTACMP_Msk  (0x01 << ACMP_ACMPTSET_TESTACMP_Pos)

/**
 * ACMP测试模式下TICK对应的系统时钟的倍数
 */
#define ACMP_TICK_TIME_10 (0)
#define ACMP_TICK_TIME_20 (1)
#define ACMP_TICK_TIME_30 (2)
#define ACMP_TICK_TIME_40 (3)

/**
 * ACMP测试模式使能
 */
#define ENABLE_ACMP_TEST  (ACMPTEST |= ACMP_ACMPTSET_TESTACMP_Msk)
#define DISABLE_ACMP_TEST (ACMPTEST &= ~ACMP_ACMPTSET_TESTACMP_Msk)

#endif /* __ACMP_H__ */