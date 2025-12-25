/**
 * @file      motor.c
 * @brief     Motor function code
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
#include "ipd.h"
#include "pid.h"
#include "util.h"

bldc_obj_t data    g_bldc_motor;
pid_struct_t xdata g_speed_pid;
enable_signal_e    g_commuta_angle;
moter_mode_e       g_sysmode;
motor_dir_e        g_motor_dir;

void BRAKE_g_sysmode(void)
{
    // PIN_POWER = 1;
    DISABLE_ACMP_INT;
    DISABLE_TIMER3;
    PWM_GPIO_OFF;
    delay_ms(500);
    BRAKE_OFF;
    delay_ms(800);
    // motor_init_param();
    // motor_init_periph();
    // g_sysmode = INTEND;
    // PIN_POWER = 0;
}

static uint16_t _get_ADCData(void);
static void     motor_intend(void);
static void     motor_start(void);
static void     motor_run(void);
static void     motor_handle_brake(void);
static void     motor_handle_stop(void);
static void     motor_handle_fault(void);
static void     motor_forced_start(void);
static void     delay_ms(uint16_t cnt);
void            BUSCurrent_ErrorValue(void);

uint16_t code NTC3435_10K[] = {
    3581, 3559, 3535, 3511, 3486, 3461, 3435, 3408, 3381, 3353, 3324, 3295, 3266, 3234, 3203, 3171, 3138, 3105,
    3072, 3037, 3003, 2968, 2932, 2896, 2859, 2823, 2785, 2748, 2710, 2672, 2633, 2595, 2556, 2517, 2478, 2438,
    2399, 2360, 2321, 2281, 2242, 2203, 2164, 2125, 2086, 2048, 2009, 1971, 1933, 1896, 1858, 1822, 1785, 1749,
    1713, 1678, 1643, 1608, 1574, 1540, 1507, 1475, 1436, 1411, 1380, 1349, 1319, 1289, 1260, 1231, 1203, 1176,
    1149, 1122, 1096, 1070, 1045, 1021, 997,  974,  951,  928,  906,  885,  864,  843,  823,  803,  784,  766,
    747,  729,  712,  695,  678,  662,  646,  631,  616,  601,  587,  573,  559,  546,  533,  520,  508,  496,
    484,  473,  462,  451,  440,  430,  420,  410,  400,  391,  382,  373,  365,  356,  348,  340,  332,  325,
    317,  310,  303,  296,  290,  283,  277,  271,  265,  259,  253,  247,  242,  237,  231,
};

/******************************************************************************
 * function name    : motor_start                        				                 *
 * description      : Motor start-up mode            						            	 *
 * input parameter  : null                                                     *
 * description      : ----                                                     *
 * output parameter : null                                                     *
 * description      : ----                                                     *
 * Creat date       : 2024-09                                                  *
 ******************************************************************************/

/**
 *
 *
 */
static void motor_intend(void) /*准备*/
{
    //    static uint16_t PotAdcData;
    //	motor_init_param();
    //    motor_init_periph();
    g_bldc_motor.timer_30 = 0;
    //    PotAdcData            = motor_get_pot_ADCData();
    //    if (PotAdcData > 380) {
    g_sysmode = STARTMODE;
    //    }
}
/**
 * @brief Handler of start motor.
 *
 */
static void motor_start(void) /*启动，包括启动函数*/
{
    if (motor_start_sensorless() == true) {
        g_sysmode = RUNMODE;
    } else {
        g_sysmode = BRAKEMODE;
    }
}

/**
 * @brief Handler of normally run motor.
 *
 */
uint8_t     key_start = 0;
static void motor_run(void) /*正常运行，包括一些任务，计速，保护检测等*/
{
    uint16_t PotAdcData, PwmDuty, pwm_duty;
//    motor_handle_protection();
#ifdef SPEED_OPEN_LOOP /*开环*/
//     PotAdcData = 4094; // 819;//motor_get_pot_ADCData();
    // //    if (PotAdcData < 300) {
    // //        g_sysmode = STOPMODE;
    // //    }

    // =====================================================
    PotAdcData = return_PotAdcData();
    // =====================================================
//        PotAdcData = 3562;
    if (1 == g_bldc_motor.pwm_change) {

        PwmDuty = ((uint32_t)PotAdcData * MAX_DUTY) >> 12; /*占空比*/
        if (PwmDuty < NOSEN_MIN_DUTY) {
            PwmDuty = NOSEN_MIN_DUTY;
        }
        pwm_duty = (PWMD0H << 8) + PWMD0L;
        if (pwm_duty < PwmDuty) {
            delay_ms(50);
            pwm_duty += 1;
        } else if (pwm_duty > PwmDuty) {
            delay_ms(20);
            pwm_duty -= 1;
        } else if (pwm_duty == PwmDuty) {
            pwm_duty = PwmDuty;

            // ============================================
            g_bldc_motor.pwm_change = 0;
            // ============================================
        }
        if (pwm_duty < NOSEN_MIN_DUTY) {
            pwm_duty = NOSEN_MIN_DUTY;
        } else if (pwm_duty > MAX_DUTY) {
            pwm_duty = MAX_DUTY;
        }

        // g_bldc_motor.pwm_change = 0;
        Update_PwmDuty(pwm_duty);
    }

#endif
#ifdef SPEED_CLOSE_LOOP                /*闭环*/
    g_bldc_motor.desired_speed = 4000; /*速度设定*/
    motor_get_speed_sensorless();
#endif
}

/**
 * @brief Handler of brake motor.
 * @note 刹车处理函数
 */
static void motor_handle_brake(void)
{
    PIN_POWER = 1;
    DISABLE_ACMP_INT;
    DISABLE_TIMER3;
    PWM_GPIO_OFF;
    delay_ms(500);
    BRAKE_OFF;
    delay_ms(800);
    while (1) {
        if (1 == g_bldc_motor.fault_flag) {
            g_bldc_motor.fault_flag = 0;
            PIN_POWER               = 0;
        } else {
            if (1 == g_bldc_motor.led_flag) {
                g_bldc_motor.led_flag = 0;
                if (0 != g_bldc_motor.fault_led) {
                    PIN_LED = ~PIN_LED;
                    if (1 == PIN_LED) {
                        g_bldc_motor.fault_led--;
                    }
                }
            }
        }
    }
}

/**
 * @brief Handler of stop motor.
 *
 */
static void motor_handle_stop(void)
{
    PIN_POWER = 1;
    DISABLE_ACMP_INT;
    DISABLE_TIMER3;
    PWM_GPIO_OFF;
    delay_ms(500);
    BRAKE_OFF;
    delay_ms(800);
    motor_init_param();
    motor_init_periph();
    // g_sysmode = INTEND;
    PIN_POWER = 0;
}

/**
 * @brief Handler of motor fault.
 * @note /*故障，包括堵转，过流，过温，过压。进入此模式后不可恢复，只能断电后检查故障再次重启
 */
static void motor_handle_fault(void)
{
#ifdef PROTECT_OFF_PWM
    PWM_GPIO_OFF;
#endif
#ifdef PROTECT_BRAKE
    BRAKE_OFF;
#endif
}

/**
 * @brief Schedule function of motor work.
 *
 */
void motor_work(void)
{
    switch (g_sysmode) {
    case INTEND:
        motor_intend();
        break;
    case STARTMODE:
        motor_start();
        break;
    case RUNMODE:
        motor_run();
        break;
    case BRAKEMODE:
        motor_handle_brake();
        break;
    case STOPMODE:
        motor_handle_stop();
        break;
    case FAULTMODE:
        motor_handle_fault();
        break;
    default:
        g_sysmode = FAULTMODE;
        break;
    }
}

/**
 * @brief Function of init motor parameters.
 *
 */
void motor_init_param(void)
{
    g_sysmode                          = INTEND;
    g_bldc_motor.overvoltage_en        = OVER_VOLTAGE_EN;
    g_bldc_motor.undervoltage_en       = UNDER_VOLTAGE_EN;
    g_bldc_motor.overtemp_en           = OVER_TEMPER_EN;
    g_bldc_motor.start_crosszero_delay = START_CROSSZERO_DELAY;
    pid_init(&g_speed_pid);
    //		PORT_SET_MUX(PIOCFG_POWER, GPIO_MUX_MODE);
    //		GPIO_ConfigOutput(PORTn_POWER, GPIO_PP, GPIO_PULLUP, CURRENT_11);
    //    PIN_POWER = 1;
    // delay_ms(2000);
    delay_ms(200);
//    PORT_SET_MUX(PIOCFG_FWD, GPIO_MUX_MODE);
//    GPIO_ConfigInput(PORTn_FWD, GPIO_PULLUP);
#if MOTORDIR == 1
    //    if (0 == PIN_FWD) {
    g_motor_dir           = MOTOR_DIR_CW; /*顺时针*/
    g_bldc_motor.vnp_acmp = 0x40;
    g_bldc_motor.wnp_acmp = 0x44;

//    } else {
//        g_motor_dir           = MOTOR_DIR_CCW; /*逆时针*/
//        g_bldc_motor.vnp_acmp = 0x44;
//        g_bldc_motor.wnp_acmp = 0x40;
//    }
#else
    //    if (1 == PIN_FWD) {
    //        g_motor_dir           = MOTOR_DIR_CW; /*顺时针*/
    //        g_bldc_motor.vnp_acmp = 0x44;
    //        g_bldc_motor.wnp_acmp = 0x40;

    //    } else {
    g_motor_dir           = MOTOR_DIR_CCW; /*逆时针*/
    g_bldc_motor.vnp_acmp = 0x44;
    g_bldc_motor.wnp_acmp = 0x40;
//    }
#endif
}

/**
 * @brief  Function of init motor periphs.
 *
 */
void motor_init_periph(void)
{
    System_ConfigCLK(SYSCLK_HRC_48M, CLK_DIV_NOT, WAITS_48M);
    ADC_Config();
    // OPA_Config();
    PWM_Config();
    ACMP_Config();
    TIMER3_Config(); /*过零30度*/
    TIMER1_Config(); /*计时*/
    TIMER2_Config(); /*测速*/
    ENABLE_ALL_INT;
}

/**
 * @brief Forced start function of sensorless BLDC.
 *
 */
static void motor_forced_start(void)
{
    switch (g_bldc_motor.phase) {
    case 0:
        PHASE_A_H;
        PHASE_B_L;
        SENSE_C;
        SENSE_FALLING_INT;
        break;
    case 1:
        PHASE_A_H;
        PHASE_C_L;
        SENSE_B;
        SENSE_RISING_INT;
        break;
    case 2:
        PHASE_B_H;
        PHASE_C_L;
        SENSE_A;
        SENSE_FALLING_INT;
        break;
    case 3:
        PHASE_B_H;
        PHASE_A_L;
        SENSE_C;
        SENSE_RISING_INT;
        break;
    case 4:
        PHASE_C_H;
        PHASE_A_L;
        SENSE_B;
        SENSE_FALLING_INT;
        break;
    case 5:
        PHASE_C_H;
        PHASE_B_L;
        SENSE_A;
        SENSE_RISING_INT;
        break;
    default:
        break;
    }
    g_bldc_motor.emf_state &= ~(1 << g_bldc_motor.phase);
    g_bldc_motor.emf_state |= (SENSE_H << g_bldc_motor.phase);
}

/**
 * @brief Sensorless motor start function
 *
 * @return true Success to start.
 * @return false  Fail to start.
 */
bool motor_start_sensorless(void)
{
    uint16_t timer = START_DELAY, i, j = 0;
    uint8_t  pwm = STARTING_RATIO;
    DISABLE_ACMP_INT;
    g_bldc_motor.phase = 0;
    //    GPIO_OutPut_Config();
    //    BUSCurrent_ErrorValue();
    //    ipd_check();
    //    ipd_check();
    PWM_Config();
    SetPwm(pwm);
    motor_forced_start();
    SetPwm(5);
    delay_ms(180);
    SetPwm(10);
    delay_ms(140);
    //	  SetPwm(60);
    //    delay_ms(180);
    SetPwm(pwm);
    delay_ms(180);
    j = 0;
    while (1) {

        g_bldc_motor.phase++;
        g_bldc_motor.phase %= 6;
        motor_forced_start();

        //        GAT_ONCE_I_BUS;
        //        if (SHUNT_GATE_DATA_LEVEL1 < g_bldc_motor.bus_I_data) {
        //            return (false);
        //        }

        for (i = 0; i < timer; i++) {
            delay_ms(1);
        }
        timer -= timer / 15 + 1;
        j++;

        if (j > START_STEP_NUM) {
            if (0x00 == g_bldc_motor.emf_state) {
                pwm++;
                SetPwm(pwm);
                timer = START_DELAY;
            } else {
                ENABLE_ACMP_INT;
                return (true);
            }
        }

        if (50 < pwm) {
            PWM_OFF;
            return (false);
        }
        //        pwm += 3;
        //        SetPwm(pwm);
    }
}

/**
 * @brief Get the potentiometer ADC Data.
 *
 * @return uint16_t ADC Data of Potentiometer.
 */
uint16_t motor_get_pot_ADCData(void)
{
    ADC_ConfigChannel(ADC_CHANNEL_MAP(PORTn_POT_ADC), ADC_DIV_4);
    return (_get_ADCData());
}

/**
 * @brief Get the temperature ADC Data
 *
 * @return uint16_t  ADC Data of temperature.
 */
uint16_t motor_get_temp_ADCData(void)
{
    uint16_t current_temp;
    ADC_ConfigChannel(ADC_CHANNEL_MAP(PORTn_TEMP_ADC), ADC_DIV_4);
    current_temp = _get_ADCData();
    return (current_temp);
}

/**
 * @brief Convert ADC Data of temperature to Celsius.
 *
 * @param temp_adc ADC Data of temperature
 * @return int8_t temerature of Celsius
 */
int8_t motor_get_temp_by_ADCData(uint16_t temp_adc) /*温度转换ADC--摄氏度*/
{
    uint16_t i;
    int8_t   result;

    if (temp_adc >= NTC3435_10K[0]) {
        result = -20;
    }
    if (temp_adc <= NTC3435_10K[ARRAY_SIZE(NTC3435_10K) - 1]) {
        result = 120;
    }
    for (i = 0; i < ARRAY_SIZE(NTC3435_10K); i++) {
        if (temp_adc >= NTC3435_10K[i]) {
            result = (i - 20);
            break;
        }
    }
    return result;
}

/**
 * @brief Get ADC Data of bus current
 *
 * @return uint16_t ADC Data of bus current
 */
uint16_t motor_get_bus_current_ADCData(void) /*获取总电流*/
{
    ADC_ConfigChannel(ADC_INTERNAL_CH, ADC_DIV_4);
    ADC_ADCCON2_VREF_SEL(ADC_INPUT_OPA_ADCIN1);
    return (_get_ADCData());
}

uint16_t motor_get_ipd_bus_current_ADCData(void)
{
    volatile uint16_t xdata u16CVTValue = 0;

    ADC_ConfigChannel(ADC_INTERNAL_CH, ADC_DIV_4);
    ADC_ADCCON2_VREF_SEL(ADC_INPUT_OPA_ADCIN1);

    ADC_StartSWCVT();
    u16CVTValue = ADC_GetResultQueryMode();

    return u16CVTValue;
}

/**
 * @brief Get ADC data of Bus Voltage
 *
 * @return uint16_t ADC data of Bus Voltage
 */
uint16_t motor_get_bus_vol_ADCData(void) /*获取总电压*/
{
    ADC_ConfigChannel(ADC_CHANNEL_MAP(PORTn_BUS_VOL_ADC), ADC_DIV_4);
    return (_get_ADCData());
}

/**
 * @brief Get ADC data
 *
 * @return uint16_t ADC data
 */
static uint16_t _get_ADCData(void)
{
    uint16_t AdcData[16] = 0;
    uint8_t  i;
    for (i = 0; i < 16; i++) {
        ADC_StartSWCVT();
        AdcData[i] = ADC_GetResultQueryMode();
    }
    for (i = 1; i < 16; i++) {
        AdcData[0] += AdcData[i];
    }
    AdcData[0] = AdcData[0] >> 4;
    return (AdcData[0]);
}

/**
 * @brief Get speed of Sensorless motor.
 *
 */
void motor_get_speed_sensorless()
{

    uint16_t PwmUpdata;
    if (20 <= g_bldc_motor.speed_over) {

        g_bldc_motor.speed_over          = 0;
        g_bldc_motor.speed               = 3515625 / (g_bldc_motor.speed_count_average >> 11); /**/
        g_bldc_motor.speed_count_average = 0;
        PwmUpdata                        = pid_regulate(g_bldc_motor.desired_speed, g_bldc_motor.speed, &g_speed_pid);
        PwmUpdata                        = (PwmUpdata >> 3);
        Update_PwmDuty(PwmUpdata);
    }
}

/**
 * @brief Get speed of motor.
 *
 * @return uint16_t motor speed.
 */
uint16_t motor_get_speed(void)
{
    return (g_bldc_motor.speed);
}

/**
 * @brief Handler of motor protection.
 *
 */
void motor_handle_protection(void)
{
    static uint16_t Overflows_I_Level1_Num = 0, Overflows_I_Level2_Num = 0, Overflows_I_Level3_Num = 0,
                    Overflows_I_Level4_Num = 0;
    static uint16_t Overflows_Vo_Num = 0, Overflows_Vn_Num = 0, Overflows_To_Num = 0, Overflows_Tn_Num = 0;

    if (1 == g_bldc_motor.bus_I_flag) // 电流
    {
        g_bldc_motor.bus_I_flag = 0;
        GAT_ONCE_I_BUS;
#if OVER_SHUNT_LEVEL1_EN == 1
        if (g_bldc_motor.bus_I_data > SHUNT_GATE_DATA_LEVEL1) // 电流
        {
            Overflows_I_Level1_Num++;
            if (SHUNT_OTIME_LEVEL1 < Overflows_I_Level1_Num) {
                g_bldc_motor.fault_led = 1;
                g_sysmode              = BRAKEMODE;
            }
        } else {
            Overflows_I_Level1_Num = 0;
        }
#else
#endif
#if OVER_SHUNT_LEVEL2_EN == 1
        if (g_bldc_motor.bus_I_data > SHUNT_GATE_DATA_LEVEL2) // 电流
        {
            Overflows_I_Level2_Num++;
            if (SHUNT_OTIME_LEVEL2 < Overflows_I_Level2_Num) {
                g_bldc_motor.fault_led = 2;
                g_sysmode              = BRAKEMODE;
            }
        } else {
            Overflows_I_Level2_Num = 0;
        }
#else
#endif
#if OVER_SHUNT_LEVEL3_EN == 1
        if (g_bldc_motor.bus_I_data > SHUNT_GATE_DATA_LEVEL2) // 电流
        {
            Overflows_I_Level3_Num++;
            if (SHUNT_OTIME_LEVEL3 < Overflows_I_Level3_Num) {
                g_bldc_motor.fault_led = 3;
                g_sysmode              = BRAKEMODE;
            }
        } else {
            Overflows_I_Level3_Num = 0;
        }
#else
#endif
#if OVER_SHUNT_LEVEL4_EN == 1
        if (g_bldc_motor.bus_I_data > SHUNT_GATE_DATA_LEVEL4) // 电流
        {
            Overflows_I_Level4_Num++;
            if (SHUNT_OTIME_LEVEL4 < Overflows_I_Level4_Num) {
                g_bldc_motor.fault_led = 4;
                g_sysmode              = BRAKEMODE;
            }
        } else {
            Overflows_I_Level4_Num = 0;
        }
#else
#endif
    }

    if (1 == g_bldc_motor.bus_V_flag) {
        g_bldc_motor.bus_V_flag = 0;
        GAT_ONCE_U_BUS;
        GAT_ONCE_TEMP;

#if OVER_VOLTAGE_EN == 1
        if (g_bldc_motor.bus_V_data > OVER_VOLTAGE_DATA) // 过压
        {
            Overflows_Vo_Num++;
            if (OVER_VOLTAGE_TIME < Overflows_Vo_Num) {
                g_bldc_motor.fault_led = 8;
                g_sysmode              = BRAKEMODE;
            }
        } else {
            Overflows_Vo_Num = 0;
        }
#else
#endif
#if UNDER_VOLTAGE_EN == 1
        if (g_bldc_motor.bus_V_data < UNDER_VOLTAGE_DATA) // 欠压
        {
            Overflows_Vn_Num++;
            if (UNDER_VOLTAGE_TIME < Overflows_Vn_Num) {
                g_bldc_motor.fault_led = 9;
                g_sysmode              = BRAKEMODE;
            }
        } else {
            Overflows_Vn_Num = 0;
        }
#else
#endif

#if OVER_TEMPER_EN == 1
        if (g_bldc_motor.current_temp < OVER_TEMPER_DATA) // 高温
        {
            Overflows_To_Num++;
            if (OVER_TEMPER_TIME < Overflows_To_Num) {
                g_bldc_motor.fault_led = 7;
                g_sysmode              = BRAKEMODE;
            }
        } else {
            Overflows_To_Num = 0;
        }
#else
#endif
#if UNDER_TEMPER_EN == 1
        if (g_bldc_motor.current_temp > UNDER_TEMPER_DATA) // 低温
        {
            Overflows_Tn_Num++;
            if (UNDER_TEMPER_TIME < Overflows_Tn_Num) {
                g_sysmode = BRAKEMODE;
            }
        } else {
            Overflows_Tn_Num = 0;
        }
#else
#endif
    }
}

/**
 * @brief		母线电流检测
 * @param[in]	none
 * @return		none
 */
void BUSCurrent_ErrorValue(void)
{
    uint8_t xdata  i       = 0;
    uint16_t xdata buf[10] = {0};

    for (i = 0; i < 10; i++) {
        buf[i] = motor_get_ipd_bus_current_ADCData();
    }
    ipd_param.quiescent_current = average_filter(buf, (uint8_t)10);
}
