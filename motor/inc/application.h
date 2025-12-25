#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include "bldc.h"
#include "iap.h"
#include "pid.h"

#include "uart.h"
#include "uart_printf.h"

// ============ 自定义引脚名 ========================
#define PIN_D       P04
#define PIN_C       P25
#define PIN_E       P13
#define PIN_KEY     P14
#define PIN_BAT_CTL P12
#define PIN_ADC_NTC P02
// #define PIN_VSS
#define PIN_ADC_BAT P03
// #define PIN_VDD
#define PIN_WEBMF P07
#define PIN_VEBMF P15
#define PIN_LW    P16
#define PIN_HW    P24
#define PIN_LV    P10
#define PIN_HV    P11
#define PIN_LU    P23
#define PIN_HU    P22
// #define PIN_RST     P20
#define PIN_SWDIO P00
#define PIN_SWCLK P01
#define PIN_A     P21
#define PIN_B     P17
#define PIN_UEBMF P06
#define PIN_CMP_  P05

// ============ 自定义标志位 ========================
typedef union {
    uint8_t byte;
    struct {
        uint8_t bit0 : 1;
        uint8_t bit1 : 1;
        uint8_t bit2 : 1;
        uint8_t bit3 : 1;
        uint8_t bit4 : 1;
        uint8_t bit5 : 1;
        uint8_t bit6 : 1;
        uint8_t bit7 : 1;
    } Bits;
} byteBits_union;
extern byteBits_union Common_Flag;
#define Flag_5ms          Common_Flag.Bits.bit0 // 5ms标志位
#define key_event         Common_Flag.Bits.bit1 // 按键事件
#define Display_2s_Gear   Common_Flag.Bits.bit2
#define Display_2s_Power  Common_Flag.Bits.bit3
#define Power_off_pwmWait Common_Flag.Bits.bit4

// ============ 自定义变量 ========================
extern uint8_t Flag_5ms_counter;

// ============ 自定义函数 ========================
void        Systerm_Init(void);
void        application(void);
uint16_t    return_PotAdcData();
static void led_warrning_display(uint8_t times);

// 显示
void DG_all_Display(unsigned char EN_ALL);
// void Fan_Percent_Display();
void DG_Display(const unsigned char DG_num);
void Led_Deal(void);

// ADC
static uint16_t _get_ADCData_t(void);
float           Test_ADC_Get(void);

// Config
void        ADC_ConfigSWCVTNoInt(void);
static void _GPIO_INT_Config(void);
static void _GPIO_OutPut_Config(void);
void        UART0_Test(void);

#endif /* __APPLICATION_H__ */