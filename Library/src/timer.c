/**
 * @file      timer.c
 * @brief     TIMER模块驱动
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#include "timer.h"

/**
 * TIMER0配置模式
 * @param[in] u8mode  模式
 * -# TIMER01_MODE0  模式0，13位定时器/计数器
 * -# TIMER01_MODE1  模式1，16位定时器/计数器
 * -# TIMER01_MODE2  模式2，8位定时器/计数器，TL溢出后数值从TH自动重装载入TL
 * -# TIMER01_MODE3  模式3，TL0配置为8位定时器/计数器(TIMER0控制位)，TH0配置为8位定时器/计数器(TIMER1控制位)
 * @param[in] u8gate 门控制
 * -# TIMER01_TR_GATE:    TCON.TR0位为1时，开始计数
 * -# TIMER01_INT_TR_GATE:INT0为1且TR0为1时，开始计数
 * @param[in] u8cnt 时钟选择
 * -# TIMER01_ICLK:作为定时器0，选择的驱动时钟从内部时钟输入
 * -# TIMER01_TCLK:作为计数器0，选择的驱动时钟从引脚T0输入
 */
void TIMER0_ConfigMode(uint8_t u8mode, uint8_t u8gate, uint8_t u8cnt)
{
    TIMER0_TMOD_MODE_SET(u8mode);  /* 模式选择 */
    TIMER0_TMOD_GATE0_SET(u8gate); /* 门控制 */
    TIMER0_TMOD_CNT0_SET(u8cnt);   /* 选择的驱动时钟 */
}

/**
 * TIMER1配置模式
 * @param[in] u8mode  模式
 * -# TIMER01_MODE0  模式0，13位定时器/计数器
 * -# TIMER01_MODE1  模式1，16位定时器/计数器
 * -# TIMER01_MODE2  模式2，8位定时器/计数器，TL溢出后数值从TH自动重装载入TL
 * -# TIMER01_MODE3  模式3，TL0配置为8位定时器/计数器(TIMER0控制位)，TH0配置为8位定时器/计数器(TIMER1控制位)
 * @param[in] u8gate 门控制
 * -# TIMER01_TR_GATE:    TCON.TR0位为1时，开始计数
 * -# TIMER01_INT_TR_GATE:INT1为1且TR1为1时，开始计数
 * @param[in] u8cnt 时钟选择
 * -# TIMER01_ICLK:作为定时器0，选择的驱动时钟从内部时钟输入
 * -# TIMER01_TCLK:作为计数器0，选择的驱动时钟从引脚T1输入
 */
void TIMER1_ConfigMode(uint8_t u8mode, uint8_t u8gate, uint8_t u8cnt)
{
    TIMER1_TMOD_MODE_SET(u8mode);  /* 模式选择 */
    TIMER1_TMOD_GATE1_SET(u8gate); /* 门控制 */
    TIMER1_TMOD_CNT1_SET(u8cnt);   /* 选择的驱动时钟 */
}

/**
 * TIMER2配置输入捕获0通道
 * @param[in] u8trigger  捕获触发方式
 * -# TIMER2_CAPLS_FALLING:        下降沿
 * -# TIMER2_CAPLS_RISING:         上升沿
 * -# TIMER2_CAPLS_RISING_FALLING: 上升沿或下降沿
 * @param[in] u8filter 打开/关闭噪声滤波
 * -# DISABLE_CAP_FILTER:关闭输入捕获通道的噪声滤波
 * -# ENABLE_CAP_FILTER: 打开输入捕获通道的噪声滤波
 */
void TIMER2_ConfigCap0Mode(uint8_t u8trigger, uint8_t u8filter)
{
    TIMER2_CAPCON1_CAP0LS_SET(u8trigger);
    TIMER2_CAPCON0_CAPFEN0_SET(u8filter);
}

/**
 * TIMER2配置输入捕获1通道
 * @param[in] u8trigger  捕获触发方式
 * -# TIMER2_CAPLS_FALLING:        下降沿
 * -# TIMER2_CAPLS_RISING:         上升沿
 * -# TIMER2_CAPLS_RISING_FALLING: 上升沿或下降沿
 * @param[in] u8filter 打开/关闭噪声滤波
 * -# DISABLE_CAP_FILTER:关闭输入捕获通道的噪声滤波
 * -# ENABLE_CAP_FILTER: 打开输入捕获通道的噪声滤波
 */
void TIMER2_ConfigCap1Mode(uint8_t u8trigger, uint8_t u8filter)
{
    TIMER2_CAPCON1_CAP1LS_SET(u8trigger);
    TIMER2_CAPCON0_CAPFEN1_SET(u8filter);
}

/**
 * TIMER2配置输入捕获2通道
 * @param[in] u8trigger  捕获触发方式
 * -# TIMER2_CAPLS_FALLING:        下降沿
 * -# TIMER2_CAPLS_RISING:         上升沿
 * -# TIMER2_CAPLS_RISING_FALLING: 上升沿或下降沿
 * @param[in] u8filter 打开/关闭噪声滤波
 * -# DISABLE_CAP_FILTER:关闭输入捕获通道的噪声滤波
 * -# ENABLE_CAP_FILTER: 打开输入捕获通道的噪声滤波
 */
void TIMER2_ConfigCap2Mode(uint8_t u8trigger, uint8_t u8filter)
{
    TIMER2_CAPCON1_CAP2LS_SET(u8trigger);
    TIMER2_CAPCON0_CAPFEN2_SET(u8filter);
}

/**
 * TIMER2配置输入捕获3通道
 * @param[in] u8trigger  捕获触发方式
 * -# TIMER2_CAPLS_FALLING:        下降沿
 * -# TIMER2_CAPLS_RISING:         上升沿
 * -# TIMER2_CAPLS_RISING_FALLING: 上升沿或下降沿
 * @param[in] u8filter 打开/关闭噪声滤波
 * -# DISABLE_CAP_FILTER:关闭输入捕获通道的噪声滤波
 * -# ENABLE_CAP_FILTER: 打开输入捕获通道的噪声滤波
 */
void TIMER2_ConfigCap3Mode(uint8_t u8trigger, uint8_t u8filter)
{
    TIMER2_CAPCON1_CAP3LS_SET(u8trigger);
    TIMER2_CAPCON0_CAPFEN3_SET(u8filter);
}
