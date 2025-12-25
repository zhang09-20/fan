/**
 * @file      wdt.c
 * @brief     WDT驱动
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#include "wdt.h"
#include "common.h"

/**
 * WDT初始化配置
 * @param[in] u8div  WDT溢出时长
 * -# WDT_DIV_2     WDT计数时钟为CLK_LRC的2分频
 * -# WDT_DIV_4     WDT计数时钟为CLK_LRC的4分频
 * -# WDT_DIV_8     WDT计数时钟为CLK_LRC的8分频
 * -# WDT_DIV_16    WDT计数时钟为CLK_LRC的16分频
 * -# WDT_DIV_32    WDT计数时钟为CLK_LRC的32分频
 * -# WDT_DIV_64    WDT计数时钟为CLK_LRC的64分频
 * -# WDT_DIV_128   WDT计数时钟为CLK_LRC的128分频
 * -# WDT_DIV_256   WDT计数时钟为CLK_LRC的256分频
 * -# WDT_DIV_512   WDT计数时钟为CLK_LRC的512分频
 * -# WDT_DIV_1024  WDT计数时钟为CLK_LRC的1024分频
 * @param[in] u8overRstFlag 溢出复位控制
 * -# DISABLE_OVER_RST:溢出后禁止复位
 * -# ENABLE_OVER_RST: 溢出后复位使能
 * @param[in] u8Mode WDT工作模式配置
 * -# WDT_IDLE_SLEEP_MODE    WDT在Idle模式和Sleep模式下均运行
 * -# WDT_IDLE_MODE          WDT在Idle模式下运行，在Sleep模式下停止运行
 * -# WDT_NONE_MODE          WDT在Idle模式和Sleep模式下均停止运行
 */
void WDT_ConfigMode(uint8_t u8div, uint8_t u8overRstFlag, uint8_t u8Mode)
{
    bit bitTemp;

    bitTemp = EA;
    EA      = 0;
    TA      = 0xAA;
    TA      = 0x55;
    WDT_WDTCON_PSDIV_SET(u8div); /* 溢出时间配置 */
    TA = 0xAA;
    TA = 0x55;
    WDT_WDTMOD_WDTRST_SET(u8overRstFlag); /* 溢出复位控制 */
    TA = 0xAA;
    TA = 0x55;
    WDT_WDTMOD_WDTMOD_SET(u8Mode); /* WDT工作模式配置 */
    TA = 0xAA;
    TA = 0x55;
    EA = bitTemp;
}

/**
 * WDT使能
 * @param[in] u8WDTFlag
 * -# DISABLE_WDT:WDT 运行禁止
 * -# ENABLE_WDT: WDT 运行使能
 */
void WDT_Run(uint8_t u8WDTFlag)
{
    bit bitTemp;

    bitTemp = EA;
    EA      = 0;
    TA      = 0xAA;
    TA      = 0x55;
    WDT_WDTCON_WDTEN_SET(u8WDTFlag);
    EA = bitTemp;
}

/**
 * WDT 计数清除位
 * @note 受TA保护
 * @note 清除看门狗计数后，需要等待看门狗定时器清零
 */
void WDT_ClearWDT(void)
{
    bit bitTemp;

    bitTemp = EA;
    EA      = 0;
    if (WDTCON & BIT7) {
        TA = 0xAA;
        TA = 0x55;
        WDTCON |= BIT6;
        while (WDTCON & BIT6)
            ; /* 等待看门狗定时器清零 */
    }
    EA = bitTemp;
}

/**
 * WDT 清除超时标志位
 * @note 受TA保护
 */
void WDT_ClearTF(void)
{
    bit bitTemp;

    bitTemp = EA;
    EA      = 0;
    TA      = 0xAA;
    TA      = 0x55;
    WDTCON &= ~BIT5;
    EA = bitTemp;
}
