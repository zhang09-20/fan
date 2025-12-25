/**
 * @file      opa.h
 * @brief     OPA驱动配置
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#ifndef __OPA_H__
#define __OPA_H__

#include "WY8S9003xx.h"
#include "common.h"

#define OPA_OPA0CON_OP0PS_POS   (0)
#define OPA_OPA0CON_OP0PS_MSK   (0x1 << OPA_OPA0CON_OP0PS_POS)
#define OPA_OPA0CON_OP0FIL_POS  (5)
#define OPA_OPA0CON_OP0FIL_MSK  (0x1 << OPA_OPA0CON_OP0FIL_POS)
#define OPA_OPA0CON_OP0DOUT_POS (6)
#define OPA_OPA0CON_OP0DOUT_MSK (0x1 << OPA_OPA0CON_OP0DOUT_POS)
#define OPA_OPA0CON_OP0EN_POS   (7)
#define OPA_OPA0CON_OP0EN_MSK   (0x1 << OPA_OPA0CON_OP0EN_POS)

#define OPA_OPA1CON_OP1PS_POS   (0)
#define OPA_OPA1CON_OP1PS_MSK   (0x1 << OPA_OPA1CON_OP1PS_POS)
#define OPA_OPA1CON_OP1FIL_POS  (5)
#define OPA_OPA1CON_OP1FIL_MSK  (0x1 << OPA_OPA1CON_OP1FIL_POS)
#define OPA_OPA1CON_OP1DOUT_POS (6)
#define OPA_OPA1CON_OP1DOUT_MSK (0x1 << OPA_OPA1CON_OP1DOUT_POS)
#define OPA_OPA1CON_OP1EN_POS   (7)
#define OPA_OPA1CON_OP1EN_MSK   (0x1 << OPA_OPA1CON_OP1EN_POS)

#define OPA_MODE_OPA            (0)                                 /* 运放模式 */
#define OPA_MODE_ACMP           (1)                                 /* 比较模式 */

#define OPA_POSITIVE_P          (0)                                 /* 选择OP0_P作为正端输入 */

#define OPA0_ENABLE             (OPA0CON |= OPA_OPA0CON_OP0EN_MSK)  /* 使能OPA0 */
#define OPA0_DISABLE            (OPA0CON &= ~OPA_OPA0CON_OP0EN_MSK) /* 禁止OPA0 */

/**
 * 获取OPA0比较模式输出
 * @return 1:正端电压高于负端电压
 *         0:正端电压低于负端电压
 */
#define OPA0_GET_OUTPUT (((OPA0CON & OPA_OPA0CON_OP0EN_MSK) >> OPA_OPA0CON_OP0EN_POS))

/**
 * OPA1工作模式选择
 * @param[in] mode:
 * -# OPA_MODE_OPA:运放模式
 * -# OPA_MODE_ACMP:比较模式，比较结果由OPA1_CON1.OP1DOUT观测
 */
#define OPA0_SET_RUN_Mode(mode) (OPA0CON = ((OPA0CON & (~OPA_OPA0CON_OP0FIL_MSK)) | ((mode) << OPA_OPA0CON_OP0FIL_POS)))

/**
 * OPA0正端通道选择位
 * @param[in] source:
 * -# OPA_POSITIVE_P:选择OP0_P作为正端输入
 */
#define OPA0_SET_POSITIVE(source)                                                                                      \
    (OPA0CON = ((OPA0CON & (~OPA_OPA0CON_OP0FIL_MSK)) | ((source) << OPA_OPA0CON_OP0FIL_POS)))

#define OPA1_ENABLE  (OPA1CON |= OPA_OPA1CON_OP1EN_MSK)  /* 使能OPA1 */
#define OPA1_DISABLE (OPA1CON &= ~OPA_OPA1CON_OP1EN_MSK) /* 禁止OPA1 */

/**
 * 获取OPA1比较模式输出
 * @return 1:正端电压高于负端电压
 *         0:正端电压低于负端电压
 */
#define OPA1_GET_OUTPUT (((OPA1CON & OPA_OPA1CON_OP1EN_MSK) >> OPA_OPA1CON_OP1EN_POS))

/**
 * OPA1工作模式选择
 * @param[in] mode:
 * -# OPA_MODE_OPA:运放模式
 * -# OPA_MODE_ACMP:比较模式，比较结果由OPA1_CON1.OP1DOUT观测
 */
#define OPA1_SET_RUN_Mode(mode) (OPA1CON = ((OPA1CON & (~OPA_OPA1CON_OP1FIL_MSK)) | ((mode) << OPA_OPA1CON_OP1FIL_POS)))

/**
 * OPA1正端通道选择位
 * @param[in] source:
 * -# OPA_POSITIVE_P:选择OP1_P作为正端输入
 */
#define OPA1_SET_POSITIVE(source)                                                                                      \
    (OPA1CON = ((OPA1CON & (~OPA_OPA1CON_OP1FIL_MSK)) | ((source) << OPA_OPA1CON_OP1FIL_POS)))

#define OPA_INP0 (0)
#define OPA_INP1 (1)

#define OPA_INN0 (0)
#define OPA_INN1 (1)

#define OPA_OUT0 (0)
#define OPA_OUT1 (1)
/**@name OPA正端输入通道对应的PORT管脚
 * @{
 */
#define OPA_INP_PORT0 (PIO06CFG)
#define OPA_INP_PORT1 (PIO12CFG)

/**@name OPA负端输入通道对应的PORT管脚
 * @{
 */
#define OPA_INN_PORT0 (PIO05CFG)
#define OPA_INN_PORT1 (PIO13CFG)

/**@name OPA输出通道对应的PORT管脚
 * @{
 */
#define OPA_OUT_PORT0 (PIO04CFG)
#define OPA_OUT_PORT1 (PIO25CFG)

void OPA_ConfigChannel(uint8_t u8channel_P, uint8_t u8channel_N, uint8_t u8channel_O);

#endif /* __OPA_H__ */
