#ifndef __BLDC_H__
#define __BLDC_H__
//---------------user includes------------------------------------------//
#include "WY8S9003xx.h"
#include "acmp.h"
#include "adc.h"
#include "bsp.h"
#include "bsp_config.h"
#include "common.h"
#include "gpio.h"
#include "hall.h"
#include "motor.h"
#include "pwm.h"
#include "timer.h"
#include "uart_printf.h"

//---------------constant define------------------------------------------//

//---------------variable define------------------------------------------//

#define true  1
#define false 0
typedef enum {
    OFF = 0, // 关
    ON       // 开
} enable_signal_e;

typedef enum {
    MOTOR_DIR_CW = 0, // 顺时针
    MOTOR_DIR_CCW     // 逆时针
} motor_dir_e;

typedef enum { INTEND = 0, STARTMODE, RUNMODE, BRAKEMODE, STOPMODE, FAULTMODE } moter_mode_e;

typedef struct {
    int16_t  Kp_gain;              // 比例系数
    uint16_t Kp_divisor;           // 比例系数因子
    int16_t  Ki_gain;              // 积分系数
    uint16_t Ki_divisor;           // 积分系数因子
    int32_t  lower_limit_output;   // 总输出下限
    int32_t  upper_limit_output;   // 总输出上限
    int32_t  lower_limit_integral; // 积分项下限
    int32_t  upper_limit_integral; // 积分项上限
    int32_t  integral;             // 积分累积
    int16_t  Kd_gain;              // 微分系数
    uint16_t Kd_divisor;           // 微分系数因子
    int32_t  last_error;           // 上次误差
} pid_struct_t;

typedef struct {
    volatile uint8_t  phase;     /*相位*/
    uint8_t           emf_state; /*反电动势*/
    int16_t           desired_speed;
    int16_t           speed;
    uint16_t          speed_count[6];
    volatile uint16_t speed_timer; /*timer溢出次数*/
    uint8_t           speed_over;
    uint32_t          speed_count_average;
    uint32_t          count_zero30;
    uint8_t           timer_freq;
    uint16_t          timer_freq_led;
    uint8_t           led_flag;
    uint16_t          timer_freq_fault;
    uint8_t           fault_flag;
    uint16_t          bus_V_data;
    uint16_t          bus_I_data;
    uint16_t          current_temp;
    uint8_t           bus_V_flag;
    uint8_t           bus_I_flag;
    uint8_t           over_temp_flag;
    uint8_t           overvoltage_en;
    uint8_t           undervoltage_en;
    uint8_t           overcurrent_en;
    uint8_t           overtemp_en;
    uint8_t           over30_en;
    uint8_t           interacmp;

    uint8_t vnp_acmp;
    uint8_t wnp_acmp;

    uint8_t  pwm_change;
    uint16_t start_crosszero_delay;
    uint16_t timer_30;
    uint8_t  fault_led;
} bldc_obj_t;

//---------------function define------------------------------------------//
extern bldc_obj_t data    g_bldc_motor;
extern pid_struct_t xdata g_speed_pid;
extern enable_signal_e    g_commuta_angle;
extern motor_dir_e        g_motor_dir;

#endif //__BLDC_H__
