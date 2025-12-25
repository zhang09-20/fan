#include "application.h"

#define VDD_VOL (3300.0) /*!< External supply voltage is 3.3V */

// led 输出控制
#define led_io_A_in  P2DIR &= ~(1 << 1) // A in
#define led_io_B_in  P1DIR &= ~(1 << 7) // B in
#define led_io_C_in  P2DIR &= ~(1 << 5) // C in
#define led_io_D_in  P0DIR &= ~(1 << 4) // D in
#define led_io_E_in  P1DIR &= ~(1 << 3) // E in

#define led_io_A_out P2DIR |= (1 << 1)  // A out
#define led_io_B_out P1DIR |= (1 << 7)  // B out
#define led_io_C_out P2DIR |= (1 << 5)  // C out
#define led_io_D_out P0DIR |= (1 << 4)  // D out
#define led_io_E_out P1DIR |= (1 << 3)  // E out

byteBits_union DG1_display;
#define DG1_0 DG1_display.Bits.bit0
#define DG1_1 DG1_display.Bits.bit1
#define DG1_2 DG1_display.Bits.bit2
#define DG1_3 DG1_display.Bits.bit3
#define DG1_4 DG1_display.Bits.bit4
#define DG1_5 DG1_display.Bits.bit5
#define DG1_6 DG1_display.Bits.bit6

byteBits_union DG2_display;
#define DG2_0 DG2_display.Bits.bit0
#define DG2_1 DG2_display.Bits.bit1
#define DG2_2 DG2_display.Bits.bit2
#define DG2_3 DG2_display.Bits.bit3
#define DG2_4 DG2_display.Bits.bit4
#define DG2_5 DG2_display.Bits.bit5
#define DG2_6 DG2_display.Bits.bit6

byteBits_union DG3_display;
#define DG3_0 DG3_display.Bits.bit0 // 百位数
#define DG3_1 DG3_display.Bits.bit1
// #define FAN1_display  DG3_display.Bits.bit2 // 风扇
// #define FAN2_display  DG3_display.Bits.bit3
// #define Gear_display1 DG3_display.Bits.bit4 // 挡位
// #define Gear_display2 DG3_display.Bits.bit5
#define DG3_2            DG3_display.Bits.bit2
#define DG3_3            DG3_display.Bits.bit3
#define Display_Fan1     DG3_2
#define Display_Fan2     DG3_3
#define DG3_4            DG3_display.Bits.bit4
#define DG3_5            DG3_display.Bits.bit5
#define Dispaly_Percent1 DG3_4
#define Dispaly_Percent2 DG3_5

byteBits_union Common_Flag; // 不要给这个变量加宏
byteBits_union Common2_Flag;
#define Flag_GetADC_BAT  Common2_Flag.Bits.bit0
#define Flag_GetADC_NTC  Common2_Flag.Bits.bit1
#define Flag_Gear_Down   Common2_Flag.Bits.bit2
#define Flag_Gear_Change Common2_Flag.Bits.bit3

// 自用变量
uint8_t  Flag_5ms_counter        = 0;
uint16_t Power_off_counter       = 0;
uint16_t Tick_Common_Counter     = 0;
uint16_t Tick_2s_Display_Counter = 0;
uint8_t  Tick_Gear_Down          = 0;
uint8_t  led_display_step        = 0;

volatile uint16_t PotAdcData = 1023;
volatile uint16_t u16ChipBG  = 0; /* BandGap voltage saved in the chip's factory, in mV */
// uint8_t  Power_Num  = 0;
// volatile uint16_t Tick_Common_Counter = 0;

typedef enum { Gear0 = 0, Gear1, Gear2, Gear3, Gear4, Gear5 } Gear_t;
typedef enum { OFF_STATUS = 0, NORMAL, BAT_DOWN, BAT_LOW, NTC_LOW, NTC_HIGH } Device_Status_t;
Gear_t          current_Gear  = Gear0;
Gear_t          last_Gear     = Gear0;
Device_Status_t DEVICE_STATUS = OFF_STATUS;

// ================== ADC配置 =================================
// volatile uint16_t u16CVTData = 0;
// volatile uint16_t ADC_Result    = 0;

/**
 * @brief Get ADC data
 *
 * @return uint16_t ADC data
 */
static uint16_t _get_ADCData_t(void)
{
    uint8_t i, h;

    uint16_t adsum, admin, admax, adresult = 0, ad_temp = 0;

    for (h = 0; h < 2; h++) {
        adsum = 0;
        admin = 0;
        admax = 0;

        for (i = 0; i < 10; i++) {
            ADC_StartSWCVT();
            ad_temp = ADC_GetResultQueryMode();
            if (i == 0) {
                admax = ad_temp;
                admin = ad_temp;
            } else {
                if (ad_temp > admax)
                    admax = ad_temp;
                else if (ad_temp < admin)
                    admin = ad_temp;
            }
            adsum += ad_temp;
        }
        adsum -= admax;
        if (adsum >= admin)
            adsum -= admin;
        else
            adsum = 0;
        adresult += (adsum >> 3); // 8次平均值加到临时变量上
    }
    adresult >>= 1;
    return adresult;
}
float Test_ADC_Get(void)
{
    return 0;
}
static void led_warrning_display(uint8_t times)
{
    unsigned char i, j;

    for (i = 0; i < times; i++) {
        DG_all_Display(1);
        for (j = 0; j < 30; j++) {
            delay_ms(10);
        }
        DG_all_Display(0);
        for (j = 0; j < 30; j++) {
            delay_ms(10);
        }
    }

    for (i = 0; j < 40; j++) {
        delay_ms(10);
    }
}
// ============================================================

volatile uint8_t  Power_Percent   = 0;
volatile uint8_t  ntc_low_counter = 0, ntc_high_counter = 0;
volatile uint16_t u16ADC_BG = 0;
#define VDD_VOL_MY ((uint32_t)4095 * u16ChipBG / u16ADC_BG)

void application(void)
{
    uint16_t xdata i;

    uint16_t U16ADC_BAT = 0; /* BandGap voltage collected by ADC */
    uint16_t U16ADC_NTC = 0; /* BandGap voltage collected by ADC */

    float fvol_bat = 0.0;    /* Analog voltage value collected by ADC */
    float fvol_ntc = 0.0;    /* Analog voltage value collected by ADC */

    if (DEVICE_STATUS == OFF_STATUS) {
        return;
    }

    // 按键事件处理
    if (key_event == 1) {
        delay_ms(10);
        key_event = 0;

        current_Gear++;

        if (current_Gear > Gear5) {
            current_Gear   = Gear1;
            Flag_Gear_Down = 1;
        } else {
            last_Gear = current_Gear;
        }

        // led数字显示
        DG_Display(current_Gear * 20);
        Display_Fan1 = 1;
        Display_Fan2 = 1;

        Display_2s_Gear         = 1;
        Tick_2s_Display_Counter = 0;

        PotAdcData = (uint32_t)(35 + current_Gear * 13) * 4094 / 100;

        g_bldc_motor.pwm_change = 1;
    }
    // // 挡位回落
    // if (last_Gear == Gear5 && Flag_Gear_Down == 1) {
    //     Tick_Gear_Down++;
    //     if (Tick_Gear_Down >= 60) {
    //         PotAdcData     = (uint32_t)(35 + current_Gear * 13) * 4094 / 100;
    //         Tick_Gear_Down = 0;
    //         Flag_Gear_Down = 0;
    //         last_Gear      = current_Gear;
    //     } else if (Tick_Gear_Down >= 45) {
    //         PotAdcData = (uint32_t)(35 + (current_Gear + 1) * 13) * 4094 / 100;
    //     } else if (Tick_Gear_Down >= 30) {
    //         PotAdcData = (uint32_t)(35 + (current_Gear + 2) * 13) * 4094 / 100;
    //     } else if (Tick_Gear_Down >= 15) {
    //         PotAdcData = (uint32_t)(35 + (current_Gear + 3) * 13) * 4094 / 100;
    //     }
    //     g_bldc_motor.pwm_change = 1;
    // } else {
    //     Flag_Gear_Down = 0;
    //     Tick_Gear_Down = 0;
    // }

    if (Power_off_pwmWait == 1 && Power_off_counter >= 160) {
        BRAKE_g_sysmode();
        DG_all_Display(0);

        PIN_BAT_CTL = 0;
        delay_ms(100);
    }
    if (PIN_KEY == 0) {
        if (++Power_off_counter >= 200) {
            Power_off_counter = 0;

            PotAdcData              = 0;
            g_bldc_motor.pwm_change = 1;
            // DG_all_Display(0);
            // DEVICE_STATUS = OFF_STATUS;

            // PotAdcData              = 0;
            // g_bldc_motor.pwm_change = 1;

            Power_off_pwmWait = 1;
        }
    } else {
        Power_off_counter = 0;
    }

    // ====== 通用辅助定时 =======
    Tick_Common_Counter++;

    // 采集内隙电压实际值
    ADC_ConfigChannel(ADC_INTERNAL_CH, ADC_DIV_4);
    ADC_ADCCON2_VREF_SEL(ADC_INPUT_BAND_GAP);
    /* For BandGap voltage collection, after enabling ADC, wait for more than 100us */
    for (i = 1600; i > 0; i--) {
    };
    u16ADC_BG = _get_ADCData_t();

    // adc NTC温度
    if ((Tick_Common_Counter % 10) == 0) {
        // Flag_GetADC_NTC = 1;
        // Flag_GetADC_BAT = 0;

        ADC_ConfigChannel(ADC_AIN6, ADC_DIV_4);
        /* For BandGap voltage collection, after enabling ADC, wait for more than 100us */
        for (i = 1600; i > 0; i--) {
        };
        U16ADC_NTC = _get_ADCData_t();

        fvol_ntc = (float)U16ADC_NTC * u16ChipBG / u16ADC_BG;
        if (fvol_ntc <= ((uint32_t)VDD_VOL_MY * 22 / (22 + 20))) {
            ntc_high_counter++;
            ntc_low_counter = 0;
        } else if (fvol_ntc >= ((uint32_t)VDD_VOL_MY * 1151 / (1151 + 20))) {
            ntc_low_counter++;
            ntc_high_counter = 0;
        } else {
            ntc_high_counter = 0;
            ntc_low_counter  = 0;
        }

        if (ntc_low_counter >= 10) {
            DEVICE_STATUS = NTC_LOW;
        } else if (ntc_high_counter >= 10) {
            DEVICE_STATUS = NTC_HIGH;
        }
    }

    // adc 电池电压采集
    if ((Tick_Common_Counter % 20) == 0) {

        ADC_ConfigChannel(ADC_AIN6, ADC_DIV_4);
        /* For BandGap voltage collection, after enabling ADC, wait for more than 100us */
        for (i = 1600; i > 0; i--) {
        };

        U16ADC_BAT = _get_ADCData_t();

        fvol_bat = (float)U16ADC_BAT * u16ChipBG / u16ADC_BG;
        if (fvol_bat <= 1952) {
            Power_Percent = 0;
        } else if (fvol_bat >= 2581) {
            Power_Percent = 100;
        } else {
            Power_Percent = (uint32_t)(fvol_bat - 1952) * 100 / (2581 - 1952); // 4.1v === 3.1v
        }

        // 状态判断
        if (Power_Percent <= 0) {
            DEVICE_STATUS = BAT_DOWN;
        } else if (Power_Percent <= 10) {
            DEVICE_STATUS = BAT_LOW;
        }
    }

    if (Tick_Common_Counter >= 40) {
        Tick_Common_Counter = 0;
    }
    // ================

    // 挡位-电量-挡位 2s显示切换
    if ((Display_2s_Gear == 1 || Display_2s_Power == 1) && Power_off_pwmWait == 0) {
        if (++Tick_2s_Display_Counter >= 400) {
            Tick_2s_Display_Counter = 0;

            if (Display_2s_Gear == 1) {
                Display_2s_Gear  = 0;
                Display_2s_Power = 1;

                DG_Display(Power_Percent);
                Dispaly_Percent1 = 1;
                Dispaly_Percent2 = 1;

            } else if (Display_2s_Power == 1) {
                Display_2s_Power = 0;

                DG_Display(current_Gear * 20);
                Display_Fan1 = 1;
                Display_Fan2 = 1;
            }
        }
    } else {
        Tick_2s_Display_Counter = 0;
    }
}

/**
 * @brief Systerm_Init.
 * @note  This function is used to Systerm_Init
 *
 *  系统初始化函数
 *
 */
void Systerm_Init(void)
{
    _GPIO_OutPut_Config();
    _GPIO_INT_Config();

    ADC_ConfigSWCVTNoInt();
    // UART0_Test();

    u16ChipBG = IAP_GetChipBandGap(); /* Get the BandGap voltage saved in the chip's factory */

    DG1_display.byte  = 0;
    DG2_display.byte  = 0;
    DG3_display.byte  = 0;
    Common_Flag.byte  = 0;
    Common2_Flag.byte = 0;

    Flag_5ms_counter = 0;
    DEVICE_STATUS    = NORMAL;

    PotAdcData = 0;

    g_bldc_motor.pwm_change = 1;

    DG_all_Display(1);
    // g_sysmode = STOPMODE;
    // BRAKE_g_sysmode();
}

/**
 * ADC software conversion configuration
 */
void ADC_ConfigSWCVTNoInt(void)
{
    ADC_ConfigChannel(ADC_AIN6, ADC_DIV_4);
    // ADC_ConfigChannel(ADC_AIN7, ADC_DIV_4);
    ADC_ConfigSWCVT();
    ENABLE_ADC;
}

/**
 * GPIO interrupt mode configuration
 */
static void _GPIO_INT_Config(void)
{
    PORT_SET_MUX(PIO14CFG, GPIO_MUX_MODE);
    GPIO1_ConfigInput(GPIO_PIN_4, GPIO_PULLUP);   /* P14 is input pull-up */
    GPIO1_ConfigINT(GPIO_PIN_4, GPIO_INT_RISING); /* P14 is configured as rising edge trigger */

    ENABLE_ALL_INT;
    ENABLE_GPIO_INT;
}

/**
 * GPIO output configuration
 */
static void _GPIO_OutPut_Config(void)
{
    // BAT-CTL 电池锁定输出
    PORT_SET_MUX(PIO12CFG, GPIO_MUX_MODE); // E out
    GPIO1_ConfigOutput(GPIO_PIN_2, GPIO_PP, GPIO_NOPULL, CURRENT_11);
    PIN_BAT_CTL = 1;

    // led-control A、B、C、D、E
    PORT_SET_MUX(PIO04CFG, GPIO_MUX_MODE); // D out
    GPIO0_ConfigOutput(GPIO_PIN_4, GPIO_PP, GPIO_NOPULL, CURRENT_11);
    PIN_D = 0;

    PORT_SET_MUX(PIO13CFG, GPIO_MUX_MODE); // E out
    GPIO1_ConfigOutput(GPIO_PIN_3, GPIO_PP, GPIO_NOPULL, CURRENT_11);
    PIN_E = 0;

    PORT_SET_MUX(PIO17CFG, GPIO_MUX_MODE); // B out
    GPIO1_ConfigOutput(GPIO_PIN_7, GPIO_PP, GPIO_NOPULL, CURRENT_11);
    PIN_B = 0;

    PORT_SET_MUX(PIO21CFG, GPIO_MUX_MODE); // A out
    GPIO2_ConfigOutput(GPIO_PIN_1, GPIO_PP, GPIO_NOPULL, CURRENT_11);
    PIN_A = 0;

    PORT_SET_MUX(PIO25CFG, GPIO_MUX_MODE); // C out
    GPIO2_ConfigOutput(GPIO_PIN_5, GPIO_PP, GPIO_NOPULL, CURRENT_11);
    PIN_C = 0;
}

/**
 * @brief IRQ Handler of GPIO.
 * @note  This function is used to deal key_event
 *
 *  按键中断
 *
 */
void _PORT1_IRQHandler(void) interrupt GPIO_VECTOR
{
    // clear the GPIO interrupt flag.
    if (PIO1IF4 == 1) {
        PIO1IF4 = 0;

        key_event = 1;
    }

    PIO0IF = 0; /*清中断*/
    PIO1IF = 0;
}

// void Fan_Percent_Display()
// {
//     asm("clrwdt");
//     // 风扇指示灯，状态切换
//     if (fan_flag == 1) {
//         DG3_2 = 1;
//         DG3_3 = 1;
//         // DG_Display(current_gear * 20);
//     } else if (fan_flag == 0) {
//         DG3_2 = 0;
//         DG3_3 = 0;
//     }

//     // 百分比指示灯，状态切换
//     if (power_percent_flag == 1) {
//         DG3_4 = 1;
//         DG3_5 = 1;
//         // DG_Display(current_power_ad_led);
//     } else if (power_percent_flag == 0) {
//         DG3_4 = 0;
//         DG3_5 = 0;
//     }
// }

uint16_t return_PotAdcData()
{
    return PotAdcData;
}

void DG_all_Display(unsigned char EN_ALL)
{
    if (EN_ALL == 1) {
        DG1_display.byte = 0xff;
        DG2_display.byte = 0xff;
        DG3_display.byte = 0xff;
    } else if (EN_ALL == 0) {
        DG1_display.byte = 0;
        DG2_display.byte = 0;
        DG3_display.byte = 0;
    }
}

void DG_Display(const unsigned char DG_num)
{
    unsigned char DG_num0 = DG_num / 100;        // 取百位
    unsigned char DG_num1 = (DG_num % 100) / 10; // 取十位
    unsigned char DG_num2 = DG_num % 10;         // 取个位

    if (DG_num0 == 1) {
        DG_num1 = 0; // 十位
        DG_num2 = 0; // 个位
    }

    DG_all_Display(0);

    switch (DG_num0) {
    case 0:
        DG3_0 = 0;
        DG3_1 = 0;
        break;
    case 1:
        DG3_0 = 1;
        DG3_1 = 1;
        break;
    default:
        break;
    }

    switch (DG_num1) {
    case 0:
        DG1_0 = 1;
        DG1_1 = 1;
        DG1_2 = 1;
        DG1_4 = 1;
        DG1_5 = 1;
        DG1_3 = 1;
        break;
    case 1:
        DG1_2 = 1;
        DG1_1 = 1;
        break;
    case 2:
        DG1_1 = 1;
        DG1_0 = 1;
        DG1_3 = 1;
        DG1_4 = 1;
        DG1_6 = 1;
        break;
    case 3:
        DG1_1 = 1;
        DG1_0 = 1;
        DG1_3 = 1;
        DG1_2 = 1;
        DG1_6 = 1;
        break;
    case 4:
        DG1_1 = 1;
        DG1_2 = 1;
        DG1_6 = 1;
        DG1_5 = 1;
        break;
    case 5:
        DG1_0 = 1;
        DG1_2 = 1;
        DG1_3 = 1;
        DG1_5 = 1;
        DG1_6 = 1;
        break;
    case 6:
        DG1_0 = 1;
        DG1_2 = 1;
        DG1_3 = 1;
        DG1_4 = 1;
        DG1_5 = 1;
        DG1_6 = 1;
        break;
    case 7:
        DG1_1 = 1;
        DG1_2 = 1;
        DG1_0 = 1;
        break;
    case 8:
        DG1_0 = 1;
        DG1_1 = 1;
        DG1_2 = 1;
        DG1_3 = 1;
        DG1_4 = 1;
        DG1_5 = 1;
        DG1_6 = 1;
        break;
    case 9:
        DG1_0 = 1;
        DG1_1 = 1;
        DG1_2 = 1;
        DG1_3 = 1;
        DG1_5 = 1;
        DG1_6 = 1;
        break;
    default:
        break;
    }

    switch (DG_num2) {
    case 0:
        DG2_0 = 1;
        DG2_1 = 1;
        DG2_2 = 1;
        DG2_4 = 1;
        DG2_5 = 1;
        DG2_3 = 1;
        break;
    case 1:
        DG2_2 = 1;
        DG2_1 = 1;
        break;
    case 2:
        DG2_1 = 1;
        DG2_0 = 1;
        DG2_3 = 1;
        DG2_4 = 1;
        DG2_6 = 1;
        break;
    case 3:
        DG2_1 = 1;
        DG2_2 = 1;
        DG2_3 = 1;
        DG2_0 = 1;
        DG2_6 = 1;
        break;
    case 4:
        DG2_1 = 1;
        DG2_2 = 1;
        DG2_6 = 1;
        DG2_5 = 1;
        break;
    case 5:
        DG2_0 = 1;
        DG2_2 = 1;
        DG2_3 = 1;
        DG2_5 = 1;
        DG2_6 = 1;
        break;
    case 6:
        DG2_0 = 1;
        DG2_2 = 1;
        DG2_3 = 1;
        DG2_4 = 1;
        DG2_5 = 1;
        DG2_6 = 1;
        break;
    case 7:
        DG2_1 = 1;
        DG2_2 = 1;
        DG2_0 = 1;
        break;
    case 8:
        DG2_0 = 1;
        DG2_1 = 1;
        DG2_2 = 1;
        DG2_3 = 1;
        DG2_4 = 1;
        DG2_5 = 1;
        DG2_6 = 1;
        break;
    case 9:
        DG2_0 = 1;
        DG2_1 = 1;
        DG2_2 = 1;
        DG2_3 = 1;
        DG2_5 = 1;
        DG2_6 = 1;
        break;
    default:
        break;
    }
}

void Led_Deal(void)
{
    led_io_A_in;
    led_io_B_in;
    led_io_C_in;
    led_io_D_in;
    led_io_E_in;

    PIN_A = 0;
    PIN_B = 0;
    PIN_C = 0;
    PIN_D = 0;
    PIN_E = 0;

    if (led_display_step == 0) {
        if (DG1_0 == 1) {
            led_io_B_out;
            PIN_B = 0;
        }
        if (DG1_1 == 1) {
            led_io_D_out;
//            PIN_D = 0;
        }
        if (DG1_2 == 1) {
            led_io_E_out;
            PIN_E = 0;
        }
        if (DG1_5 == 1) {
            led_io_C_out;
            PIN_C = 0;
        }
        led_io_A_out;
        PIN_A = 1;
    } else if (led_display_step == 1) {
        if (DG2_0 == 1) {
            led_io_C_out;
            PIN_C = 0;
        }
        if (DG2_3 == 1) {
            led_io_E_out;
            PIN_E = 0;
        }
        if (DG2_4 == 1) {
            led_io_A_out;
            PIN_A = 0;
        }
        if (DG2_5 == 1) {
            led_io_D_out;
            PIN_D = 0;
        }
        led_io_B_out;
        PIN_B = 1;
    } else if (led_display_step == 2) {
        if (DG3_0 == 1) {
            led_io_D_out;
            PIN_D = 0;
        }
        if (DG1_4 == 1) {
            led_io_A_out;
            PIN_A = 0;
        }
        if (DG2_1 == 1) {
            led_io_B_out;
            PIN_B = 0;
        }
        if (DG3_2 == 1) {
            led_io_E_out;
            PIN_E = 0;
        }
        led_io_C_out;
        PIN_C = 1;
    } else if (led_display_step == 3) {
        if (DG3_1 == 1) {
            led_io_C_out;
            PIN_C = 0;
        }
        if (DG1_6 == 1) {
            led_io_A_out;
            PIN_A = 0;
        }
        if (DG2_6 == 1) {
            led_io_B_out;
            PIN_B = 0;
        }
        if (DG3_5 == 1) {
            led_io_E_out;
            PIN_E = 0;
        }
        led_io_D_out;
        PIN_D = 1;
    } else if (led_display_step == 4) {
        if (DG1_3 == 1) {
            led_io_A_out;
            PIN_A = 0;
        }
        if (DG2_2 == 1) {
            led_io_B_out;
            PIN_B = 0;
        }
        if (DG3_3 == 1) {
            led_io_C_out;
            PIN_C = 0;
        }
        if (DG3_4 == 1) {
            led_io_D_out;
            PIN_D = 0;
        }
        led_io_E_out;
        PIN_E = 1;
    }

    led_display_step++;
    if (led_display_step >= 5) {
        led_display_step = 0;
    }
}