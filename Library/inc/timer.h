/**
 * @file      timer.h
 * @brief     timer驱动配置
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include "WY8S9003xx.h"

/**@name TIMER0/1模式寄存器-TMOD
 * @{
 */
#define TIMER1_TMOD_GATE1_POS (7)
#define TIMER1_TMOD_GATE1_MSK (0x1 << TIMER1_TMOD_GATE1_POS)
#define TIMER1_TMOD_CNT1_POS  (6)
#define TIMER1_TMOD_CNT1_MSK  (0x1 << TIMER1_TMOD_CNT1_POS)
#define TIMER1_TMOD_MODE_POS  (4)
#define TIMER1_TMOD_MODE_MSK  (0x3 << TIMER1_TMOD_MODE_POS)
#define TIMER0_TMOD_GATE0_POS (3)
#define TIMER0_TMOD_GATE0_MSK (0x1 << TIMER0_TMOD_GATE0_POS)
#define TIMER0_TMOD_CNT0_POS  (2)
#define TIMER0_TMOD_CNT0_MSK  (0x1 << TIMER0_TMOD_CNT0_POS)
#define TIMER0_TMOD_MODE_POS  (0)
#define TIMER0_TMOD_MODE_MSK  (0x3 << TIMER0_TMOD_MODE_POS)

#define TIMER01_MODE0         (0x00) /*!< 模式0，13位定时器/计数器 */
#define TIMER01_MODE1         (0x01) /*!< 模式1，16位定时器/计数器 */
#define TIMER01_MODE2         (0x02) /*!< 模式2，8位定时器/计数器，TL溢出后数值从TH自动重装载入TL */
#define TIMER01_MODE3                                                                                                  \
    (0x03) /*!< 模式3，TL0配置为8位定时器/计数器(TIMER0控制位)，TH0配置为8位定时器/计数器(TIMER1控制位) */

#define TIMER01_TR_GATE     (0)
#define TIMER01_INT_TR_GATE (1)

#define TIMER01_ICLK        (0)
#define TIMER01_TCLK        (1)

/**
 * TIMER1门控制
 * @param[in] status
 * -# TIMER01_TR_GATE:    TCON.TR1位为1时，开始计数
 * -# TIMER01_INT_TR_GATE:INT1为1且TR1为1时，开始计数
 */
#define TIMER1_TMOD_GATE1_SET(status) (TMOD = ((TMOD & (~TIMER1_TMOD_GATE1_MSK)) | ((status) << TIMER1_TMOD_GATE1_POS)))
/**
 * TIMER1计数/定时选择
 * @param[in] status
 * -# TIMER01_ICLK:作为定时器1，选择的驱动时钟从内部时钟输入
 * -# TIMER01_TCLK:作为计数器1，选择的驱动时钟从引脚T1输入
 */
#define TIMER1_TMOD_CNT1_SET(status) (TMOD = ((TMOD & (~TIMER1_TMOD_CNT1_MSK)) | ((status) << TIMER1_TMOD_CNT1_POS)))
/**
 * TIMER1模式选择
 * @param[in] mode
 * -# TIMER01_MODE0:模式0，13位定时器/计数器
 * -# TIMER01_MODE1:模式1，16位定时器/计数器
 * -# TIMER01_MODE2:模式2，8位定时器/计数器，TH1溢出后数值从TH1自动重装载入TL1
 * -# TIMER01_MODE3:模式3，定时器 1 停止
 */
#define TIMER1_TMOD_MODE_SET(mode) (TMOD = ((TMOD & (~TIMER1_TMOD_MODE_MSK)) | ((mode) << TIMER1_TMOD_MODE_POS)))
/**
 * TIMER0门控制
 * @param[in] status
 * -# TIMER01_TR_GATE:    TCON.TR0位为1时，开始计数
 * -# TIMER01_INT_TR_GATE:INT0为1且TR0为1时，开始计数
 */
#define TIMER0_TMOD_GATE0_SET(status) (TMOD = ((TMOD & (~TIMER0_TMOD_GATE0_MSK)) | ((status) << TIMER0_TMOD_GATE0_POS)))
/**
 * TIMER0计数/定时选择
 * @param[in] status
 * -# TIMER01_ICLK:作为定时器0，选择的驱动时钟从内部时钟输入
 * -# TIMER01_TCLK:作为计数器0，选择的驱动时钟从引脚T0输入
 */
#define TIMER0_TMOD_CNT0_SET(status) (TMOD = ((TMOD & (~TIMER0_TMOD_CNT0_MSK)) | ((status) << TIMER0_TMOD_CNT0_POS)))
/**
 * TIMER0模式选择
 * @param[in] mode
 * -# TIMER01_MODE0:模式0，13位定时器/计数器
 * -# TIMER01_MODE1:模式1，16位定时器/计数器
 * -# TIMER01_MODE2:模式2，8位定时器/计数器，TH0溢出后数值从TH0自动重装载入TL0
 * -# TIMER01_MODE3:模式3，TL0配置为8位定时器/计数器(TIMER0控制位)，TH0配置为8位定时器/计数器(TIMER1控制位)
 *
 */
#define TIMER0_TMOD_MODE_SET(mode) (TMOD = ((TMOD & (~TIMER0_TMOD_MODE_MSK)) | ((mode) << TIMER0_TMOD_MODE_POS)))
/**@} */

/**@name TIMER0/1控制寄存器-TCON
 * @{
 */
/**
 * TIMER1溢出标志
 * @return 0:TIMER1无溢出\n
 *         1:TIMER1溢出，溢出后由硬件置1，同时也由硬件清零
 */
#define IS_TIME1_OVER_FLAG  (TF1)
#define CLR_TIME1_OVER_FLAG (TF1 = 0) /*!< 清除标志 */

#define ENABLE_TIMER1       (TR1 = 1) /*!< TIMER1启动 */
#define DISABLE_TIMER1      (TR1 = 0) /*!< TIMER1关闭 */

/**
 * TIMER0溢出标志
 * @return 0:TIMER0无溢出\n
 *         1:TIMER0溢出，溢出后由硬件置1，同时也由硬件清零
 */
#define IS_TIME0_OVER_FLAG  (TF0)
#define CLR_TIME0_OVER_FLAG (TF0 = 0) /*!< 清除标志 */

#define ENABLE_TIMER0       (TR0 = 1) /*!< TIMER0启动 */
#define DISABLE_TIMER0      (TR0 = 0) /*!< TIMER0关闭 */

/**@} */

/**@name TIMER0/1数据寄存器-THx TLx
 * @{
 */
/**
 * TIMER0数据寄存器
 * @param[in] dataH  数据寄存器高位
 * @param[in] dataL  数据寄存器低位
 */
#define TIMER0_DATA_REG(dataH, dataL)                                                                                  \
    TH0 = (dataH);                                                                                                     \
    TL0 = (dataL);
/**
 * TIMER1数据寄存器
 * @param[in] dataH  数据寄存器高位
 * @param[in] dataL  数据寄存器低位
 */
#define TIMER1_DATA_REG(dataH, dataL)                                                                                  \
    TH1 = (dataH);                                                                                                     \
    TL1 = (dataL);
/**@} */

/**@name TIMER2数据寄存器-T2RH T2RL
 * @{
 */
/**
 * TIMER2数据寄存器
 * @param[in] dataH  数据寄存器高位
 * @param[in] dataL  数据寄存器低位
 */
#define TIMER2_DATA_REG(dataH, dataL)                                                                                  \
    T2RH = (dataH);                                                                                                    \
    T2RL = (dataL);
/**@} */

/**@name TIMER2重载 / 比较数据寄存器-RCMP2H RCMP2L
 * @{
 */
/**
 * TIMER2重载 / 比较数据寄存器
 * @param[in] dataH  寄存器高位
 * @param[in] dataL  寄存器低位
 */
#define TIMER2_RCMP_DATA_REG(dataH, dataL)                                                                             \
    RCMP2H = (dataH);                                                                                                  \
    RCMP2L = (dataL);
/**@} */

/**@name TIMER2控制寄存器-T2CON
 * @{
 */
#define TIMER2_T2CON_TR2_POS   (1)
#define TIMER2_T2CON_TR2_MSK   (0x1 << TIMER2_T2CON_TR2_POS)
#define TIMER2_T2CON_CMRL_POS  (0)
#define TIMER2_T2CON_CMRL_MSK  (0x1 << TIMER2_T2CON_CMRL_POS)
#define TIMER2_T2CON_CMPCR_POS (2)
#define TIMER2_T2CON_CMPCR_MSK (0x1 << TIMER2_T2CON_CMPCR_POS)

#define ENABLE_TIMER2          (T2CON |= TIMER2_T2CON_TR2_MSK)    /*!< TIMER2启动 */
#define DISABLE_TIMER2         (T2CON &= ~TIMER2_T2CON_TR2_MSK)   /*!< TIMER2关闭 */

#define TIMER2_SET_COMP_MODE   (T2CON |= TIMER2_T2CON_CMRL_MSK)   /*!< 设置TIMER2比较模式 */
#define TIMER2_SET_RELOAD_MODE (T2CON &= ~TIMER2_T2CON_CMRL_MSK)  /*!< 设置TIMER2重载模式 */

#define ENABLE_TIMER2_CMPCR    (T2CON |= TIMER2_T2CON_CMPCR_MSK)  /*!< 比较符合之后，定时器2计数值清0 */
#define DISABLE_TIMER2_CMPCR   (T2CON &= ~TIMER2_T2CON_CMPCR_MSK) /*!< 比较符合之后，定时器2计数值按之前值继续计数 */

/**
 * 判断TIME2溢出标志
 * @return 1: CPU执行定时器2中断服务程序
 * @note:该位硬件不能自动清除，需要软件写0清0
 */
#define IS_TIME2_TF2_FLAG  (T2CON & (1 << 5))
#define CLR_TIME2_TF2_FLAG (T2CON &= ~(1 << 5)); /*!< 清除TIME2溢出标志 */
/**
 * 判断定时器2比较数据匹配
 * return 1: CPU执行定时器2中断服务程序
 * @note:该位硬件不能自动清除，需要软件写0清0
 */
#define IS_TIME2_TC2_FLAG  (T2CON & (1 << 4))
#define CLR_TIME2_TC2_FLAG (T2CON &= ~(1 << 4)); /*!< 清除TIME2比较数据匹配标志 */
/**@} */

/**@name 定时器2模式选择寄存器-T2MOD
 * @{
 */
#define TIMER2_T2MOD_LDEN_POS  (7)
#define TIMER2_T2MOD_LDEN_MSK  (0x1 << TIMER2_T2MOD_LDEN_POS)
#define TIMER2_T2MOD_T2DIV_POS (4)
#define TIMER2_T2MOD_T2DIV_MSK (0x7 << TIMER2_T2MOD_T2DIV_POS)
#define TIMER2_T2MOD_CAPCR_POS (3)
#define TIMER2_T2MOD_CAPCR_MSK (0x1 << TIMER2_T2MOD_CAPCR_POS)
#define TIMER2_T2MOD_LDTS_POS  (0)
#define TIMER2_T2MOD_LDTS_MSK  (0x7 << TIMER2_T2MOD_LDTS_POS)

#define ENABLE_TIMER2_RELOAD   (T2MOD |= TIMER2_T2MOD_LDEN_MSK)  /*!< RCMP2H及RCMP2L自动重载至TH2及TL2功能打开 */
#define DISABLE_TIMER2_RELOAD  (T2MOD &= ~TIMER2_T2MOD_LDEN_MSK) /*!< RCMP2H及RCMP2L自动重载至TH2及TL2功能关闭 */

#define TIMER2_T2DIV_1DIV      (0x00)
#define TIMER2_T2DIV_4DIV      (0x01)
#define TIMER2_T2DIV_16DIV     (0x02)
#define TIMER2_T2DIV_32DIV     (0x03)
#define TIMER2_T2DIV_64DIV     (0x04)
#define TIMER2_T2DIV_128DIV    (0x05)
#define TIMER2_T2DIV_256DIV    (0x06)
#define TIMER2_T2DIV_512DIV    (0x07)
/**
 * TIMER2时钟分频值
 * @param[in] mode
 * -# TIMER2_T2DIV_1DIV:  TIMER2时钟除频为1/1
 * -# TIMER2_T2DIV_4DIV:  TIMER2时钟除频为1/4
 * -# TIMER2_T2DIV_16DIV: TIMER2时钟除频为1/16
 * -# TIMER2_T2DIV_32DIV: TIMER2时钟除频为1/32
 * -# TIMER2_T2DIV_64DIV: TIMER2时钟除频为1/64
 * -# TIMER2_T2DIV_128DIV:TIMER2时钟除频为1/128
 * -# TIMER2_T2DIV_256DIV:TIMER2时钟除频为1/256
 * -# TIMER2_T2DIV_512DIV:TIMER2时钟除频为1/512
 */
#define TIMER2_T2MOD_T2DIV_SET(mode)                                                                                   \
    (T2MOD = ((T2MOD & (~TIMER2_T2MOD_T2DIV_MSK)) | ((mode) << TIMER2_T2MOD_T2DIV_POS)))

#define ENABLE_TIMER2_CAPCR (T2MOD |= TIMER2_T2MOD_CAPCR_MSK) /*!< 捕获事件发生后定时器2计数值自动清0 */
#define DISABLE_TIMER2_CAPCR                                                                                           \
    (T2MOD &= ~TIMER2_T2MOD_CAPCR_MSK) /*!< 捕获事件发生后定时器2计数值按之前计数值继续累加     \
                                        */

#define TIMER2_LDTS_CAP0 (0x00)
#define TIMER2_LDTS_CAP1 (0x01)
#define TIMER2_LDTS_CAP2 (0x02)
#define TIMER2_LDTS_CAP3 (0x03)
#define TIMER2_LDTS_OVER (0x04)
/**
 * TIMER2自动重载触发选择
 * @param[in] mode
 * -# TIMER2_LDTS_CAP0: 当捕获0通道事件发生，自动重载
 * -# TIMER2_LDTS_CAP1: 当捕获1通道事件发生，自动重载
 * -# TIMER2_LDTS_CAP2: 当捕获2通道事件发生，自动重载
 * -# TIMER2_LDTS_CAP3: 当捕获3通道事件发生，自动重载
 * -# TIMER2_LDTS_OVER: 当定时器2溢出时，自动重载
 */
#define TIMER2_T2MOD_LDTS_SET(mode) (T2MOD = ((T2MOD & (~TIMER2_T2MOD_LDTS_MSK)) | ((mode) << TIMER2_T2MOD_LDTS_POS)))
/**@} */

/**@name 输入捕获控制寄存器0-CAPCON0
 * @{
 */
#define TIMER2_CAPCON0_CAPEN3_POS  (7)
#define TIMER2_CAPCON0_CAPEN3_MSK  (0x1 << TIMER2_CAPCON0_CAPEN3_POS)
#define TIMER2_CAPCON0_CAPEN2_POS  (6)
#define TIMER2_CAPCON0_CAPEN2_MSK  (0x1 << TIMER2_CAPCON0_CAPEN2_POS)
#define TIMER2_CAPCON0_CAPEN1_POS  (5)
#define TIMER2_CAPCON0_CAPEN1_MSK  (0x1 << TIMER2_CAPCON0_CAPEN1_POS)
#define TIMER2_CAPCON0_CAPEN0_POS  (4)
#define TIMER2_CAPCON0_CAPEN0_MSK  (0x1 << TIMER2_CAPCON0_CAPEN0_POS)
#define TIMER2_CAPCON0_CAPFEN3_POS (3)
#define TIMER2_CAPCON0_CAPFEN3_MSK (0x1 << TIMER2_CAPCON0_CAPFEN3_POS)
#define TIMER2_CAPCON0_CAPFEN2_POS (2)
#define TIMER2_CAPCON0_CAPFEN2_MSK (0x1 << TIMER2_CAPCON0_CAPFEN2_POS)
#define TIMER2_CAPCON0_CAPFEN1_POS (1)
#define TIMER2_CAPCON0_CAPFEN1_MSK (0x1 << TIMER2_CAPCON0_CAPFEN1_POS)
#define TIMER2_CAPCON0_CAPFEN0_POS (0)
#define TIMER2_CAPCON0_CAPFEN0_MSK (0x1 << TIMER2_CAPCON0_CAPFEN0_POS)

#define ENABLE_TIMER2_CAP3         (CAPCON0 |= TIMER2_CAPCON0_CAPEN3_MSK)  /*!< 打开TIMER2输入捕获通道3 */
#define DISABLE_TIMER2_CAP3        (CAPCON0 &= ~TIMER2_CAPCON0_CAPEN3_MSK) /*!< 关闭TIMER2输入捕获通道3 */
#define ENABLE_TIMER2_CAP2         (CAPCON0 |= TIMER2_CAPCON0_CAPEN2_MSK)  /*!< 打开TIMER2输入捕获通道2 */
#define DISABLE_TIMER2_CAP2        (CAPCON0 &= ~TIMER2_CAPCON0_CAPEN2_MSK) /*!< 关闭TIMER2输入捕获通道2 */
#define ENABLE_TIMER2_CAP1         (CAPCON0 |= TIMER2_CAPCON0_CAPEN1_MSK)  /*!< 打开TIMER2输入捕获通道1 */
#define DISABLE_TIMER2_CAP1        (CAPCON0 &= ~TIMER2_CAPCON0_CAPEN1_MSK) /*!< 关闭TIMER2输入捕获通道1 */
#define ENABLE_TIMER2_CAP0         (CAPCON0 |= TIMER2_CAPCON0_CAPEN0_MSK)  /*!< 打开TIMER2输入捕获通道0 */
#define DISABLE_TIMER2_CAP0        (CAPCON0 &= ~TIMER2_CAPCON0_CAPEN0_MSK) /*!< 关闭TIMER2输入捕获通道0 */

#define DISABLE_CAP_FILTER         (0)                                     /*!< 关闭噪声滤波 */
#define ENABLE_CAP_FILTER          (1)                                     /*!< 使能噪声滤波 */
/* * 定时器 2 输入捕获通道3 噪声滤波使能位
 * @param[in] status
 * -# DISABLE_CAP_FILTER:关闭输入捕获通道3的噪声滤波
 * -# ENABLE_CAP_FILTER: 打开输入捕获通道3的噪声滤波
 */
#define TIMER2_CAPCON0_CAPFEN3_SET(status)                                                                             \
    (CAPCON0 = ((CAPCON0 & (~TIMER2_CAPCON0_CAPFEN3_MSK)) | ((status) << TIMER2_CAPCON0_CAPFEN3_POS)))
/**
 * 定时器 2 输入捕获通道2 噪声滤波使能位
 * @param[in] status
 * -# DISABLE_CAP_FILTER:关闭输入捕获通道2的噪声滤波
 * -# ENABLE_CAP_FILTER: 打开输入捕获通道2的噪声滤波
 */
#define TIMER2_CAPCON0_CAPFEN2_SET(status)                                                                             \
    (CAPCON0 = ((CAPCON0 & (~TIMER2_CAPCON0_CAPFEN2_MSK)) | ((status) << TIMER2_CAPCON0_CAPFEN2_POS)))
/**
 * 定时器 2 输入捕获通道1 噪声滤波使能位
 * @param[in] status
 * -# DISABLE_CAP_FILTER:关闭输入捕获通道1的噪声滤波
 * -# ENABLE_CAP_FILTER: 打开输入捕获通道1的噪声滤波
 */
#define TIMER2_CAPCON0_CAPFEN1_SET(status)                                                                             \
    (CAPCON0 = ((CAPCON0 & (~TIMER2_CAPCON0_CAPFEN1_MSK)) | ((status) << TIMER2_CAPCON0_CAPFEN1_POS)))

/**
 * 定时器 2 输入捕获通道0 噪声滤波使能位
 * @param[in] status
 * -# DISABLE_CAP_FILTER:关闭输入捕获通道0的噪声滤波
 * -# ENABLE_CAP_FILTER: 打开输入捕获通道0的噪声滤波
 */
#define TIMER2_CAPCON0_CAPFEN0_SET(status)                                                                             \
    (CAPCON0 = ((CAPCON0 & (~TIMER2_CAPCON0_CAPFEN0_MSK)) | ((status) << TIMER2_CAPCON0_CAPFEN0_POS)))

/**@} */

/**@name 输入捕获控制寄存器1-CAPCON1
 * @{
 */
#define TIMER2_CAPCON1_CAP3LS_POS   (6)
#define TIMER2_CAPCON1_CAP3LS_MSK   (0x3 << TIMER2_CAPCON1_CAP3LS_POS)
#define TIMER2_CAPCON1_CAP2LS_POS   (4)
#define TIMER2_CAPCON1_CAP2LS_MSK   (0x3 << TIMER2_CAPCON1_CAP2LS_POS)
#define TIMER2_CAPCON1_CAP1LS_POS   (2)
#define TIMER2_CAPCON1_CAP1LS_MSK   (0x3 << TIMER2_CAPCON1_CAP1LS_POS)
#define TIMER2_CAPCON1_CAP0LS_POS   (0)
#define TIMER2_CAPCON1_CAP0LS_MSK   (0x3 << TIMER2_CAPCON1_CAP0LS_POS)

#define TIMER2_CAPLS_FALLING        (0x00)
#define TIMER2_CAPLS_RISING         (0x01)
#define TIMER2_CAPLS_RISING_FALLING (0x02)
/**
 * TIMER2输入捕获通道3条件选择
 * @param[in] mode
 * -# TIMER2_CAPLS_FALLING:        下降沿
 * -# TIMER2_CAPLS_RISING:         上升沿
 * -# TIMER2_CAPLS_RISING_FALLING: 上升沿或下降沿
 */
#define TIMER2_CAPCON1_CAP3LS_SET(mode)                                                                                \
    (CAPCON1 = ((CAPCON1 & (~TIMER2_CAPCON1_CAP3LS_MSK)) | ((mode) << TIMER2_CAPCON1_CAP3LS_POS)))
#define GET_TIMER2_CAP3LS                                                                                              \
    ((CAPCON1 & TIMER2_CAPCON1_CAP3LS_MSK) >> TIMER2_CAPCON1_CAP3LS_POS) /*!< 获取捕获通道3触发条件状态 */
/**
 * TIMER2输入捕获通道2条件选择
 * @param[in] mode
 * -# TIMER2_CAPLS_FALLING:        下降沿
 * -# TIMER2_CAPLS_RISING:         上升沿
 * -# TIMER2_CAPLS_RISING_FALLING: 上升沿或下降沿
 */
#define TIMER2_CAPCON1_CAP2LS_SET(mode)                                                                                \
    (CAPCON1 = ((CAPCON1 & (~TIMER2_CAPCON1_CAP2LS_MSK)) | ((mode) << TIMER2_CAPCON1_CAP2LS_POS)))
#define GET_TIMER2_CAP2LS                                                                                              \
    ((CAPCON1 & TIMER2_CAPCON1_CAP2LS_MSK) >> TIMER2_CAPCON1_CAP2LS_POS) /*!< 获取捕获通道2触发条件状态 */
/**
 * TIMER2输入捕获通道1条件选择
 * @param[in] mode
 * -# TIMER2_CAPLS_FALLING:        下降沿
 * -# TIMER2_CAPLS_RISING:         上升沿
 * -# TIMER2_CAPLS_RISING_FALLING: 上升沿或下降沿
 */
#define TIMER2_CAPCON1_CAP1LS_SET(mode)                                                                                \
    (CAPCON1 = ((CAPCON1 & (~TIMER2_CAPCON1_CAP1LS_MSK)) | ((mode) << TIMER2_CAPCON1_CAP1LS_POS)))
#define GET_TIMER2_CAP1LS                                                                                              \
    ((CAPCON1 & TIMER2_CAPCON1_CAP1LS_MSK) >> TIMER2_CAPCON1_CAP1LS_POS) /*!< 获取捕获通道1触发条件状态 */

/**
 * TIMER2输入捕获通道0条件选择
 * @param[in] mode
 * -# TIMER2_CAPLS_FALLING:        下降沿
 * -# TIMER2_CAPLS_RISING:         上升沿
 * -# TIMER2_CAPLS_RISING_FALLING: 上升沿或下降沿
 */
#define TIMER2_CAPCON1_CAP0LS_SET(mode)                                                                                \
    (CAPCON1 = ((CAPCON1 & (~TIMER2_CAPCON1_CAP0LS_MSK)) | ((mode) << TIMER2_CAPCON1_CAP0LS_POS)))
#define GET_TIMER2_CAP0LS                                                                                              \
    ((CAPCON1 & TIMER2_CAPCON1_CAP0LS_MSK) >> TIMER2_CAPCON1_CAP0LS_POS) /*!< 获取捕获通道0触发条件状态 */

/**@} */

/**@name 输入捕获控制寄存器2-CAPCON2
 * @{
 */
#define TIMER2_CAPCON2_CAPF3_POS (3)
#define TIMER2_CAPCON2_CAPF3_MSK (0x1 << TIMER2_CAPCON2_CAPF3_POS)
#define TIMER2_CAPCON2_CAPF2_POS (2)
#define TIMER2_CAPCON2_CAPF2_MSK (0x1 << TIMER2_CAPCON2_CAPF2_POS)
#define TIMER2_CAPCON2_CAPF1_POS (1)
#define TIMER2_CAPCON2_CAPF1_MSK (0x1 << TIMER2_CAPCON2_CAPF1_POS)
#define TIMER2_CAPCON2_CAPF0_POS (0)
#define TIMER2_CAPCON2_CAPF0_MSK (0x1 << TIMER2_CAPCON2_CAPF0_POS)

/**
 * 输入捕获通道0标志位
 * @return 1: 输入捕获通道0探测到边沿触发事件发生
 * @note   该位由硬件置位，由软件写0清零
 */
#define IS_TIME2_CAPF0_FLAG  ((CAPCON2 & TIMER2_CAPCON2_CAPF0_MSK) >> TIMER2_CAPCON2_CAPF0_POS)
#define CLR_TIME2_CAPF0_FLAG (CAPCON2 &= ~TIMER2_CAPCON2_CAPF0_MSK) /*!< 清除输入捕获通道0标志位 */
/**
 * 输入捕获通道1标志位
 * @return 1: 输入捕获通道1探测到边沿触发事件发生
 * @note   该位由硬件置位，由软件写0清零
 */
#define IS_TIME2_CAPF1_FLAG  ((CAPCON2 & TIMER2_CAPCON2_CAPF1_MSK) >> TIMER2_CAPCON2_CAPF1_POS)
#define CLR_TIME2_CAPF1_FLAG (CAPCON2 &= ~TIMER2_CAPCON2_CAPF1_MSK) /*!< 清除输入捕获通道1标志位 */
/**
 * 输入捕获通道2标志位
 * @return 1: 输入捕获通道2探测到边沿触发事件发生
 * @note   该位由硬件置位，由软件写0清零
 */
#define IS_TIME2_CAPF2_FLAG  ((CAPCON2 & TIMER2_CAPCON2_CAPF2_MSK) >> TIMER2_CAPCON2_CAPF2_POS)
#define CLR_TIME2_CAPF2_FLAG (CAPCON2 &= ~TIMER2_CAPCON2_CAPF2_MSK) /*!< 清除输入捕获通道2标志位 */
/**
 * 输入捕获通道3标志位
 * @return 1: 输入捕获通道3探测到边沿触发事件发生
 * @note   该位由硬件置位，由软件写0清零
 */
#define IS_TIME2_CAPF3_FLAG  ((CAPCON2 & TIMER2_CAPCON2_CAPF3_MSK) >> TIMER2_CAPCON2_CAPF3_POS)
#define CLR_TIME2_CAPF3_FLAG (CAPCON2 &= ~TIMER2_CAPCON2_CAPF3_MSK) /*!< 清除输入捕获通道3标志位 */
/**@} */

/**@name TIMER3控制寄存器-T3CON
 * @{
 */
#define TIMER3_DIV_REV        (0x0) /*!< 保留位 */
#define TIMER3_DIV_2          (0x1) /*!< 2分频，TIMER3计数时钟为CLK_P/2 */
#define TIMER3_DIV_4          (0x2) /*!< 4分频，TIMER3计数时钟为CLK_P/4 */
#define TIMER3_DIV_8          (0x3) /*!< 8分频，TIMER3计数时钟为CLK_P/8 */
#define TIMER3_DIV_16         (0x4) /*!< 16分频，TIMER3计数时钟为CLK_P/16 */
#define TIMER3_DIV_32         (0x5) /*!< 32分频，TIMER3计数时钟为CLK_P/32 */
#define TIMER3_DIV_64         (0x6) /*!< 64分频，TIMER3计数时钟为CLK_P/64 */
#define TIMER3_DIV_128        (0x7) /*!< 128分频，TIMER3计数时钟为CLK_P/128 */
#define TIMER3_DIV_SLE        TIMER3_DIV_128

#define UART_TIMER3_DIV_SLE   TIMER3_DIV_2 /*!< 串口TIMER3分频选择 */

#define TIMER3_T3CON_TR3_POS  (6)
#define TIMER3_T3CON_TR3_MSK  (0x1 << TIMER3_T3CON_TR3_POS)
#define TIMER3_T3CON_T3PS_POS (0)
#define TIMER3_T3CON_T3PS_MSK (0x7 << TIMER3_T3CON_T3PS_POS)

#define ENABLE_TIMER3         (T3CON |= TIMER3_T3CON_TR3_MSK)  /*!< TIMER3启动 */
#define DISABLE_TIMER3        (T3CON &= ~TIMER3_T3CON_TR3_MSK) /*!< TIMER3关闭 */

/**
 * TIMER3分频选择
 * @param[in] mode
 * -# TIMER3_DIV_2:2分频，TIMER3计数时钟为CLK_P/2
 * -# TIMER3_DIV_4:4分频，TIMER3计数时钟为CLK_P/4
 * -# TIMER3_DIV_8:8分频，TIMER3计数时钟为CLK_P/8
 * -# TIMER3_DIV_16:16分频，TIMER3计数时钟为CLK_P/16
 * -# TIMER3_DIV_REV:保留位
 */
#define TIMER3_T3CON_DIV_SET(mode) (T3CON = ((T3CON & (~TIMER3_T3CON_T3PS_MSK)) | ((mode) << TIMER3_T3CON_T3PS_POS)))
/**@} */

/**@name TIMER3数据寄存器-T3RH T3RL
 * @{
 */
/**
 * TIMER3数据寄存器
 * @param[in] dataH  Timer3数据寄存器高位
 * @param[in] dataL  Timer3数据寄存器低位
 */
#define TIMER3_DATA_REG(dataH, dataL)                                                                                  \
    T3RH = (dataH);                                                                                                    \
    T3RL = (dataL);
/**@} */

/**@name 外部函数
 * @{
 */
void TIMER0_ConfigMode(uint8_t u8mode, uint8_t u8gate, uint8_t u8cnt);
void TIMER1_ConfigMode(uint8_t u8mode, uint8_t u8gate, uint8_t u8cnt);
void TIMER2_ConfigCap0Mode(uint8_t u8trigger, uint8_t u8filter);
void TIMER2_ConfigCap1Mode(uint8_t u8trigger, uint8_t u8filter);
void TIMER2_ConfigCap2Mode(uint8_t u8trigger, uint8_t u8filter);
void TIMER2_ConfigCap3Mode(uint8_t u8trigger, uint8_t u8filter);
/**@} */

#endif /* __TIMER_H__ */
