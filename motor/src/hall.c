/**
 * @file      hall.c
 * @brief     The function of the motor belt hall
 * @author    Software Team
 * @date      2024-09
 * @version   V1.0.0
 * @copyright WAYON
 */
/******************************************************************************
 Head file include
******************************************************************************/
#include "bldc.h"

static uint8_t get_phase_hall();

/**
 * @brief Function of BLDC switch phase.
 *
 */
void motor_switch_phase(void)
{
    static uint8_t phase;
    phase = get_phase_hall();
    if (g_motor_dir == MOTOR_DIR_CW) {
        phase = 7 - phase;
    }
    switch (phase) {
    case 1:
        PHASE_B_H;
        PHASE_C_L;
        break;
    case 2:
        PHASE_A_H;
        PHASE_B_L;
        g_bldc_motor.speed_over++;
        if (MOTOR_POLES == g_bldc_motor.speed_over) {
            g_bldc_motor.speed_count[1] = (T2RH << 8) + T2RL;
            T2RL                        = 0;
            T2RH                        = 0;
        }
        break;
    case 3:
        PHASE_A_H;
        PHASE_C_L;
        break;
    case 4:
        PHASE_C_H;
        PHASE_A_L;
        break;
    case 5:
        PHASE_B_H;
        PHASE_A_L;
        break;
    case 6:
        PHASE_C_H;
        PHASE_B_L;
        break;
    default:
        break;
    }
}

/**
 * @brief Get BLDC phase by HALL.
 *
 * @return uint8_t phase number.
 */
static uint8_t get_phase_hall()
{
    uint8_t tmp = 0;
    tmp |= PIN_HALL_U; // U(A)
    tmp <<= 1;
    tmp |= PIN_HALL_V; // V(B)
    tmp <<= 1;
    tmp |= PIN_HALL_W; // W(C)
    return (tmp & 0x07);
}
