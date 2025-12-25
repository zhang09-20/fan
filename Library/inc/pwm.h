/**
 * @file      pwm.h
 * @brief     PWM驱动配置
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#ifndef __PWM_H__
#define __PWM_H__

#include "WY8S9003xx.h"

#define PWM_0 (0)
#define PWM_1 (1)
#define PWM_2 (2)
#define PWM_3 (3)
#define PWM_4 (4)
#define PWM_5 (5)

/**@name PWM控制寄存器-PWMCON
 * @{
 */
#define PWM_PWMCON_PWMRUN_POS  (7)
#define PWM_PWMCON_PWMRUN_MSK  (0x1 << PWM_PWMCON_PWMRUN_POS)
#define PWM_PWMCON_PWMMODE_POS (5)
#define PWM_PWMCON_PWMMODE_MSK (0x3 << PWM_PWMCON_PWMMODE_POS)
#define PWM_PWMCON_FBINEN_POS  (4)
#define PWM_PWMCON_FBINEN_MSK  (0x1 << PWM_PWMCON_FBINEN_POS)
#define PWM_PWMCON_CNTTYPE_POS (3)
#define PWM_PWMCON_CNTTYPE_MSK (0x1 << PWM_PWMCON_CNTTYPE_POS)
#define PWM_PWMCON_PWMSEL_POS  (0)
#define PWM_PWMCON_PWMSEL_MSK  (0x1 << PWM_PWMCON_PWMSEL_POS)

#define ENABLE_PWM             (PWMCON |= PWM_PWMCON_PWMRUN_MSK)  /*!< 使能PWM */
#define DISABLE_PWM            (PWMCON &= ~PWM_PWMCON_PWMRUN_MSK) /*!< 禁止PWM */

#define PWM_IMDEPENDENT_MODE   (0x00)                             /*!< 独立模式 */
#define PWM_COMPLEMENTARY_MODE (0x01)                             /*!< 互补模式 */
#define PWM_SYNC_MODE          (0x02)                             /*!< 同步模式 */
/**
 * WDT 时钟预分频选择位
 * @param[in] mode
 * -# PWM_IMDEPENDENT_MODE    独立模式
 * -# PWM_COMPLEMENTARY_MODE  互补模式
 * -# PWM_SYNC_MODE           同步模式
 */
#define PWM_PWMCON_PWMMODE_SET(mode)                                                                                   \
    (PWMCON = ((PWMCON & (~PWM_PWMCON_PWMMODE_MSK)) | ((mode) << PWM_PWMCON_PWMMODE_POS)))

#define ENABLE_PWM_FB       (PWMCON |= PWM_PWMCON_FBINEN_MSK)  /*!< 使能FB管脚输入使能PWM故障刹车功能 */
#define DISABLE_PWM_FB      (PWMCON &= ~PWM_PWMCON_FBINEN_MSK) /*!< 禁止FB管脚输入使能PWM故障刹车功能 */

#define PWM_EDGE_ALIGN_MODE (0x00)                             /*!< 边沿对齐 */
#define PWM_Mid_ALIGN_MODE  (0x01)                             /*!< 中心对齐 */
/**
 * PWM计数对齐方式选择位
 * @param[in] mode
 * -# PWM_EDGE_ALIGN_MODE:边沿对齐方式
 * -# PWM_Mid_ALIGN_MODE:中心对齐方式。
 */
#define PWM_CNTTYPE_SET(mode) (PWMCON = ((PWMCON & (~PWM_PWMCON_CNTTYPE_MSK)) | ((mode) << PWM_PWMCON_CNTTYPE_POS)))

#define PWM_CLK_PSC           (0)
#define PWM_CLK_TIMER1        (1)
/**
 * PWM通道时钟CLK_pwm选择控制位
 * @param[in] status
 * -# PWM_CLK_PSC:CLK_pwm与CLK_pwmpsc相等
 * -# PWM_CLK_TIMER1:CLK_pwm与Timer1_out相等，来自Timer1输出
 */
#define PWM_CLKSEL_SET(status) (PWMCON = ((PWMCON & (~PWM_PWMCON_PWMSEL_MSK)) | ((status) << PWM_PWMCON_PWMSEL_POS)))
/**@} */

/**@name PWM时钟预分频控制寄存器-PWMPSC
 * @{
 */
/**
 * PWM通道预分频时钟CLK_pwmpsc输出控制位
 * @param[in] u8data
 * -# 00 = 预分频时钟停止
 * -# 其他 = 系统时钟CLK_sys的（PWMPSC+1）分频
 */
#define PWM_PWMPSC_DATA(u8data) (PWMPSC = (u8data))
/**@} */

/**@name PWM计数器模式控制寄存器-PWMCNTM
 * @{
 */
#define PWM_PWMCNTM_5_POS (5)
#define PWM_PWMCNTM_5_MSK (0x1 << PWM_PWMCNTM_5_POS)
#define PWM_PWMCNTM_4_POS (4)
#define PWM_PWMCNTM_4_MSK (0x1 << PWM_PWMCNTM_4_POS)
#define PWM_PWMCNTM_3_POS (3)
#define PWM_PWMCNTM_3_MSK (0x1 << PWM_PWMCNTM_3_POS)
#define PWM_PWMCNTM_2_POS (2)
#define PWM_PWMCNTM_2_MSK (0x1 << PWM_PWMCNTM_2_POS)
#define PWM_PWMCNTM_1_POS (1)
#define PWM_PWMCNTM_1_MSK (0x1 << PWM_PWMCNTM_1_POS)
#define PWM_PWMCNTM_0_POS (0)
#define PWM_PWMCNTM_0_MSK (0x1 << PWM_PWMCNTM_0_POS)

#define ONESHOT_MODE      (0)
#define AUTOLOAD_MODE     (1)

/**
 * PWM通道5计数器模式控制位
 * @param[in] status
 * -# ONESHOT_MODE:One-shot模式
 * -# AUTOLOAD_MODE:自动加载模式
 */
#define PWM5_CNT_MODE_SET(status) (PWMCNTM = ((PWMCNTM & (~PWM_PWMCNTM_5_MSK)) | ((status) << PWM_PWMCNTM_5_POS)))

/**
 * PWM通道4计数器模式控制位
 * @param[in] status
 * -# ONESHOT_MODE:One-shot模式
 * -# AUTOLOAD_MODE:自动加载模式
 */
#define PWM4_CNT_MODE_SET(status) (PWMCNTM = ((PWMCNTM & (~PWM_PWMCNTM_4_MSK)) | ((status) << PWM_PWMCNTM_4_POS)))

/**
 * PWM通道3计数器模式控制位
 * @param[in] status
 * -# ONESHOT_MODE:One-shot模式
 * -# AUTOLOAD_MODE:自动加载模式
 */
#define PWM3_CNT_MODE_SET(status) (PWMCNTM = ((PWMCNTM & (~PWM_PWMCNTM_3_MSK)) | ((status) << PWM_PWMCNTM_3_POS)))

/**
 * PWM通道2计数器模式控制位
 * @param[in] status
 * -# ONESHOT_MODE:One-shot模式
 * -# AUTOLOAD_MODE:自动加载模式
 */
#define PWM2_CNT_MODE_SET(status) (PWMCNTM = ((PWMCNTM & (~PWM_PWMCNTM_2_MSK)) | ((status) << PWM_PWMCNTM_2_POS)))

/**
 * PWM通道1计数器模式控制位
 * @param[in] status
 * -# ONESHOT_MODE:One-shot模式
 * -# AUTOLOAD_MODE:自动加载模式
 */
#define PWM1_CNT_MODE_SET(status) (PWMCNTM = ((PWMCNTM & (~PWM_PWMCNTM_1_MSK)) | ((status) << PWM_PWMCNTM_1_POS)))

/**
 * PWM通道0计数器模式控制位
 * @param[in] status
 * -# ONESHOT_MODE:One-shot模式
 * -# AUTOLOAD_MODE:自动加载模式
 */
#define PWM0_CNT_MODE_SET(status) (PWMCNTM = ((PWMCNTM & (~PWM_PWMCNTM_0_MSK)) | ((status) << PWM_PWMCNTM_0_POS)))

/**@} */
/**@name PWM计数器使能控制寄存器-PWMCNTE
 * @{
 */
#define PWM_PWMCNTE_5_POS (5)
#define PWM_PWMCNTE_5_MSK (0x1 << PWM_PWMCNTE_5_POS)
#define PWM_PWMCNTE_4_POS (4)
#define PWM_PWMCNTE_4_MSK (0x1 << PWM_PWMCNTE_4_POS)
#define PWM_PWMCNTE_3_POS (3)
#define PWM_PWMCNTE_3_MSK (0x1 << PWM_PWMCNTE_3_POS)
#define PWM_PWMCNTE_2_POS (2)
#define PWM_PWMCNTE_2_MSK (0x1 << PWM_PWMCNTE_2_POS)
#define PWM_PWMCNTE_1_POS (1)
#define PWM_PWMCNTE_1_MSK (0x1 << PWM_PWMCNTE_1_POS)
#define PWM_PWMCNTE_0_POS (0)
#define PWM_PWMCNTE_0_MSK (0x1 << PWM_PWMCNTE_0_POS)

#define ENABLE_PWM0_CNT   (PWMCNTE |= PWM_PWMCNTE_0_MSK)  /*!< 使能PWM0计数器 */
#define DISABLE_PWM0_CNT  (PWMCNTE &= ~PWM_PWMCNTE_0_MSK) /*!< 禁止PWM0计数器 */
#define ENABLE_PWM1_CNT   (PWMCNTE |= PWM_PWMCNTE_1_MSK)  /*!< 使能PWM1计数器 */
#define DISABLE_PWM1_CNT  (PWMCNTE &= ~PWM_PWMCNTE_1_MSK) /*!< 禁止PWM1计数器 */
#define ENABLE_PWM2_CNT   (PWMCNTE |= PWM_PWMCNTE_2_MSK)  /*!< 使能PWM2计数器 */
#define DISABLE_PWM2_CNT  (PWMCNTE &= ~PWM_PWMCNTE_2_MSK) /*!< 禁止PWM2计数器 */
#define ENABLE_PWM3_CNT   (PWMCNTE |= PWM_PWMCNTE_3_MSK)  /*!< 使能PWM3计数器 */
#define DISABLE_PWM3_CNT  (PWMCNTE &= ~PWM_PWMCNTE_3_MSK) /*!< 禁止PWM3计数器 */
#define ENABLE_PWM4_CNT   (PWMCNTE |= PWM_PWMCNTE_4_MSK)  /*!< 使能PWM4计数器 */
#define DISABLE_PWM4_CNT  (PWMCNTE &= ~PWM_PWMCNTE_4_MSK) /*!< 禁止PWM4计数器 */
#define ENABLE_PWM5_CNT   (PWMCNTE |= PWM_PWMCNTE_5_MSK)  /*!< 使能PWM5计数器 */
#define DISABLE_PWM5_CNT  (PWMCNTE &= ~PWM_PWMCNTE_5_MSK) /*!< 禁止PWM5计数器 */
/**@} */

/**@name PWM周期数据寄存器-PWMPH  PWMPL
 * @{
 */
/**
 * PWM通道周期数据PERIOD寄存器
 * @param[in] dataH PWM通道周期数据PERIOD寄存器高8位
 * @param[in] dataL PWM通道周期数据PERIOD寄存器低8位
 */
#define PWM_PWMPHL_DATA(dataH, dataL)                                                                                  \
    PWMPH = (dataH);                                                                                                   \
    PWMPL = dataL;
/**@} */
/**@name PWM比较数据寄存器-PWMDxL PWMDxH
 * @{
 */
/**
 * PWM比较数据寄存器
 * @param[in] dataH PWM通道0比较数据（占空比数据)CMP0寄存器高8位
 * @param[in] dataL PWM通道0比较数据（占空比数据)CMP0寄存器低8位
 */
#define PWM_PWMD0HL_DATA(dataH, dataL)                                                                                 \
    PWMD0H = (dataH);                                                                                                  \
    PWMD0L = (dataL);
/**
 * PWM比较数据寄存器
 * @param[in] dataH PWM通道1比较数据（占空比数据)CMP1寄存器高8位
 * @param[in] dataL PWM通道1比较数据（占空比数据)CMP1寄存器低8位
 */
#define PWM_PWMD1HL_DATA(dataH, dataL)                                                                                 \
    PWMD1H = (dataH);                                                                                                  \
    PWMD1L = (dataL);
/**
 * PWM比较数据寄存器
 * @param[in] dataH PWM通道2比较数据（占空比数据)CMP2寄存器高8位
 * @param[in] dataL PWM通道2比较数据（占空比数据)CMP2寄存器低8位
 */
#define PWM_PWMD2HL_DATA(dataH, dataL)                                                                                 \
    PWMD2H = (dataH);                                                                                                  \
    PWMD2L = (dataL);
/**
 * PWM比较数据寄存器
 * @param[in] dataH PWM通道3比较数据（占空比数据)CMP3寄存器高8位
 * @param[in] dataL PWM通道3比较数据（占空比数据)CMP3寄存器低8位
 */
#define PWM_PWMD3HL_DATA(dataH, dataL)                                                                                 \
    PWMD3H = (dataH);                                                                                                  \
    PWMD3L = (dataL);
/**
 * PWM比较数据寄存器
 * @param[in] dataH PWM通道4比较数据（占空比数据)CMP4寄存器高8位
 * @param[in] dataL PWM通道4比较数据（占空比数据)CMP4寄存器低8位
 */
#define PWM_PWMD4HL_DATA(dataH, dataL)                                                                                 \
    PWMD4H = (dataH);                                                                                                  \
    PWMD4L = (dataL);
/**
 * PWM比较数据寄存器
 * @param[in] dataH PWM通道5比较数据（占空比数据)CMP5寄存器高8位
 * @param[in] dataL PWM通道5比较数据（占空比数据)CMP5寄存器低8位
 */
#define PWM_PWMD5HL_DATA(dataH, dataL)                                                                                 \
    PWMD5H = (dataH);                                                                                                  \
    PWMD5L = (dataL);
/**@} */

/**@name PWM死区使能控制寄存器-PWMDTE
 * @{
 */
#define PWM_PWMDTE_45DTE_POS (2)
#define PWM_PWMDTE_45DTE_MSK (0x1 << PWM_PWMDTE_45DTE_POS)
#define PWM_PWMDTE_23DTE_POS (1)
#define PWM_PWMDTE_23DTE_MSK (0x1 << PWM_PWMDTE_23DTE_POS)
#define PWM_PWMDTE_01DTE_POS (0)
#define PWM_PWMDTE_01DTE_MSK (0x1 << PWM_PWMDTE_01DTE_POS)

#define ENABLE_PWM01_DTE     (PWMDTE |= PWM_PWMDTE_01DTE_MSK)  /*!< 使能PWM0/1通道死区延时 */
#define DISABLE_PWM01_DTE    (PWMDTE &= ~PWM_PWMDTE_01DTE_MSK) /*!< 禁止PWM0/1通道死区延时 */
#define ENABLE_PWM23_DTE     (PWMDTE |= PWM_PWMDTE_23DTE_MSK)  /*!< 使能PWM2/3通道死区延时 */
#define DISABLE_PWM23_DTE    (PWMDTE &= ~PWM_PWMDTE_23DTE_MSK) /*!< 禁止PWM2/3通道死区延时 */
#define ENABLE_PWM45_DTE     (PWMDTE |= PWM_PWMDTE_45DTE_MSK)  /*!< 使能PWM4/5通道死区延时 */
#define DISABLE_PWM45_DTE    (PWMDTE &= ~PWM_PWMDTE_45DTE_MSK) /*!< 禁止PWM4/5通道死区延时 */

/**@} */

/**@name PWM死区延时数据寄存器-PWM01DT PWM23DT PWM45DT
 * @{
 */
/**
 * PWM通道0/1死区延时数据寄存器
 * @param[in] u8data PWM通道0/1死区延时数据寄存器
 */
#define PWM_PWM01DT_DATA(u8data) (PWM01DT = (u8data))
/**
 * PWM通道2/3死区延时数据寄存器
 * @param[in] u8data PWM通道2/3死区延时数据寄存器
 */
#define PWM_PWM23DT_DATA(u8data) (PWM23DT = (u8data))
/**
 * PWM通道4/5死区延时数据寄存器
 * @param[in] u8data PWM通道4/5死区延时数据寄存器
 */
#define PWM_PWM45DT_DATA(u8data) (PWM45DT = (u8data))
/**@} */

/**@name PWM中断控制寄存器-PWMINTC
 * @{
 */
#define PWM_PWMINTC_INTTY_POS  (4)
#define PWM_PWMINTC_INTTY_MSK  (0x3 << PWM_PWMINTC_INTTY_POS)
#define PWM_PWMINTC_INTSEL_POS (0)
#define PWM_PWMINTC_INTSEL_MSK (0x7 << PWM_PWMINTC_INTSEL_POS)

#define PWM_FALLING_MODE       (0x00)
#define PWM_RISING_MODE        (0x01)
#define PWM_MIDPOINT_MODE      (0x02)
#define PWM_ENDPOINT_MODE      (0x03)
/**
 * PWM 中断类型选择
 * @param[in] mode
 * -# PWM_FALLING_MODE    PWM0/1/2/3/4/5管脚下降沿
 * -# PWM_RISING_MODE     PWM0/1/2/3/4/5管脚上升沿
 * -# PWM_MIDPOINT_MODE   每个PWM周期的中点
 * -# PWM_ENDPOINT_MODE   每个PWM周期的终点
 * @note 中心点中断方式或终点中断仅适用于PWM中心对齐模式
 */
#define PWM_PWMINTC_INTTY_SET(status)                                                                                  \
    (PWMINTC = ((PWMINTC & (~PWM_PWMINTC_INTTY_MSK)) | ((status) << PWM_PWMINTC_INTTY_POS)))

/**
 * PWM中断通道选择
 * @param[in] mode
 * -# PWM_0   选择PWM 0通道中断
 * -# PWM_1   选择PWM 1通道中断
 * -# PWM_2   选择PWM 2通道中断
 * -# PWM_3   选择PWM 3通道中断
 * -# PWM_4   选择PWM 4通道中断
 * -# PWM_5   选择PWM 5通道中断
 */
#define PWM_PWMINTC_INTSEL_SET(status)                                                                                 \
    (PWMINTC = ((PWMINTC & (~PWM_PWMINTC_INTSEL_MSK)) | ((status) << PWM_PWMINTC_INTSEL_POS)))
/**@} */

/**@name PWM中断标志位寄存器-PWMINTF
 * @{
 */
#define PWM_PWMINTF_LOAD_POS (6)
#define PWM_PWMINTF_LOAD_MSK (0x1 << PWM_PWMINTF_LOAD_POS)
#define PWM_PWMINTF_5IF_POS  (5)
#define PWM_PWMINTF_5IF_MSK  (0x1 << PWM_PWMINTF_5IF_POS)
#define PWM_PWMINTF_4IF_POS  (4)
#define PWM_PWMINTF_4IF_MSK  (0x1 << PWM_PWMINTF_4IF_POS)
#define PWM_PWMINTF_3IF_POS  (3)
#define PWM_PWMINTF_3IF_MSK  (0x1 << PWM_PWMINTF_3IF_POS)
#define PWM_PWMINTF_2IF_POS  (2)
#define PWM_PWMINTF_2IF_MSK  (0x1 << PWM_PWMINTF_2IF_POS)
#define PWM_PWMINTF_1IF_POS  (1)
#define PWM_PWMINTF_1IF_MSK  (0x1 << PWM_PWMINTF_1IF_POS)
#define PWM_PWMINTF_0IF_POS  (0)
#define PWM_PWMINTF_0IF_MSK  (0x1 << PWM_PWMINTF_0IF_POS)

/**
 * PWM载入配置位
 * @note
 * 该位写1，硬件自动在当前一个PWM周期输出结束时，载入新的配置值。更改的配置值，如周期、占空比、死区、模式等将在下一个周期起效。
 * 当载入完成后，硬件自动将LOAD位清0。
 */
#define ENABLE_PWM_LOAD (PWMINTF |= PWM_PWMINTF_LOAD_MSK)

/**
 * 返回load执行状态
 * @return  返回load执行状态
 * -# 0: 上一次配置值已经载入完成
 * -# 1: 上一次配置值仍然没完成
 * @note LOAD需在内部计数器使能后，即PWMCNTE非零的情况下使用
 */
#define IS_PWM_LOAD_FLAG ((PWMINTF & PWM_PWMINTF_LOAD_MSK) >> PWM_PWMINTF_LOAD_POS)

/**
 * PWM通道5中断标志位
 * @return 1:产生中断\n
 *         0:未产生中断
 * @note 通过软件清零
 */
#define IS_PWM5IF_FLAG                                                                                                 \
    (((PWMINTF & PWM_PWMINTF_5IF_MSK) >> PWM_PWMINTF_5IF_POS) && (PWM_5 == (PWMINTC & PWM_PWMINTC_INTSEL_MSK)))
#define CLR_PWM5IF_FLAG (PWMINTF &= ~PWM_PWMINTF_5IF_MSK)
/**
 * PWM通道4中断标志位
 * @return 1:产生中断\n
 *         0:未产生中断
 * @note 通过软件清零
 */
#define IS_PWM4IF_FLAG                                                                                                 \
    (((PWMINTF & PWM_PWMINTF_4IF_MSK) >> PWM_PWMINTF_4IF_POS) && (PWM_4 == (PWMINTC & PWM_PWMINTC_INTSEL_MSK)))
#define CLR_PWM4IF_FLAG (PWMINTF &= ~PWM_PWMINTF_4IF_MSK)
/**
 * PWM通道3中断标志位
 * @return 1:产生中断\n
 *         0:未产生中断
 * @note 通过软件清零
 */
#define IS_PWM3IF_FLAG                                                                                                 \
    (((PWMINTF & PWM_PWMINTF_3IF_MSK) >> PWM_PWMINTF_3IF_POS) && (PWM_3 == (PWMINTC & PWM_PWMINTC_INTSEL_MSK)))
#define CLR_PWM3IF_FLAG (PWMINTF &= ~PWM_PWMINTF_3IF_MSK)
/**
 * PWM通道2中断标志位
 * @return 1:产生中断\n
 *         0:未产生中断
 * @note 通过软件清零
 */
#define IS_PWM2IF_FLAG                                                                                                 \
    (((PWMINTF & PWM_PWMINTF_2IF_MSK) >> PWM_PWMINTF_2IF_POS) && (PWM_2 == (PWMINTC & PWM_PWMINTC_INTSEL_MSK)))
#define CLR_PWM2IF_FLAG (PWMINTF &= ~PWM_PWMINTF_2IF_MSK)
/**
 * PWM通道1中断标志位
 * @return 1:产生中断\n
 *         0:未产生中断
 * @note 通过软件清零
 */
#define IS_PWM1IF_FLAG                                                                                                 \
    (((PWMINTF & PWM_PWMINTF_1IF_MSK) >> PWM_PWMINTF_1IF_POS) && (PWM_1 == (PWMINTC & PWM_PWMINTC_INTSEL_MSK)))
#define CLR_PWM1IF_FLAG (PWMINTF &= ~PWM_PWMINTF_1IF_MSK)
/**
 * PWM通道0中断标志位
 * @return 1:产生中断\n
 *         0:未产生中断
 * @note 通过软件清零
 */
#define IS_PWM0IF_FLAG                                                                                                 \
    (((PWMINTF & PWM_PWMINTF_0IF_MSK) >> PWM_PWMINTF_0IF_POS) && (PWM_0 == (PWMINTC & PWM_PWMINTC_INTSEL_MSK)))
#define CLR_PWM0IF_FLAG (PWMINTF &= ~PWM_PWMINTF_0IF_MSK)
/**@} */

/**@name PWM极性控制寄存器-PWMPINV
 * @{
 */
#define PWM_PWMPINV_5_POS       (5)
#define PWM_PWMPINV_5_MSK       (0x1 << PWM_PWMPINV_5_POS)
#define PWM_PWMPINV_4_POS       (4)
#define PWM_PWMPINV_4_MSK       (0x1 << PWM_PWMPINV_4_POS)
#define PWM_PWMPINV_3_POS       (3)
#define PWM_PWMPINV_3_MSK       (0x1 << PWM_PWMPINV_3_POS)
#define PWM_PWMPINV_2_POS       (2)
#define PWM_PWMPINV_2_MSK       (0x1 << PWM_PWMPINV_2_POS)
#define PWM_PWMPINV_1_POS       (1)
#define PWM_PWMPINV_1_MSK       (0x1 << PWM_PWMPINV_1_POS)
#define PWM_PWMPINV_0_POS       (0)
#define PWM_PWMPINV_0_MSK       (0x1 << PWM_PWMPINV_0_POS)

#define ENABLE_PWM0_INV_OUTPUT  (PWMPINV |= PWM_PWMPINV_0_MSK)  /*!< 使能通道0反向输出 */
#define DISABLE_PWM0_INV_OUTPUT (PWMPINV &= ~PWM_PWMPINV_0_MSK) /*!< 禁止通道0反向输出 */
#define ENABLE_PWM1_INV_OUTPUT  (PWMPINV |= PWM_PWMPINV_1_MSK)  /*!< 使能通道1反向输出 */
#define DISABLE_PWM1_INV_OUTPUT (PWMPINV &= ~PWM_PWMPINV_1_MSK) /*!< 禁止通道1反向输出 */
#define ENABLE_PWM2_INV_OUTPUT  (PWMPINV |= PWM_PWMPINV_2_MSK)  /*!< 使能通道2反向输出 */
#define DISABLE_PWM2_INV_OUTPUT (PWMPINV &= ~PWM_PWMPINV_2_MSK) /*!< 禁止通道2反向输出 */
#define ENABLE_PWM3_INV_OUTPUT  (PWMPINV |= PWM_PWMPINV_3_MSK)  /*!< 使能通道3反向输出 */
#define DISABLE_PWM3_INV_OUTPUT (PWMPINV &= ~PWM_PWMPINV_3_MSK) /*!< 禁止通道3反向输出 */
#define ENABLE_PWM4_INV_OUTPUT  (PWMPINV |= PWM_PWMPINV_4_MSK)  /*!< 使能通道4反向输出 */
#define DISABLE_PWM4_INV_OUTPUT (PWMPINV &= ~PWM_PWMPINV_4_MSK) /*!< 禁止通道4反向输出 */
#define ENABLE_PWM5_INV_OUTPUT  (PWMPINV |= PWM_PWMPINV_5_MSK)  /*!< 使能通道5反向输出 */
#define DISABLE_PWM5_INV_OUTPUT (PWMPINV &= ~PWM_PWMPINV_5_MSK) /*!< 禁止通道5反向输出 */
/**@} */

/**@name PWM掩码使能寄存器-PWMMASKEN
 * @{
 */
#define PWM_PWMMASKEN_5_POS (5)
#define PWM_PWMMASKEN_5_MSK (0x1 << PWM_PWMMASKEN_5_POS)
#define PWM_PWMMASKEN_4_POS (4)
#define PWM_PWMMASKEN_4_MSK (0x1 << PWM_PWMMASKEN_4_POS)
#define PWM_PWMMASKEN_3_POS (3)
#define PWM_PWMMASKEN_3_MSK (0x1 << PWM_PWMMASKEN_3_POS)
#define PWM_PWMMASKEN_2_POS (2)
#define PWM_PWMMASKEN_2_MSK (0x1 << PWM_PWMMASKEN_2_POS)
#define PWM_PWMMASKEN_1_POS (1)
#define PWM_PWMMASKEN_1_MSK (0x1 << PWM_PWMMASKEN_1_POS)
#define PWM_PWMMASKEN_0_POS (0)
#define PWM_PWMMASKEN_0_MSK (0x1 << PWM_PWMMASKEN_0_POS)

#define ENABLE_PWM0_MASK    (PWMMASKEN |= PWM_PWMMASKEN_0_MSK)  /*!< 通道0使能掩码数据输出 */
#define DISABLE_PWM0_MASK   (PWMMASKEN &= ~PWM_PWMMASKEN_0_MSK) /*!< 通道0禁止掩码数据输出，正常输出PWM波形 */
#define ENABLE_PWM1_MASK    (PWMMASKEN |= PWM_PWMMASKEN_1_MSK)  /*!< 通道1使能掩码数据输出 */
#define DISABLE_PWM1_MASK   (PWMMASKEN &= ~PWM_PWMMASKEN_1_MSK) /*!< 通道1禁止掩码数据输出，正常输出PWM波形 */
#define ENABLE_PWM2_MASK    (PWMMASKEN |= PWM_PWMMASKEN_2_MSK)  /*!< 通道2使能掩码数据输出 */
#define DISABLE_PWM2_MASK   (PWMMASKEN &= ~PWM_PWMMASKEN_2_MSK) /*!< 通道2禁止掩码数据输出，正常输出PWM波形 */
#define ENABLE_PWM3_MASK    (PWMMASKEN |= PWM_PWMMASKEN_3_MSK)  /*!< 通道3使能掩码数据输出 */
#define DISABLE_PWM3_MASK   (PWMMASKEN &= ~PWM_PWMMASKEN_3_MSK) /*!< 通道3禁止掩码数据输出，正常输出PWM波形 */
#define ENABLE_PWM4_MASK    (PWMMASKEN |= PWM_PWMMASKEN_4_MSK)  /*!< 通道4使能掩码数据输出 */
#define DISABLE_PWM4_MASK   (PWMMASKEN &= ~PWM_PWMMASKEN_4_MSK) /*!< 通道4禁止掩码数据输出，正常输出PWM波形 */
#define ENABLE_PWM5_MASK    (PWMMASKEN |= PWM_PWMMASKEN_5_MSK)  /*!< 通道5使能掩码数据输出 */
#define DISABLE_PWM5_MASK   (PWMMASKEN &= ~PWM_PWMMASKEN_5_MSK) /*!< 通道5禁止掩码数据输出，正常输出PWM波形 */

/**@} */

/**@name PWM掩码数据寄存器-PWMMASKD
 * @{
 */
#define PWM_PWMMASKD_5_POS (5)
#define PWM_PWMMASKD_5_MSK (0x1 << PWM_PWMMASKD_5_POS)
#define PWM_PWMMASKD_4_POS (4)
#define PWM_PWMMASKD_4_MSK (0x1 << PWM_PWMMASKD_4_POS)
#define PWM_PWMMASKD_3_POS (3)
#define PWM_PWMMASKD_3_MSK (0x1 << PWM_PWMMASKD_3_POS)
#define PWM_PWMMASKD_2_POS (2)
#define PWM_PWMMASKD_2_MSK (0x1 << PWM_PWMMASKD_2_POS)
#define PWM_PWMMASKD_1_POS (1)
#define PWM_PWMMASKD_1_MSK (0x1 << PWM_PWMMASKD_1_POS)
#define PWM_PWMMASKD_0_POS (0)
#define PWM_PWMMASKD_0_MSK (0x1 << PWM_PWMMASKD_0_POS)
/**
 * PWM通道5掩码数据位
 * @param[in] status
 * -# OUTPUT_LOW:通道输出低
 * -# OUTPUT_HIGH:通道输出高
 */
#define PWM_PWMMASKD_5_SET(status) (PWMMASKD = ((PWMMASKD & (~PWM_PWMMASKD_5_MSK)) | ((status) << PWM_PWMMASKD_5_POS)))
/**
 * PWM通道4掩码数据位
 * @param[in] status
 * -# OUTPUT_LOW:通道输出低
 * -# OUTPUT_HIGH:通道输出高
 */
#define PWM_PWMMASKD_4_SET(status) (PWMMASKD = ((PWMMASKD & (~PWM_PWMMASKD_4_MSK)) | ((status) << PWM_PWMMASKD_4_POS)))
/**
 * PWM通道3掩码数据位
 * @param[in] status
 * -# OUTPUT_LOW:通道输出低
 * -# OUTPUT_HIGH:通道输出高
 */
#define PWM_PWMMASKD_3_SET(status) (PWMMASKD = ((PWMMASKD & (~PWM_PWMMASKD_3_MSK)) | ((status) << PWM_PWMMASKD_3_POS)))
/**
 * PWM通道2掩码数据位
 * @param[in] status
 * -# OUTPUT_LOW:通道输出低
 * -# OUTPUT_HIGH:通道输出高
 */
#define PWM_PWMMASKD_2_SET(status) (PWMMASKD = ((PWMMASKD & (~PWM_PWMMASKD_2_MSK)) | ((status) << PWM_PWMMASKD_2_POS)))
/**
 * PWM通道1掩码数据位
 * @param[in] status
 * -# OUTPUT_LOW:通道输出低
 * -# OUTPUT_HIGH:通道输出高
 */
#define PWM_PWMMASKD_1_SET(status) (PWMMASKD = ((PWMMASKD & (~PWM_PWMMASKD_1_MSK)) | ((status) << PWM_PWMMASKD_1_POS)))
/**
 * PWM通道0掩码数据位
 * @param[in] status
 * -# OUTPUT_LOW:通道输出低
 * -# OUTPUT_HIGH:通道输出高
 */
#define PWM_PWMMASKD_0_SET(status) (PWMMASKD = ((PWMMASKD & (~PWM_PWMMASKD_0_MSK)) | ((status) << PWM_PWMMASKD_0_POS)))
/**@} */

/**@name PWM故障刹车数据寄存器-PWMFBKD
 * @{
 */
#define PWM_PWMFBKD_FBF_POS    (7)
#define PWM_PWMFBKD_FBF_MSK    (0x1 << PWM_PWMFBKD_FBF_POS)
#define PWM_PWMFBKD_FBINLS_POS (6)
#define PWM_PWMFBKD_FBINLS_MSK (0x1 << PWM_PWMFBKD_FBINLS_POS)
#define PWM_PWMFBKD_5_POS      (5)
#define PWM_PWMFBKD_5_MSK      (0x1 << PWM_PWMFBKD_5_POS)
#define PWM_PWMFBKD_4_POS      (4)
#define PWM_PWMFBKD_4_MSK      (0x1 << PWM_PWMFBKD_4_POS)
#define PWM_PWMFBKD_3_POS      (3)
#define PWM_PWMFBKD_3_MSK      (0x1 << PWM_PWMFBKD_3_POS)
#define PWM_PWMFBKD_2_POS      (2)
#define PWM_PWMFBKD_2_MSK      (0x1 << PWM_PWMFBKD_2_POS)
#define PWM_PWMFBKD_1_POS      (1)
#define PWM_PWMFBKD_1_MSK      (0x1 << PWM_PWMFBKD_1_POS)
#define PWM_PWMFBKD_0_POS      (0)
#define PWM_PWMFBKD_0_MSK      (0x1 << PWM_PWMFBKD_0_POS)
/**
 * 故障刹车标志位
 * @return 1:当FBINEN设置为1，FB管脚上侦测到符合FBINLS (PWMFBKD.6)设定的边沿信号后，该位置1
 * @note 通过软件清零
 */
#define IS_PWM_FBF_FLAG  ((PWMFBKD & PWM_PWMFBKD_FBF_MSK) >> PWM_PWMFBKD_FBF_POS)
#define CLR_PWM_FBF_FLAG (PWMFBKD &= ~PWM_PWMFBKD_FBF_MSK)

#define FB_RISING        (1)
#define FB_FALLING       (0)
/**
 * FB管脚输入选择
 * @param[in] status
 * -# FB_FALLING:下降沿
 * -# FB_RISING: 上升沿
 */
#define PWM_FBINLS_SET(status)                                                                                         \
    (PWMFBKD = ((PWMFBKD & (~PWM_PWMFBKD_FBINLS_MSK)) | ((status) << PWM_PWMFBKD_FBINLS_POS)))
/**
 * PWM通道5故障输出数据
 * @param[in] status
 * -# OUTPUT_LOW:当故障发生时PWM信号输出为0
 * -# OUTPUT_HIGH:当故障发生时PWM信号输出为1
 */
#define PWM_PWMFBKD_5_SET(status) (PWMFBKD = ((PWMFBKD & (~PWM_PWMFBKD_5_MSK)) | ((status) << PWM_PWMFBKD_5_POS)))
/**
 * PWM通道4故障输出数据
 * @param[in] status
 * -# OUTPUT_LOW:当故障发生时PWM信号输出为0
 * -# OUTPUT_HIGH:当故障发生时PWM信号输出为1
 */
#define PWM_PWMFBKD_4_SET(status) (PWMFBKD = ((PWMFBKD & (~PWM_PWMFBKD_4_MSK)) | ((status) << PWM_PWMFBKD_4_POS)))
/**
 * PWM通道3故障输出数据
 * @param[in] status
 * -# OUTPUT_LOW:当故障发生时PWM信号输出为0
 * -# OUTPUT_HIGH:当故障发生时PWM信号输出为1
 */
#define PWM_PWMFBKD_3_SET(status) (PWMFBKD = ((PWMFBKD & (~PWM_PWMFBKD_3_MSK)) | ((status) << PWM_PWMFBKD_3_POS)))
/**
 * PWM通道2故障输出数据
 * @param[in] status
 * -# OUTPUT_LOW:当故障发生时PWM信号输出为0
 * -# OUTPUT_HIGH:当故障发生时PWM信号输出为1
 */
#define PWM_PWMFBKD_2_SET(status) (PWMFBKD = ((PWMFBKD & (~PWM_PWMFBKD_2_MSK)) | ((status) << PWM_PWMFBKD_2_POS)))
/**
 * PWM通道1故障输出数据
 * @param[in] status
 * -# OUTPUT_LOW:当故障发生时PWM信号输出为0
 * -# OUTPUT_HIGH:当故障发生时PWM信号输出为1
 */
#define PWM_PWMFBKD_1_SET(status) (PWMFBKD = ((PWMFBKD & (~PWM_PWMFBKD_1_MSK)) | ((status) << PWM_PWMFBKD_1_POS)))
/**
 * PWM通道0故障输出数据
 * @param[in] status
 * -# OUTPUT_LOW:当故障发生时PWM信号输出为0
 * -# OUTPUT_HIGH:当故障发生时PWM信号输出为1
 */
#define PWM_PWMFBKD_0_SET(status) (PWMFBKD = ((PWMFBKD & (~PWM_PWMFBKD_0_MSK)) | ((status) << PWM_PWMFBKD_0_POS)))
/**@} */

/**@name 外部函数
 * @{
 */
#define LOAD_PWM                                                                                                       \
    {                                                                                                                  \
        PWMINTF |= (1 << 6);                                                                                           \
    }    											
void PWM_ConfigINT(uint8_t u8pwmNum, uint8_t u8trigger);
void PWM_ConfigFBOutputLevel(uint8_t u8pwmNum, uint8_t u8pwmLevel);
void PWM_ConfigMASKOutputLevel(uint8_t u8pwmNum, uint8_t u8pwmLevel);
void PWM_StartLoad(void);

/**@} */

#endif /* __PWM_H__ */
