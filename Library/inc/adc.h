/**
 * @file      adc.h
 * @brief     ADC驱动配置
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#ifndef __ADC_H__
#define __ADC_H__

#include "WY8S9003xx.h"
#include "common.h"

/**@name ADC通道对应的PORT管脚
 * @{
 */
#define ADC_AIN0_PORT (PIO16CFG)
#define ADC_AIN1_PORT (PIO15CFG)
#define ADC_AIN2_PORT (PIO07CFG)
#define ADC_AIN3_PORT (PIO06CFG)
#define ADC_AIN4_PORT (PIO05CFG)
#define ADC_AIN5_PORT (PIO04CFG)
#define ADC_AIN6_PORT (PIO03CFG)
#define ADC_AIN7_PORT (PIO02CFG)
/**@} */

/**@name ADC控制寄存器ADCCON0
 * @{
 */
#define ENABLE_ADC  (ADCEN = 1) /*!< 使能ADC 转换电路 */
#define DISABLE_ADC (ADCEN = 0) /*!< 禁止ADC 转换电路 */
/**
 * ADC标志位
 * @return 1:ADC转换完成，此时可读取到当前ADC转换结果\n
 *         0：ADC未完成转换
 * @note 软件需要写0清除该位，当该位被清除后，下一轮转换才可以开始
 */
#define IS_ADC_IF_FLAG  (ADCIF)
#define CLR_ADC_IF_FLAG (ADCIF = 0)

#define ADC_SW_CVT_MODE (0)
#define ADC_HW_CVT_MODE (1)
/**
 * ADC转换启动信号选择位
 * @param[in] status:
 * -# ADC_SW_CVT_MODE:软件配置启动ADC转换
 * -# ADC_HW_CVT_MODE:硬件触发启动ADC转换
 */
#define ADC_ADCCON0_SC_SET(status) (ADCSC = (status))

#define ENABLE_ADC_SOFT_CVT        (ADCSWS = 1) /*!< 开始ADC软件转换 */
/**
 * 软件配置触发启动ADC转换控制位(读)
 * @return 1:ADC 模块工作中，不管触发启动的条件是什么，一旦ADC转换过中，该位读出值一直为1 \n
 *         0:ADC 模块空闲状态
 * @note ADC模块不空闲时，配置AD转换启动无效
 */
#define GET_ADC_ADCCON0_SWS (ADCSWS)

#define ADC_ENABLE_PWMFB    (1)
#define ADC_DISABLE_PWMFB   (0)
/**
 * ADC比较器结果控制PWM刹车使能位
 * @param[in] status:
 * -# ADC_DISABLE_PWMFB:禁止
 * -# ADC_ENABLE_PWMFB: 使能
 */
#define ADC_ADCCON0_FBEN_SET(status) (ADFBEN = status)

#define ADC_CR_GREATER_CMP_1         (0) /*!< 若ADRH，ADCRL>=ADCMP，则ADCMPO= 1，否则ADCMPO=0 */
#define ADC_CR_LESS_CMP_1            (1) /*!< 若ADRH，ADCRL<ADCMP，则ADCMPO=1，否则ADCMPO=0 */
/**
 * ADC比较器输出极性选择位
 * @param[in] status:
 * -# ADC_CR_GREATER_CMP_1:若ADRH，ADCRL>=ADCMP，则ADCMPO= 1，否则ADCMPO=0
 * -# ADC_CR_LESS_CMP_1:   若ADRH，ADCRL<ADCMP，则ADCMPO=1，否则ADCMPO=0
 */
#define ADC_ADCCON0_PPS_SET(status) (ADCMPPS = status)

/**
 * ADC比较器输出位
 * @return 1:比较结果为高\n
 *         0:比较结果为低
 * @note 该位输出ADC比较器输出的结果，每次ADC转换结束都会更新该位
 */
#define GET_ADC_ADCMPO (ADCMPO)
/**@} */

/**@name ADC控制器寄存器 ADCCON1
 * @{
 */
#define ADC_ADCCON1_HWSSEL_POS (5)
#define ADC_ADCCON1_HWSSEL_MSK (0x3 << ADC_ADCCON1_HWSSEL_POS)
#define ADC_ADCCON1_HWTSEL_POS (3)
#define ADC_ADCCON1_HWTSEL_MSK (0x3 << ADC_ADCCON1_HWTSEL_POS)
#define ADC_ADCCON1_CKS_POS    (0)
#define ADC_ADCCON1_CKS_MSK    (0x7 << ADC_ADCCON1_CKS_POS)

#define ADC_PWM0               (0x00)
#define ADC_PWM2               (0x01)
#define ADC_PWM4               (0x02)
#define ADC_STADC              (0x03)
/**
 * 触发启动ADC转换的硬件源选择
 * @param[in] mode:
 * -# ADC_PWM0
 * -# ADC_PWM2
 * -# ADC_PWM4
 * -# ADC_STADC
 */
#define ADC_ADCCON1_HWSSEL_SEL(mode)                                                                                   \
    (ADCCON1 = ((ADCCON1 & (~ADC_ADCCON1_HWSSEL_MSK)) | ((mode) << ADC_ADCCON1_HWSSEL_POS)))

#define ADC_PWMSTA_RISING  (0x00)
#define ADC_PWMSTA_FALLING (0x01)
#define ADC_PWM_MIDPOINT   (0x02)
#define ADC_PWM_ENDPOINT   (0x03)
/**
 * 触发启动ADC转换的硬件信号类型选择位
 * @param[in] mode:
 * -# ADC_PWM_RISING :    PWM0/2/4 或 STADC 脚的上升沿
 * -# ADC_PWM_FALLING:    PWM0/2/4 或 STADC 脚的下降沿
 * -# ADC_PWM_MIDPOINT  : PWM0/2/4周期的中点
 * -# ADC_PWM_ENDPOINT  : PWM0/2/4周期的终点
 */
#define ADC_ADCCON1_HWTSEL_SEL(mode)                                                                                   \
    (ADCCON1 = ((ADCCON1 & (~ADC_ADCCON1_HWTSEL_MSK)) | ((mode) << ADC_ADCCON1_HWTSEL_POS)))

#define ADC_DIV_2   (0x00)
#define ADC_DIV_4   (0x01)
#define ADC_DIV_8   (0x02)
#define ADC_DIV_16  (0x03)
#define ADC_DIV_32  (0x04)
#define ADC_DIV_64  (0x05)
#define ADC_DIV_128 (0x06)
#define ADC_DIV_256 (0x07)
/**
 * ADC转换时钟分频控制
 * @param[in] mode:
 * -# ADC_DIV_2  : Fsys/2
 * -# ADC_DIV_4  : Fsys/4
 * -# ADC_DIV_8  : Fsys/8
 * -# ADC_DIV_16 : Fsys/16
 * -# ADC_DIV_32 : Fsys/32
 * -# ADC_DIV_64 : Fsys/64
 * -# ADC_DIV_128: Fsys/128
 * -# ADC_DIV_256: Fsys/256
 */
#define ADC_ADCCON1_CKS_SEL(mode) (ADCCON1 = ((ADCCON1 & (~ADC_ADCCON1_CKS_MSK)) | ((mode) << ADC_ADCCON1_CKS_POS)))
/**@} */

/**@name ADC控制器寄存器 ADCCON2
 * @{
 */
#define ADC_ADCCON2_CHS_POS  (4)
#define ADC_ADCCON2_CHS_MSK  (0xF << ADC_ADCCON2_CHS_POS)
#define ADC_ADCCON2_VREF_POS (2)
#define ADC_ADCCON2_VREF_MSK (0x3 << ADC_ADCCON2_VREF_POS)
#define ADC_ADCCON2_DLY_POS  (0)
#define ADC_ADCCON2_DLY_MSK  (0x3 << ADC_ADCCON2_DLY_POS)

#define ADC_AIN0             (0x00)
#define ADC_AIN1             (0x01)
#define ADC_AIN2             (0x02)
#define ADC_AIN3             (0x03)
#define ADC_AIN4             (0x04)
#define ADC_AIN5             (0x05)
#define ADC_AIN6             (0x06)
#define ADC_AIN7             (0x07)
#define ADC_INTERNAL_CH      (0x08)
/**
 * ADC转换通道选择位
 * @param[in] mode:
 * -# ADC_AIN0----ADC_AIN7 分别对应通道0-7
 * -# ADC_INTERNAL_CH 内部通道
 */
#define ADC_ADCCON2_CHS_SEL(mode) (ADCCON2 = ((ADCCON2 & (~ADC_ADCCON2_CHS_MSK)) | ((mode) << ADC_ADCCON2_CHS_POS)))

#define ADC_INPUT_OPA_ADCIN0      (0x00)
#define ADC_INPUT_OPA_ADCIN1      (0x01)
#define ADC_INPUT_BAND_GAP        (0x02)
/**
 * ADC参考电压选择位
 * @param[in] mode:
 * -# ADC_INPUT_OPA_ADCIN0: 选择OPA_ADCIN0作为输入
 * -# ADC_INPUT_OPA_ADCIN1: 选择OPA_ADCIN1作为输入
 * -# ADC_INPUT_BAND_GAP  : 内部带隙电压1.2V
 */
#define ADC_ADCCON2_VREF_SEL(mode) (ADCCON2 = ((ADCCON2 & (~ADC_ADCCON2_VREF_MSK)) | ((mode) << ADC_ADCCON2_VREF_POS)))
/**@} */

/**@name ADC硬件触发延时数据寄存器
 * @{
 */
/**
 * 配置硬件触发延时
 * @param[in] u16Data: 硬件触发延时时间
 * @note 硬件延时共10bit ADCCON2[1:0]为高两位 ADDLYL[7:0]为低8位
 */
#define ADC_ADDLY_DATA(u16Data)                                                                                        \
    ADCCON2 = ((ADCCON2 & 0xFC) | (((u16Data) >> 8) & 0x03));                                                          \
    ADDLYL  = (u16Data) & 0xFF;
/**@} */

/**@name ADC 转换结果寄存器
 * @{
 */
/**
 * 获取ADC转换结果
 * @return 12bit转换结果 {ADCRH[7:0] ADCRL[3:0]}
 */
#define GET_ADC_CVT_12BIT ((ADCRH << 4) | (ADCRL & 0x0F))
/**@} */

/**@name ADC 比较值寄存器
 * @{
 */
/**
 * 配置ADC比较值
 * @param[in] u16Data: ADC比较值
 * @note 12bit比较值共12bit {ADCMPH[7:0] ADCMPL[3:0]}
 */
#define ADC_CMP_12BIT_SET(u16Data)                                                                                     \
    ADCMPH = ((u16Data) >> 4) & 0xFF;                                                                                  \
    ADCMPL = (u16Data) & 0x0F;
/**@} */

/**@name 外部函数
 * @{
 */
void     ADC_ConfigChannel(uint8_t u8channel, uint8_t u8div);
void     ADC_ConfigCMP(uint8_t u8FBStatus, uint8_t u8cmpSel);
void     ADC_ConfigHWCVT(uint8_t u8HWsource, uint8_t u8trigger, uint16_t u16delay);
void     ADC_ConfigSWCVT(void);
void     ADC_StartSWCVT(void);
uint16_t ADC_GetResultQueryMode(void);

/**@} */

#endif /* __ADC_H__ */
