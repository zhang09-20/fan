#ifndef __IPD_H__
#define __IPD_H__

#include "common.h"

/*

/**
 * @brief IPD结构体定义
 *
 */
typedef struct {
    volatile int16_t  I_a_pos;
    volatile int16_t  I_a_neg;
    volatile int16_t  I_b_pos;
    volatile int16_t  I_b_neg;
    volatile int16_t  I_c_pos;
    volatile int16_t  I_c_neg;
    volatile int16_t  I_a_error;
    volatile int16_t  I_b_error;
    volatile int16_t  I_c_error;
    volatile int16_t  I_abc[6];
    volatile uint16_t quiescent_current;
} bldc_IPD_para_t;

typedef void (*pctr)(void);

extern bldc_IPD_para_t xdata ipd_param;
extern uint8_t xdata         new_hall_state;

void ipd_inject_pulse(uint8_t hall_state);
void ipd_check(void);
void motor_get_init_pos(void);

#endif /** __IPD_H__ */
