/**
 * @file      pwm.c
 * @brief     PWM驱动
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#include "pwm.h"
#include "common.h"

/**
 * PWM中断配置
 * @param[in] u8pwmNum  PWM通道
 * -# PWM_0 - PWM_5
 * @param[in] u8trigger 中断触发方式
 * -# PWM_FALLING_MODE    PWM0/1/2/3/4/5管脚下降沿
 * -# PWM_RISING_MODE     PWM0/1/2/3/4/5管脚上升沿
 * -# PWM_MIDPOINT_MODE   每个PWM周期的中点
 * -# PWM_ENDPOINT_MODE   每个PWM周期的终点
 * @note 中心点中断方式或终点中断仅适用于PWM中心对齐模式
 */
void PWM_ConfigINT(uint8_t u8pwmNum, uint8_t u8trigger)
{
    PWM_PWMINTC_INTSEL_SET(u8pwmNum); /* 产生中断通道配置 */
    PWM_PWMINTC_INTTY_SET(u8trigger); /* 选择管脚产生中断触发方式 */
}

/**
 * PWM通道故障后输出的电平
 * @param[in] u8pwmNum  PWM通道
 * -# PWM_0 - PWM_5
 * @param[in] u8pwmLevel 输出电平
 * -# OUTPUT_HIGH
 * -# OUTPUT_LOW
 */
void PWM_ConfigFBOutputLevel(uint8_t u8pwmNum, uint8_t u8pwmLevel)
{
    switch (u8pwmNum) {
    case PWM_0:
        PWM_PWMFBKD_0_SET(u8pwmLevel);
        break;
    case PWM_1:
        PWM_PWMFBKD_1_SET(u8pwmLevel);
        break;
    case PWM_2:
        PWM_PWMFBKD_2_SET(u8pwmLevel);
        break;
    case PWM_3:
        PWM_PWMFBKD_3_SET(u8pwmLevel);
        break;
    case PWM_4:
        PWM_PWMFBKD_4_SET(u8pwmLevel);
        break;
    case PWM_5:
        PWM_PWMFBKD_5_SET(u8pwmLevel);
        break;
    default:
        break;
    }
}

/**
 * PWM配置掩码输出电平
 * @param[in] u8pwmNum  PWM通道
 * -# PWM_0 - PWM_5
 * @param[in] u8pwmLevel  输出电平
 * -# OUTPUT_HIGH
 * -# OUTPUT_LOW
 */
void PWM_ConfigMASKOutputLevel(uint8_t u8pwmNum, uint8_t u8pwmLevel)
{
    switch (u8pwmNum) {
    case PWM_0:
        PWM_PWMMASKD_0_SET(u8pwmLevel);
        break;
    case PWM_1:
        PWM_PWMMASKD_1_SET(u8pwmLevel);
        break;
    case PWM_2:
        PWM_PWMMASKD_2_SET(u8pwmLevel);
        break;
    case PWM_3:
        PWM_PWMMASKD_3_SET(u8pwmLevel);
        break;
    case PWM_4:
        PWM_PWMMASKD_4_SET(u8pwmLevel);
        break;
    case PWM_5:
        PWM_PWMMASKD_5_SET(u8pwmLevel);
        break;
    default:
        break;
    }
}

/**
 * PWM载入配置
 * @note
 * 该位写1，硬件自动在当前一个PWM周期输出结束时，载入新的配置值。更改的配置值，如周期、占空比、死区、模式等将在下一个周期起效
 */
void PWM_StartLoad(void)
{
    ENABLE_PWM_LOAD;

    /* 等待load完成 */
    while (1 == IS_PWM_LOAD_FLAG)
        ;
}
