#ifndef __UTIL_H__
#define __UTIL_H__
#include "acmp.h"
#include "adc.h"
#include "opa.h"
#include <assert.h>

// 注意：使用DEBUG_PRINTF宏时，需要使用两层括号
#ifdef NDEBUG
#define DEBUG_PRINTF(msg)
#else
#define DEBUG_PRINTF(msg) printf msg;
#endif

#define ELAPSED_TIME(begin, end)                                                                                       \
    (((begin) <= (end)) ? (end) - (begin) : 65536 - (begin) + (end)) /*<! begin至end已经过去的时间，单位: 100ms */

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define Join(a, b)      (a##b)
#define Join3(a, b, c)  (a##b##c)

#define GEN_PIN(a)      Join(P, a)
#define GEN_PIOCFG(a)   Join3(PIO, a, CFG)

#define VALID_ACMP0_INP_PORT(__PORT__)                                                                                 \
    assert((__PORT__) == 15 || (__PORT__) == 07 || (__PORT__) == 12 || (__PORT__) == 06)
#define ACMP0_INP_MAP(__PORT__)                                                                                        \
    ((__PORT__) == 15   ? ACMP0_INP0                                                                                   \
     : (__PORT__) == 07 ? ACMP0_INP1                                                                                   \
     : (__PORT__) == 12 ? ACMP0_INP2                                                                                   \
     : (__PORT__) == 06 ? ACMP0_INP3                                                                                   \
                        : 0xFF)
#define VALID_ACMP0_INN_PORT(__PORT__) assert((__PORT__) == 05 || (__PORT__) == 04)
#define ACMP0_INN_MAP(__PORT__)        ((__PORT__) == 05 ? ACMP0_INN0 : (__PORT__) == 04 ? ACMP0_INN1 : 0xFF)

#define VALID_ACMP1_INP_PORT(__PORT__)                                                                                 \
    assert((__PORT__) == 02 || (__PORT__) == 13 || (__PORT__) == 14 || (__PORT__) == 16)
#define ACMP1_INP_MAP(__PORT__)                                                                                        \
    ((__PORT__) == 02   ? ACMP1_INP0                                                                                   \
     : (__PORT__) == 13 ? ACMP1_INP1                                                                                   \
     : (__PORT__) == 14 ? ACMP1_INP2                                                                                   \
     : (__PORT__) == 16 ? ACMP1_INP3                                                                                   \
                        : 0xFF)
#define VALID_ACMP1_INN_PORT(__PORT__) assert((__PORT__) == 03 || (__PORT__) == 25)
#define ACMP1_INN_MAP(__PORT__)        ((__PORT__) == 03 ? ACMP1_INN0 : (__PORT__) == 25 ? ACMP1_INN1 : 0xFF)

#define OPA0_INP_MAP(__PORT__)         ((__PORT__) == 06 ? OPA_PIN0 : 0xFF)
#define OPA0_INN_MAP(__PORT__)         ((__PORT__) == 05 ? OPA_NIN0 : 0xFF)
#define OPA0_OUT_MAP(__PORT__)         ((__PORT__) == 04 ? OPA_OUT0 : 0xFF)

#define OPA1_INP_MAP(__PORT__)         ((__PORT__) == 12 ? OPA_PIN0 : 0xFF)
#define OPA1_INN_MAP(__PORT__)         ((__PORT__) == 13 ? OPA_NIN0 : 0xFF)
#define OPA1_OUT_MAP(__PORT__)         ((__PORT__) == 25 ? OPA_OUT0 : 0xFF)

#define ADC_CHANNEL_MAP(__PORT__)                                                                                      \
    ((__PORT__) == 16   ? ADC_AIN0                                                                                     \
     : (__PORT__) == 15 ? ADC_AIN1                                                                                     \
     : (__PORT__) == 07 ? ADC_AIN2                                                                                     \
     : (__PORT__) == 06 ? ADC_AIN3                                                                                     \
     : (__PORT__) == 05 ? ADC_AIN4                                                                                     \
     : (__PORT__) == 04 ? ADC_AIN5                                                                                     \
     : (__PORT__) == 03 ? ADC_AIN6                                                                                     \
     : (__PORT__) == 02 ? ADC_AIN7                                                                                     \
                        : 0xFF)

#ifndef NDEBUG
void abort(void);
#endif

void     delay_ms(uint16_t u16X100us);
void     delay_cnt(uint32_t delay);
uint16_t average_filter(volatile uint16_t *pDuty, uint8_t Len);
#endif /* __UTIL_H__ */