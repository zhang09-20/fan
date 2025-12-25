/**
 * @file      wy8sxx_it.c
 * @brief     execute bldc motor controller interrupt program
 * @author    Software Team
 * @date      2024-09
 * @version   V1.0.0
 * @copyright WAYON
 */
/******************************************************************************
 Head file include
******************************************************************************/
#include "application.h"
#include "bldc.h"
#include "pid.h"

extern moter_mode_e g_sysmode;
/**
 * @brief IRQ Handler of TIMER1.
 * @note  This function is used to set the flag to sample bus voltage, temperature and
 *        bus current.
 */
void _TIMER1_IRQHandler(void) interrupt TIMER1_VECTOR /*1ms*/
{
    TH1 = 0xA2;
    TL1 = 0x40;

    // ===== 自定义 5ms周期 ========================
    // Flag_1ms = 1;

//    Led_Deal();

    if (++Flag_5ms_counter >= 5) {
        Flag_5ms_counter = 0;
        Flag_5ms         = 1;
    }
    // ============================================

    g_bldc_motor.bus_I_flag = 1; // 电流1ms采集一次

    g_bldc_motor.timer_freq++;

    if (50 <= g_bldc_motor.timer_freq) {
        g_bldc_motor.bus_V_flag = 1;
        g_bldc_motor.timer_freq = 0;
    }

    if (0 != g_bldc_motor.fault_led) {
        g_bldc_motor.timer_freq_led++;
        if (500 <= g_bldc_motor.timer_freq_led) // 0.5S
        {
            g_bldc_motor.led_flag       = 1;
            g_bldc_motor.timer_freq_led = 0;
        }
    }

    if (BRAKEMODE == g_sysmode) {
        g_bldc_motor.timer_freq_fault++;
        if (10000 <= g_bldc_motor.timer_freq_fault) // 10S
        {
            g_bldc_motor.fault_flag       = 1;
            g_bldc_motor.timer_freq_fault = 0;
        }
    }
}

/**
 * @brief IRQ handler of TIMER2.
 * @note This funtion is used to count the motor speed.
 */
void _TIMER2_IRQHandler(void) interrupt TIMER2_VECTOR
{
    CLR_TIME2_TF2_FLAG;
    g_bldc_motor.speed_timer++;
}

/**
 * @brief IRQ handler of TIMER3.
 * @note  This function is used to handle the operation in crossing zero by 30 degrees.
 */
void _TIMER3_IRQHandler(void) interrupt TIMER3_VECTOR
{
    DISABLE_TIMER3;
//    P04 =! P04;
    g_bldc_motor.pwm_change = 1;
    switch (g_bldc_motor.phase) {
    case 0:

        SENSE_B;
        SENSE_RISING_INT;
        ClrSENSE;
        ENABLE_ACMP_INT;
        PHASE_A_H;
        PHASE_C_L;
        g_bldc_motor.phase++;
        break;
    case 1:

        SENSE_A;
        SENSE_FALLING_INT;
        ClrSENSE;
        ENABLE_ACMP_INT;
        PHASE_C_L;
        PHASE_B_H;
        g_bldc_motor.phase++;

        break;
    case 2:

        SENSE_C;
        SENSE_RISING_INT;
        ClrSENSE;
        ENABLE_ACMP_INT;
        PHASE_B_H;
        PHASE_A_L;
        g_bldc_motor.phase++;

        break;
    case 3:

        SENSE_B;
        SENSE_FALLING_INT;
        ClrSENSE;
        ENABLE_ACMP_INT;
        PHASE_A_L;
        PHASE_C_H;
        g_bldc_motor.phase++;

        break;
    case 4:

        SENSE_A;
        SENSE_RISING_INT;
        ClrSENSE;
        ENABLE_ACMP_INT;
        PHASE_C_H;
        PHASE_B_L;
        g_bldc_motor.phase++;

        break;
    case 5:

        SENSE_C;
        SENSE_FALLING_INT;
        ClrSENSE;
        ENABLE_ACMP_INT;
        PHASE_B_L;
        PHASE_A_H;
        g_bldc_motor.phase = 0;
        g_bldc_motor.speed_over++;

        break;
    }
    g_bldc_motor.interacmp = 0;

    if (0 == g_bldc_motor.phase % 2) // 下
    {
        g_bldc_motor.speed_count[2] = (T2RH << 8) + T2RL;
        g_bldc_motor.speed_count_average += g_bldc_motor.speed_count[2];

    } else // 上
    {
        g_bldc_motor.speed_count[1] = (T2RH << 8) + T2RL;
        g_bldc_motor.speed_count_average += g_bldc_motor.speed_count[1];
    }
    T2RL = 0;
    T2RH = 0;
}

/**
 * @brief IRQ handler of ACMP.
 *
 */
void _ACMP_IRQHandler(void) interrupt ACMP_VECTOR
{
    uint16_t u16data;
    ClrSENSE;
//    P04 =! P04;
    if (1 == g_bldc_motor.interacmp) {

        ACMP0_HYSCTL_SEL(ACMP0_HYSCTL_CLOSE);
    } else {
//        P04 =! P04;
        if (0 == g_bldc_motor.phase % 2) {
            ACMP0_HYSCTL_SEL(ACMP0_HYSCTL_P);

            /* 设置ACMP输出迟滞电压 */
            ACMP0_HYS_VOLT_SEL(ACMP0_HYS_VOLT60MV);
        } else {
            ACMP0_HYSCTL_SEL(ACMP0_HYSCTL_N);

            /* 设置ACMP输出迟滞电压 */
            ACMP0_HYS_VOLT_SEL(ACMP0_HYS_VOLT60MV);
        }
        ClrSENSE;
    }
    g_bldc_motor.interacmp++;
    if (2 == g_bldc_motor.interacmp) {
//        P04 =! P04;
        if (12 > g_bldc_motor.timer_30) {
            g_bldc_motor.timer_30++;
            if (0 == g_bldc_motor.phase % 2) {
                u16data = 65535 - (g_bldc_motor.start_crosszero_delay); // 下

            } else {
                u16data = 65535 - (g_bldc_motor.start_crosszero_delay); // 上
            }

        } else {
            if (0 == g_bldc_motor.phase % 2) // 下
            {

                u16data = 65535 - (g_bldc_motor.speed_count[1] >> 3); // 下

            } else                                                    // 上
            {
                u16data = 65535 - (g_bldc_motor.speed_count[2] >> 2)+50; // 上
            }
        }

        T3RH = (u16data >> 8) & 0xFF;
        T3RL = u16data & 0xFF;
        ENABLE_TIMER3;
        DISABLE_ACMP_INT;
    }
}

// /**
//  * @brief IRQ Handler of GPIO.
//  *
//  */
// void _GPIO_IRQHandler(void) interrupt GPIO_VECTOR
// {
//     // clear the GPIO interrupt flag.
//     PIO0IF = 0; /*清中断*/
//     PIO1IF = 0;

//     PIO1IF4   = 0;
//     key_event = 1;
// }

/**
 * @brief IRQ Handler of PWM.
 *
 */
void _PWM_IRQHandler(void) interrupt PWM_VECTOR
{
    CLR_PWM1IF_FLAG;
}
