/**
 * @file      delay.c
 * @brief     精确延时函数
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#include "common.h"
#include "timer.h"
#include "delay.h"

/**
 * @brief 使用Timer0产生1ms延时
 *
 * @param u8Xms 延时时间，单位为ms
 * @note 入参为uint8_t型，因此最大支持255ms延迟
 */
void Timer0_Delay_ms(uint8_t u8Xms)
{
    TIMER0_TMOD_MODE_SET(TIMER01_MODE1); /* 模式选择 */
    ENABLE_TIMER0;                       /* TIMER0启动 */
    while (u8Xms != 0)                   /* 1次循环为1ms */
    {
        TH0 = 0xE0;
        TL0 = 0xC0;
        while (IS_TIME0_OVER_FLAG != 1)
            ;
        CLR_TIME0_OVER_FLAG;
        u8Xms--;
    }
    DISABLE_TIMER0; /* TIMER0关闭 */
}
