/**
 * @file      common.c
 * @brief     公共调用函数
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#include "common.h"

uint32_t g_u32SystemClock = HRC_48M_VALUE; /*!< 系统时钟全局变量 */

/**
 * 配置系统时钟
 * @param[in] u8clkSel 时钟源选择
 * -# SYSCLK_HRC_16M
 * -# SYSCLK_HRC_24M
 * -# SYSCLK_HRC_48M
 * -# SYSCLK_LRC
 * -# SYSCLK_OSC
 * @param[in] u8divSel 时钟分频系数
 * -# CLK_DIV_NOT
 * -# CLK_DIV_2
 * -# CLK_DIV_4
 * -# CLK_DIV_8
 * -# CLK_DIV_16
 * -# CLK_DIV_32
 * -# CLK_DIV_64
 * -# CLK_DIV_128
 * @param[in] u8waits 闪存取指访问等待周期
 * -# WAITS_LOWER16M   主频16MHz及以下等待周期配置
 * -# WAITS_24M        主频24MHz等待周期配置
 * -# WAITS_48M        主频48MHz等待周期配置
 *
 * @note 当u8divSel = 0时，CLK_sys为时钟源频率
 * @note 当u8divSel !=0时，CLK_sys = 时钟源频率/(2 * u8divSel)
 * @note 如果选择CLKSEL_OSC模式，需要在OSC_VALUE中更改外部时钟频率
 * @note 若系统时钟从高频切到低频，先配置CLKCON再配置WAITSTS； 若系统时钟从低频切到高频，先配置WAITSTS再配置CLKCON
 */
void System_ConfigCLK(sysclk_t u8clkSel, uint8_t u8divSel, uint8_t u8waits)
{
    /* 如果选择外部时钟，需等待MCU内部配置外部晶振模块稳定后，再进行时钟配置 */
    if (u8clkSel == SYSCLK_OSC) {
        while (0 == IS_OSCST_FLAG)
            ;
    }

    if (u8waits > GET_SYS_CLK_WAITS) {
        SYS_CLK_WAITS(u8waits);
    }

    switch (u8clkSel) {
    case SYSCLK_HRC_16M:
        SYS_CLK_SEL(CLKSEL_HRC); /* 系统时钟源来自HRC */
        SYS_CLK_PER(CLK_HRC_16MHz);
        g_u32SystemClock = HRC_16M_VALUE;
        break;
    case SYSCLK_HRC_24M:
        SYS_CLK_SEL(CLKSEL_HRC); /* 系统时钟源来自HRC */
        SYS_CLK_PER(CLK_HRC_24MHz);
        g_u32SystemClock = HRC_24M_VALUE;
        break;
    case SYSCLK_HRC_48M:
        SYS_CLK_SEL(CLKSEL_HRC); /* 系统时钟源来自HRC */
        SYS_CLK_PER(CLK_HRC_48MHz);
        g_u32SystemClock = HRC_48M_VALUE;
        break;
    case SYSCLK_LRC:
        SYS_CLK_SEL(CLKSEL_LRC); /* 系统时钟源来自LRC */
        g_u32SystemClock = LRC_VALUE;
        break;
    case SYSCLK_OSC:
        SYS_CLK_SEL(CLKSEL_OSC); /* 系统时钟源来自外部输入 */
        g_u32SystemClock = OSC_VALUE;
        break;
    }

    SYS_CLK_DIV(u8divSel); /* 配置分频系数 */

    if (u8waits < GET_SYS_CLK_WAITS) {
        SYS_CLK_WAITS(u8waits);
    }

    g_u32SystemClock >>= u8divSel; /* 更新g_u32SystemClock */
}

/**
 * 进入睡眠模式
 * @return 0:进入失败 1:进入成功
 * @note 当SFRS.SYSD为1时才可进入sleep模式
 */
uint8_t System_EnterSleep(void)
{
    if (0x00 == IS_SYSD_FLAG) {
        return 0;
    }
    _nop_();
    PCON |= BIT1;
    _nop_();
    _nop_();
    _nop_();
    return 1;
}

/**
 * 进入空闲模式
 */
void System_EnterIdle(void)
{
    _nop_();
    PCON |= BIT0;
    _nop_();
}

/**
 * 软件复位
 */
void System_SoftReset(void)
{
    EA   = 0;
    TA   = 0xAA;
    TA   = 0x55;
    SFRS = 0x01;
    TA   = 0xAA;
    TA   = 0x55;
    CHPCON |= BIT7;
}
