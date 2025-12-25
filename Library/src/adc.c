/**
 * @file      adc.c
 * @brief     ADC模块驱动
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#include "adc.h"
#include "iap.h"

/**
 * ADC配置硬件转换模式
 * @param[in] u8channel ADC转换通道
 * -# ADC_AIN0
 * -# ADC_AIN1
 * -# ADC_AIN2
 * -# ADC_AIN3
 * -# ADC_AIN4
 * -# ADC_AIN5
 * -# ADC_AIN6
 * -# ADC_AIN7
 * -# ADC_INTERNAL_CH
 * @param[in] u8div 时钟分频
 * -# ADC_DIV_2 : Fsys/2
 * -# ADC_DIV_4 : Fsys/4
 * -# ADC_DIV_8 : Fsys/8
 * -# ADC_DIV_16: Fsys/16
 */
void ADC_ConfigChannel(uint8_t u8channel, uint8_t u8div)
{
    switch (u8channel) {
    case ADC_AIN0:
        PORT_SET_MUX(ADC_AIN0_PORT, ANALOG_MUX_MODE);
        ADC_ADCCON2_CHS_SEL(ADC_AIN0);
        break;
    case ADC_AIN1:
        PORT_SET_MUX(ADC_AIN1_PORT, ANALOG_MUX_MODE);
        ADC_ADCCON2_CHS_SEL(ADC_AIN1);
        break;
    case ADC_AIN2:
        PORT_SET_MUX(ADC_AIN2_PORT, ANALOG_MUX_MODE);
        ADC_ADCCON2_CHS_SEL(ADC_AIN2);
        break;
    case ADC_AIN3:
        PORT_SET_MUX(ADC_AIN3_PORT, ANALOG_MUX_MODE);
        ADC_ADCCON2_CHS_SEL(ADC_AIN3);
        break;
    case ADC_AIN4:
        PORT_SET_MUX(ADC_AIN4_PORT, ANALOG_MUX_MODE);
        ADC_ADCCON2_CHS_SEL(ADC_AIN4);
        break;
    case ADC_AIN5:
        PORT_SET_MUX(ADC_AIN5_PORT, ANALOG_MUX_MODE);
        ADC_ADCCON2_CHS_SEL(ADC_AIN5);
        break;
    case ADC_AIN6:
        PORT_SET_MUX(ADC_AIN6_PORT, ANALOG_MUX_MODE);
        ADC_ADCCON2_CHS_SEL(ADC_AIN6);
        break;
    case ADC_AIN7:
        PORT_SET_MUX(ADC_AIN7_PORT, ANALOG_MUX_MODE);
        ADC_ADCCON2_CHS_SEL(ADC_AIN7);
        break;
    case ADC_INTERNAL_CH:
        ADC_ADCCON2_CHS_SEL(ADC_INTERNAL_CH);
        break;
    default:
        break;
    }
    ADC_ADCCON1_CKS_SEL(u8div); /* 时钟分频控制 */
}
/**
 * ADC配置比较器模式
 * @param[in] u8FBStatus ADC比较器结果控制PWM刹车使能控制
 * -# ADC_DISABLE_PWMFB:禁止
 * -# ADC_ENABLE_PWMFB: 使能
 * @param[in] u8cmpSel ADC比较器输出极性选择位
 * -# ADC_CR_GREATER_CMP_1:若ADRH，ADCRL>=ADCMP，则ADCMPO= 1，否则ADCMPO=0
 * -# ADC_CR_LESS_CMP_1:   若ADRH，ADCRL<ADCMP，则ADCMPO=1，否则ADCMPO=0
 */
void ADC_ConfigCMP(uint8_t u8FBStatus, uint8_t u8cmpSel)
{
    ADC_ADCCON0_FBEN_SET(u8FBStatus);
    ADC_ADCCON0_PPS_SET(u8cmpSel);
}

/**
 * ADC配置硬件转换模式
 * @param[in] u8HWsource 触发启动ADC转换的硬件源选择
 * -# ADC_PWM0
 * -# ADC_PWM2
 * -# ADC_PWM4
 * -# ADC_STADC
 * @param[in] u8trigger 硬件触发类型
 * -# ADC_PWMSTA_RISING :    PWM0/2/4 或 STADC 脚的上升沿
 * -# ADC_PWMSTA_FALLING:    PWM0/2/4 或 STADC 脚的下降沿
 * -# ADC_PWM_MIDPOINT  : PWM0/2/4周期的中点
 * -# ADC_PWM_ENDPOINT  : PWM0/2/4周期的终点
 * @param[in] u8delay 硬件延时 : 共10bit ADCCON2[1:0]为高两位 ADDLYL[7:0]为低8位
 */
void ADC_ConfigHWCVT(uint8_t u8HWsource, uint8_t u8trigger, uint16_t u16delay)
{
    ADC_ADCCON0_SC_SET(ADC_HW_CVT_MODE); /* 选择硬件转换模式 */
    ADC_ADCCON1_HWSSEL_SEL(u8HWsource);  /* 触发启动ADC转换的硬件源选择 */
    ADC_ADCCON1_HWTSEL_SEL(u8trigger);   /* 硬件触发类型 */
    ADCCON2 = (ADCCON2 & 0xFC) | ((u16delay >> 8) & 0x03);
    ADDLYL  = (u16delay) & 0xFF;
}

/**
 * ADC配置软件转换模式
 */
void ADC_ConfigSWCVT(void)
{
    ADC_ADCCON0_SC_SET(ADC_SW_CVT_MODE); /* 选择软件转换模式 */
}

/**
 * 开启软件转换
 * @note 开启转换之前必须等待ADC模块空闲
 */
void ADC_StartSWCVT(void)
{
    while (1 == GET_ADC_ADCCON0_SWS)
        ;
    ENABLE_ADC_SOFT_CVT; /* 开始ADC软件转换 */
}
/**
 * 在查询模式下获取ADC转换结果
 * @return ADC转换结果(位宽:12bit)
 */
uint16_t ADC_GetResultQueryMode(void)
{
    while (0 == IS_ADC_IF_FLAG)
        ;
    CLR_ADC_IF_FLAG; /* 清除转换完成标志 */
    return GET_ADC_CVT_12BIT;
}
