/**
 * @file      ipd.c
 * @brief     The function of the motor ipd
 * @author    Software Team
 * @date      2024-09
 * @version   V1.0.0
 * @copyright WAYON
 */
/******************************************************************************
 Head file include
******************************************************************************/
#include "ipd.h"
#include "bldc.h"
#include "bsp.h"
#include "string.h"
#include "util.h"

/* IPD变量定义 */
bldc_IPD_para_t xdata ipd_param;
uint8_t xdata         new_hall_state = 0;

extern uint16_t        motor_get_ipd_bus_current_ADCData(void);
extern bldc_obj_t data g_bldc_motor;

static void motor_inject_pulse_A_B(void);
static void motor_inject_pulse_B_A(void);
static void motor_inject_pulse_B_C(void);
static void motor_inject_pulse_C_B(void);
static void motor_inject_pulse_C_A(void);
static void motor_inject_pulse_A_C(void);
static void motor_stop_inject(void);
static void motor_inject_pulse_ABC_L(void);
static void motor_inject_pulse_A_BC(void);
static void motor_inject_pulse_BC_A(void);
static void motor_inject_pulse_B_AC(void);
static void motor_inject_pulse_AC_B(void);
static void motor_inject_pulse_C_AB(void);
static void motor_inject_pulse_AB_C(void);

enum ipd_table1_idx_e {
    IPD1_STOP_INJECT_IDX = 0,
    IPD1_INJECT_PULSE_A_B_IDX,
    IPD1_INJECT_PULSE_B_A_IDX,
    IPD1_INJECT_PULSE_B_C_IDX,
    IPD1_INJECT_PULSE_C_B_IDX,
    IPD1_INJECT_PULSE_A_C_IDX,
    IPD1_INJECT_PULSE_C_A_IDX,
    IPD1_INJECT_PULSE_ABC_L_IDX
};

/* IPD两相输出脉冲 */
pctr ipd_table1[8] = {&motor_stop_inject,
                      &motor_inject_pulse_A_B,
                      &motor_inject_pulse_B_A,
                      &motor_inject_pulse_B_C,
                      &motor_inject_pulse_C_B,
                      &motor_inject_pulse_A_C,
                      &motor_inject_pulse_C_A,
                      &motor_inject_pulse_ABC_L};

enum ipd_table2_idx_e {
    IPD2_STOP_INJECT_IDX = 0,
    IPD2_INJECT_PULSE_A_BC_IDX,
    IPD2_INJECT_PULSE_BC_A_IDX,
    IPD2_INJECT_PULSE_B_AC_IDX,
    IPD2_INJECT_PULSE_AC_B_IDX,
    IPD2_INJECT_PULSE_AB_C_IDX,
    IPD2_INJECT_PULSE_C_AB_IDX,
    IPD2_INJECT_PULSE_ABC_L_IDX
};

/* IPD三相输出脉冲 */
pctr ipd_table2[8] = {&motor_stop_inject,
                      &motor_inject_pulse_A_BC,
                      &motor_inject_pulse_BC_A,
                      &motor_inject_pulse_B_AC,
                      &motor_inject_pulse_AC_B,
                      &motor_inject_pulse_C_AB,
                      &motor_inject_pulse_AB_C,
                      &motor_inject_pulse_ABC_L};

/**
 * @brief		IPD脉冲注入
 * @param[in]	mode 上下管注入模式
 * @return		none
 */
void ipd_inject_pulse(uint8_t mode)
{
#ifdef IPD_MODE_2PHASE_INJECT
    ipd_table1[mode]();
#else
    ipd_table2[mode]();
#endif
}

/**
 * @brief		IPD脉冲注入检测
 * @param[in]	none
 * @return		none
 */
void ipd_check(void)
{
    ipd_inject_pulse(IPD1_INJECT_PULSE_A_B_IDX);
    delay_cnt(PULSE_HIGH_LEVEL_TIME);
    ipd_param.I_a_pos = motor_get_ipd_bus_current_ADCData() - ipd_param.quiescent_current;
    ipd_param.I_a_pos = motor_get_ipd_bus_current_ADCData() - ipd_param.quiescent_current;
    ipd_inject_pulse(IPD1_STOP_INJECT_IDX);
    delay_cnt(PULSE_WAIT_TIME);
    ipd_inject_pulse(IPD1_INJECT_PULSE_B_A_IDX);
    delay_cnt(PULSE_LOW_LEVEL_TIME);
    ipd_param.I_a_neg = motor_get_ipd_bus_current_ADCData() - ipd_param.quiescent_current;
    ipd_inject_pulse(IPD1_STOP_INJECT_IDX);
    delay_cnt(PULSE_WAIT_TIME);

    ipd_inject_pulse(3);
    delay_cnt(PULSE_HIGH_LEVEL_TIME);
    ipd_param.I_b_pos = motor_get_ipd_bus_current_ADCData() - ipd_param.quiescent_current;
    ipd_inject_pulse(0);
    delay_cnt(PULSE_WAIT_TIME);
    ipd_inject_pulse(4);
    delay_cnt(PULSE_LOW_LEVEL_TIME);
    ipd_param.I_b_neg = motor_get_ipd_bus_current_ADCData() - ipd_param.quiescent_current;
    ipd_inject_pulse(0);
    delay_cnt(PULSE_WAIT_TIME);

    ipd_inject_pulse(5);
    delay_cnt(PULSE_HIGH_LEVEL_TIME);
    ipd_param.I_c_pos = motor_get_ipd_bus_current_ADCData() - ipd_param.quiescent_current;
    ipd_inject_pulse(0);
    delay_cnt(PULSE_WAIT_TIME);
    ipd_inject_pulse(6);
    delay_cnt(PULSE_LOW_LEVEL_TIME);
    ipd_param.I_c_neg = motor_get_ipd_bus_current_ADCData() - ipd_param.quiescent_current;
    ipd_inject_pulse(0);
    delay_cnt(PULSE_WAIT_TIME);

    motor_get_init_pos();
}

/**
 * @brief		获取电机初始位置
 * @param[in]	none
 * @return		none
 */
void motor_get_init_pos(void)
{
    uint8_t i   = 0;
    int16_t max = 0;
#ifdef IPD_MODE_2PHASE_INJECT
    ipd_param.I_a_error = ipd_param.I_a_pos + ipd_param.I_a_neg;
    ipd_param.I_b_error = ipd_param.I_b_pos + ipd_param.I_b_neg;
    ipd_param.I_c_error = ipd_param.I_c_pos + ipd_param.I_c_neg;

    ipd_param.I_abc[0] = ipd_param.I_a_pos;
    ipd_param.I_abc[1] = ipd_param.I_a_neg;
    ipd_param.I_abc[2] = ipd_param.I_b_pos;
    ipd_param.I_abc[3] = ipd_param.I_b_neg;
    ipd_param.I_abc[4] = ipd_param.I_c_pos;
    ipd_param.I_abc[5] = ipd_param.I_c_neg;
    new_hall_state     = 0;

    max = ipd_param.I_abc[0];
    for (i = 0; i <= 5; i++) {
        if (ipd_param.I_abc[i] > max) {
            max            = ipd_param.I_abc[i];
            new_hall_state = i + 1;
        }
    }

#else
    //    ipd_param.I_a_error = ipd_param.I_a_pos - ipd_param.I_a_neg;
    //    ipd_param.I_b_error = ipd_param.I_b_pos - ipd_param.I_b_neg;
    //    ipd_param.I_c_error = ipd_param.I_c_pos - ipd_param.I_c_neg;

    //    new_hall_state = 0;

    //    if ((ipd_param.I_a_error > ipd_param.I_b_error) && (ipd_param.I_c_error > ipd_param.I_b_error)) {
    //        new_hall_state = 1;
    //    } else if ((ipd_param.I_b_error > ipd_param.I_c_error) && (ipd_param.I_a_error > ipd_param.I_c_error)) {
    //        new_hall_state = 3;
    //    } else if ((ipd_param.I_b_error > ipd_param.I_a_error) && (ipd_param.I_a_error > ipd_param.I_c_error)) {
    //        new_hall_state = 2;
    //    } else if ((ipd_param.I_b_error > ipd_param.I_a_error) && (ipd_param.I_b_error > ipd_param.I_c_error)) {
    //        new_hall_state = 6;
    //    } else if ((ipd_param.I_c_error > ipd_param.I_b_error) && (ipd_param.I_c_error > ipd_param.I_a_error)) {
    //        new_hall_state = 4;
    //    } else if ((ipd_param.I_a_error > ipd_param.I_b_error) && (ipd_param.I_c_error > ipd_param.I_a_error)) {
    //        new_hall_state = 5;
    //    }
    ipd_param.I_a_error = ipd_param.I_a_pos + ipd_param.I_a_neg;
    ipd_param.I_b_error = ipd_param.I_b_pos + ipd_param.I_b_neg;
    ipd_param.I_c_error = ipd_param.I_c_pos + ipd_param.I_c_neg;

    ipd_param.I_abc[0] = ipd_param.I_a_pos;
    ipd_param.I_abc[1] = ipd_param.I_a_neg;
    ipd_param.I_abc[2] = ipd_param.I_b_pos;
    ipd_param.I_abc[3] = ipd_param.I_b_neg;
    ipd_param.I_abc[4] = ipd_param.I_c_pos;
    ipd_param.I_abc[5] = ipd_param.I_c_neg;
    new_hall_state     = 0;

    max = ipd_param.I_abc[0];
    for (i = 0; i <= 5; i++) {
        if (ipd_param.I_abc[i] > max) {
            max            = ipd_param.I_abc[i];
            new_hall_state = i;
        }
    }

#endif

    //    if (g_motor_dir == MOTOR_DIR_CW)
    //		{
    //				switch (new_hall_state)
    //				{
    //						case  0x01:  g_bldc_motor.phase = 0;break;
    //						case  0x02:  g_bldc_motor.phase = 3;break;
    //						case  0x03:  g_bldc_motor.phase = 4;break;
    //						case  0x04:  g_bldc_motor.phase = 1;break;
    //						case  0x05:  g_bldc_motor.phase = 5;break;
    //						case  0x06:  g_bldc_motor.phase = 2;break;
    //						default:    break;
    //				}
    //    }
    //		else
    //		{
    switch (new_hall_state) {
    case 0x01:
        g_bldc_motor.phase = 4;
        break;
    case 0x02:
        g_bldc_motor.phase = 3;
        break;
    case 0x05:
        g_bldc_motor.phase = 2;
        break;
    case 0x00:
        g_bldc_motor.phase = 1;
        break;
    case 0x03:
        g_bldc_motor.phase = 0;
        break;
    case 0x04:
        g_bldc_motor.phase = 5;
        break;
    default:
        break;
    }
    //		}
    memset(&ipd_param, 0, sizeof(ipd_param));
}

/**
 * @brief		Inject a pulse from phase A to phase B.
 * @param[in]	none
 * @return		none
 */
static void motor_inject_pulse_A_B(void)
{
    PIN_PWM_AP = PWM_H_ON;
    //  	PIN_PWM_BN = PWM_L_ON;
    if (g_motor_dir == MOTOR_DIR_CW) {
        PIN_PWM_BN = PWM_L_ON;
    } else {
        PIN_PWM_BN_DIR = PWM_L_ON;
    }
    //    PIN_PWM_BP = PWM_H_OFF;
    //    PIN_PWM_CP = PWM_H_OFF;
    //    PIN_PWM_AN = PWM_L_OFF;
    //
    //    PIN_PWM_CN = PWM_L_OFF;
}

/**
 * @brief		Inject a pulse from phase B to phase A.
 * @param[in]	none
 * @return		none
 */
static void motor_inject_pulse_B_A(void)
{
    //    PIN_PWM_AP = PWM_H_OFF;
    if (g_motor_dir == MOTOR_DIR_CW) {
        PIN_PWM_BP = PWM_H_ON;
    } else {
        PIN_PWM_BP_DIR = PWM_H_ON;
    }
    PIN_PWM_AN = PWM_L_ON;
    //    PIN_PWM_CP = PWM_H_OFF;
    //
    //    PIN_PWM_BN = PWM_L_OFF;
    //    PIN_PWM_CN = PWM_L_OFF;
}

/**
 * @brief		Inject a pulse from phase B to phase C.
 * @param[in]	none
 * @return		none
 */
static void motor_inject_pulse_B_C(void)
{
    //    PIN_PWM_AP = PWM_H_OFF;

    if (g_motor_dir == MOTOR_DIR_CW) {
        PIN_PWM_BP = PWM_H_ON;
        PIN_PWM_CN = PWM_L_ON;
    } else {
        PIN_PWM_BP_DIR = PWM_H_ON;
        PIN_PWM_CN_DIR = PWM_L_ON;
    }
    //    PIN_PWM_CP = PWM_H_OFF;
    //    PIN_PWM_AN = PWM_L_OFF;
    //    PIN_PWM_BN = PWM_L_OFF;
}

/**
 * @brief		Inject a pulse from phase C to phase B.
 * @param[in]	none
 * @return		none
 */
static void motor_inject_pulse_C_B(void)
{
    //    PIN_PWM_AP = PWM_H_OFF;
    //    PIN_PWM_BP = PWM_H_OFF;

    if (g_motor_dir == MOTOR_DIR_CW) {
        PIN_PWM_CP = PWM_H_ON;
        PIN_PWM_BN = PWM_L_ON;
    } else {
        PIN_PWM_CP_DIR = PWM_H_ON;
        PIN_PWM_BN_DIR = PWM_L_ON;
    }
    //    PIN_PWM_AN = PWM_L_OFF;
    //
    //    PIN_PWM_CN = PWM_L_OFF;
}

/**
 * @brief		Inject a pulse from phase C to phase A.
 * @param[in]	none
 * @return		none
 */
static void motor_inject_pulse_C_A(void)
{
    //    PIN_PWM_AP = PWM_H_OFF;
    //    PIN_PWM_BP = PWM_H_OFF;
    if (g_motor_dir == MOTOR_DIR_CW) {
        PIN_PWM_CP = PWM_H_ON;
    } else {
        PIN_PWM_CP_DIR = PWM_H_ON;
    }

    PIN_PWM_AN = PWM_L_ON;
    //    PIN_PWM_BN = PWM_L_OFF;
    //    PIN_PWM_CN = PWM_L_OFF;
}

/**
 * @brief		Inject a pulse from phase A to phase C.
 * @param[in]	none
 * @return		none
 */
static void motor_inject_pulse_A_C(void)
{
    PIN_PWM_AP = PWM_H_ON;

    if (g_motor_dir == MOTOR_DIR_CW) {
        PIN_PWM_CN = PWM_L_ON;
    } else {
        PIN_PWM_CN_DIR = PWM_L_ON;
    }
    //    PIN_PWM_BP = PWM_H_OFF;
    //    PIN_PWM_CP = PWM_H_OFF;
    //    PIN_PWM_AN = PWM_L_OFF;
    //    PIN_PWM_BN = PWM_L_OFF;
    //    PIN_PWM_CN = PWM_L_ON;
}

/**
 * @brief		Stop to inject pulse.
 * @param[in]	none
 * @return		none
 */
static void motor_stop_inject(void)
{
    PIN_PWM_AP = PWM_H_OFF;
    PIN_PWM_BP = PWM_H_OFF;
    PIN_PWM_CP = PWM_H_OFF;
    PIN_PWM_AN = PWM_L_OFF;
    PIN_PWM_BN = PWM_L_OFF;
    PIN_PWM_CN = PWM_L_OFF;
}

/**
 * @brief	Inject pulse in low side of phase A, B and C.
 * @param[in]	none
 * @return		none
 */
static void motor_inject_pulse_ABC_L(void)
{
    PIN_PWM_AP = PWM_H_OFF;
    PIN_PWM_BP = PWM_H_OFF;
    PIN_PWM_CP = PWM_H_OFF;
    PIN_PWM_AN = PWM_L_ON;
    PIN_PWM_BN = PWM_L_ON;
    PIN_PWM_CN = PWM_L_ON;
}

/**
 * @brief		Inject a pulse from phase A to B and C.
 * @param[in]	none
 * @return		none
 */
static void motor_inject_pulse_A_BC(void)
{
    PIN_PWM_AP = PWM_H_ON;
		PIN_PWM_AN = PWM_L_OFF;
	if(g_motor_dir == MOTOR_DIR_CW){
		PIN_PWM_BP = PWM_H_OFF;
		PIN_PWM_BN = PWM_L_ON;
		PIN_PWM_CP = PWM_H_OFF;
    PIN_PWM_CN = PWM_L_ON;
	
	}
		else{
		PIN_PWM_BP_DIR = PWM_H_OFF;
		PIN_PWM_BN_DIR = PWM_L_ON;
		PIN_PWM_CP_DIR = PWM_H_OFF;	
    PIN_PWM_CN_DIR = PWM_L_ON;}
}

/**
 * @brief		Inject a pulse from phase B, c to phase A.
 * @param[in]	none
 * @return		none
 */
static void motor_inject_pulse_BC_A(void)
{
	if(g_motor_dir == MOTOR_DIR_CW){
		PIN_PWM_BP = PWM_H_ON;
		PIN_PWM_BN = PWM_L_OFF;
    PIN_PWM_CP = PWM_H_ON;
	  PIN_PWM_CN = PWM_L_OFF; 
	  }
		else{
		PIN_PWM_BP_DIR = PWM_H_ON;
		PIN_PWM_BN_DIR = PWM_L_OFF;
    PIN_PWM_CP_DIR = PWM_H_ON;
		PIN_PWM_CN_DIR = PWM_L_OFF;
		}
		PIN_PWM_AP = PWM_H_OFF;
    PIN_PWM_AN = PWM_L_ON;
		

}

/**
 * @brief		Inject a pulse from phase B to phase A and C.
 * @param[in]	none
 * @return		none
 */
static void motor_inject_pulse_B_AC(void)
{
	if(g_motor_dir == MOTOR_DIR_CW){
    PIN_PWM_BP = PWM_H_ON;
		PIN_PWM_BN = PWM_L_OFF;
    PIN_PWM_AP = PWM_H_OFF;
    PIN_PWM_AN = PWM_L_ON;
    PIN_PWM_CP = PWM_H_OFF;
    PIN_PWM_CN = PWM_L_ON;}
		else{
    PIN_PWM_BP_DIR = PWM_H_ON;
		PIN_PWM_BN_DIR = PWM_L_OFF;
		PIN_PWM_AP = PWM_H_OFF;
    PIN_PWM_AN = PWM_L_ON;
		PIN_PWM_CP_DIR = PWM_H_OFF;	
    PIN_PWM_CN_DIR = PWM_L_ON;}
}

/**
 * @brief		Inject a pulse from phase A, C to phase B.
 * @param[in]	none
 * @return		none
 */
static void motor_inject_pulse_AC_B(void)
{
	
		if(g_motor_dir == MOTOR_DIR_CW){
		PIN_PWM_AP = PWM_H_ON;
		PIN_PWM_AN = PWM_L_OFF;
    PIN_PWM_CP = PWM_H_ON;
		PIN_PWM_CN = PWM_L_OFF;
		PIN_PWM_BP = PWM_H_OFF;
    PIN_PWM_BN = PWM_L_ON;
			}
		else{
		PIN_PWM_AP = PWM_H_ON;
		PIN_PWM_AN = PWM_L_OFF;
    PIN_PWM_CP_DIR = PWM_H_ON;
		PIN_PWM_CN_DIR = PWM_L_OFF;
		PIN_PWM_BP_DIR = PWM_H_OFF;
    PIN_PWM_BN_DIR = PWM_L_ON;
			}
}

/**
 * @brief		Inject a pulse from phase C to phase A and B.
 * @param[in]	none
 * @return		none
 */
static void motor_inject_pulse_C_AB(void)
{
		if(g_motor_dir == MOTOR_DIR_CW){
    PIN_PWM_CP = PWM_H_ON;
		PIN_PWM_CN = PWM_L_OFF;
		PIN_PWM_AP = PWM_H_OFF;
    PIN_PWM_AN = PWM_L_ON;
		PIN_PWM_BP = PWM_H_OFF;
    PIN_PWM_BN = PWM_L_ON;
			}
		else{
    PIN_PWM_CP_DIR = PWM_H_ON;
		PIN_PWM_CN_DIR = PWM_L_OFF;
		PIN_PWM_AP = PWM_H_OFF;	
    PIN_PWM_AN = PWM_L_ON;
		PIN_PWM_BP_DIR = PWM_H_OFF;
    PIN_PWM_BN_DIR = PWM_L_ON;
			}
	
	
}

/**
 * @brief		Inject a pulse from phase A and B to phase C.
 * @param[in]	none
 * @return		none
 */
static void motor_inject_pulse_AB_C(void)
{
			if(g_motor_dir == MOTOR_DIR_CW){
    PIN_PWM_AP = PWM_H_ON;
		PIN_PWM_AN = PWM_L_OFF;
    PIN_PWM_BP = PWM_H_ON;
		PIN_PWM_BN = PWM_L_OFF;
		PIN_PWM_CP = PWM_H_OFF;
    PIN_PWM_CN = PWM_L_ON;
			}
		else{
    PIN_PWM_AP = PWM_H_ON;
		PIN_PWM_AN = PWM_L_OFF;
    PIN_PWM_BP_DIR = PWM_H_ON;
		PIN_PWM_BN_DIR = PWM_L_OFF;
		PIN_PWM_CP_DIR = PWM_H_OFF;
    PIN_PWM_CN_DIR = PWM_L_ON;
			}
}
