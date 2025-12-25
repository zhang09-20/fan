#include "util.h"
#include "timer.h"

#ifndef NDEBUG
void abort(void)
{
    //    while (1)
    //        ;
}
#endif

/**
 * @brief Delay function.
 *
 * @param u16X100us The time to delay.(Unit : 100us)
 */
void delay_ms(uint16_t u16X100us) /*100us*/
{
    uint8_t time0_H = 0xF6;
    uint8_t time0_L = 0xA0;
    TIMER0_TMOD_MODE_SET(TIMER01_MODE1);
    ENABLE_TIMER0;
    while (u16X100us != 0) {
        TH0 = time0_H;
        TL0 = time0_L;
        while (IS_TIME0_OVER_FLAG != 1)
            ;
        CLR_TIME0_OVER_FLAG;
        u16X100us--;
    }
    DISABLE_TIMER0;
}

/**
 * @brief		�����ӳ�
 * @param[in]	delay	��ʱʱ��
 * @return		none
 */
void delay_cnt(uint32_t cnt)
{
    while (cnt) {
        cnt--;
    }
}

/**
 * @brief		��ֵ����
 * @param[in]	*buf	��������
 * @param[in]	len		���鳤��
 * @return		��ֵ���
 */
uint16_t average_filter(volatile uint16_t *buf, uint8_t len)
{
    volatile uint8_t  i;
    volatile uint32_t sum = 0;

    if (len < 3) {
        return *buf;
    }

    for (i = 1; i < len; i++, buf++) {
        if (*buf > *(buf + 1)) {
            *buf ^= *(buf + 1);
            *(buf + 1) = *buf ^ *(buf + 1);
            *buf       = *buf ^ *(buf + 1);
        }
    }

    buf--;
    for (i = 1; i < len - 1; i++, buf--) {
        if (*buf < *(buf - 1)) {
            *buf ^= *(buf - 1);
            *(buf - 1) = *buf ^ *(buf - 1);
            *buf       = *buf ^ *(buf - 1);
        }
    }

    buf++;
    for (i = 0; i < (len - 2); i++, buf++) {
        sum += *buf;
    }

    return (uint16_t)(sum / (len - 2));
}
