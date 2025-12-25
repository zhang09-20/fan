/**
 * @file      bsp.h
 * @brief     Board Support package header file
 * @author    Way-On MCU Application Team
 * @date      2024-09
 * @version   V1.0.0
 * @copyright WAYON
 */
#ifndef __BSP_H__
#define __BSP_H__
#include "common.h"

//---------------constant define------------------------------------------//

//---------------variable define------------------------------------------//

//---------------function define------------------------------------------//
void ACMP_Config(void);
void ADC_Config(void);
void OPA_Config(void);
void PWM_Config(void);
void SetPwm(uint8_t tmp_pwm);
void Update_PwmDuty(uint16_t duty_pwm);
void TIMER1_Config(void);
void TIMER2_Config(void);
void TIMER3_Config(void);
void GPIO_OutPut_Config(void);

#endif /* __BSP_H__ */