/**
 * @file      wdt.h
 * @brief     WDT驱动配置
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#ifndef __WDT_H__
#define __WDT_H__

#include "WY8S9003xx.h"

/**@name WDT控制寄存器-WDTCON(TA保护)
 * @{
 */
#define WDT_WDTCON_WDTEN_POS  (7)
#define WDT_WDTCON_WDTEN_MSK  (0x1 << WDT_WDTCON_WDTEN_POS)
#define WDT_WDTCON_WDTCLR_POS (6)
#define WDT_WDTCON_WDTCLR_MSK (0x1 << WDT_WDTCON_WDTCLR_POS)
#define WDT_WDTCON_WDTF_POS   (5)
#define WDT_WDTCON_WDTF_MSK   (0x1 << WDT_WDTCON_WDTF_POS)
#define WDT_WDTCON_WDTPS_POS  (0)
#define WDT_WDTCON_WDTPS_MSK  (0xF << WDT_WDTCON_WDTPS_POS)

#define ENABLE_WDT            1 /*!< 使能WDT */
#define DISABLE_WDT           0 /*!< 禁止WDT */
/**
 * WDT 运行使能位
 * @param[in] status
 * -# DISABLE_WDT:WDT 运行禁止
 * -# ENABLE_WDT:WDT 运行使能
 * @note 受TA保护
 */
#define WDT_WDTCON_WDTEN_SET(status)                                                                                   \
    (WDTCON = ((WDTCON & (~WDT_WDTCON_WDTEN_MSK)) | ((status) << WDT_WDTCON_WDTEN_POS)))

/**
 * WDT 超时标志位
 * @return 1:WDT定时器溢出\n
 *         0: WDT定时器未溢出
 */
#define IS_WDT_TF_FLAG ((WDTCON & WDT_WDTCON_WDTF_MSK) >> WDT_WDTCON_WDTF_POS)

#define WDT_DIV_2      (0x00)
#define WDT_DIV_4      (0x01)
#define WDT_DIV_8      (0x02)
#define WDT_DIV_16     (0x03)
#define WDT_DIV_32     (0x04)
#define WDT_DIV_64     (0x05)
#define WDT_DIV_128    (0x06)
#define WDT_DIV_256    (0x07)
#define WDT_DIV_512    (0x08)
#define WDT_DIV_1024   (0x0F)
/**
 * WDT 时钟预分频选择位
 * @param[in] div
 * -# WDT_DIV_2     WDT计数时钟为CLK_LRC的2分频
 * -# WDT_DIV_4     WDT计数时钟为CLK_LRC的4分频
 * -# WDT_DIV_8     WDT计数时钟为CLK_LRC的8分频
 * -# WDT_DIV_16    WDT计数时钟为CLK_LRC的16分频
 * -# WDT_DIV_32    WDT计数时钟为CLK_LRC的32分频
 * -# WDT_DIV_64    WDT计数时钟为CLK_LRC的64分频
 * -# WDT_DIV_128   WDT计数时钟为CLK_LRC的128分频
 * -# WDT_DIV_256   WDT计数时钟为CLK_LRC的256分频
 * -# WDT_DIV_512   WDT计数时钟为CLK_LRC的512分频
 * -# WDT_DIV_1024  WDT计数时钟为CLK_LRC的1024分频
 * @note 受TA保护
 */
#define WDT_WDTCON_PSDIV_SET(div) (WDTCON = ((WDTCON & (~WDT_WDTCON_WDTPS_MSK)) | ((div) << WDT_WDTCON_WDTPS_POS)))
/**@} */

/**@name WDT模式寄存器-WDTMOD（TA保护）
 * @{
 */
#define WDT_WDTMOD_WDTRST_POS (7)
#define WDT_WDTMOD_WDTRST_MSK (0x1 << WDT_WDTMOD_WDTRST_POS)
#define WDT_WDTMOD_WDTMOD_POS (5)
#define WDT_WDTMOD_WDTMOD_MSK (0x3 << WDT_WDTMOD_WDTMOD_POS)

#define ENABLE_OVER_RST       (1)
#define DISABLE_OVER_RST      (0)

/**
 * WDT溢出复位控制
 * @param[in] status
 * -# DISABLE_OVER_RST:溢出后禁止复位
 * -# ENABLE_OVER_RST: 溢出后复位使能
 * @note 受TA保护
 */
#define WDT_WDTMOD_WDTRST_SET(status)                                                                                  \
    (WDTMOD = ((WDTMOD & (~WDT_WDTMOD_WDTRST_MSK)) | ((status) << WDT_WDTMOD_WDTRST_POS)))

#define WDT_IDLE_SLEEP_MODE 0x00
#define WDT_IDLE_MODE       0x01
#define WDT_NONE_MODE       0x03
/**
 * WDT工作模式配置
 * @param[in] mode
 * -# WDT_IDLE_SLEEP_MODE    WDT在Idle模式和Sleep模式下均运行
 * -# WDT_IDLE_MODE          WDT在Idle模式下运行，在Sleep模式下停止运行
 * -# WDT_NONE_MODE          WDT在Idle模式和Sleep模式下均停止运行
 * @note 受TA保护
 */
#define WDT_WDTMOD_WDTMOD_SET(mode) (WDTMOD = ((WDTMOD & (~WDT_WDTMOD_WDTMOD_MSK)) | ((mode) << WDT_WDTMOD_WDTMOD_POS)))
/**@} */

/**@name 外部函数
 * @{
 */
void WDT_ConfigMode(uint8_t u8div, uint8_t u8overRstFlag, uint8_t u8Mode);
void WDT_Run(uint8_t u8WDTFlag);
void WDT_ClearWDT(void);
void WDT_ClearTF(void);
/**@} */

#endif /* __WDT_H__ */
