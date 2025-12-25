#ifndef __MOTOR_H__
#define __MOTOR_H__
//---------------constant define------------------------------------------//

//---------------variable define------------------------------------------//

//---------------function define------------------------------------------//
#ifdef MD2403
#define PWM_L_OFF 0U
#define PWM_L_ON  1U

#define PWM_H_OFF 0U
#define PWM_H_ON  1U
#endif

#ifdef MD2430
#define PWM_L_OFF 1U
#define PWM_L_ON  0U

#define PWM_H_OFF 0U
#define PWM_H_ON  1U
#endif

#ifdef MD4803
#define PWM_L_OFF 1U
#define PWM_L_ON  0U

#define PWM_H_OFF 0U
#define PWM_H_ON  1U
#endif

#ifdef MD4830
#define PWM_L_OFF 1U
#define PWM_L_ON  0U

#define PWM_H_OFF 0U
#define PWM_H_ON  1U
#endif

#define PWM_C_ON  PWMMASKEN = 0xC5;
#define PWM_B_ON  PWMMASKEN = 0xD1;
#define PWM_A_ON  PWMMASKEN = 0xD4;

#define PWM_OFF   PWMMASKEN = 0xD5; // 需要将PWM全关

#define PHASE_A_H PWM_A_ON
#define PHASE_B_H PWM_B_ON
#define PHASE_C_H PWM_C_ON

#define PHASE_A_L                                                                                                      \
    do {                                                                                                               \
        if (g_motor_dir == MOTOR_DIR_CW) {                                                                             \
            PIN_PWM_CN = PWM_L_OFF;                                                                                    \
            PIN_PWM_BN = PWM_L_OFF;                                                                                    \
        } else {                                                                                                       \
            PIN_PWM_CN_DIR = PWM_L_OFF;                                                                                \
            PIN_PWM_BN_DIR = PWM_L_OFF;                                                                                \
        }                                                                                                              \
        PIN_PWM_AN = PWM_L_ON;                                                                                         \
    } while (0)

#define PHASE_B_L                                                                                                      \
    do {                                                                                                               \
        PIN_PWM_AN = PWM_L_OFF;                                                                                        \
        if (g_motor_dir == MOTOR_DIR_CW) {                                                                             \
            PIN_PWM_CN = PWM_L_OFF;                                                                                    \
            PIN_PWM_BN = PWM_L_ON;                                                                                     \
        } else {                                                                                                       \
            PIN_PWM_CN_DIR = PWM_L_OFF;                                                                                \
            PIN_PWM_BN_DIR = PWM_L_ON;                                                                                 \
        }                                                                                                              \
    } while (0)

#define PHASE_C_L                                                                                                      \
    do {                                                                                                               \
        PIN_PWM_AN = PWM_L_OFF;                                                                                        \
        \ 
				if (g_motor_dir == MOTOR_DIR_CW)                                                       \
        {                                                                                                              \
            PIN_PWM_BN = PWM_L_OFF;                                                                                    \
            PIN_PWM_CN = PWM_L_ON;                                                                                     \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            PIN_PWM_BN_DIR = PWM_L_OFF;                                                                                \
            PIN_PWM_CN_DIR = PWM_L_ON;                                                                                 \
        }                                                                                                              \
    } while (0)

#define PWM_GPIO_OFF                                                                                                   \
    do {                                                                                                               \
        PIN_PWM_CN = PWM_L_OFF;                                                                                        \
        PIN_PWM_AN = PWM_L_OFF;                                                                                        \
        PIN_PWM_BN = PWM_L_OFF;                                                                                        \
        PWM_OFF;                                                                                                       \
    } while (0)

#define BRAKE_OFF                                                                                                      \
    do {                                                                                                               \
        PIN_PWM_CN = PWM_L_ON;                                                                                         \
        PIN_PWM_AN = PWM_L_ON;                                                                                         \
        PIN_PWM_BN = PWM_L_ON;                                                                                         \
        PWM_OFF;                                                                                                       \
    } while (0)

#define GAT_ONCE_I_BUS                                                                                                 \
    do {                                                                                                               \
        ADC_ConfigChannel(ADC_INTERNAL_CH, ADC_DIV_4);                                                                 \
        \ 
				ADC_ADCCON2_VREF_SEL(ADC_INPUT_OPA_ADCIN1);                                            \
        while (1 == GET_ADC_ADCCON0_SWS)                                                                               \
            ;                                                                                                          \
        ENABLE_ADC_SOFT_CVT;                                                                                           \
        while (0 == IS_ADC_IF_FLAG)                                                                                    \
            ;                                                                                                          \
        CLR_ADC_IF_FLAG;                                                                                               \
        g_bldc_motor.bus_I_data = GET_ADC_CVT_12BIT;                                                                   \
    } while (0)
#define GAT_ONCE_U_BUS                                                                                                 \
    do {                                                                                                               \
        ADC_ConfigChannel(ADC_CHANNEL_MAP(PORTn_BUS_VOL_ADC), ADC_DIV_4);                                              \
        \ 
				while (1 == GET_ADC_ADCCON0_SWS);                                                      \
        ENABLE_ADC_SOFT_CVT;                                                                                           \
        while (0 == IS_ADC_IF_FLAG)                                                                                    \
            ;                                                                                                          \
        CLR_ADC_IF_FLAG;                                                                                               \
        g_bldc_motor.bus_V_data = GET_ADC_CVT_12BIT;                                                                   \
    } while (0)
#define GAT_ONCE_TEMP                                                                                                  \
    do {                                                                                                               \
        ADC_ConfigChannel(ADC_CHANNEL_MAP(PORTn_TEMP_ADC), ADC_DIV_4);                                                 \
        \ 
				while (1 == GET_ADC_ADCCON0_SWS);                                                      \
        ENABLE_ADC_SOFT_CVT;                                                                                           \
        while (0 == IS_ADC_IF_FLAG)                                                                                    \
            ;                                                                                                          \
        CLR_ADC_IF_FLAG;                                                                                               \
        g_bldc_motor.current_temp = GET_ADC_CVT_12BIT;                                                                 \
    } while (0)

#define SENSE_A           ACMP0CON0 = 0x4C                  // ACMP_ACMP0CON0_COPS_SEL(ACMP0_INP3);
#define SENSE_B           ACMP0CON0 = g_bldc_motor.vnp_acmp // ACMP_ACMP0CON0_COPS_SEL(ACMP0_INP0);
#define SENSE_C           ACMP0CON0 = g_bldc_motor.wnp_acmp // ACMP_ACMP0CON0_COPS_SEL(ACMP0_INP1);

#define ClrSENSE          ACMP0CON0 &= (~0x80)
#define SENSE             ((ACMP0CON0 & 0x80))
#define SENSE_L           (!(ACMP0CON0 & 0x01)) //
#define SENSE_H           ((ACMP0CON0 & 0x01))
#define ENABLE_SENSE_INT  EI2 |= 0x04;
#define DISABLE_SENSE_INT EI2 &= ~0x04;

#define SENSE_FALLING_INT ACMPBCON = 0x02; // {ACMP0_FB_SEL(ACMP0_FALLING_INC_EDGEFB);}
#define SENSE_RISING_INT  ACMPBCON = 0x01; // {ACMP0_FB_SEL(ACMP0_RISING_INC_EDGEFB);}
#define SENSE_TOGGLE_INT  ACMPBCON = 0x03; // {ACMP0_FB_SEL(ACMP0_BOTH_INC_EDGEFB);}

void     motor_forced_start(void);
void     motor_init_param(void);
void     motor_init_periph(void);
bool     motor_start_sensorless(void);
void     motor_work(void);
uint16_t motor_get_pot_ADCData(void);
uint16_t motor_get_speed(void);
void     motor_get_speed_sensorless();
void     motor_get_speed_hall(void);
void     motor_handle_protection(void);
int8_t   motor_get_temp_by_ADCData(uint16_t temp_adc);

void BRAKE_g_sysmode(void);

#endif /* __MOTOR_H__ */
