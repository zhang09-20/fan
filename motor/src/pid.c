/**
 * @file      pid.c
 * @brief     Pid adjustment function
 * @author    Software Team
 * @date      2024-09
 * @version   V1.0.0
 * @copyright WAYON
 */
/******************************************************************************
 Head file include
******************************************************************************/
#include "pid.h"
#include "bldc.h"

/**
 * @brief PID parameters initialization.
 *
 * @param pid Structure pointer of PID parameters.
 */
void pid_init(pid_struct_t *pid)
{
    /******************************************* PID**************************************************************/
    pid->Kp_gain              = PID_SPEED_KP_DEFAULT;
    pid->Kp_divisor           = SP_KPDIV;
    pid->Ki_gain              = PID_SPEED_KI_DEFAULT;
    pid->Ki_divisor           = SP_KIDIV;
    pid->Kd_gain              = PID_SPEED_KD_DEFAULT;
    pid->Kd_divisor           = SP_KDDIV;
    pid->last_error           = 0;
    pid->lower_limit_output   = MAX_DUTY / 100 * STARTING_RATIO * 8;
    pid->upper_limit_output   = IQMAX * 8;
    pid->lower_limit_integral = -65535; // MAX_DUTY/100*4* SP_KIDIV*10;
    pid->upper_limit_integral = 65535;  // IQMAX * SP_KIDIV*10;
    pid->integral             = 0;
    /******************************************* PID**************************************************************/
}

/**
 * @brief Function of PID regulate.
 *
 * @param reference Target value.
 * @param present_fb Current value.
 * @param pid Structure pointer of PID parameters.
 * @return uint16_t controlled object.
 */
uint16_t pid_regulate(int16_t reference, int16_t present_fb, pid_struct_t *pid)
{
    volatile int32_t error, p_term, i_term, res;
    volatile int32_t aux;
    volatile int32_t temp;
    volatile int32_t d_term;
    int32_t          wDischarge = 0;
    error                       = (int32_t)(reference - present_fb);
    p_term                      = (int32_t)pid->Kp_gain * error;
    if (pid->Ki_gain == 0) {
        pid->integral = 0;
    } else {
        i_term = (int32_t)pid->Ki_gain * error;
        aux    = pid->integral + (int32_t)(i_term);
        if (aux > pid->upper_limit_integral) {
            pid->integral = pid->upper_limit_integral;
        } else if (aux < pid->lower_limit_integral) {
            pid->integral = pid->lower_limit_integral;
        } else {
            pid->integral = (int32_t)(aux);
        }
    }
    if (pid->Ki_gain == 0) {
        d_term = 0;
    } else {
        temp            = error - pid->last_error;
        d_term          = pid->Kd_gain * temp;
        pid->last_error = error;
    }
    res = (int32_t)(p_term >> pid->Kp_divisor) + (pid->integral >> pid->Ki_divisor) + (d_term >> pid->Kd_divisor);
    if (res >= pid->upper_limit_output) {
        wDischarge = pid->upper_limit_output - res;
        res        = pid->upper_limit_output;
    } else if (res < pid->lower_limit_output) {
        wDischarge = pid->lower_limit_output - res;
        res        = pid->lower_limit_output;
    }
    pid->integral += wDischarge;
    return ((uint16_t)(res));
}
