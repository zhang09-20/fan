#ifndef __BSP_CONFIG_H__
#define __BSP_CONFIG_H__

#include "util.h"

/********************* 管脚配置 ******************************************/
// ACMP Port in Sensorless BLDC
#define PORTn_ACMP_INP_U 06
#define PORTn_ACMP_INP_V 15
#define PORTn_ACMP_INP_W 07
#define PORTn_ACMP_INN   05

#define PORTn_ACMP_INP_V_DIR 07
#define PORTn_ACMP_INP_W_DIR 15
// HALL Port in Sensor BLDC
#define PORTn_HALL_U 02
#define PORTn_HALL_V 13
#define PORTn_HALL_W 14
// PWM Port
#define PORTn_PWM_AP 22
#define PORTn_PWM_AN 23
#define PORTn_PWM_BP 11
#define PORTn_PWM_BN 10
#define PORTn_PWM_CP 24
#define PORTn_PWM_CN 16

#define PORTn_PWM_BP_DIR 24
#define PORTn_PWM_BN_DIR 16
#define PORTn_PWM_CP_DIR 11
#define PORTn_PWM_CN_DIR 10
// Potentiometer Port
#define PORTn_POT_ADC 04
// Temperature Port
#define PORTn_TEMP_ADC 04
// Bus Vol Port
#define PORTn_BUS_VOL_ADC  04

#define PORTn_FWD  14
#define PORTn_POWER  12
#define PORTn_LED         21

/**/
#define PIOCFG_ACMP_INP_U     GEN_PIOCFG(PORTn_ACMP_INP_U)
#define PIOCFG_ACMP_INP_V     GEN_PIOCFG(PORTn_ACMP_INP_V)
#define PIOCFG_ACMP_INP_W     GEN_PIOCFG(PORTn_ACMP_INP_W)
#define PIOCFG_ACMP_INN       GEN_PIOCFG(PORTn_ACMP_INN)
#define PIOCFG_PWM_AP         GEN_PIOCFG(PORTn_PWM_AP)
#define PIOCFG_PWM_AN         GEN_PIOCFG(PORTn_PWM_AN)
#define PIOCFG_PWM_BP         GEN_PIOCFG(PORTn_PWM_BP)
#define PIOCFG_PWM_BN         GEN_PIOCFG(PORTn_PWM_BN)
#define PIOCFG_PWM_CP         GEN_PIOCFG(PORTn_PWM_CP)
#define PIOCFG_PWM_CN         GEN_PIOCFG(PORTn_PWM_CN)
#define PIOCFG_POT_ADC        GEN_PIOCFG(PORTn_POT_ADC)
#define PIOCFG_TEMP_ADC       GEN_PIOCFG(PORTn_TEMP_ADC)
#define PIOCFG_BUS_VOL_ADC    GEN_PIOCFG(PORTn_BUS_VOL_ADC)

#define PIOCFG_FWD            GEN_PIOCFG(PORTn_FWD)
#define PIOCFG_POWER          GEN_PIOCFG(PORTn_POWER)
#define PIOCFG_LED            GEN_PIOCFG(PORTn_LED)
#define PIOCFG_ACMP_INP_V_DIR GEN_PIOCFG(PORTn_ACMP_INP_V_DIR)
#define PIOCFG_ACMP_INP_W_DIR GEN_PIOCFG(PORTn_ACMP_INP_W_DIR)
#define PIOCFG_PWM_BP_DIR     GEN_PIOCFG(PORTn_PWM_BP_DIR)
#define PIOCFG_PWM_BN_DIR     GEN_PIOCFG(PORTn_PWM_BN_DIR)
#define PIOCFG_PWM_CP_DIR     GEN_PIOCFG(PORTn_PWM_CP_DIR)
#define PIOCFG_PWM_CN_DIR     GEN_PIOCFG(PORTn_PWM_CN_DIR)
/**/
#define PIN_PWM_AP     GEN_PIN(PORTn_PWM_AP)
#define PIN_PWM_AN     GEN_PIN(PORTn_PWM_AN)
#define PIN_PWM_BP     GEN_PIN(PORTn_PWM_BP)
#define PIN_PWM_BN     GEN_PIN(PORTn_PWM_BN)
#define PIN_PWM_CP     GEN_PIN(PORTn_PWM_CP)
#define PIN_PWM_CN     GEN_PIN(PORTn_PWM_CN)

#define PIN_FWD        GEN_PIN(PORTn_FWD)
#define PIN_POWER      GEN_PIN(PORTn_POWER)
#define PIN_LED        GEN_PIN(PORTn_LED)
#define PIN_PWM_BP_DIR GEN_PIN(PORTn_PWM_BP_DIR)
#define PIN_PWM_BN_DIR GEN_PIN(PORTn_PWM_BN_DIR)
#define PIN_PWM_CP_DIR GEN_PIN(PORTn_PWM_CP_DIR)
#define PIN_PWM_CN_DIR GEN_PIN(PORTn_PWM_CN_DIR)

//---------------macro define------------------------------------------//
#define SYSCLK 48000000L
/*******************电机参数*****************************/
#define MOTOR_POLES 2 // 电机极对数
#define MOTORDIR    1 // 电机正反转（MOTOR_DIR_CCW逆时针，MOTOR_DIR_CW顺时针）
/*******************PWM配置*****************************/
#define PWM_CARRIER 120000                      // 载频（HZ）
#define MAX_DUTY    (SYSCLK / PWM_CARRIER / 2) // 最大占空比（此处为了好算故不减一）
/*******************启动算法*****************************/
#define STARTING_RATIO        20 // 启动占空比
#define NOSEN_MIN_DUTY        (MAX_DUTY * STARTING_RATIO / 100)

#define ACMP_FILT             2 // 0-7
#define START_DELAY           82 //(单位0.1ms,不同电机启动时间需要微调，高转数电机需要调小，低转速电机需要调大)
#define START_STEP_NUM        4  // 拖动步数,建议2-6之间
#define START_CROSSZERO_DELAY 2600
/*******************高频注入***************************/
#define IPD_MODE_3PHASE_INJECT     /** 三相注入模式 */
#define PULSE_HIGH_LEVEL_TIME  30  /*脉冲高电平时长*/
#define PULSE_LOW_LEVEL_TIME   30  /* (PULSEHIGHLEVELTIME / 2) */
#define PULSE_WAIT_TIME        380 /* (PULSEHIGHLEVELTIME * 2) */

/*******************电流参数*****************************/
#define SHUNT_RES              1    // 分流电阻（mΩ）
#define SHUNT_MULT             52   // 放大倍数
#define PROTECT_OFF_PWM             //(PROTECT_OFF_PWM/PROTECT_BRAKE)关闭六臂/电机自身刹车

#define OVER_SHUNT_LEVEL1_EN   1    // 一级过流保护使能 0不使能 1使能
#define OVER_SHUNT_LEVEL2_EN   1    // 二级过流保护使能 0不使能 1使能
#define OVER_SHUNT_LEVEL3_EN   1    // 三级过流保护使能 0不使能 1使能
#define OVER_SHUNT_LEVEL4_EN   1    // 四级过流保护使能 0不使能 1使能

#define SHUNT_OTIME_LEVEL1     1000 // 一级过流限时（ms)
#define SHUNT_GATE_DATA_LEVEL1 1278 // 一级过流保护值（30A）（50A*采样电阻0.001）*（放大倍数52）/5V*（4095）

#define SHUNT_OTIME_LEVEL2     110  // 二级过流限时（ms)
#define SHUNT_GATE_DATA_LEVEL2 1618 // 二级过流保护值（38A）（60A*采样电阻0.001）*（放大倍数52）/5V*（4095）

#define SHUNT_OTIME_LEVEL3     21   // 三级过流限时（ms)
#define SHUNT_GATE_DATA_LEVEL3 2257 // 三级过流保护值（53A）（70A*采样电阻0.001）*（放大倍数52）/5V*（4095）

#define SHUNT_OTIME_LEVEL4     10   // 四级过流限时（ms)
#define SHUNT_GATE_DATA_LEVEL4 2981 // 四级过流保护值（70A）（90A*采样电阻0.001）*（放大倍数52）/5V*（4095）

/*******************电压参数*****************************/
#define VOLTAGE_MULT       6   // 放大倍数
#define OVER_VOLTAGE_EN    1    // 过压使能（1:使能。0：不使能）
#define OVER_VOLTAGE_DATA  3276 // 过压阈值24v(保护电压/放大倍数/5*4095)
#define OVER_VOLTAGE_TIME  20   // 过压限时(50ms)
#define UNDER_VOLTAGE_EN   1    // 欠压使能（1:使能。0：不使能）
#define UNDER_VOLTAGE_DATA 1706  // 欠压阈值12.5v(保护电压/放大倍数/5*4095)
#define UNDER_VOLTAGE_TIME 20   // 欠压限时(50ms)
/*******************温度参数*****************************/
#define OVER_TEMPER_EN    1    // 过温使能（1:使能。0：不使能）
#define OVER_TEMPER_DATA  40  // 过温阈值100 (1000/(1000+100000)*4095)
#define OVER_TEMPER_TIME  20   // 过温限时(50ms)
#define UNDER_TEMPER_EN   1    // 低温使能（1:使能。0：不使能）
#define UNDER_TEMPER_DATA 1686 // 低温阈值-20 (70000/(70000+100000)*4095)
#define UNDER_TEMPER_TIME 20   // 低温限时(50ms)

/*******************速度参数*****************************/
#define SPEED_OPEN_LOOP //(SPEED_OPEN_LOOP/SPEED_CLOSE_LOOP)

/*******************驱动板型号*****************************/
#define MD2403
/*******************PID参数*****************************/
/****************************** 速度环的PID参数 *******************************************************/
#define PID_SPEED_KP_DEFAULT (int16_t)1 // 68//53//563//230//200
#define PID_SPEED_KI_DEFAULT (int16_t)1 // 4//7//600//200//2
#define PID_SPEED_KD_DEFAULT (int16_t)0
#define IQMAX                MAX_DUTY   // 速度环输出最大值

#define SP_KPDIV             ((uint8_t)(2))
#define SP_KIDIV             ((uint8_t)(2))
#define SP_KDDIV             ((uint8_t)(0))

//---------------constant define------------------------------------------//

//---------------variable define------------------------------------------//

//---------------function define------------------------------------------//

#endif /* __BSP_CONFIG_H__ */
