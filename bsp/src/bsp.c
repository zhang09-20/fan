/**
 * @file      bsp.c
 * @brief     BSP drive function
 * @author    Way-On MCU Application Team
 * @date      2024-09
 * @version   V1.0.0
 * @copyright WAYON
 */
/******************************************************************************
 Head file include
******************************************************************************/
#include "bsp.h"
#include "acmp.h"
#include "adc.h"
#include "bldc.h"
#include "bsp_config.h"
#include "common.h"
#include "gpio.h"
#include "opa.h"
#include "pwm.h"
#include "timer.h"
#include "util.h"

#define PWM_DIV_DATA (0) /*!< PWM分频值，实际PWM分频值为:PWM_DIV_DATA + 1 */
static void _PWM_PORT_Config(void);
static void _PWM_OutWave_Config(void);

/**
 * @brief Config ACMP
 *
 */
void ACMP_Config(void)
{

    VALID_ACMP0_INP_PORT(PORTn_ACMP_INP_U);
    VALID_ACMP0_INN_PORT(PORTn_ACMP_INN);
		if(g_motor_dir == MOTOR_DIR_CW)
		{
			VALID_ACMP0_INP_PORT(PORTn_ACMP_INP_V);
			VALID_ACMP0_INP_PORT(PORTn_ACMP_INP_W);
			/* 设置ACMP正端输入 */
			ACMP_ACMP0CON0_COPS_SEL(ACMP0_INP_MAP(PORTn_ACMP_INP_W));
		}
		else
		{
			VALID_ACMP0_INP_PORT(PORTn_ACMP_INP_V_DIR);
			VALID_ACMP0_INP_PORT(PORTn_ACMP_INP_W_DIR);
			/* 设置ACMP正端输入 */
			ACMP_ACMP0CON0_COPS_SEL(ACMP0_INP_MAP(PORTn_ACMP_INP_W_DIR));
		}

    /* 设置ACMP负端输入 */
    ACMP_ACMP0CON0_CONS_SEL(ACMP0_INN_MAP(PORTn_ACMP_INN));

    /* 设置ACMP输出相位 */
    ACMP0_POLARITY_NORMAL; // Z

    /* 设置ACMP输出滤波 */
    ACMP0_FILT_SEL(ACMP_FILT);
    ENABLE_ACMP0_FILT;
    TIMER3_PRIORITY_H;
    ACMP_PRIORITY_H;
    ACMP0_FB_SEL(ACMP0_BOTH_INC_EDGEFB);

    /* 设置ACMP IO */
    PORT_SET_MUX(PIOCFG_ACMP_INP_U, ANALOG_MUX_MODE);
    PORT_SET_MUX(PIOCFG_ACMP_INN, ANALOG_MUX_MODE);
		if(g_motor_dir == MOTOR_DIR_CW)
		{
		PORT_SET_MUX(PIOCFG_ACMP_INP_V, ANALOG_MUX_MODE);
    PORT_SET_MUX(PIOCFG_ACMP_INP_W, ANALOG_MUX_MODE);
		}
		else
		{
		PORT_SET_MUX(PIOCFG_ACMP_INP_V_DIR, ANALOG_MUX_MODE);
    PORT_SET_MUX(PIOCFG_ACMP_INP_W_DIR, ANALOG_MUX_MODE);
		}
	
		/* 开启ACMP */
    ENABLE_ACMP0;
		
		PORT_SET_MUX(PIOCFG_POWER, GPIO_MUX_MODE);
		GPIO_ConfigOutput(PORTn_POWER, GPIO_PP, GPIO_PULLUP, CURRENT_11);
    PIN_POWER = 1;

//    PORT_SET_MUX(PIOCFG_LED, GPIO_MUX_MODE);
//    GPIO_ConfigOutput(PORTn_LED, GPIO_PP, GPIO_PULLUP, CURRENT_11);
//    PIN_LED = 1;
}

/**
 * @brief ADC Config
 *
 */
void ADC_Config(void)
{
    ADC_ConfigChannel(ADC_CHANNEL_MAP(PORTn_POT_ADC), ADC_DIV_4);
    ADC_ConfigSWCVT(); /* 配置软件启动 */
    ENABLE_ADC;        /* 使能ADC */
}


/**
 * @brief OPA Config
 *
 */
void OPA_Config(void)
{
    /* 设置OPA的运行模式 */
    OPA1_SET_RUN_Mode(OPA_MODE_OPA);
    /* OPA通道配置 */
    OPA_ConfigChannel(OPA_INP1, OPA_INN1, OPA_OUT1);
    /* 开启OPA */
    OPA1_ENABLE;
}

/**
 * @brief PWM configuration
 *
 */
void PWM_Config(void)
{
    _PWM_PORT_Config();                           /* 配置PWM端口 */
    PWM_PWMCON_PWMMODE_SET(PWM_IMDEPENDENT_MODE); /* PWM配置为独立模式 */
    PWM0_CNT_MODE_SET(AUTOLOAD_MODE);             /* PWM通道0为自动加载模式*/
    PWM1_CNT_MODE_SET(AUTOLOAD_MODE);             /* PWM通道1为自动加载模式(产生中断)*/
    PWM2_CNT_MODE_SET(AUTOLOAD_MODE);             /* PWM通道2为自动加载模式 */
    PWM4_CNT_MODE_SET(AUTOLOAD_MODE);             /* PWM通道4为自动加载模式 */
    _PWM_OutWave_Config();                        /* 输出波形参数配置*/
    PWM_PWMMASKD_0_SET(OUTPUT_HIGH);
    PWM_PWMMASKD_2_SET(OUTPUT_HIGH);
    PWM_PWMMASKD_4_SET(OUTPUT_HIGH);

//    ENABLE_PWM0_INV_OUTPUT;
//    ENABLE_PWM1_INV_OUTPUT;
//    ENABLE_PWM2_INV_OUTPUT;
//    ENABLE_PWM4_INV_OUTPUT;
	
    ENABLE_PWM0_MASK;
    ENABLE_PWM2_MASK;
    ENABLE_PWM4_MASK;
    ENABLE_PWM0_CNT;
    ENABLE_PWM1_CNT;
    ENABLE_PWM2_CNT;
    ENABLE_PWM4_CNT;
    //	PWM_PRIORITY_H;
    //	PWM_PWMINTC_INTTY_SET(PWM_RISING_MODE);
    //	PWM_PWMINTC_INTSEL_SET(PWM_1);
    //	ENABLE_PWM_INT;
    LOAD_PWM;
    ENABLE_PWM;
}

/**
 * @brief PWM PORT Config
 *
 */
static void _PWM_PORT_Config(void)
{
    if (g_motor_dir == MOTOR_DIR_CW) {
        PORT_SET_MUX(PIOCFG_PWM_AP, PWM0_MUX_MODE);
        PORT_SET_MUX(PIOCFG_PWM_AN, GPIO_MUX_MODE);
        PORT_SET_MUX(PIOCFG_PWM_BP, PWM2_MUX_MODE);
        PORT_SET_MUX(PIOCFG_PWM_BN, GPIO_MUX_MODE);
        PORT_SET_MUX(PIOCFG_PWM_CP, PWM4_MUX_MODE);
        PORT_SET_MUX(PIOCFG_PWM_CN, GPIO_MUX_MODE);

        GPIO_SetDriveCap(PORTn_PWM_AP, CURRENT_11);
        GPIO_SetDriveCap(PORTn_PWM_BP, CURRENT_11);
        GPIO_SetDriveCap(PORTn_PWM_CP, CURRENT_11);

        PIN_PWM_AN = 0;
        PIN_PWM_BN = 0;
        PIN_PWM_CN = 0;

        GPIO_ConfigOutput(PORTn_PWM_AN, GPIO_PP, GPIO_PULLUP, CURRENT_11);
        GPIO_ConfigOutput(PORTn_PWM_BN, GPIO_PP, GPIO_PULLUP, CURRENT_11);
        GPIO_ConfigOutput(PORTn_PWM_CN, GPIO_PP, GPIO_PULLUP, CURRENT_11);
    } else {
        PORT_SET_MUX(PIOCFG_PWM_AP, PWM0_MUX_MODE);
        PORT_SET_MUX(PIOCFG_PWM_AN, GPIO_MUX_MODE);
        PORT_SET_MUX(PIOCFG_PWM_BP_DIR, PWM2_MUX_MODE);
        PORT_SET_MUX(PIOCFG_PWM_BN_DIR, GPIO_MUX_MODE);
        PORT_SET_MUX(PIOCFG_PWM_CP_DIR, PWM4_MUX_MODE);
        PORT_SET_MUX(PIOCFG_PWM_CN_DIR, GPIO_MUX_MODE);

        GPIO_SetDriveCap(PORTn_PWM_AP, CURRENT_11);
        GPIO_SetDriveCap(PORTn_PWM_BP_DIR, CURRENT_11);
        GPIO_SetDriveCap(PORTn_PWM_CP_DIR, CURRENT_11);

        PIN_PWM_AN     = 0;
        PIN_PWM_BN_DIR = 0;
        PIN_PWM_CN_DIR = 0;

        GPIO_ConfigOutput(PORTn_PWM_AN, GPIO_PP, GPIO_PULLUP, CURRENT_11);
        GPIO_ConfigOutput(PORTn_PWM_BN_DIR, GPIO_PP, GPIO_PULLUP, CURRENT_11);
        GPIO_ConfigOutput(PORTn_PWM_CN_DIR, GPIO_PP, GPIO_PULLUP, CURRENT_11);
    }
}

/**
 * @brief Config of PWM OUTPUT
 * @note 边沿对齐方式: 高电平时间= PWMDn * Tpwm                   周期 = （PWMP+1） * Tpwm      \n
 *       中心对齐方式: 高电平时间= (PWMP * 2 - PWMD x2 +1）* Tpwm 周期 = （PWMP*2+1） * Tpwm    \n
 *       占空比 = 高电平时间/周期
 *
 */
static void _PWM_OutWave_Config(void)
{
    uint16_t u16Period;
    uint16_t u16Cmp;
    PWM_PWMPSC_DATA(PWM_DIV_DATA);       /* PWM时钟为系统时钟的1分频 */
    PWM_CNTTYPE_SET(PWM_Mid_ALIGN_MODE); /* 边沿对齐方式 */
    u16Period = MAX_DUTY;
    PWM_PWMPHL_DATA((u16Period >> 8) & 0xFF, u16Period & 0xFF);
    u16Cmp = 0;                                                              /* 占空比0% */
    PWM_PWMD0HL_DATA((u16Cmp >> 8) & 0xFF, u16Cmp & 0xFF);
    PWM_PWMD1HL_DATA(((MAX_DUTY >> 1) >> 8) & 0xFF, (MAX_DUTY >> 1) & 0xFF); /*50%占空比*/
    PWM_PWMD2HL_DATA((u16Cmp >> 8) & 0xFF, u16Cmp & 0xFF);
    PWM_PWMD4HL_DATA((u16Cmp >> 8) & 0xFF, u16Cmp & 0xFF);
}

void SetPwm(uint8_t tmp_pwm)
{
    uint16_t duty;
    if (tmp_pwm > 100) {
        DISABLE_PWM;
        LOAD_PWM;
    } else {
        duty = (uint32_t)tmp_pwm * MAX_DUTY / 100;
        Update_PwmDuty(duty);
    }
}

void Update_PwmDuty(uint16_t duty_pwm)
{
    PWM_PWMD0HL_DATA((duty_pwm >> 8) & 0xFF, duty_pwm & 0xFF);
    PWM_PWMD1HL_DATA(((duty_pwm >> 1) >> 8) & 0xFF, (duty_pwm >> 1) & 0xFF);
    PWM_PWMD2HL_DATA((duty_pwm >> 8) & 0xFF, duty_pwm & 0xFF);
    PWM_PWMD4HL_DATA((duty_pwm >> 8) & 0xFF, duty_pwm & 0xFF);
    LOAD_PWM;
}

/**
 * @brief Timer1 Config
 *
 */
void TIMER1_Config(void)
{
    TH1 = 0xA2;
    TL1 = 0x40;
    TIMER1_TMOD_CNT1_SET(TIMER01_ICLK);
    TIMER1_TMOD_MODE_SET(TIMER01_MODE1);
    TIMER1_TMOD_GATE1_SET(TIMER01_TR_GATE);

    ENABLE_TIMER1;

    ENABLE_TIME1_INT; /* 使能TIMER1中断 */
}

/**
 * @brief Timer2 Config
 *
 */
void TIMER2_Config(void)
{
    ENABLE_TIMER2_RELOAD;
    TIMER2_T2MOD_T2DIV_SET(TIMER2_T2DIV_4DIV);
    TIMER2_T2MOD_LDTS_SET(TIMER2_LDTS_OVER);
    TIMER2_RCMP_DATA_REG(0, 1);
    ENABLE_TIMER2;
    ENABLE_TIME2_INT; /* TIMER2启动中断 */
}

/**
 * @brief Timer3 Config
 *
 */
void TIMER3_Config(void)
{
    TIMER3_T3CON_DIV_SET(TIMER3_DIV_4); /* TIMER3分频选择 */
    ENABLE_TIME3_INT;                   /* TIMER3启动中断 */
}

/**
 * @brief		GPIO输出配置
 * @param[in]	none
 * @return		none
 */
void GPIO_OutPut_Config(void)
{
    /* PWM1H配置 */
    PORT_SET_MUX(PIOCFG_PWM_AP, GPIO_MUX_MODE);
    GPIO_ConfigOutput(PORTn_PWM_AP, GPIO_PP, GPIO_PULLUP, CURRENT_11);
    PIN_PWM_AP = PWM_H_OFF;

    /* PWM2H配置 */
    PORT_SET_MUX(PIOCFG_PWM_BP, GPIO_MUX_MODE);
    GPIO_ConfigOutput(PORTn_PWM_BP, GPIO_PP, GPIO_PULLUP, CURRENT_11);
    PIN_PWM_BP = PWM_H_OFF;

    /* PWM3H配置 */
    PORT_SET_MUX(PIOCFG_PWM_CP, GPIO_MUX_MODE);
    GPIO_ConfigOutput(PORTn_PWM_CP, GPIO_PP, GPIO_PULLUP, CURRENT_11);
    PIN_PWM_CP = PWM_H_OFF;

    /* PWM1L配置 */
    PORT_SET_MUX(PIOCFG_PWM_AN, GPIO_MUX_MODE);
    GPIO_ConfigOutput(PORTn_PWM_AN, GPIO_PP, GPIO_PULLUP, CURRENT_11);
    PIN_PWM_AN = PWM_L_OFF;

    /* PWM2L配置 */
    PORT_SET_MUX(PIOCFG_PWM_BN, GPIO_MUX_MODE);
    GPIO_ConfigOutput(PORTn_PWM_BN, GPIO_PP, GPIO_PULLUP, CURRENT_11);
    PIN_PWM_BN = PWM_L_OFF;

    /* PWM3L配置 */
    PORT_SET_MUX(PIOCFG_PWM_CN, GPIO_MUX_MODE);
    GPIO_ConfigOutput(PORTn_PWM_CN, GPIO_PP, GPIO_PULLUP, CURRENT_11);
    PIN_PWM_CN = PWM_L_OFF;
}
