/**
 * @file      i2c.h
 * @brief     IIC驱动配置
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#ifndef __I2C_H__
#define __I2C_H__

#include "WY8S9003xx.h"

/**@name 控制寄存器-I2CCON
 * @{
 */
#define I2C_I2CCON_EN_POS         (7)
#define I2C_I2CCON_EN_MSK         (0x1 << I2C_I2CCON_EN_POS)
#define I2C_I2CCON_NACK_POS       (6)
#define I2C_I2CCON_NACK_MSK       (0x1 << I2C_I2CCON_NACK_POS)
#define I2C_I2CCON_AGC_POS        (5)
#define I2C_I2CCON_AGC_MSK        (0x1 << I2C_I2CCON_AGC_POS)
#define I2C_I2CCON_FS_POS         (4)
#define I2C_I2CCON_FS_MSK         (0x1 << I2C_I2CCON_FS_POS)
#define I2C_I2CCON_STOP_POS       (2)
#define I2C_I2CCON_STOP_MSK       (0x1 << I2C_I2CCON_STOP_POS)
#define I2C_I2CCON_CMD_POS        (1)
#define I2C_I2CCON_CMD_MSK        (0x1 << I2C_I2CCON_CMD_POS)
#define I2C_I2CCON_MS_POS         (0)
#define I2C_I2CCON_MS_MSK         (0x1 << I2C_I2CCON_MS_POS)

#define ENABLE_I2C                (I2CCON |= I2C_I2CCON_EN_MSK)    /*!< 使能I2C */
#define DISABLE_I2C               (I2CCON &= ~I2C_I2CCON_EN_MSK)   /*!< 禁止I2C */

#define ENABLE_I2C_SLAVE_NACK     (I2CCON |= I2C_I2CCON_NACK_MSK)  /*!< 从机模式时，接收到数据后，产生NACK应答 */
#define DISABLE_I2C_SLAVE_NACK    (I2CCON &= ~I2C_I2CCON_NACK_MSK) /*!< 根据正常的通信情况产生ACK或者NACK应答 */

#define ENABLE_I2C_ROADCAST_NACK  (I2CCON |= I2C_I2CCON_AGC_MSK)   /*!< 从机接收到广播帧时返回ACK */
#define DISABLE_I2C_ROADCAST_NACK (I2CCON &= ~I2C_I2CCON_AGC_MSK)  /*!< 从机接收到广播帧时不返回ACK */

#define I2C_FAST_SPEED_MODE       (1)
#define I2C_NORMAL_SPEED_MODE     (0)
/**
 * 传输速率配置位
 * @param[in] status
 * -# I2C_NORMAL_SPEED_MODE:标准模式
 * -# I2C_FAST_SPEED_MODE:  快速模式
 */
#define I2C_I2CCON_FS_SET(status) (I2CCON = ((I2CCON & (~I2C_I2CCON_FS_MSK)) | ((status) << I2C_I2CCON_FS_POS)))

#define ENABLE_I2C_STOP           (I2CCON |= I2C_I2CCON_STOP_MSK)  /*!< 当前BUFFER中的数据发送完成后产生STOP信号 */
#define DISABLE_I2C_STOP          (I2CCON &= ~I2C_I2CCON_STOP_MSK) /*!< 不产生STOP信号 */

#define I2C_WRITE_MODE            (I2CCON &= ~I2C_I2CCON_CMD_MSK)  /*!< 主机I2C写模式 */
#define I2C_READ_MODE             (I2CCON |= I2C_I2CCON_CMD_MSK)   /*!< 主机I2C读模式 */

/**
 * 判断为读模式还是写模式
 */
#define IS_I2C_READ_WRITE ((I2CCON & I2C_I2CCON_CMD_MSK) >> I2C_I2CCON_CMD_POS)

#define I2C_READ          (0)
#define I2C_WRITE         (1)

#define I2C_MASTER_MODE   (1)
#define I2C_SLAVE_MODE    (0)
/**
 * 主/从模式配置
 * @param[in] status
 * -# I2C_SLAVE_MODE:从机模式
 * -# I2C_MASTER_MODE:主机模式
 */
#define I2C_I2CCON_MS_SET(status) (I2CCON = ((I2CCON & (~I2C_I2CCON_MS_MSK)) | ((status) << I2C_I2CCON_MS_POS)))
/**@} */

/**@name 状态寄存器1-I2CSTA1
 * @{
 */
#define I2C_I2CSTA1_START_POS  (7)
#define I2C_I2CSTA1_START_MSK  (0x1 << I2C_I2CSTA1_START_POS)
#define I2C_I2CSTA1_STOP_POS   (5)
#define I2C_I2CSTA1_STOP_MSK   (0x1 << I2C_I2CSTA1_STOP_POS)
#define I2C_I2CSTA1_RXDONE_POS (4)
#define I2C_I2CSTA1_RXDONE_MSK (0x1 << I2C_I2CSTA1_RXDONE_POS)
#define I2C_I2CSTA1_RD_POS     (3)
#define I2C_I2CSTA1_RD_MSK     (0x1 << I2C_I2CSTA1_RD_POS)
#define I2C_I2CSTA1_GC_POS     (2)
#define I2C_I2CSTA1_GC_MSK     (0x1 << I2C_I2CSTA1_GC_POS)
#define I2C_I2CSTA1_IDLE_POS   (1)
#define I2C_I2CSTA1_IDLE_MSK   (0x1 << I2C_I2CSTA1_IDLE_POS)
#define I2C_I2CSTA1_TXERR_POS  (0)
#define I2C_I2CSTA1_TXERR_MSK  (0x1 << I2C_I2CSTA1_TXERR_POS)
/**
 * 当I2C处于从机或者主机模式时，检测到START或者RESTART条件标志
 * @return 1:检测到START或者RESTART标志
 * @note 该位写0清除
 */
#define IS_I2C_START_FLAG  ((I2CSTA1 & I2C_I2CSTA1_START_MSK) >> I2C_I2CSTA1_START_POS)
#define CLR_I2C_START_FLAG (I2CSTA1 &= ~I2C_I2CSTA1_START_MSK)
/**
 * STOP条件检测标志
 * @return 1:从机模式或者主机模式时，表示接收到STOP信号
 * @note 该位写0清除
 */
#define IS_I2C_STOP_FLAG  ((I2CSTA1 & I2C_I2CSTA1_STOP_MSK) >> I2C_I2CSTA1_STOP_POS)
#define CLR_I2C_STOP_FLAG (I2CSTA1 &= ~I2C_I2CSTA1_STOP_MSK)
/**
 * 传输完成标志
 * @return 1:当作为从机发送数据时，若在某一个BIT传输完成后主机给出NACK响应，则表示本次传输完成，本状态位置1
 * @note 该位写0清除
 */
#define IS_I2C_RXDONE_FLAG  ((I2CSTA1 & I2C_I2CSTA1_RXDONE_MSK) >> I2C_I2CSTA1_RXDONE_POS)
#define CLR_I2C_RXDONE_FLAG (I2CSTA1 &= ~I2C_I2CSTA1_RXDONE_MSK)
/**
 * 读请求标志
 * @return 1:当I2C作为从机时，接收到主机的读请求
 * @note 该位写0清除
 */
#define IS_I2C_RD_FLAG  ((I2CSTA1 & I2C_I2CSTA1_RD_MSK) >> I2C_I2CSTA1_RD_POS)
#define CLR_I2C_RD_FLAG (I2CSTA1 &= ~I2C_I2CSTA1_RD_MSK)
/**
 * 接收到广播地址标志：当作为从机时，且配置为应答广播帧时，若接收到广播帧该位置1
 * @return 1:接收到广播地址
 * @note 该位写0清除
 */
#define IS_I2C_GC_FLAG  ((I2CSTA1 & I2C_I2CSTA1_GC_MSK) >> I2C_I2CSTA1_GC_POS)
#define CLR_I2C_GC_FLAG (I2CSTA1 &= ~I2C_I2CSTA1_GC_MSK)
/**
 * 总线忙标志
 * @return 1:I2C总线空闲 0:I2C总线正在被占用
 * @note 该标志位为只读。当I2C模块不使能时，该位读出值为0。
 */
#define IS_I2C_IDLE_FLAG ((I2CSTA1 & I2C_I2CSTA1_IDLE_MSK) >> I2C_I2CSTA1_IDLE_POS)
/**
 * 发送错误中止标志
 * @return 1:当处于发送状态时，发送被中止
 * @note 该位写0清除，该位被清除的同时，也会将I2CABRTSRC寄存器清0，并且将发送BUFFER中的数据清除
 */
#define IS_I2C_TXERR_FLAG  ((I2CSTA1 & I2C_I2CSTA1_TXERR_MSK) >> I2C_I2CSTA1_TXERR_POS)
#define CLR_I2C_TXERR_FLAG (I2CSTA1 &= ~I2C_I2CSTA1_TXERR_MSK)
/**@} */

/**@name 状态寄存器2-I2CSTA2
 * @{
 */
#define I2C_I2CSTA2_RXUNF_POS   (4)
#define I2C_I2CSTA2_RXUNF_MSK   (0x1 << I2C_I2CSTA2_RXUNF_POS)
#define I2C_I2CSTA2_RXFUL_POS   (3)
#define I2C_I2CSTA2_RXFUL_MSK   (0x1 << I2C_I2CSTA2_RXFUL_POS)
#define I2C_I2CSTA2_RXOVF_POS   (2)
#define I2C_I2CSTA2_RXOVF_MSK   (0x1 << I2C_I2CSTA2_RXOVF_POS)
#define I2C_I2CSTA2_TXEMPTY_POS (1)
#define I2C_I2CSTA2_TXEMPTY_MSK (0x1 << I2C_I2CSTA2_TXEMPTY_POS)
#define I2C_I2CSTA2_TXOVF_POS   (0)
#define I2C_I2CSTA2_TXOVF_MSK   (0x1 << I2C_I2CSTA2_TXOVF_POS)
/**
 * 接收下溢：当接收BUFFER为空时，又来一次主机读操作。
 * @return 1:发生接收下溢
 * @note 该位写0清除; 接收BUFFER深度为1
 */
#define IS_I2C_RXUNF_FLAG  ((I2CSTA2 & I2C_I2CSTA2_RXUNF_MSK) >> I2C_I2CSTA2_RXUNF_POS)
#define CLR_I2C_RXUNF_FLAG (I2CSTA2 &= ~I2C_I2CSTA2_RXUNF_MSK)
/**
 * 接收BUFFER满
 * @return 1:接收BUFFER为满
 * @note 当将BUFFER中的数据读出后，该位清除
 */
#define IS_I2C_RXFUL_FLAG ((I2CSTA2 & I2C_I2CSTA2_RXFUL_MSK) >> I2C_I2CSTA2_RXFUL_POS)
/**
 * 接收上溢
 * @return 1:发生接收上溢
 * @note 该位写0清除
 */
#define IS_I2C_RXOVF_FLAG  ((I2CSTA2 & I2C_I2CSTA2_RXOVF_MSK) >> I2C_I2CSTA2_RXOVF_POS)
#define CLR_I2C_RXOVF_FLAG (I2CSTA2 &= ~I2C_I2CSTA2_RXOVF_MSK)
/**
 * 发送BUFFER空标志
 * @return 1:发送BUFFER为空
 * @note BUFFER中写入数据后，该位清除
 */
#define IS_I2C_TXEMPTY_FLAG ((I2CSTA2 & I2C_I2CSTA2_TXEMPTY_MSK) >> I2C_I2CSTA2_TXEMPTY_POS)
/**
 * 发送上溢：发送BUFFER满且有新的数据向发送BUFFER写入
 * @return 1:发送BUFFER上溢
 * @note 软件写0清除I2CSTA2.TX_OVF中断标志
 */
#define IS_I2C_TXOVF_FLAG  ((I2CSTA2 & I2C_I2CSTA2_TXOVF_MSK) >> I2C_I2CSTA2_TXOVF_POS)
#define CLR_I2C_TXOVF_FLAG (I2CSTA2 &= ~I2C_I2CSTA2_TXOVF_MSK)
/**@} */
/**@name 速率寄存器-I2CRAT
 * @{
 */
/**
 * SCL频率配置位
 * @note CLK_CNT计算方法：CLK_CNT = (Fclk_sys/Fscl - 8)/4;
 */
#define I2C_I2CRAT_CLKCNT(u8data) (I2CRAT = (u8data))
/**@} */

/**@name 主机目标地址寄存器-I2CTADDR
 * @{
 */
#define I2C_I2CTADDR_GC_POS    (7)
#define I2C_I2CTADDR_GC_MSK    (0x1 << I2C_I2CTADDR_GC_POS)
#define I2C_I2CTADDR_TADDR_POS (0)
#define I2C_I2CTADDR_TADDR_MSK (0x7F << I2C_I2CTADDR_TADDR_POS)

#define I2C_BROADCAST_MODE     (1)
#define I2C_NORMAL_MODE        (0)
/**
 * 广播模式配置位
 * @param[in] status
 * -# I2C_NORMAL_MODE:   普通模式
 * -# I2C_BROADCAST_MODE:广播模式
 */
#define I2C_I2CTADDR_GC_SET(status)                                                                                    \
    (I2CTADDR = ((I2CTADDR & (~I2C_I2CTADDR_GC_MSK)) | ((status) << I2C_I2CTADDR_GC_POS)))
/**
 * 主机模式时的目标地址
 */
#define I2C_I2CTADDR_TADDR_SET(taddr)                                                                                  \
    (I2CTADDR = ((I2CTADDR & (~I2C_I2CTADDR_TADDR_MSK)) | ((taddr) << I2C_I2CTADDR_TADDR_POS)))
/**@} */
/**@name 从机地址寄存器-I2CSADDR
 * @{
 */
#define I2C_I2CSADDR_SADDR_POS (0)
#define I2C_I2CSADDR_SADDR_MSK (0x7F << I2C_I2CSADDR_SADDR_POS)
/**
 * 从机地址
 */
#define I2C_I2CSADDR_SADDR_SET(taddr)                                                                                  \
    (I2CSADDR = ((I2CSADDR & (~I2C_I2CSADDR_SADDR_MSK)) | ((taddr) << I2C_I2CSADDR_SADDR_POS)))
/**@} */

/**@name 异常中止寄存器-I2CABRTSRC
 * @{
 */
#define I2C_I2CABRTSRC_SLVRD_ERR_POS  (7)
#define I2C_I2CABRTSRC_SLVRD_ERR_MSK  (0x1 << I2C_I2CABRTSRC_SLVRD_ERR_POS)
#define I2C_I2CABRTSRC_SLVTR_ERR_POS  (6)
#define I2C_I2CABRTSRC_SLVTR_ERR_MSK  (0x1 << I2C_I2CABRTSRC_SLVTR_ERR_POS)
#define I2C_I2CABRTSRC_GC_ERR_POS     (5)
#define I2C_I2CABRTSRC_GC_ERR_MSK     (0x1 << I2C_I2CABRTSRC_GC_ERR_POS)
#define I2C_I2CABRTSRC_SLV_BUS_POS    (4)
#define I2C_I2CABRTSRC_SLV_BUS_MSK    (0x1 << I2C_I2CABRTSRC_SLV_BUS_POS)
#define I2C_I2CABRTSRC_MST_ARB_POS    (3)
#define I2C_I2CABRTSRC_MST_ARB_MSK    (0x1 << I2C_I2CABRTSRC_MST_ARB_POS)
#define I2C_I2CABRTSRC_NOACK_ADDR_POS (2)
#define I2C_I2CABRTSRC_NOACK_ADDR_MSK (0x1 << I2C_I2CABRTSRC_NOACK_ADDR_POS)
#define I2C_I2CABRTSRC_NOACK_DATA_POS (1)
#define I2C_I2CABRTSRC_NOACK_DATA_MSK (0x1 << I2C_I2CABRTSRC_NOACK_DATA_POS)
#define I2C_I2CABRTSRC_NOACK_GC_POS   (0)
#define I2C_I2CABRTSRC_NOACK_GC_MSK   (0x1 << I2C_I2CABRTSRC_NOACK_GC_POS)
/**
 * SLV发送功能配置错误
 * @return 1:当从机向主机发送读数据时，向控制寄存器中的CMD写1；
 * @note 当向I2CSTA1的TX_ERR位写0，则该状态位被清除
 */
#define IS_I2C_SLVRD_ERR_FLAG ((I2CABRTSRC & I2C_I2CABRTSRC_SLVRD_ERR_MSK) >> I2C_I2CABRTSRC_SLVRD_ERR_POS)
/**
 * 软件在从机模式下是否配置了主机功能
 * @return 1:软件在从机模式下配置了主机功能
 * @note 当向I2CSTA1的TX_ERR位写0，则该状态位被清除
 */
#define IS_I2C_SLVTR_ERR_FLAG ((I2CABRTSRC & I2C_I2CABRTSRC_SLVTR_ERR_MSK) >> I2C_I2CABRTSRC_SLVTR_ERR_POS)
/**
 * @return 1:主机模式下，配置了广播帧的发送，但是将控制寄存器的CMD位配置为1；
 * @note 当向I2CSTA1的TX_ERR位写0，则该状态位被清除
 */
#define IS_I2C_GC_ERR_FLAG ((I2CABRTSRC & I2C_I2CABRTSRC_GC_ERR_MSK) >> I2C_I2CABRTSRC_GC_ERR_POS)
/**
 * @return 1:从机向主机发送数据时总线被抢占
 * @note 当向I2CSTA1的TX_ERR位写0，则该状态位被清除
 */
#define IS_I2C_SLV_BUS_FLAG ((I2CABRTSRC & I2C_I2CABRTSRC_SLV_BUS_MSK) >> I2C_I2CABRTSRC_SLV_BUS_POS)
/**
 * @return 1:主机总线仲裁失败
 * @note 当向I2CSTA1的TX_ERR位写0，则该状态位被清除
 */
#define IS_I2C_MST_ARB_FLAG ((I2CABRTSRC & I2C_I2CABRTSRC_MST_ARB_MSK) >> I2C_I2CABRTSRC_MST_ARB_POS)
/**
 * @return 1:主机发送地址后，未收到应答信号
 * @note 当向I2CSTA1的TX_ERR位写0，则该状态位被清除
 */
#define IS_I2C_NOACK_ADDR_FLAG ((I2CABRTSRC & I2C_I2CABRTSRC_NOACK_ADDR_MSK) >> I2C_I2CABRTSRC_NOACK_ADDR_POS)
/**
 * @return 1:主机发送地址，收到应答后发送数据时，未收到应答信号
 * @note 当向I2CSTA1的TX_ERR位写0，则该状态位被清除
 */
#define IS_I2C_NOACK_DATA_FLAG ((I2CABRTSRC & I2C_I2CABRTSRC_NOACK_DATA_MSK) >> I2C_I2CABRTSRC_NOACK_DATA_POS)
/**
 * @return 1:主机发送广播帧后，无从机产生应答
 * @note 当向I2CSTA1的TX_ERR位写0，则该状态位被清除
 */
#define IS_I2C_NOACK_GC_FLAG ((I2CABRTSRC & I2C_I2CABRTSRC_NOACK_GC_MSK) >> I2C_I2CABRTSRC_NOACK_GC_POS)
/**@} */

/**@name I2C数据寄存器
 * @{
 */
/**
 * I2C 写入数据
 * @param[in] u8data 写入的数据
 */
#define I2C_WRITE_DATA(u8data) (I2CDAT = (u8data))
/**
 * I2C 读出数据
 * @return I2CDAT 读出的数据
 */
#define I2C_READ_DATA (I2CDAT)

/**@} */

/**@name 外部函数
 * @{
 */
void   I2C_ConfigMasterMode(uint8_t u8addr7bit, uint8_t u8gcMode, uint32_t u32cnt);
void   I2C_ConfigSlaveMode(uint8_t u8addr7bit, uint8_t u8rateMode);
void   I2C_SendStartACK(void);
int8_t I2C_MasterTRBuffer(uint8_t mode, uint8_t *buffer, uint8_t length);

/**@} */

#endif /* __I2C_H__ */
