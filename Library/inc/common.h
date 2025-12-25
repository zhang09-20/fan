/**
 * @file      common.h
 * @brief     公共驱动配置
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include "WY8S9003xx.h"

#define SET_BIT     (1U) /*!< BIT置1 */
#define CLR_BIT     (0U) /*!< BIT置0 */

#define OUTPUT_HIGH (1)  /*!< 输出高电平 */
#define OUTPUT_LOW  (0)  /*!< 输出低电平 */

#define BIT0        (1U << 0)
#define BIT1        (1U << 1)
#define BIT2        (1U << 2)
#define BIT3        (1U << 3)
#define BIT4        (1U << 4)
#define BIT5        (1U << 5)
#define BIT6        (1U << 6)
#define BIT7        (1U << 7)

#define SFR_PAGE_0                                                                                                     \
    {                                                                                                                  \
        TA   = 0xAA;                                                                                                   \
        TA   = 0x55;                                                                                                   \
        SFRS = 0x0;                                                                                                    \
    }
#define SFR_PAGE_1                                                                                                     \
    {                                                                                                                  \
        TA   = 0xAA;                                                                                                   \
        TA   = 0x55;                                                                                                   \
        SFRS = 0x1;                                                                                                    \
    }

/**@name 中断向量号定义
 * @{
 */
#define INT0_VECTOR   0  /*!< INT0中断号 */
#define BOD_VECTOR    1  /*!< 欠压中断号 */
#define INT1_VECTOR   2  /*!< INT1中断号 */
#define TIMER0_VECTOR 3  /*!< TIMER0中断号 */
#define UART0_VECTOR  4  /*!< UART0中断号 */
#define TIMER1_VECTOR 5  /*!< TIMER1中断号 */
#define UART1_VECTOR  6  /*!< UART1中断号 */
#define WDT_VECTOR    7  /*!< 看门狗中断号 */
#define TIMER2_VECTOR 8  /*!< TIMER2中断号 */
#define TIMER3_VECTOR 9  /*!< TIMER3中断号 */
#define SPI_VECTOR    10 /*!< SPI中断号 */
#define GPIO_VECTOR   11 /*!< 管脚中断号 */
#define ADC_VECTOR    12 /*!< ADC中断号 */
#define PWM_VECTOR    13 /*!< PWM中断号 */
#define FB_VECTOR     14 /*!< 刹车中断号 */
#define I2C_VECTOR    15 /*!< I2C中断号 */
#define SWT_VECTOR    16 /*!< SWT自唤醒中断号 */
#define ACMP_VECTOR   17 /*!< ACMP中断号 */
/**@} */

/**@name 中断屏蔽寄存器
 * @{
 */
#define ENABLE_ALL_INT    (EA = 1)       /*!< 使能全局中断 */
#define DISABLE_ALL_INT   (EA = 0)       /*!< 禁止全局中断 */
#define ENABLE_UART1_INT  (ET6 = 1)      /*!< 使能UART1中断 */
#define DISABLE_UART1_INT (ET6 = 0)      /*!< 禁止UART1中断 */
#define ENABLE_TIME1_INT  (ET5 = 1)      /*!< 使能TIME1中断 */
#define DISABLE_TIME1_INT (ET5 = 0)      /*!< 禁止TIME1中断 */
#define ENABLE_UART0_INT  (ET4 = 1)      /*!< 使能UART0中断 */
#define DISABLE_UART0_INT (ET4 = 0)      /*!< 禁止UART0中断 */
#define ENABLE_TIME0_INT  (ET3 = 1)      /*!< 使能TIME0中断 */
#define DISABLE_TIME0_INT (ET3 = 0)      /*!< 禁止TIME0中断 */
#define ENABLE_INT1_INT   (ET2 = 1)      /*!< 使能INT1中断 */
#define DISABLE_INT1_INT  (ET2 = 0)      /*!< 禁止INT1中断 */
#define ENABLE_BOD_INT    (ET1 = 1)      /*!< 使能BOD中断 */
#define DISABLE_BOD_INT   (ET1 = 0)      /*!< 禁止BOD中断 */
#define ENABLE_INT0_INT   (ET0 = 1)      /*!< 使能INT0中断 */
#define DISABLE_INT0_INT  (ET0 = 0)      /*!< 禁止INT0中断 */

#define ENABLE_FB_INT     (EI1 |= BIT7)  /*!< 使能FB中断 */
#define DISABLE_FB_INT    (EI1 &= ~BIT7) /*!< 禁止FB中断 */
#define ENABLE_PWM_INT    (EI1 |= BIT6)  /*!< 使能PWM中断 */
#define DISABLE_PWM_INT   (EI1 &= ~BIT6) /*!< 禁止PWM中断 */
#define ENABLE_ADC_INT    (EI1 |= BIT5)  /*!< 使能ADC中断 */
#define DISABLE_ADC_INT   (EI1 &= ~BIT5) /*!< 禁止ADC中断 */
#define ENABLE_GPIO_INT   (EI1 |= BIT4)  /*!< 使能管脚中断 */
#define DISABLE_GPIO_INT  (EI1 &= ~BIT4) /*!< 禁止管脚中断 */
#define ENABLE_SPI_INT    (EI1 |= BIT3)  /*!< 使能SPI中断 */
#define DISABLE_SPI_INT   (EI1 &= ~BIT3) /*!< 禁止SPI中断 */
#define ENABLE_TIME3_INT  (EI1 |= BIT2)  /*!< 使能TIME3中断 */
#define DISABLE_TIME3_INT (EI1 &= ~BIT2) /*!< 禁止TIME3中断 */
#define ENABLE_TIME2_INT  (EI1 |= BIT1)  /*!< 使能TIME2中断 */
#define DISABLE_TIME2_INT (EI1 &= ~BIT1) /*!< 禁止TIME2中断 */
#define ENABLE_WDT_INT    (EI1 |= BIT0)  /*!< 使能WDT中断 */
#define DISABLE_WDT_INT   (EI1 &= ~BIT0) /*!< 禁止WDT中断 */

#define ENABLE_ACMP_INT   (EI2 |= BIT2)  /*!< 使能ACMP中断 */
#define DISABLE_ACMP_INT  (EI2 &= ~BIT2) /*!< 禁止ACMP中断 */
#define ENABLE_SWT_INT    (EI2 |= BIT1)  /*!< 使能SWT中断 */
#define DISABLE_SWT_INT   (EI2 &= ~BIT1) /*!< 禁止SWT中断 */
#define ENABLE_I2C_INT    (EI2 |= BIT0)  /*!< 使能I2C中断 */
#define DISABLE_I2C_INT   (EI2 &= ~BIT0) /*!< 禁止I2C中断 */

/**@} */
/**@name 中断优先级控制寄存器
 * @{
 */
#define UART1_PRIORITY_H  (IP |= BIT6)   /*!< UART1优先级高 */
#define UART1_PRIORITY_L  (IP &= ~BIT6)  /*!< UART1优先级低 */
#define TIME1_PRIORITY_H  (IP |= BIT5)   /*!< TIMER1优先级高 */
#define TIME1_PRIORITY_L  (IP &= ~BIT5)  /*!< TIMER1优先级低 */
#define UART0_PRIORITY_H  (IP |= BIT4)   /*!< UART0优先级高 */
#define UART0_PRIORITY_L  (IP &= ~BIT4)  /*!< UART0优先级低 */
#define TIME0_PRIORITY_H  (IP |= BIT3)   /*!< TIMER0优先级高 */
#define TIME0_PRIORITY_L  (IP &= ~BIT3)  /*!< TIMER0优先级低 */
#define INT1_PRIORITY_H   (IP |= BIT2)   /*!< INT1优先级高 */
#define INT1_PRIORITY_L   (IP &= ~BIT2)  /*!< INT1优先级低 */
#define BOD_PRIORITY_H    (IP |= BIT1)   /*!< BOD优先级高 */
#define BOD_PRIORITY_L    (IP &= ~BIT1)  /*!< BOD优先级低 */
#define INT0_PRIORITY_H   (IP |= BIT0)   /*!< INT0优先级高 */
#define INT0_PRIORITY_L   (IP &= ~BIT0)  /*!< INT0优先级低 */

#define FB_PRIORITY_H     (IP1 |= BIT7)  /*!< 刹车优先级高 */
#define FB_PRIORITY_L     (IP1 &= ~BIT7) /*!< 刹车优先级低 */
#define PWM_PRIORITY_H    (IP1 |= BIT6)  /*!< PWM优先级高 */
#define PWM_PRIORITY_L    (IP1 &= ~BIT6) /*!< PWM优先级低 */
#define ADC_PRIORITY_H    (IP1 |= BIT5)  /*!< ADC优先级高 */
#define ADC_PRIORITY_L    (IP1 &= ~BIT5) /*!< ADC优先级低 */
#define GPIO_PRIORITY_H   (IP1 |= BIT4)  /*!< GPIO优先级高 */
#define GPIO_PRIORITY_L   (IP1 &= ~BIT4) /*!< GPIO优先级低 */
#define SPI_PRIORITY_H    (IP1 |= BIT3)  /*!< SPI优先级高 */
#define SPI_PRIORITY_L    (IP1 &= ~BIT3) /*!< SPI优先级低 */
#define TIMER3_PRIORITY_H (IP1 |= BIT2)  /*!< TIMER3优先级高 */
#define TIMER3_PRIORITY_L (IP1 &= ~BIT2) /*!< TIMER3优先级低 */
#define TIMER2_PRIORITY_H (IP1 |= BIT1)  /*!< TIMER2优先级高 */
#define TIMER2_PRIORITY_L (IP1 &= ~BIT1) /*!< TIMER2优先级低 */
#define WDT_PRIORITY_H    (IP1 |= BIT0)  /*!< WDT优先级高 */
#define WDT_PRIORITY_L    (IP1 &= ~BIT0) /*!< WDT优先级低 */

#define ACMP_PRIORITY_H   (IP2 |= BIT2)  /*!< ACMP优先级高 */
#define ACMP_PRIORITY_L   (IP2 &= ~BIT2) /*!< ACMP优先级低 */
#define SWT_PRIORITY_H    (IP2 |= BIT1)  /*!< SWT优先级高 */
#define SWT_PRIORITY_L    (IP2 &= ~BIT1) /*!< SWT优先级低 */
#define I2C_PRIORITY_H    (IP2 |= BIT0)  /*!< I2C优先级高 */
#define I2C_PRIORITY_L    (IP2 &= ~BIT0) /*!< I2C优先级低 */

/**@} */
/**@name 复用引脚配置表
 * @{
 */
#define GPIO_MUX_MODE      (0)  /*!< 引脚复用模式为GPIO */
#define SCK_MUX_MOD        (1)  /*!< 引脚复用模式为SPI_SCK模式 */
#define MOSI_MUX_MOD       (2)  /*!< 引脚复用模式为SPI_MOSI模式 */
#define MISO_MUX_MOD       (3)  /*!< 引脚复用模式为SPI_MISO模式 */
#define NSS_MUX_MOD        (4)  /*!< 引脚复用模式为SPI_NSS模式 */
#define UART0_RXD_MUX_MODE (5)  /*!< 引脚复用模式为UART0_RX */
#define UART1_RXD_MUX_MODE (6)  /*!< 引脚复用模式为UART1_RX */
#define I2CSCL_MUX_MOD     (7)  /*!< 引脚复用模式为I2C_SCL模式 */
#define I2CSDA_MUX_MOD     (8)  /*!< 引脚复用模式为I2C_SDA模式 */
#define UART0_TXD_MUX_MODE (9)  /*!< 引脚复用模式为UART0_TX */
#define UART1_TXD_MUX_MODE (10) /*!< 引脚复用模式为UART1_TX */
#define PWM0_MUX_MODE      (11) /*!< 引脚复用模式为PWM0模式 */
#define PWM1_MUX_MODE      (12) /*!< 引脚复用模式为PWM1模式 */
#define PWM2_MUX_MODE      (13) /*!< 引脚复用模式为PWM2模式 */
#define PWM3_MUX_MODE      (14) /*!< 引脚复用模式为PWM3模式 */
#define PWM4_MUX_MODE      (15) /*!< 引脚复用模式为PWM4模式 */
#define PWM5_MUX_MODE      (16) /*!< 引脚复用模式为PWM5模式 */
#define CAP0_MUX_MODE      (17) /*!< 引脚复用模式为CAP0模式 */
#define CAP1_MUX_MODE      (18) /*!< 引脚复用模式为CAP1模式 */
#define CAP2_MUX_MODE      (19) /*!< 引脚复用模式为CAP2模式 */
#define CAP3_MUX_MODE      (20) /*!< 引脚复用模式为CAP3模式 */
#define STADC_MUX_MODE     (21) /*!< 引脚复用模式为STADC模式 */
#define FB_MUX_MODE        (22) /*!< 引脚复用模式为刹车模式 */
#define INT0_MUX_MODE      (23) /*!< 引脚复用模式为INT0模式 */
#define INT1_MUX_MODE      (24) /*!< 引脚复用模式为INT1模式 */
#define TIME0_T0_MUX_MODE  (25) /*!< 引脚复用模式为T0模式 */
#define TIME1_T1_MUX_MODE  (26) /*!< 引脚复用模式为T1模式 */
#define ACMP0OUT_MUX_MODE  (27) /*!< 引脚复用模式为ACMP0输出模式 */
#define ACMP1OUT_MUX_MODE  (28) /*!< 引脚复用模式为ACMP1输出模式 */
#define ANALOG_MUX_MODE    (31) /*!< 引脚复用模式为模拟功能 */

/**
 * 引脚复用功能配置
 * @param[in] PioCFG:
 * -# PIO00CFG - PIO07CFG
 * -# PIO10CFG - PIO17CFG
 * -# PIO20CFG - PIO25CFG
 * @param[in] MUXMode: 见复用引脚配置表GPIO_MUX_MODE......ANALOG_MUX_MODE
 */
#define PORT_SET_MUX(PioCFG, MUXMode) ((PioCFG) = (MUXMode))
/**@} */

/**@name 系统时钟配置
 * @{
 */
#define HRC_16M_VALUE     (16000000)        /* HRC时钟频率为16MHz */
#define HRC_24M_VALUE     (24000000)        /* HRC时钟频率为24MHz */
#define HRC_48M_VALUE     (48000000)        /* HRC时钟频率为48MHz */
#define OSC_VALUE         (8000000)         /* 如果选择外部时钟模式，此处输入外部晶振频率 */
#define LRC_VALUE         (50000000 / 1024) /* LRC时钟频率 */

#define CLKSEL_HRC        (0x00)            /*!< 内部高速时钟:48MHz */
#define CLKSEL_LRC        (0x01)            /*!< 内部低频时钟:47KHz */
#define CLKSEL_OSC        (0x02)            /*!< 外部时钟:1MHz~48MHz */

#define CLK_HRC_16MHz     (0x00)            /*!< 内部高速时钟分频为16MHz */
#define CLK_HRC_24MHz     (0x01)            /*!< 内部高速时钟分频为24MHz */
#define CLK_HRC_48MHz     (0x02)            /*!< 内部高速时钟不分频，48MHz */

#define CLK_DIV_NOT       (0)               /* 系统时钟不分频 */
#define CLK_DIV_2         (1)               /* 系统时钟2分频 */
#define CLK_DIV_4         (2)               /* 系统时钟4分频 */
#define CLK_DIV_8         (3)               /* 系统时钟8分频 */
#define CLK_DIV_16        (4)               /* 系统时钟16分频 */
#define CLK_DIV_32        (5)               /* 系统时钟32分频 */
#define CLK_DIV_64        (6)               /* 系统时钟64分频 */
#define CLK_DIV_128       (7)               /* 系统时钟128分频 */

#define CLKCON_SEL_POS    (6)
#define CLKCON_SEL_MSK    (0x3 << CLKCON_SEL_POS)
#define CLKCON_CLKPER_POS (4)
#define CLKCON_CLKPER_MSK (0x3 << CLKCON_CLKPER_POS)
#define CLKCON_DIV_POS    (0)
#define CLKCON_DIV_MSK    (0x7 << CLKCON_DIV_POS)
/**
 * 系统时钟源设置
 * @param[in] mode:
 * -# CLKSEL_HRC 内部高速时钟:48MHz
 * -# CLKSEL_LRC 内部低速时钟:47KHz
 * -# CLKSEL_OSC 外部高速晶体振荡:(1MHz~48MHz)
 */
#define SYS_CLK_SEL(mode) (CLKCON = ((CLKCON & (~CLKCON_SEL_MSK)) | ((mode) << CLKCON_SEL_POS)))

/**
 * CLK_HRC分频系数选择
 * @param[in] presc:
 * -# CLK_HRC_16MHz 内部高速时钟分频为16MHz
 * -# CLK_HRC_24MHz 内部高速时钟分频为24MHz
 * -# CLK_HRC_48MHz 内部高速时钟不分频
 */
#define SYS_CLK_PER(presc) (CLKCON = ((CLKCON & (~CLKCON_CLKPER_MSK)) | ((presc) << CLKCON_CLKPER_POS)))

/**
 * 系统时钟分频控制
 * @param[in] divData 系统时钟分频系数，取值为0..7
 * -# CLK_DIV_NOT
 * -# CLK_DIV_2
 * -# CLK_DIV_4
 * -# CLK_DIV_8
 * -# CLK_DIV_16
 * -# CLK_DIV_32
 * -# CLK_DIV_64
 * -# CLK_DIV_128
 */
#define SYS_CLK_DIV(divData) (CLKCON = ((CLKCON & (~CLKCON_DIV_MSK)) | ((divData) << CLKCON_DIV_POS)))

#define WAITSTS_WAITSTS_POS  (0)
#define WAITSTS_WAITSTS_MSK  (0x3 << WAITSTS_WAITSTS_POS)

#define WAITS_LOWER16M       (0) /* 主频16MHz及以下等待周期配置 */
#define WAITS_24M            (1) /* 主频24MHz等待周期配置 */
#define WAITS_48M            (2) /* 主频48MHz等待周期配置 */
/**
 * 闪存取指访问周期配置
 * @param[in] wait:
 * -# WAITSTS_LOWER16M 主频16MHz及以下等待周期配置
 * -# WAITSTS_24M      主频24MHz等待周期配置
 * -# WAITSTS_48M      主频48MHz等待周期配置
 */
#define SYS_CLK_WAITS(waits) (WAITSTS = ((WAITSTS & (~WAITSTS_WAITSTS_MSK)) | ((waits) << WAITSTS_WAITSTS_POS)))

/**
 * 获取闪存取指访问周期配置
 * @return 0: 主频16MHz及以下等待周期配置
 *         1: 主频24MHz等待周期配置
 *         3: 主频48MHz等待周期配置
 */
#define GET_SYS_CLK_WAITS ((WAITSTS & WAITSTS_WAITSTS_MSK) >> WAITSTS_WAITSTS_POS)

/**
 * 获取内部高速振荡器HRC细调配置值
 * @note 该寄存器的初始值用于调校HRC，令其能够准确输出48MHz的目标频率。
 */
#define GET_CLK_HRC_FTUNE (HRCFTUNE)

/**
 * 更改内部高速振荡器HRC细调配置值
 * @note 该寄存器的初始值用于调校HRC，令其能够准确输出48MHz的目标频率。
 * @note HRC细调寄存器配置值和HRC输出频率对应关系如下：
 * 细调寄存器的值              HRC输出频率
 * HRCFTUNE+N                (48+0.144*N)MHz
 * HRCFTUNE-N                (48-0.144*N)MHz
 */
#define CLK_INCREASE_HRC_FTUNE(_N_) (HRCFTUNE += _N_)
#define CLK_DECREASE_HRC_FTUNE(_N_) (HRCFTUNE -= _N_)

/**
 * 外部晶振输入稳定标志位
 * @return 1:MCU内部配置外部晶振已准备好 \n
 *         0:外部晶振未准备好
 */
#define IS_OSCST_FLAG ((SFRS & BIT2) >> 2)

/**@name 复位管理
 * @{
 */
/**
 * 获取系统复位原因
 * @return 第7位: 0:未发生软件复位;1:发生软件复位。该位硬件置1，需要软件进行写0清除。\n
 *         第6位: 0:未发生外部复位;1:发生外部复位。该位硬件置1，需要软件进行写0清除。\n
 *         第5位: 0:未发生BOD复位; 1:发生BOD复位。该位硬件置1，需要软件进行写0清除。\n
 *         第4位: 0:未发生WDT复位; 1:发生WDT复位。该位硬件置1，需要软件进行写0清除。
 */
#define GET_SYS_RST_REASON (SYSRST)

/**
 * 清除所有的复位原因
 */
#define CLR_ALL_RST_REASON (SYSRST &= 0x0F)

/**@} */

/**@} */

/**@name 电源管理
 * @{
 */
#define POWER_PCON_SLEEPWPP_POS    (5)
#define POWER_PCON_SLEEPWPP_MSK    (0x1 << POWER_PCON_SLEEPWPP_POS)
#define POWER_PCON_GF1_POS         (3)
#define POWER_PCON_GF1_MSK         (0x1 << POWER_PCON_GF1_POS)
#define POWER_PCON_GF0_POS         (2)
#define POWER_PCON_GF0_MSK         (0x1 << POWER_PCON_GF0_POS)

#define ENABLE_PORTINT_WAKE_SLEEP  (PCON |= POWER_PCON_SLEEPWPP_MSK)  /*!< 使能通过管脚中断唤醒Sleep模式 */
#define DISABLE_PORTINT_WAKE_SLEEP (PCON &= ~POWER_PCON_SLEEPWPP_MSK) /*!< 禁止通过管脚中断唤醒Sleep模式 */

/**
 * 通用标志 1
 * @param[in] status:
 * -# CLR_BIT:通用标志清零
 * -# SET_BIT:通用标志置位
 */
#define POWER_PCON_GF1_SET(status) (PCON = ((PCON & (~POWER_PCON_GF1_MSK)) | ((status) << POWER_PCON_GF1_POS)))
/**
 * 通用标志 0
 * @param[in] status:
 * -# CLR_BIT:通用标志清零
 * -# SET_BIT:通用标志置位
 */
#define POWER_PCON_GF0_SET(status) (PCON = ((PCON & (~POWER_PCON_GF0_MSK)) | ((status) << POWER_PCON_GF0_POS)))

/**
 * SYSD系统标志位
 * @return 1:系统可配置进入Sleep \n
 *         0:系统不可配置进入Sleep
 */
#define IS_SYSD_FLAG            ((SFRS & BIT1) >> 1)

#define POWER_BODCON_BODEN_POS  (7)
#define POWER_BODCON_BODEN_MSK  (0x1 << POWER_BODCON_BODEN_POS)
#define POWER_BODCON_BODF_POS   (6)
#define POWER_BODCON_BODF_MSK   (0x1 << POWER_BODCON_BODF_POS)
#define POWER_BODCON_BODRST_POS (5)
#define POWER_BODCON_BODRST_MSK (0x1 << POWER_BODCON_BODRST_POS)
#define POWER_BODCON_BODV_POS   (2)
#define POWER_BODCON_BODV_MSK   (0x7 << POWER_BODCON_BODV_POS)

#define ENABLE_BOD              (BODCON |= POWER_BODCON_BODEN_MSK)  /*!< 使能欠压检测电路 */
#define DISABLE_BOD             (BODCON &= ~POWER_BODCON_BODEN_MSK) /*!< 禁用欠压检测电路 */
/**
 * 欠压中断标志位
 * @return 0:VDD高于VBOD\n
 *         1:VDD下降到VBOD以下
 * @note 该位硬件置1，需要软件进行写0清除
 */
#define IS_BODCON_BOD_FLAG  ((BODCON & POWER_BODCON_BODF_MSK) >> POWER_BODCON_BODF_POS)
#define CLR_BODCON_BOD_FLAG (BODCON &= ~POWER_BODCON_BODF_MSK)

#define ENABLE_BODRST       (BODCON |= POWER_BODCON_BODRST_MSK)  /*!< 使能欠压检测复位 */
#define DISABLE_BODRST      (BODCON &= ~POWER_BODCON_BODRST_MSK) /*!< 禁用欠压检测复位 */

#define BODV_SEL2V4         (0x01)
#define BODV_SEL2V8         (0x02)
#define BODV_SEL3V2         (0x03)
#define BODV_SEL3V6         (0x04)
#define BODV_SEL4V0         (0x05)
#define BODV_SEL4V4         (0x06)
#define BODV_SEL4V8         (0x07)
/**
 * 欠压侦测电压选择
 * @param[in] mode:
 * -# BODV_SEL2V4:VBOD 电压 2.4V
 * -# BODV_SEL2V8:VBOD 电压 2.8V
 * -# BODV_SEL3V2:VBOD 电压 3.2V
 * -# BODV_SEL3V6:VBOD 电压 3.6V
 * -# BODV_SEL4V0:VBOD 电压 4.0V
 * -# BODV_SEL4V4:VBOD 电压 4.4V
 * -# BODV_SEL4V8:VBOD 电压 4.8V
 */
#define POWER_BODCON_BODV_SET(mode) (BODCON = ((BODCON & (~POWER_BODCON_BODV_MSK)) | ((mode) << POWER_BODCON_BODV_POS)))
/**@} */

/**@name SWT计数器
 * @{
 */
#define SWT_SWTCON_SWTIF_POS (4)
#define SWT_SWTCON_SWTIF_MSK (0x1 << SWT_SWTCON_SWTIF_POS)
#define SWT_SWTCON_SWTR_POS  (3)
#define SWT_SWTCON_SWTR_MSK  (0x1 << SWT_SWTCON_SWTR_POS)
#define SWT_SWTCON_SWTPS_POS (0)
#define SWT_SWTCON_SWTPS_MSK (0x7 << SWT_SWTCON_SWTPS_POS)

/**
 * SWT 溢出标志
 * @return 1:SWT 计数溢出\n
 *         0:SWT 计数未溢出
 */
#define IS_SWT_SWTIF_FLAG  ((SWTCON & SWT_SWTCON_SWTIF_MSK) >> SWT_SWTCON_SWTIF_POS)
#define CLR_SWT_SWTIF_FLAG (SWTCON &= ~SWT_SWTCON_SWTIF_MSK)

#define SWT_PSDIV_2        0x00
#define SWT_PSDIV_4        0x01
#define SWT_PSDIV_16       0x02
#define SWT_PSDIV_64       0x03
#define SWT_PSDIV_256      0x04
#define SWT_PSDIV_512      0x05
#define SWT_PSDIV_1024     0x06
#define SWT_PSDIV_2048     0x07
/**
 * SWT使能并配置时钟
 * @param[in] psdiv:
 * -# SWT_PSDIV_2     SWT计数时钟为CLK_LRC的2分频；
 * -# SWT_PSDIV_4     SWT计数时钟为CLK_LRC的4分频；
 * -# SWT_PSDIV_16    SWT计数时钟为CLK_LRC的16分频；
 * -# SWT_PSDIV_64    SWT计数时钟为CLK_LRC的64分频；
 * -# SWT_PSDIV_256   SWT计数时钟为CLK_LRC的256分频；
 * -# SWT_PSDIV_512   SWT计数时钟为CLK_LRC的512分频；
 * -# SWT_PSDIV_1024  SWT计数时钟为CLK_LRC的1024分频；
 * -# SWT_PSDIV_2048  SWT计数时钟为CLK_LRC的2048分频。
 */
#define SWT_ENABLE(psdiv)                                                                                              \
    (SWTCON = ((SWTCON & (~SWT_SWTCON_SWTPS_MSK)) | ((psdiv) << SWT_SWTCON_SWTPS_POS)) | SWT_SWTCON_SWTR_MSK)
#define SWT_DISABLE (SWTCON &= ~(SWT_SWTCON_SWTR_MSK | SWT_SWTCON_SWTIF_MSK)) /*!< 禁止SWT */
/**
 *  SWT 数据寄存器
 * @param[in] data SWT 8 位计数值
 * @note SWT_OVERFLOW = CLK_LRC/((256 - SWTR)*SWTPS)
 */
#define SWT_SWTR_SET(data) (SWTR = (data))
/**@} */

/**@name 外部中断INT0/INT1
 * @{
 */
#define INT_FALLING  (1)
#define INT_LOWLEVEL (0)

/**
 * 外部中断1标志位
 * @return 0:外部中断1没有产生中断 \n
 *         1:外部中断1产生中断
 */
#define IS_INT1_FLAG (IE1)
/**
 * 外部中断1触发方式控制位：
 * @param[in] mode:
 * -# INT_FALLING:下降沿触发
 * -# INT_LOWLEVEL:低电平触发
 */
#define INT1_TRIGGER_MODE_SET(status) (IT1 = (status))
/**
 * 外部中断0标志位
 * @return 0:外部中断0没有产生中断 \n
 *         1:外部中断0产生中断
 */
#define IS_INT0_FLAG (IE0)
/**
 * 外部中断0触发方式控制位：
 * @param[in] mode:
 * -# INT_FALLING:下降沿触发
 * -# INT_LOWLEVEL:低电平触发
 */
#define INT0_TRIGGER_MODE_SET(status) (IT0 = (status))
/**@} */

typedef enum {
    SYSCLK_HRC_16M = 0U, /*!< 内部高速时钟：16MHz */
    SYSCLK_HRC_24M = 1U, /*!< 内部高速时钟：24MHz */
    SYSCLK_HRC_48M = 2U, /*!< 内部高速时钟：48MHz */
    SYSCLK_LRC     = 3U, /*!< 内部低频时钟：47KHz */
    SYSCLK_OSC     = 4U  /*!< 外部时钟：1MHz~48MHz */
} sysclk_t;

extern uint32_t g_u32SystemClock; /*!< 系统时钟全局变量 */

/**@name 外部函数
 * @{
 */
void    System_ConfigCLK(sysclk_t u8clkSel, uint8_t u8divSel, uint8_t u8waits);
uint8_t System_EnterSleep(void);
void    System_EnterIdle(void);
void    System_SoftReset(void);

/**@} */
#endif /*end _COMMON_H_*/
